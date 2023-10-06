// Copyright (C) 2023 twyleg
#include <time.pb.h>

#include <nngpp/nngpp.h>
#include <nngpp/protocol/req0.h>
#include <nngpp/platform/platform.h>

#include <string>
#include <chrono>
#include <thread>
#include <iostream>
#include <iomanip>


using namespace std::literals::chrono_literals;
using namespace std::literals::string_literals;


const std::string address = "ipc:///tmp/reqrep_time_date_protobuf.ipc";


void request(playground::nng::time::Request::RequestType requestType, std::chrono::milliseconds delay) {

	auto req = nng::req::open();
	req.dial(address.c_str());

	while(true) {
		std::cout << "Requesting " << requestType << std::endl;

		playground::nng::time::Request request;
		request.set_request_type(requestType);

		const auto serializedObject = request.SerializeAsString();

		req.send(nng::view(serializedObject.data(), serializedObject.size()));

		auto msg = req.recv_msg();
		const nng::view msgView = msg.body().get();

		switch(requestType) {
		case playground::nng::time::Request::REQUEST_TYPE_TIME: {

			playground::nng::time::Time time;
			time.ParseFromArray(msgView.data(), msgView.size());
			std::cout << "Received time:" << time.DebugString() << std::endl;
			break;
		}
		case playground::nng::time::Request::REQUEST_TYPE_DATE: {

			playground::nng::time::Date date;
			date.ParseFromArray(msgView.data(), msgView.size());
			std::cout << "Received date:" << date.DebugString() << std::endl;
			break;
		}
		}

		std::this_thread::sleep_for(delay);
	}

}


int main(int argc, char *argv[]) {
	std::cout << "Started reqrep_time_request\n\r";
	std::thread requestTimeThread(request, playground::nng::time::Request::REQUEST_TYPE_TIME, 1000ms);
	std::thread requestDateThread(request, playground::nng::time::Request::REQUEST_TYPE_DATE, 5000ms);

	requestTimeThread.join();
	requestDateThread.join();

	return 0;
}
