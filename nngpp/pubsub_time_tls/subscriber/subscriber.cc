// Copyright (C) 2023 twyleg
#include <nngpp/nngpp.h>
#include <nngpp/protocol/sub0.h>
#include <nngpp/platform/platform.h>
#include <nngpp/transport/tls.h>
#include <nngpp/transport/tcp.h>

#include <string>
#include <chrono>
#include <thread>
#include <iostream>


const std::string address = "tls+tcp://localhost:5556";


int main(int argc, char *argv[]) {
	std::cout << "Started pubsub_time_subscriber\n\r";

	auto sub = nng::sub::open();
	nng::dialer dialer(sub, address.c_str());

	nng::sub::set_opt_subscribe(sub, nng::view("", 0));

	nng::tls::config cfg( nng::tls::mode::client );
	cfg.config_ca_file("ca.crt");
	cfg.config_auth_mode(nng::tls::auth_mode::none);
	set_opt_config(dialer, cfg );

	dialer.start();

	int i = 0;
	while(true) {
		auto msg = nng::make_msg(0);
		msg = sub.recv_msg();

		const nng::view msg_view = msg.body().get();
		std::cout << i++ << " Message: " << std::basic_string_view(msg_view.data<char>(), msg_view.size()) << std::endl;
	}

	return 0;
}
