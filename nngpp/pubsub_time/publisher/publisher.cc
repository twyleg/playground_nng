// Copyright (C) 2023 twyleg
#include <nngpp/nngpp.h>
#include <nngpp/protocol/pub0.h>
#include <nngpp/platform/platform.h>

#include <rapidjson/rapidjson.h>
#include <rapidjson/writer.h>

#include <string>
#include <chrono>
#include <thread>
#include <iostream>
#include <iomanip>


const std::string address = "ipc:///tmp/pubsub_time.ipc";


std::string getJsonTimeString() {

	rapidjson::StringBuffer sb;
	rapidjson::Writer<rapidjson::StringBuffer> writer(sb);

	const std::chrono::time_point<std::chrono::system_clock> now =
			std::chrono::system_clock::now();

	const std::time_t t_c = std::chrono::system_clock::to_time_t(now);

	std::stringstream timeStringStream;
	timeStringStream << std::put_time(std::localtime(&t_c), "%T");

	std::stringstream dateStringStream;
	dateStringStream << std::put_time(std::localtime(&t_c), "%F");

	writer.StartObject();
	writer.String("time");
	writer.String(timeStringStream.str().c_str());

	writer.String("date");
	writer.String(dateStringStream.str().c_str());
	writer.EndObject();

	return std::string(sb.GetString(), sb.GetLength());
}


int main(int argc, char *argv[]) {
	std::cout << "Started pubsub_time_publisher\n\r";


	auto pub = nng::pub::open();
	pub.listen(address.c_str());

	int i = 0;
	while(true) {

		const auto timeString = getJsonTimeString();

		auto msg = nng::make_msg(timeString.size());

		std::cout << i++ << ": Publishing time_date " << timeString << std::endl;
		pub.send(nng::view(timeString.c_str(), timeString.size()));
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}

	return 0;
}
