// Copyright (C) 2023 twyleg
#include <nngpp/nngpp.h>
#include <nngpp/protocol/rep0.h>
#include <nngpp/platform/platform.h>

#include <rapidjson/rapidjson.h>
#include <rapidjson/writer.h>

#include <string>
#include <chrono>
#include <thread>
#include <iostream>
#include <iomanip>


const std::string address = "ipc:///tmp/reqrep_time_date.ipc";


std::string getJsonTimeString() {

	rapidjson::StringBuffer sb;
	rapidjson::Writer<rapidjson::StringBuffer> writer(sb);

	const std::chrono::time_point<std::chrono::system_clock> now =
			std::chrono::system_clock::now();

	const std::time_t t_c = std::chrono::system_clock::to_time_t(now);

	std::stringstream timeStringStream;
	timeStringStream << std::put_time(std::localtime(&t_c), "%T");

	writer.StartObject();
	writer.String("time");
	writer.String(timeStringStream.str().c_str());
	writer.EndObject();

	return std::string(sb.GetString(), sb.GetLength());
}


std::string getJsonDateString() {

	rapidjson::StringBuffer sb;
	rapidjson::Writer<rapidjson::StringBuffer> writer(sb);

	const std::chrono::time_point<std::chrono::system_clock> now =
			std::chrono::system_clock::now();

	const std::time_t t_c = std::chrono::system_clock::to_time_t(now);

	std::stringstream dateStringStream;
	dateStringStream << std::put_time(std::localtime(&t_c), "%F");

	writer.StartObject();
	writer.String("date");
	writer.String(dateStringStream.str().c_str());
	writer.EndObject();

	return std::string(sb.GetString(), sb.GetLength());
}


int main(int argc, char *argv[]) {
	std::cout << "Started reqrep_time_responder\n\r";


	auto res = nng::rep::open();
	res.listen(address.c_str());

	int i = 0;
	while(true) {

		auto msg = res.recv_msg();

		const nng::view msg_view = msg.body().get();
		const auto request = std::basic_string_view(msg_view.data<char>(), msg_view.size());

		std::cout << "Received request: \"" << request << "\"" << std::endl;

		if(request == "time") {
			const auto time = getJsonTimeString();
			res.send(nng::view(time.data(), time.size()));
			std::cout << "Responded with time: " << time << std::endl;

		} else if(request == "date") {
			const auto date = getJsonDateString();
			res.send(nng::view(date.data(), date.size()));
			std::cout << "Responded with date: " << date << std::endl;
		}
	}

	return 0;
}
