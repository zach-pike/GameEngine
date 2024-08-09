#pragma once

#include "imgui/imgui.h"

#include <chrono>
#include <deque>
#include <string>

class Logger {
public:
    enum class LoggerSeverity {
        INFO,
        WARN,
        ERROR
    };

    static const char* getLoggerSeverityString(LoggerSeverity sev);

    struct LoggerMessage {
        std::chrono::system_clock::time_point timePoint;
        LoggerSeverity                        severity;
        std::string                           loggerMessage;
    };

    bool open = true;
private:
    std::deque<LoggerMessage> logs;

    void addLog(LoggerMessage message);
public:
    Logger();
    ~Logger();

    void logInfo(std::string message);
    void logWarn(std::string message);
    void logError(std::string message);

    void render(ImGuiWindowFlags extraFlags);
};