#include "RunSimulation.hpp"
#include <iostream>

namespace usecase {

RunSimulation::RunSimulation(
    domain::model::Environment& env,
    const domain::service::Controller& controller,
    infrastructure::Logger& logger)
    : env_(env), controller_(controller), logger_(logger) {}

void RunSimulation::run(int total_steps, double dt) {
    // CSVヘッダ出力
    logger_.write_header();

    for (int step = 0; step < total_steps; ++step) {
        const double time = step * dt;

        // 制御入力計算
        const double acceleration =
            controller_.compute_acceleration(env_);

        // 加速度設定
        env_.ego().set_acceleration(acceleration);

        // 状態更新
        env_.ego().update(dt);
        env_.lead().update(dt);

        // ログ出力
        logger_.log(
            time,
            env_.distance(),
            env_.ego().get_velocity(),
            env_.lead().get_velocity(),
            acceleration
        );

        // コンソール出力
        std::cout << "Step " << step
                  << " Distance: " << env_.distance()
                  << std::endl;
    }
}

}  // namespace usecase