#include "Vehicle.hpp"

namespace domain::model {

Vehicle::Vehicle(double position, double velocity, double acceleration)
    : position_(position), velocity_(velocity), acceleration_(acceleration) {}

void Vehicle::update(double dt) {
    // 速度更新：v = v + a * dt
    velocity_ += acceleration_ * dt;

    // 位置更新：x = x + v * dt
    // ※シンプルなオイラー積分を使用
    position_ += velocity_ * dt;
}

double Vehicle::get_position() const {
    return position_;
}

double Vehicle::get_velocity() const {
    return velocity_;
}

double Vehicle::get_acceleration() const {
    return acceleration_;
}

void Vehicle::set_acceleration(double acceleration) {
    // 加速度を外部から設定（Controllerが使用）
    acceleration_ = acceleration;
}

}  // namespace domain::model