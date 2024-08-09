#pragma once

#include <memory>
#include <string>



class LoggerWindow;

class LoggerProfile {
private:
    std::shared_ptr<LoggerWindow> loggerWindowPtr;

    std::string loggerName;
public:
    LoggerProfile(std::shared_ptr<LoggerWindow> loggerWindow, const std::string& name);
    ~LoggerProfile();

    const std::string& getName() const;

    void logInfo(std::string message);
    void logWarn(std::string message);
    void logError(std::string message);
};