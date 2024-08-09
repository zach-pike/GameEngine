#pragma once

#include "imgui/imgui.h"

#include "LoggerProfile/LoggerProfile.hpp"

#include <chrono>
#include <deque>
#include <string>

class LoggerWindow {
public:
    enum class LoggerSeverity {
        INFO,
        WARN,
        ERROR
    };

    static const char* getLoggerSeverityString(LoggerSeverity sev);

    struct LoggerMessage {
        const LoggerProfile& profile;

        std::chrono::system_clock::time_point timePoint;
        LoggerSeverity                        severity;
        std::string                           loggerMessage;
    };

    bool open = true;
private:
    std::deque<LoggerMessage> logs;

public:
    LoggerWindow();
    ~LoggerWindow();

    void render(ImGuiWindowFlags extraFlags);
    void addLog(LoggerMessage message);
};