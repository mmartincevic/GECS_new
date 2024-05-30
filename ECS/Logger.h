#pragma once

#include <iostream>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

namespace gecs {

    class Logger {
    private:
        Logger() {}

        template<typename T>
        void Console(const std::string& message);

        template<typename T>
        void ToFile(const std::string& message);

        std::shared_ptr<spdlog::logger> file_logger;

    public:


        static Logger& Get() {
            static Logger instance; // Static local variable ensures it's initialized only once
            return instance;
        }

        Logger(Logger const&) = delete;
        void operator=(Logger const&) = delete;

        template <typename T>
        void Log(T ct, const std::string& message, LoggerType type = LoggerType::ALL);
    };

    // Define template specializations outside the class
    template<typename T>
    void Logger::Console(const std::string& message) {
        switch (static_cast<LogType>(T{})) {
        case LogType::GECS_DEBUG:
            spdlog::debug(message);
            break;
        case LogType::GECS_WARN:
            spdlog::warn(message);
            break;
        case LogType::GECS_ERROR:
            spdlog::error(message);
            break;
        case LogType::GECS_CRITICAL:
            spdlog::critical(message);
            break;
        default:
        case LogType::GECS_INFO:
            spdlog::info(message);
            break;
        }
    }

    template<typename T>
    void Logger::ToFile(const std::string& message) 
    {
        if (!file_logger)
        {
            try {
                file_logger = spdlog::basic_logger_mt("basic_logger", "GECS_log.txt");
            }
            catch (const spdlog::spdlog_ex& _ex) {
                throw std::runtime_error("GECS - Could not log to file");
            }
        }
            
        switch (static_cast<LogType>(T{})) {
        case LogType::GECS_DEBUG:
            file_logger->debug(message);
            break;
        case LogType::GECS_WARN:
            file_logger->warn(message);
            break;
        case LogType::GECS_ERROR:
            file_logger->error(message);
            break;
        case LogType::GECS_CRITICAL:
            file_logger->critical(message);
            break;
        default:
        case LogType::GECS_INFO:
            file_logger->info(message);
            break;
        }
      
    }

    template <typename T>
    void Logger::Log(T ct, const std::string& message, LoggerType type) {
        switch (type) {
        case LoggerType::Console:
            Console<T>(message);
            break;
        case LoggerType::File:
            ToFile<T>(message);
            break;
        case LoggerType::ALL:
            Console<T>(message);
            ToFile<T>(message);
            break;
        }
    }
};