#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include "acc_simulation/src/common/EventBus.h"

namespace logger {

/**
 * @brief LoggerService は指定トピックのメッセージを監視し、ログとして出力するサービスです。
 *
 * JSON メッセージをコンソールやファイルに出力します。トレースやデバッグに活用できます。
 */
class LoggerService {
 public:
  /**
   * @brief コンストラクタ。
   *
   * @param event_bus EventBus への参照
   * @param topics ログ出力対象のトピックリスト
   * @param log_to_file true の場合、ファイルにもログを出力
   * @param filename ログファイル名（省略時は "simulation.log"）
   */
  LoggerService(EventBus& event_bus,
                const std::vector<std::string>& topics,
                bool log_to_file = false,
                const std::string& filename = "simulation.log");

  /**
   * @brief 指定されたトピックの購読を開始します。
   */
  void init();

 private:
  /**
   * @brief メッセージ受信時に呼ばれるコールバック関数。
   *
   * @param topic トピック名
   * @param data JSON データ
   */
  void onMessage(const std::string& topic, const nlohmann::json& data);

  EventBus& event_bus_;
  std::vector<std::string> topics_;
  bool log_to_file_;
  std::string filename_;
  std::ofstream log_file_;
};

}  // namespace logger
