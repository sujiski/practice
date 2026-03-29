#pragma once

/**
 * @file SimulationStep.hpp
 * @brief Executes a single simulation step.
 */

#include "../domain/model/Environment.hpp"
#include "../domain/service/Controller.hpp"
#include "../infrastructure/Logger.hpp"

namespace usecase {

/**
 * @brief Handles one step of the simulation.
 *
 * This class encapsulates the logic for a single time step,
 * including control computation, state update, and logging.
 */
class SimulationStep {
public:
    /**
     * @brief Constructs a SimulationStep.
     *
     * @param controller Control logic
     * @param logger CSV logger
     */
    SimulationStep(
        const domain::service::Controller& controller,
        infrastructure::Logger& logger
    );

    /**
     * @brief Executes one simulation step.
     *
     * @param env Simulation environment
     * @param time Current simulation time [s]
     * @param dt Time step [s]
     */
    void execute(
        domain::model::Environment& env,
        double time,
        double dt
    );

private:
    const domain::service::Controller& controller_;
    infrastructure::Logger& logger_;
};

}  // namespace usecase