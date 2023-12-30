#include "Logger.h"
#include <iostream>
#include <iomanip>
#include <ctime>

const std::string greenColor = "\033[1;32m";
const std::string redColor = "\033[1;31m";
const std::string resetColor = "\033[0m";

std::tm* Logger::getCurrentTime() {
    std::time_t currentTime = std::time(nullptr);
    std::tm* localTime = std::localtime(&currentTime);
    return localTime;
}

void Logger::log(const std::string& message) {
    std::tm* localTime = getCurrentTime();
    std::cout << greenColor << "LOG: " << std::put_time(localTime, "[%d/%m/%y %T]") << " - " << message << resetColor << std::endl;
}

void Logger::err(const std::string& message) {
    std::tm* localTime = getCurrentTime();
    std::cout << redColor << "ERR: " << std::put_time(localTime, "[%d/%m/%y %T]") << " - " << message << resetColor << std::endl;
}