#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <mutex>
#include <time.h>

enum class LogLevel{
    ENTER,
    ACTION, 
    CHANGE,
    EXIT,
    ERROR, 
};

class Logger {
public:
    // Получение единственного экземпляра (Singleton)
    static Logger& getInstance();
    
    // Запись сообщения в лог
    void log(const std::string& message);
    void log(LogLevel level, const std::string& message);

    // Запрещаем копирование и присваивание
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

private:
    Logger(); 
    ~Logger(); 
    
    std::ofstream logFile;
    std::mutex logMutex; // потокобезопастность

    std::string generateFilename() const;
};

#endif // LOGGER_H