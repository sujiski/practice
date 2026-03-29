#include "RunSimulation.hpp"
#include "SimulationStep.hpp"

namespace usecase {

RunSimulation::RunSimulation(
    domain::model::Environment& env,
    const domain::service::Controller& controller,
    infrastructure::Logger& logger)
    : env_(env), controller_(controller), logger_(logger) {}

void RunSimulation::run(int total_steps, double dt) {
    logger_.write_header(); // CSVヘッダ出力
    SimulationStep stepper(controller_, logger_); // 1ステップ処理オブジェクト

    for (int step = 0; step < total_steps; ++step) {
        const double time = step * dt;
        stepper.execute(env_, time, dt);
    }
}

}  // namespace usecase