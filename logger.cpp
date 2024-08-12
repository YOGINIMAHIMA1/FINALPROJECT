#include "Logger.h"
#include <iostream>
#include <ctime>

Logger::Logger(const std::string& filename) : log_file(filename, std::ios::app) {
    if (!log_file.is_open()) {
        std::cerr << "Failed to open log file: " << filename << std::endl;
    }
}

Logger::~Logger() {
    if (log_file.is_open()) {
        log_file.close();
    }
}

void Logger::log(const std::string& message) {
    std::time_t now = std::time(nullptr);
    char buffer[100];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    log_file << buffer << ": " << message << std::endl;
}