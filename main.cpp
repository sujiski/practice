#include <iostream>
#include "domain/model/Vehicle.hpp"
#include "domain/model/Environment.hpp"
#include "domain/service/Controller.hpp"
#include "usecase/RunSimulation.hpp"
#include "infrastructure/Logger.hpp"

int main()
{
    // 環境構築
    const double initial_position_ego = 0.0;
    const double initial_velocity_ego = 2.0;
    const double initial_acceleration_ego = 0.0;
    const double initial_position_lead = 10.0;
    const double initial_velocity_lead = 10.0;
    const double initial_acceleration_lead = 0.0;
    domain::model::Environment env(
        domain::model::Vehicle(initial_position_ego , initial_velocity_ego, initial_acceleration_ego) ,
        domain::model::Vehicle(initial_position_lead , initial_velocity_lead, initial_acceleration_lead)
    );

    domain::service::Controller controller;
    infrastructure::Logger logger("data/output/simulation_log.csv");

    // Usecase実行
    usecase::RunSimulation sim(env, controller, logger);
    const int total_steps = 600;
    const double step_interval_sec = 0.1;
    sim.run(total_steps, step_interval_sec);

    return 0;
}