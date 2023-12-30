#include "Logger.h"
#include <iostream>
#include <iomanip>
#include <ctime>

const std::string greenColor = "\033[1;32m";
const std::string redColor = "\033[1;31m";
const std::string resetColor = "\033[0m";

std::tm* getCurrentTime() {
    std::time_t currentTime = std::time(nullptr);
    std::tm* localTime = std::localtime(&currentTime);
    return localTime;
}

std::__1::__iom_t10<char> getFormattedTime(std::tm* time) {
    return std::put_time(time, "[%d/%m/%y %T]");
}

void Logger::log(const std::string& message) {
    std::tm* localTime = getCurrentTime();
    std::cout << greenColor << "LOG: " << getFormattedTime(localTime) << " - " << message << resetColor << std::endl;
}

void Logger::err(const std::string& message) {
    std::tm* localTime = getCurrentTime();
    std::cerr << redColor << "ERR: " << getFormattedTime(localTime) << " - " << message << resetColor << std::endl;
}