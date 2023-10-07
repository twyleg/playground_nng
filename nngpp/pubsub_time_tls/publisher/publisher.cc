// Copyright (C) 2023 twyleg
#include <utils/time.h>

#include <nngpp/nngpp.h>
#include <nngpp/protocol/pub0.h>
#include <nngpp/platform/platform.h>
#include <nngpp/transport/tls.h>
#include <nngpp/transport/tcp.h>

#include <rapidjson/rapidjson.h>
#include <rapidjson/writer.h>

#include <string>
#include <chrono>
#include <thread>
#include <iostream>
#include <iomanip>


const std::string address = "tls+tcp://localhost:5556";


int main(int argc, char *argv[]) {
	std::cout << "Started pubsub_time_tls_publisher\n\r";

	auto pub = nng::pub::open();
	nng::listener listener(pub, address.c_str());

	nng::tls::config cfg( nng::tls::mode::server );
	cfg.config_cert_key_file("key_pair_file.pem");
	nng::tls::set_opt_config(listener, cfg);

	listener.start();

	int i = 0;
	while(true) {

		const auto timeDateString = getJsonTimeDateString();

		auto msg = nng::make_msg(timeDateString.size());

		std::cout << i++ << ": Publishing time_date " << timeDateString << std::endl;
		pub.send(nng::view(timeDateString.c_str(), timeDateString.size()));
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}

	return 0;
}
