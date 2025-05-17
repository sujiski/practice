#include <chrono>
#include <thread>
#include <iostream>

#include "acc_simulation/src/common/EventBus.h"
#include "acc_simulation/src/sensor/SensorService.h"
#include "acc_simulation/src/decision/DecisionService.h"
#include "acc_simulation/src/control/ControlService.h"
#include "acc_simulation/src/vehicle/VehicleState.h"
#include "acc_simulation/src/logger/LoggerService.h"

using namespace std::chrono_literals;

/**
 * @brief メインエントリポイント。全サービスを初期化し、制御ループを実行します。
 *
 * 各サービスは EventBus を介して疎結合に通信します。
 * この関数は指定されたステップ数だけ一定周期でシミュレーションを行います。
 *
 * @return int 終了コード（常に 0 を返します）
 */
int main() {
  // EventBus の作成（全サービスで共有）
  EventBus event_bus;

  // 各サービスの初期化
  sensor::SensorService sensor(event_bus);
  decision::DecisionService decision(event_bus);
  control::ControlService control(event_bus);
  vehicle::VehicleState vehicle(event_bus);

  std::vector<std::string> log_topics = {
      "sensor/obstacle_distance",
      "decision/following_state",
      "control/accel_command",
      "vehicle/ego_state"
  };
  logger::LoggerService logger(event_bus, log_topics, true, "acc_simulation.log");

  // 各サービスの購読初期化
  decision.init();
  control.init();
  vehicle.init();
  logger.init();

  // シミュレーション設定
  const int total_steps = 100;             // 総ステップ数
  const int step_interval_ms = 100;        // 各ステップの時間間隔（ミリ秒）

  std::cout << "Simulation started.\n";

  for (int step = 0; step < total_steps; ++step) {
    std::cout << "Step " << step << std::endl;

    // 1. センサ情報を発行
    sensor.publishSensorData(step);

    // 2. 一定周期で次のステップまで待機
    std::this_thread::sleep_for(std::chrono::milliseconds(step_interval_ms));
  }

  std::cout << "Simulation finished.\n";
  return 0;
}
