#pragma once

/**
 * @file Vehicle.hpp
 * @brief Defines the Vehicle entity in 1D kinematic simulation.
 */

namespace domain::model {

/**
 * @brief Vehicle entity representing motion in 1D space.
 *
 * This class encapsulates position, velocity, and acceleration,
 * and provides an update function based on simple kinematics.
 */
class Vehicle {
public:
    /**
     * @brief Constructs a Vehicle with initial state.
     *
     * @param position Initial position [m]
     * @param velocity Initial velocity [m/s]
     * @param acceleration Initial acceleration [m/s^2]
     */
    Vehicle(double position, double velocity, double acceleration);

    /**
     * @brief Updates the vehicle state using simple kinematics.
     *
     * @param dt Time step [s]
     */
    void update(double dt);

    /**
     * @brief Gets current position.
     *
     * @return Position [m]
     */
    double get_position() const;

    /**
     * @brief Gets current velocity.
     *
     * @return Velocity [m/s]
     */
    double get_velocity() const;

    /**
     * @brief Gets current acceleration.
     *
     * @return Acceleration [m/s^2]
     */
    double get_acceleration() const;

    /**
     * @brief Sets acceleration.
     *
     * @param acceleration New acceleration [m/s^2]
     */
    void set_acceleration(double acceleration);

private:
    double position_;
    double velocity_;
    double acceleration_;
};

}  // namespace domain::model