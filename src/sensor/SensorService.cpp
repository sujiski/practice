#include "acc_simulation/src/sensor/SensorService.h"
#include <random>
#include <iostream>

namespace sensor {

SensorService::SensorService(EventBus& event_bus, int interval_ms)
    : event_bus_(event_bus),
      interval_ms_(interval_ms),
      running_(false) {}

void SensorService::start() {
  running_ = true;
  thread_ = std::thread(&SensorService::run, this);
}

void SensorService::stop() {
  running_ = false;
  if (thread_.joinable()) {
    thread_.join();
  }
}

void SensorService::publishSensorData(int step) {
  // 擬似的な速度データを1回生成し、EventBusに送信
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> speed_dist(0.0, 30.0);

  double speed = speed_dist(gen);

  nlohmann::json data;
  data["timestamp"] = std::chrono::duration_cast<std::chrono::milliseconds>(
                          std::chrono::system_clock::now().time_since_epoch())
                          .count();
  data["speed_mps"] = speed;
  data["step"] = step;

  event_bus_.publish("vehicle/speed", data);
}

void SensorService::run() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> speed_dist(0.0, 30.0);  // 0～30 m/s のランダム速度

  while (running_) {
    double speed = speed_dist(gen);  // 疑似センサ値（速度）

    nlohmann::json data;
    data["timestamp"] = std::chrono::duration_cast<std::chrono::milliseconds>(
                            std::chrono::system_clock::now().time_since_epoch())
                            .count();
    data["speed_mps"] = speed;

    // EventBus へ publish
    event_bus_.publish("vehicle/speed", data);

    std::this_thread::sleep_for(std::chrono::milliseconds(interval_ms_));
  }
}

}  // namespace sensor
