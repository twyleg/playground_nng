// Copyright (C) 2023 twyleg
#include <utils/time.h>

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



int main(int argc, char *argv[]) {
	std::cout << "Started pubsub_time_publisher\n\r";


	auto pub = nng::pub::open();
	pub.listen(address.c_str());

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
