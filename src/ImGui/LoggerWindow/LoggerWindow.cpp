#include "LoggerWindow.hpp"

#include <algorithm>    // std::min
#include <format>

const char* LoggerWindow::getLoggerSeverityString(LoggerSeverity sev) {
    switch(sev) {
        case LoggerSeverity::INFO: return "Info";
        case LoggerSeverity::WARN: return "Warn";
        case LoggerSeverity::ERROR: return "Error";
    }

    return "Info";
}

LoggerWindow::LoggerWindow() {

}

LoggerWindow::~LoggerWindow() {

}

void LoggerWindow::addLog(LoggerMessage message) {
    logs.push_front(message);
}

void LoggerWindow::render(ImGuiWindowFlags extraFlags) {
    if (!open) return;
    ImGui::Begin("Logger", &open, extraFlags);

    if (ImGui::BeginTable("logger", 4, ImGuiTableFlags_Borders | ImGuiTableFlags_Resizable)) {
        ImGui::TableSetupColumn("Time");
        ImGui::TableSetupColumn("Severity");
        ImGui::TableSetupColumn("Name");
        ImGui::TableSetupColumn("Log");

        ImGui::TableHeadersRow();

        for (int i=0; i < std::min( (int)logs.size(), 50 ); i++) {
            const LoggerMessage& msg = logs.at(i);

            ImGui::TableNextColumn();
            std::chrono::time_point tp = msg.timePoint;
            std::string s = std::format("{:%m/%d/%Y %H:%M:%S}", tp);
            ImGui::Text(s.c_str());

            ImGui::TableNextColumn();
            ImGui::Text(LoggerWindow::getLoggerSeverityString(msg.severity));

            ImGui::TableNextColumn();
            ImGui::Text(msg.profile.getName().c_str());

            ImGui::TableNextColumn();
            ImGui::Text(msg.loggerMessage.c_str());
        }


        ImGui::EndTable();
    }

    ImGui::End();
}