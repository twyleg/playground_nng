// Copyright (C) 2023 twyleg
#include <utils/time.h>

#include <nngpp/nngpp.h>
#include <nngpp/protocol/pub0.h>
#include <nngpp/platform/platform.h>

#include <rapidjson/rapidjson.h>
#include <rapidjson/writer.h>

#include <string>
#include <chrono>
#include <thread>
#include <mutex>
#include <iostream>
#include <iomanip>
#include <vector>


using namespace std::string_literals;


const std::string address = "ipc:///tmp/pubsub_multiple_topics.ipc";


class MultiPub0: public nng::socket {

public:

	static MultiPub0 open() {
		nng::socket sock = nng::pub::open();
		return MultiPub0(std::move(sock));
	}

	MultiPub0( nng::socket&& rhs ) noexcept : nng::socket(std::forward<nng::socket>(rhs)) {}
	MultiPub0() = delete;

	size_t send_with_topic(const std::string& topic, const std::string_view& data) const {
		static const auto seperator = ": "s;

		std::size_t n = 0;
		std::vector<char> msgData(topic.size() + seperator.size() + data.size());
		n += topic.copy(msgData.data(), topic.size());
		n += seperator.copy(msgData.data() + n, seperator.size());
		n += data.copy(msgData.data() + n, data.size());

		nng::socket::send(nng::view(msgData.data(), msgData.size()));
		return n;
	}

};


void publishTime(MultiPub0& pub, std::mutex& pubMutex) {

	int i = 0;
	while(true) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		const auto timeString = getJsonTimeString();
		auto msg = nng::make_msg(timeString.size());

		auto lockGuard = std::lock_guard<std::mutex>(pubMutex);
		std::cout << i++ << ": Publishing time " << timeString << std::endl;
		pub.send_with_topic("time", timeString);

	}

}


void publishDate(MultiPub0& pub, std::mutex& pubMutex) {

	int i = 0;
	while(true) {
		std::this_thread::sleep_for(std::chrono::milliseconds(5000));
		const auto dateString = getJsonDateString();
		auto msg = nng::make_msg(dateString.size());

		auto lockGuard = std::lock_guard<std::mutex>(pubMutex);
		std::cout << i++ << ": Publishing date " << dateString << std::endl;
		pub.send_with_topic("date", dateString);
	}
}


int main(int argc, char *argv[]) {
	std::cout << "Started pubsub_time_publisher\n\r";

	auto pub = MultiPub0::open();
	pub.listen(address.c_str());

	std::mutex pubMutex;


	std::thread publishTimeThread(publishTime, std::ref(pub), std::ref(pubMutex));
	std::thread publishDateThread(publishDate, std::ref(pub), std::ref(pubMutex));

	publishTimeThread.join();
	publishDateThread.join();

	return 0;
}
