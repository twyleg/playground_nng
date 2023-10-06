// Copyright (C) 2023 twyleg
#include <utils/time.h>

#include <time.pb.h>

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


const std::string address = "ipc:///tmp/reqrep_time_date_protobuf.ipc";


int main(int argc, char *argv[]) {
	std::cout << "Started reqrep_time_responder\n\r";


	auto res = nng::rep::open();
	res.listen(address.c_str());

	int i = 0;
	while(true) {

		auto msg = res.recv_msg();
		const nng::view msgView = msg.body().get();

		playground::nng::time::Request request;
		request.ParseFromArray(msgView.data<char>(), msgView.size());

		std::cout << "Received request: \"" << request.request_type() << "\"" << std::endl;

		switch (request.request_type()) {
		case playground::nng::time::Request::RequestType::Request_RequestType_REQUEST_TYPE_TIME: {
			playground::nng::time::Time time;
			time.set_time(getTimeString());

			const auto serializedObject = time.SerializeAsString();
			res.send(nng::view(serializedObject.c_str(), serializedObject.size()));
			std::cout << "Responded with time: " << time.DebugString() << std::endl;
			break;
		}
		case playground::nng::time::Request::RequestType::Request_RequestType_REQUEST_TYPE_DATE: {
			playground::nng::time::Date date;
			date.set_date(getDateString());

			const auto serializedObject = date.SerializeAsString();
			res.send(nng::view(serializedObject.c_str(), serializedObject.size()));
			std::cout << "Responded with date: " << date.DebugString() << std::endl;
			break;
		}
		}
	}

	return 0;
}
