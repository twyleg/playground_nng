// Copyright (C) 2023 twyleg
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


const std::string address = "ipc:///tmp/reqrep_time_date.ipc";


void request(const std::string& requestName, std::chrono::milliseconds delay) {

	auto req = nng::req::open();
	req.dial(address.c_str());

	while(true) {
		std::cout << "Requesting " << requestName << std::endl;

		req.send(nng::view(requestName.data(), requestName.size()));

		auto msg = req.recv_msg();
		const nng::view msg_view = msg.body().get();
		const auto response = std::basic_string_view(msg_view.data<char>(), msg_view.size());
		std::cout << "Received " << requestName << ": " << response << std::endl;

		std::this_thread::sleep_for(delay);
	}

}


int main(int argc, char *argv[]) {
	std::cout << "Started reqrep_time_request\n\r";

	std::thread requestTimeThread(request, "time", 1000ms);
	std::thread requestDateThread(request, "date", 5000ms);

	requestTimeThread.join();
	requestDateThread.join();

	return 0;
}
