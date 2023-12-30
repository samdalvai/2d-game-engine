#ifndef LOGGER_H
#define LOGGER_H

#include <string>

class Logger {
    private:
        static std::tm* getCurrentTime();
    public:
        static void log(const std::string& message);
        static void err(const std::string& message);
};

#endif