#pragma once

/**
 * @file Environment.hpp
 * @brief Defines the simulation environment containing vehicles.
 */

#include "Vehicle.hpp"

namespace domain::model {

/**
 * @brief Environment holding ego and lead vehicles.
 *
 * This class represents the simulation state at a given time.
 */
class Environment {
public:
    /**
     * @brief Constructs the environment with ego and lead vehicles.
     *
     * @param ego Ego vehicle
     * @param lead Lead vehicle
     */
    Environment(const Vehicle& ego, const Vehicle& lead);

    /**
     * @brief Gets mutable reference to ego vehicle.
     *
     * @return Reference to ego vehicle
     */
    Vehicle& ego();

    /**
     * @brief Gets const reference to ego vehicle.
     *
     * @return Const reference to ego vehicle
     */
    const Vehicle& ego() const;

    /**
     * @brief Gets mutable reference to lead vehicle.
     *
     * @return Reference to lead vehicle
     */
    Vehicle& lead();

    /**
    * @brief Gets const reference to lead vehicle.
    *
    * @return Const reference to lead vehicle
    */
    const Vehicle& lead() const;

    /**
     * @brief Gets distance between lead and ego.
     *
     * @return Distance [m]
     */
    double distance() const;

private:
    Vehicle ego_;
    Vehicle lead_;
};

}  // namespace domain::model