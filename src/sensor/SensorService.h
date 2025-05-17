#pragma once

#include <string>
#include <thread>
#include <atomic>
#include <chrono>
#include <nlohmann/json.hpp>
#include "acc_simulation/src/common/EventBus.h"

namespace sensor {

/**
 * @brief SensorService は車両センサデータ（例：速度）を周期的に発行するサービスです。
 *
 * このサービスは EventBus を通じて "vehicle/speed" トピックに JSON 形式のデータを publish します。
 * データは指定周期でシミュレートされ、一定範囲内の疑似ランダム値を持ちます。
 */
class SensorService {
 public:
  /**
   * @brief コンストラクタ。
   *
   * @param event_bus イベント配信用の EventBus への参照
   * @param interval_ms データ発行の周期（ミリ秒）
   */
  SensorService(EventBus& event_bus, int interval_ms = 100);

  /**
   * @brief センサデータ発行スレッドを開始します。
   */
  void start();

  /**
   * @brief センサデータ発行スレッドを停止します。
   */
  void stop();

  /**
   * @brief センサデータを外部ステップに応じて1回分生成して publish します（手動モード用）。
   *
   * @param step シミュレーションステップ（使用しない場合もあります）
   */
  void publishSensorData(int step);

 private:
  /**
   * @brief センサデータを周期的に生成・publish するメイン処理。
   */
  void run();

  EventBus& event_bus_;
  int interval_ms_;
  std::thread thread_;
  std::atomic<bool> running_;
};

}  // namespace sensor
