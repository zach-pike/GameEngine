#include "LoggerProfile.hpp"

#include "../LoggerWindow.hpp"

LoggerProfile::LoggerProfile(std::shared_ptr<LoggerWindow> _loggerWindow, const std::string& _name):
    loggerName(_name),
    loggerWindowPtr(_loggerWindow)
{

}

LoggerProfile::~LoggerProfile() {

}

const std::string& LoggerProfile::getName() const {
    return loggerName;
}

void LoggerProfile::logInfo(std::string message) {
    loggerWindowPtr->addLog(LoggerWindow::LoggerMessage{
        .profile = *this,
        .timePoint = std::chrono::system_clock::now(),
        .severity = LoggerWindow::LoggerSeverity::INFO,
        .loggerMessage = message
    });
}

void LoggerProfile::logWarn(std::string message) {
    loggerWindowPtr->addLog(LoggerWindow::LoggerMessage{
        .profile = *this,
        .timePoint = std::chrono::system_clock::now(),
        .severity = LoggerWindow::LoggerSeverity::WARN,
        .loggerMessage = message
    });
}

void LoggerProfile::logError(std::string message) {
    loggerWindowPtr->addLog(LoggerWindow::LoggerMessage{
        .profile = *this,
        .timePoint = std::chrono::system_clock::now(),
        .severity = LoggerWindow::LoggerSeverity::ERROR,
        .loggerMessage = message
    });
}
