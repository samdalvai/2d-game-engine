#include "Logger.h"
#include <iostream>
#include <string>
#include <chrono>
#include <ctime>

const std::string greenColor = "\033[1;32m";
const std::string redColor = "\033[1;31m";
const std::string resetColor = "\033[0m";

std::vector<LogEntry> Logger::messages;

std::string currentDateTimeToString() {
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::string output(30, '\0');
    std::strftime(&output[0], output.size(), "%d-%b-%Y %H:%M:%S", std::localtime(&now));

    return output;
}

void Logger::log(const std::string& message) {
    LogEntry logEntry;
    logEntry.type = LOG_INFO;
    logEntry.message = "LOG: [" + currentDateTimeToString() + "] - " + message;
    std::cout << greenColor << logEntry.message << resetColor << std::endl;

    messages.push_back(logEntry);
}

void Logger::err(const std::string& message) {
    LogEntry logEntry;
    logEntry.type = LOG_ERROR;
    logEntry.message = "ERR: [" + currentDateTimeToString() + "] - " + message;
    messages.push_back(logEntry);

    std::cerr << redColor << logEntry.message << resetColor << std::endl;
}
