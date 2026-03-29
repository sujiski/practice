#pragma once

/**
 * @file RunSimulation.hpp
 * @brief Use case for running vehicle simulation.
 */

#include "../domain/model/Environment.hpp"
#include "../domain/service/Controller.hpp"
#include "../infrastructure/Logger.hpp"

namespace usecase {

/**
 * @brief Runs the vehicle following simulation.
 *
 * This class orchestrates the simulation loop,
 * coordinating domain logic and infrastructure.
 */
class RunSimulation {
public:
    /**
     * @brief Constructs the simulation use case.
     *
     * @param env Simulation environment
     * @param controller Control logic
     * @param logger CSV logger
     */
    RunSimulation(
        domain::model::Environment& env,
        const domain::service::Controller& controller,
        infrastructure::Logger& logger
    );

    /**
     * @brief Executes the simulation.
     *
     * @param total_steps Number of steps
     * @param dt Time step [s]
     */
    void run(int total_steps, double dt);

private:
    domain::model::Environment& env_;
    const domain::service::Controller& controller_;
    infrastructure::Logger& logger_;
};

}  // namespace usecase