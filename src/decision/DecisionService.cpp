#include "acc_simulation/src/decision/DecisionService.h"
#include <iostream>

namespace decision {

DecisionService::DecisionService(EventBus& event_bus)
    : event_bus_(event_bus) {}

void DecisionService::init() {
  // "vehicle/speed" トピックを購読
  event_bus_.subscribe("vehicle/speed",
                       [this](const std::string& topic, const nlohmann::json& data) {
                         this->onSensorDataReceived(topic, data);
                       });
}

void DecisionService::onSensorDataReceived(const std::string& topic, const nlohmann::json& data) {
  try {
    if (!data.contains("speed_mps")) {
      std::cerr << "Sensor data missing 'speed_mps' field.\n";
      return;
    }

    double speed = data.at("speed_mps").get<double>();

    // 判定ロジック：速度が threshold を超えていれば true
    bool acc_enabled = speed >= speed_threshold_;

    nlohmann::json acc_status;
    acc_status["timestamp"] = std::chrono::duration_cast<std::chrono::milliseconds>(
                                  std::chrono::system_clock::now().time_since_epoch())
                                  .count();
    acc_status["acc_enabled"] = acc_enabled;

    // 結果を publish
    event_bus_.publish("control/acc_enabled", acc_status);

  } catch (const std::exception& e) {
    std::cerr << "Error in onSensorDataReceived: " << e.what() << std::endl;
  }
}

}  // namespace decision
