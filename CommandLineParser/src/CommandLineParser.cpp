#include "CommandLineParser.h"

CommandLineParser::CommandLineParser(const int argc, const char* argv[]) {
	for (int i = 1; i < argc; i += 2) {
		if (i + 1 < argc) {
			if (argv[i + 1][0] == '-' && !isdigit(argv[i + 1][1])) {
				m_arguments[argv[i]] = "";
				i -= 1;
			}
			else {
				m_arguments[argv[i]] = argv[i + 1];
			}
		}
		else {
			m_arguments[argv[i]] = "";
			i -= 1;
		}
	}
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

bool CommandLineParser::getExists(const std::string& key) {
	if (auto search = m_arguments.find(key); search != m_arguments.end()) {
		return true;
	}
	return false;
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
