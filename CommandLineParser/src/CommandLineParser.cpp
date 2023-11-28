#include "CommandLineParser.h"

CommandLineParser::CommandLineParser(const int argc, const char* argv[]) {
	for (int i = 1; i < argc; i += 2) {
		m_arguments[argv[i]] = argv[i + 1];
	}
}

bool CommandLineParser::getValueOr(const std::string& key, bool defaultValue) {
	if (auto search = m_arguments.find(key); search != m_arguments.end()) {
		return std::stoi(search->second);
	}
	return defaultValue;
}

int32_t CommandLineParser::getValueOr(const std::string& key, int32_t defaultValue) {
	if (auto search = m_arguments.find(key); search != m_arguments.end()) {
		return std::stoi(search->second);
	}
	return defaultValue;
}

uint32_t CommandLineParser::getValueOr(const std::string& key, uint32_t defaultValue) {
	if (auto search = m_arguments.find(key); search != m_arguments.end()) {
		return std::stoi(search->second);
	}
	return defaultValue;
}

std::string CommandLineParser::getValueOr(const std::string& key, const std::string defaultValue) {
	if (auto search = m_arguments.find(key); search != m_arguments.end()) {
		return search->second;
	}
	return defaultValue;
}

float CommandLineParser::getValueOr(const std::string& key, float defaultValue) {
	if (auto search = m_arguments.find(key); search != m_arguments.end()) {
		return std::stof(search->second);
	}
	return defaultValue;
}
