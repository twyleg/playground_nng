// Copyright (C) 2023 twyleg
#include <nngpp/nngpp.h>
#include <nngpp/protocol/sub0.h>
#include <nngpp/platform/platform.h>

#include <string>
#include <chrono>
#include <thread>
#include <iostream>


const std::string address = "ipc:///tmp/pubsub_time.ipc";


int main(int argc, char *argv[]) {
	std::cout << "Started pubsub_time_subscriber\n\r";


	auto sub = nng::sub::open();
	nng::sub::set_opt_subscribe(sub, nng::view("", 0));
	sub.dial(address.c_str());

	int i = 0;
	while(true) {
		auto msg = nng::make_msg(0);
		msg = sub.recv_msg();

		const nng::view msg_view = msg.body().get();
		std::cout << i++ << " Message: " << std::basic_string_view(msg_view.data<char>(), msg_view.size()) << std::endl;
	}

	return 0;
}
