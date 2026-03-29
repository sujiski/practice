#include <gtest/gtest.h>

#include "../domain/model/Vehicle.hpp"
#include "../domain/model/Environment.hpp"
#include "../domain/service/Controller.hpp"
#include "../infrastructure/Logger.hpp"
#include "../usecase/SimulationStep.hpp"

/**
 * @brief SimulationStepの基本動作テスト
 */
TEST(SimulationStepTest, DistanceDecreasesWhenTooFar) {
    // 初期状態（距離が大きい）
    domain::model::Environment env(
        domain::model::Vehicle(0.0, 20.0, 0.0),
        domain::model::Vehicle(100.0, 10.0, 0.0)
    );

    domain::service::Controller controller;
    infrastructure::Logger logger("test.csv");

    usecase::SimulationStep step(controller, logger);

    const double initial_distance = env.distance();

    // 1ステップ実行
    step.execute(env, 0.0, 0.1);

    const double new_distance = env.distance();

    // 距離が縮まることを期待
    EXPECT_LT(new_distance, initial_distance);
}