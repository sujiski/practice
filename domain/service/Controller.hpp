#pragma once

/**
 * @file Controller.hpp
 * @brief Defines vehicle control logic.
 */

#include "../model/Environment.hpp"

namespace domain::service {

/**
 * @brief Controller for computing acceleration based on environment state.
 *
 * This class provides control logic to maintain a target distance
 * between ego and lead vehicle.
 */
class Controller {
public:
    /**
     * @brief Computes acceleration command.
     *
     * @param env Current environment state
     * @return Acceleration command [m/s^2]
     */
    double compute_acceleration(const domain::model::Environment& env) const;
};

}  // namespace domain::service