#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <iostream>
#include <string>

class Logger {
public:
    Logger(const std::string& filename) {
        logfile.open(filename, std::ios::app);
        if (!logfile.is_open()) {
            std::cerr << "Failed to open log file: " << filename << std::endl;
        }
    }

    ~Logger() {
        if (logfile.is_open()) {
            logfile.close();
        }
    }

    void log(const std::string& message) {
        if (logfile.is_open()) {
            logfile << message << std::endl;
        }
    }

private:
    std::ofstream logfile;
};

#endif // LOGGER_H
