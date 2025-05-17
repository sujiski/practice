#include "acc_simulation/src/logger/LoggerService.h"
#include <iostream>
#include <chrono>
#include <iomanip>

namespace logger {

LoggerService::LoggerService(EventBus& event_bus,
                             const std::vector<std::string>& topics,
                             bool log_to_file,
                             const std::string& filename)
    : event_bus_(event_bus),
      topics_(topics),
      log_to_file_(log_to_file),
      filename_(filename) {
  if (log_to_file_) {
    log_file_.open(filename_, std::ios::out | std::ios::trunc);
    if (!log_file_.is_open()) {
      std::cerr << "Failed to open log file: " << filename_ << std::endl;
    }
  }
}

void LoggerService::init() {
  for (const auto& topic : topics_) {
    event_bus_.subscribe(topic,
                         [this](const std::string& topic, const nlohmann::json& data) {
                           this->onMessage(topic, data);
                         });
  }
}

void LoggerService::onMessage(const std::string& topic, const nlohmann::json& data) {
  // 現在時刻（秒＋ミリ秒）を取得
  auto now = std::chrono::system_clock::now();
  auto now_c = std::chrono::system_clock::to_time_t(now);
  auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

  std::ostringstream oss;
  oss << "[" << std::put_time(std::localtime(&now_c), "%F %T")
      << "." << std::setfill('0') << std::setw(3) << ms.count() << "] "
      << "[" << topic << "] "
      << data.dump();

  // コンソール出力
  std::cout << oss.str() << std::endl;

  // ファイル出力
  if (log_file_.is_open()) {
    log_file_ << oss.str() << std::endl;
  }
}

}  // namespace logger
