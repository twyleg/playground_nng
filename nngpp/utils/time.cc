// Copyright (C) 2023 twyleg
#include <rapidjson/rapidjson.h>
#include <rapidjson/writer.h>

#include <string>
#include <chrono>
#include <thread>
#include <iostream>
#include <iomanip>


std::string getJsonTimeDateString() {

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
