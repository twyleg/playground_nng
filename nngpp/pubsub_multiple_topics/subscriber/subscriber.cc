// Copyright (C) 2023 twyleg
#include <nngpp/nngpp.h>
#include <nngpp/protocol/sub0.h>
#include <nngpp/platform/platform.h>

#include <string>
#include <chrono>
#include <thread>
#include <iostream>
#include <set>


const std::string address = "ipc:///tmp/pubsub_multiple_topics.ipc";


class MultiSub0: public nng::socket {

public:

	struct msg_with_topic {
		std::string topic;
		std::string_view data;
	};

	static MultiSub0 open() {
		nng::socket sock = nng::sub::open();
		return MultiSub0(std::move(sock));
	}

	MultiSub0( nng::socket&& rhs ) noexcept : nng::socket(std::forward<nng::socket>(rhs)) {}
	MultiSub0() = delete;

	void subscribe(const std::string& topic) {
		nng::sub::set_opt_subscribe(*this, nng::view(topic.data(), topic.size()));
		mTopics.emplace(topic);
	}

	msg_with_topic recv_msg_with_topic() {
		static const std::string seperator = ": ";
		auto msg = recv_msg();
		auto msgDataStringView = std::string_view(static_cast<char*>(msg.body().data()), msg.body().size());

		for(const auto topic: mTopics) {
			if(msgDataStringView.find(topic) == 0){
				return {
					topic,
					std::string_view(msgDataStringView.data() + topic.size() + seperator.size(), msgDataStringView.size() - (topic.size() + seperator.size()))
				};
			}
		}
		throw std::runtime_error("Unreachable");
	}

private:

	std::set<std::string> mTopics;

};




int main(int argc, char *argv[]) {
	std::cout << "Started pubsub_multiple_topics_subscriber\n\r";


	auto sub = MultiSub0::open();
//	sub.subscribe("time");
//	sub.subscribe("date");
	sub.subscribe("");
	sub.dial(address.c_str());

	int i = 0;
	while(true) {
		auto msg_with_topic = sub.recv_msg_with_topic();
		std::cout << i++ << " Received topic='" << msg_with_topic.topic << "', data='" << msg_with_topic.data << "'" << std::endl;
	}

	return 0;
}
