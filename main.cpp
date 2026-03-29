#include <iostream>
#include "domain/model/Vehicle.hpp"
#include "domain/model/Environment.hpp"
#include "domain/service/Controller.hpp"
#include "infrastructure/Logger.hpp"

int main()
{
    domain::model::Environment env( domain::model::Vehicle(0.0 , 0.0, 0.0) , domain::model::Vehicle(100.0 , 10.0, 0.0) );
    domain::service::Controller controller;
    infrastructure::Logger logger("data/output/simulation_log.csv");
    logger.write_header();

    // シミュレーション設定
    const int total_steps = 100;
    const double step_interval_sec = 0.1;
    double acceleration;
    int step = 0;
    for(step = 0; step < total_steps; step += 1) {
        std::cout << "Step " << step << std::endl;

        // 加速度(制御入力)を計算
        acceleration = controller.compute_acceleration(env);
        env.ego().set_acceleration(acceleration);

        // 状態更新
        env.ego().update(step_interval_sec);
        env.lead().update(step_interval_sec);

        // log出力
        const double time = step * step_interval_sec;
        logger.log(
            time,
            env.distance(),
            env.ego().get_velocity(),
            env.lead().get_velocity(),
            acceleration
        );

        // 状態出力（デバッグ用）
        std::cout << "  Distance: " << env.distance() << " m\n";
        std::cout << "  Position_ego: " << env.ego().get_position()
                  << " m, Velocity_ego: " << env.ego().get_velocity()
                  << " m/s" << std::endl;
        std::cout << "  Position_lead: " << env.lead().get_position()
                  << " m, Velocity_lead: " << env.lead().get_velocity()
                  << " m/s" << std::endl;
                }

    std::cout << "Simulation finished.\n";
    return 0;
}