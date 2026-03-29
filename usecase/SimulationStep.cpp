#include "SimulationStep.hpp"
#include <iostream>

namespace usecase {

SimulationStep::SimulationStep(
    const domain::service::Controller& controller,
    infrastructure::Logger& logger)
    : controller_(controller), logger_(logger) {}

void SimulationStep::execute(
    domain::model::Environment& env,
    double time,
    double dt
) {
    // ===== 制御入力計算 =====
    const double acceleration =
        controller_.compute_acceleration(env);

    // ===== 加速度設定 =====
    env.ego().set_acceleration(acceleration);

    // ===== 状態更新 =====
    env.ego().update(dt);
    env.lead().update(dt);

    // ===== ログ出力 =====
    logger_.log(
        time,
        env.distance(),
        env.ego().get_velocity(),
        env.lead().get_velocity(),
        acceleration
    );

    // ===== コンソール出力 =====
    std::cout << "Time: " << time
              << " Distance: " << env.distance()
              << std::endl;
}

}  // namespace usecase