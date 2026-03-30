#include <algorithm>
#include "Controller.hpp"

namespace domain::service {

double Controller::compute_acceleration(const domain::model::Environment& env) const {
    // 車間距離の取得、距離偏差の算出
    const double distance_target = 20.0;
    double distance_act = env.distance();
    double distance_error;
    distance_error = distance_act - distance_target;

    // 加減速指令
    double acceleration_request;

    // 加減速指令 (車間距離 Pゲイン)
    const double gainP_dist2accel = 0.3; // [1/sec^2]
    double acceleration_request_pterm;
    acceleration_request_pterm = gainP_dist2accel * distance_error;

    // 相対速度の取得
    double velocity_lead;
    double velocity_ego;
    double relative_velocity;
    velocity_lead = env.lead().get_velocity();
    velocity_ego = env.ego().get_velocity();
    relative_velocity = velocity_lead - velocity_ego;

    // 加減速指令 (相対速度 Dゲイン)
    const double gainD_v2accel = 1.0; // [1/sec]
    double acceleration_request_dterm;
    acceleration_request_dterm = gainD_v2accel * relative_velocity;

    acceleration_request = acceleration_request_pterm + acceleration_request_dterm;

    // 加減速指令 (上下限リミット)
    const double max_acc = 2.0;   // 最大加速 [m/s^2]
    const double min_acc = -3.0;  // 最大減速 [m/s^2]
    acceleration_request = std::clamp(acceleration_request, min_acc, max_acc);

    return acceleration_request;
}

}  // namespace domain::service