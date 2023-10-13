#pragma once

class CommandLineParser {
public:
	CommandLineParser(const int argc, const char* argv[]);
	~CommandLineParser()								   = default;
	CommandLineParser(const CommandLineParser&)			   = delete;
	CommandLineParser(CommandLineParser&&)				   = delete;
	CommandLineParser& operator=(const CommandLineParser&) = delete;
	CommandLineParser& operator=(CommandLineParser&&)	   = delete;

	int getValueOr(const std::string& key, int defaultValue);
	std::string getValueOr(const std::string& key, const std::string defaultValue);
	float getValueOr(const std::string& key, float defaultValue);

private:
	std::map<std::string, std::string> m_arguments{};
};