#include "logger.h"
#include <chrono>
#include <time.h>

Logger& Logger::getInstance() {
    static Logger instance; // Гарантированно создается один раз
    return instance;
}

Logger::Logger() {
    std::string filename = generateFilename();
    logFile.open(filename, std::ios::out | std::ios::app);
    if (!logFile.is_open()) {
        throw std::runtime_error("Failed to open log file: " + filename);
    }
    log("=== Logging started ===");
}

Logger::~Logger() {
    log("=== Logging ended ===");
    if (logFile.is_open()) {
        logFile.close();
    }
}

std::string Logger::generateFilename() const {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    
    std::tm tm;
    #ifdef _WIN32
    localtime_s(&tm, &in_time_t);   // Используем localtime_r для потокобезопасности
    #else
        localtime_r(&in_time_t, &tm);
    #endif
    
    std::ostringstream oss;
    oss << "logs/" << std::put_time(&tm, "%Y-%m-%d_%H-%M-%S") << ".log";
    return oss.str();
}

void Logger::log(const std::string& message) {
    std::lock_guard<std::mutex> lock(logMutex);
    
    if (logFile.is_open()) {
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);
        
        std::tm tm;
        #ifdef _WIN32
        localtime_s(&tm, &in_time_t);
        #else
            localtime_r(&in_time_t, &tm);
        #endif
            
        logFile << std::put_time(&tm, "[%Y-%m-%d %H:%M:%S] ") << message << std::endl;
    }
}

void Logger::log(LogLevel level, const std::string& message) {
    std::lock_guard<std::mutex> lock(logMutex);
    
    if (logFile.is_open()) {
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);
        
        std::tm tm;
        #ifdef _WIN32
        localtime_s(&tm, &in_time_t);
        #else
            localtime_r(&in_time_t, &tm);
        #endif
            
        logFile << std::put_time(&tm, "[%Y-%m-%d %H:%M:%S] ");
        std::string levelStr;
        switch (level)
        {
            case LogLevel::ENTER: levelStr="ENTER"; break;
            case LogLevel::ACTION: levelStr="ACTION"; break;
            case LogLevel::CHANGE: levelStr="CHANGE"; break;
            case LogLevel::EXIT: levelStr="EXIT"; break;
            case LogLevel::ERROR: levelStr="ERROR"; break;
        }
        logFile << '[' << levelStr << ']' << message << std::endl;
    }
}