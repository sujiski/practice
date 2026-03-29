#include "Logger.hpp"
#include <iostream>

namespace infrastructure {

Logger::Logger(const std::string& file_path) {
    // ファイルを開く
    file_.open(file_path);

    if (!file_.is_open()) {
        std::cerr << "Failed to open file: " << file_path << std::endl;
    }
}

Logger::~Logger() {
    // ファイルを閉じる
    if (file_.is_open()) {
        file_.close();
    }
}

void Logger::write_header() {
    // CSVヘッダを書き込み
    file_ << "time,distance,ego_velocity,lead_velocity,acceleration\n";
}

void Logger::log(double time,
                 double distance,
                 double ego_velocity,
                 double lead_velocity,
                 double acceleration) {
    // 1ステップ分のデータをCSVに書き込み
    file_ << time << ","
          << distance << ","
          << ego_velocity << ","
          << lead_velocity << ","
          << acceleration << "\n";
}

}  // namespace infrastructure