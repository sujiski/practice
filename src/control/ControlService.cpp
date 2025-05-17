#include "acc_simulation/src/control/ControlService.h"
#include <chrono>
#include <iostream>

namespace control {

ControlService::ControlService(EventBus& event_bus)
    : event_bus_(event_bus) {}

void ControlService::init() {
  // "control/acc_enabled" トピックを購読
  event_bus_.subscribe("control/acc_enabled",
                       [this](const std::string& topic, const nlohmann::json& data) {
                         this->onAccStatusReceived(topic, data);
                       });
}

void ControlService::onAccStatusReceived(const std::string& topic, const nlohmann::json& data) {
  try {
    if (!data.contains("acc_enabled")) {
      std::cerr << "Missing 'acc_enabled' field.\n";
      return;
    }

    bool acc_enabled = data.at("acc_enabled").get<bool>();
    double accel = acc_enabled ? acc_value_ : 0.0;

    nlohmann::json accel_command;
    accel_command["timestamp"] = std::chrono::duration_cast<std::chrono::milliseconds>(
                                     std::chrono::system_clock::now().time_since_epoch())
                                     .count();
    accel_command["accel_mps2"] = accel;

    event_bus_.publish("vehicle/accel_command", accel_command);

  } catch (const std::exception& e) {
    std::cerr << "Error in onAccStatusReceived: " << e.what() << std::endl;
  }
}

}  // namespace control
