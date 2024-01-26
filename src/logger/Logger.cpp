#include "Logger.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <string>

std::vector<LogEntry> Logger::messages;

std::string CurrentDateTimeToString() {
    std::time_t currentTime = std::time(nullptr);
    std::tm* localTime = std::localtime(&currentTime);
    char formattedTime[100];
    std::strftime(formattedTime, sizeof(formattedTime), "%d-%b-%Y %H:%M:%S", localTime);
    std::string formattedTimeString(formattedTime);
    return formattedTimeString;
}

void Logger::Log(const std::string& message) {
    LogEntry logEntry;
    logEntry.type = LOG_INFO;
    logEntry.message = "LOG: [" + CurrentDateTimeToString() + "]: " + message;
    std::cout << "\x1B[32m" << logEntry.message << "\033[0m" << std::endl;
    messages.push_back(logEntry);
}

void Logger::Err(const std::string& message) {
    LogEntry logEntry;
    logEntry.type = LOG_ERROR;
    logEntry.message = "ERR: [" + CurrentDateTimeToString() + "]: " + message;
    messages.push_back(logEntry);
    std::cerr << "\x1B[91m"<< logEntry.message << "\033[0m" << std::endl;
}

std::vector<LogEntry> Logger::GetLastMessages(int numberOfMessages) {
    if (numberOfMessages >= messages.size()) {
        return messages;
    } else {
        return std::vector<LogEntry>(messages.end() - numberOfMessages, messages.end());
    }
}
