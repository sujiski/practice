#include "sensor/SensorService.h"
#include "control/ControlService.h"
#include "decision/DecisionService.h"
#include "vehicle/VehicleState.h"
#include "logger/LoggerService.h"
#include "common/EventBus.h"

#include <chrono>
#include <thread>

int main() {
    EventBus bus;
    VehicleState vehicle;

    SensorService sensor(bus);
    DecisionService decision(bus);
    ControlService control(bus);
    LoggerService logger(bus);

    constexpr double dt = 0.1; // 100ms
    for (int i = 0; i < 100; ++i) {
        sensor.update();              // Sensor測定 → publish
        decision.update();            // Decision処理 → subscribe/req
        double acc = control.update(); // 制御指令生成
        vehicle.update(acc, dt);      // 車両状態更新

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
