#include "Logger.h"
#include <iostream>

void Logger::log(const std::string& message) {
    std::cout << message << std::endl;
}

void Logger::err(const std::string& message) {
    std::cerr << message << std::endl; 
}