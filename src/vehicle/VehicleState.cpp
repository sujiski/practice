#include "acc_simulation/src/vehicle/VehicleState.h"
#include <chrono>
#include <iostream>

namespace vehicle {

VehicleState::VehicleState(EventBus& event_bus)
    : event_bus_(event_bus) {}

void VehicleState::init() {
  // "vehicle/accel_command" を購読
  event_bus_.subscribe("vehicle/accel_command",
                       [this](const std::string& topic, const nlohmann::json& data) {
                         this->onAccelCommandReceived(topic, data);
                       });
}

void VehicleState::onAccelCommandReceived(const std::string& topic, const nlohmann::json& data) {
  try {
    if (!data.contains("accel_mps2")) {
      std::cerr << "Missing 'accel_mps2' field.\n";
      return;
    }

    double accel = data.at("accel_mps2").get<double>();
    updateState(accel);
  } catch (const std::exception& e) {
    std::cerr << "Error in onAccelCommandReceived: " << e.what() << std::endl;
  }
}

void VehicleState::updateState(double accel) {
  // 簡易な運動方程式による更新
  velocity_mps_ += accel * dt_sec_;
  if (velocity_mps_ < 0.0) velocity_mps_ = 0.0;

  position_m_ += velocity_mps_ * dt_sec_;

  // ego_state を構築して配信
  nlohmann::json ego_state;
  ego_state["timestamp"] = std::chrono::duration_cast<std::chrono::milliseconds>(
                               std::chrono::system_clock::now().time_since_epoch())
                               .count();
  ego_state["velocity_mps"] = velocity_mps_;
  ego_state["position_m"] = position_m_;

  event_bus_.publish("vehicle/ego_state", ego_state);
}

}  // namespace vehicle
