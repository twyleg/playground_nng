// Copyright (C) 2023 twyleg
#include <nngpp/nngpp.h>
#include <nngpp/protocol/sub0.h>
#include <nngpp/platform/platform.h>

#include <string>
#include <chrono>
#include <thread>
#include <iostream>


const std::string address = "ipc:///tmp/pubsub_time_asyncio.ipc";


int main(int argc, char *argv[]) {
	std::cout << "Started pubsub_time_subscriber\n\r";


	auto sub = nng::sub::open();
	sub.dial(address.c_str());

	while(true) {
		std::cout << "Waiting for message...";
		std::cout.flush();

		auto msg = nng::make_msg(0);
		msg = sub.recv_msg();
		std::cout << " Message received!" << std::endl;

		const nng::view msg_view = msg.body().get();
		std::cout << std::basic_string_view(msg_view.data<char>(), msg_view.size()) << std::endl;

	}

	return 0;
}
