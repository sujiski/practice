#pragma once

/**
 * @file Logger.hpp
 * @brief CSV logger for simulation data.
 */

#include <fstream>
#include <string>

namespace infrastructure {

/**
 * @brief Logger class for writing simulation results to CSV file.
 *
 * This class handles file I/O and provides an interface
 * to log simulation state per time step.
 */
class Logger {
public:
    /**
     * @brief Constructs a Logger and opens a file.
     *
     * @param file_path Output CSV file path
     */
    explicit Logger(const std::string& file_path);

    /**
     * @brief Destructor closes the file.
     */
    ~Logger();

    /**
     * @brief Writes CSV header.
     */
    void write_header();

    /**
     * @brief Logs one step of simulation data.
     *
     * @param time Simulation time [s]
     * @param distance Distance between vehicles [m]
     * @param ego_velocity Ego vehicle velocity [m/s]
     * @param lead_velocity Lead vehicle velocity [m/s]
     * @param acceleration Acceleration command [m/s^2]
     */
    void log(double time,
             double distance,
             double ego_velocity,
             double lead_velocity,
             double acceleration);

private:
    std::ofstream file_;
};

}  // namespace infrastructure