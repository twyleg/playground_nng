// Copyright (C) 2023 twyleg
#include <rapidjson/rapidjson.h>
#include <rapidjson/writer.h>

#include <string>
#include <chrono>
#include <thread>
#include <iostream>
#include <iomanip>


std::string getTimeString() {

	rapidjson::StringBuffer sb;
	rapidjson::Writer<rapidjson::StringBuffer> writer(sb);

	const std::chrono::time_point<std::chrono::system_clock> now =
			std::chrono::system_clock::now();

	const std::time_t t_c = std::chrono::system_clock::to_time_t(now);

	std::stringstream timeStringStream;
	timeStringStream << std::put_time(std::localtime(&t_c), "%T");

	return timeStringStream.str();
}

std::string getDateString() {

	rapidjson::StringBuffer sb;
	rapidjson::Writer<rapidjson::StringBuffer> writer(sb);

	const std::chrono::time_point<std::chrono::system_clock> now =
			std::chrono::system_clock::now();

	const std::time_t t_c = std::chrono::system_clock::to_time_t(now);

	std::stringstream dateStringStream;
	dateStringStream << std::put_time(std::localtime(&t_c), "%F");

	return dateStringStream.str();
}



std::string getJsonTimeDateString() {

	rapidjson::StringBuffer sb;
	rapidjson::Writer<rapidjson::StringBuffer> writer(sb);

	const auto timeString = getTimeString();
	const auto dateString = getDateString();

	writer.StartObject();
	writer.String("time");
	writer.String(timeString.c_str());

	writer.String("date");
	writer.String(dateString.c_str());
	writer.EndObject();

	return std::string(sb.GetString(), sb.GetLength());
}


std::string getJsonTimeString() {

	rapidjson::StringBuffer sb;
	rapidjson::Writer<rapidjson::StringBuffer> writer(sb);

	const auto timeString = getTimeString();

	writer.StartObject();
	writer.String("time");
	writer.String(timeString.c_str());
	writer.EndObject();

	return std::string(sb.GetString(), sb.GetLength());
}


std::string getJsonDateString() {

	rapidjson::StringBuffer sb;
	rapidjson::Writer<rapidjson::StringBuffer> writer(sb);

	const auto dateString = getDateString();

	writer.StartObject();
	writer.String("date");
	writer.String(dateString.c_str());
	writer.EndObject();

	return std::string(sb.GetString(), sb.GetLength());
}
