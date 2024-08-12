#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>

class Logger {
public:
    Logger(const std::string& filename);
    ~Logger();
    void log(const std::string& message);

private:
    std::ofstream log_file;
};

#endif // LOGGER_H