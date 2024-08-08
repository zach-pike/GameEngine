#include "Logger.hpp"

#include <algorithm>    // std::min
#include <format>

const char* Logger::getLoggerSeverityString(LoggerSeverity sev) {
    switch(sev) {
        case LoggerSeverity::INFO: return "Info";
        case LoggerSeverity::WARN: return "Warn";
        case LoggerSeverity::ERROR: return "Error";
    }
}

Logger::Logger() {

}

Logger::~Logger() {

}

void Logger::addLog(LoggerMessage message) {
    logs.push_front(message);
}

void Logger::logInfo(std::string message) {
    addLog(LoggerMessage{
        .timePoint = std::chrono::system_clock::now(),
        .severity = LoggerSeverity::INFO,
        .loggerMessage = message
    });
}

void Logger::logWarn(std::string message) {
        addLog(LoggerMessage{
        .timePoint = std::chrono::system_clock::now(),
        .severity = LoggerSeverity::WARN,
        .loggerMessage = message
    });
}

void Logger::logError(std::string message) {
        addLog(LoggerMessage{
        .timePoint = std::chrono::system_clock::now(),
        .severity = LoggerSeverity::ERROR,
        .loggerMessage = message
    });
}

void Logger::render(ImGuiWindowFlags extraFlags) {
    ImGui::Begin("Logger", nullptr, extraFlags);

    if (ImGui::BeginTable("logger", 3, ImGuiTableFlags_Borders | ImGuiTableFlags_Resizable)) {
        ImGui::TableSetupColumn("Time");
        ImGui::TableSetupColumn("Severity");
        ImGui::TableSetupColumn("Log");

        ImGui::TableHeadersRow();

        for (int i=0; i < std::min( (int)logs.size(), 50 ); i++) {
            const LoggerMessage& msg = logs.at(i);

            ImGui::TableNextColumn();
            std::chrono::time_point tp = msg.timePoint;
            std::string s = std::format("{:%m/%d/%Y %H:%M:%S}", tp);
            ImGui::Text(s.c_str());

            ImGui::TableNextColumn();
            ImGui::Text(Logger::getLoggerSeverityString(msg.severity));

            ImGui::TableNextColumn();
            ImGui::Text(msg.loggerMessage.c_str());
        }


        ImGui::EndTable();
    }

    ImGui::End();
}