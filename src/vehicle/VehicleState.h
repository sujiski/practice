#pragma once

#include <string>
#include <nlohmann/json.hpp>
#include "acc_simulation/src/common/EventBus.h"

namespace vehicle {

/**
 * @brief VehicleState は自車の状態（速度、位置など）を更新・配信するサービスです。
 *
 * 加減速コマンドを受け取り、一定時間ステップごとに速度・位置を更新します。
 * 更新された状態は "vehicle/ego_state" トピックに配信されます。
 */
class VehicleState {
 public:
  /**
   * @brief コンストラクタ。
   *
   * @param event_bus EventBus への参照
   */
  explicit VehicleState(EventBus& event_bus);

  /**
   * @brief イベントバスへの購読を初期化します。
   */
  void init();

 private:
  /**
   * @brief 加減速コマンドを受信した際のコールバック関数。
   *
   * @param topic トピック名（"vehicle/accel_command"）
   * @param data JSON データ（例: { "accel_mps2": 1.0 }）
   */
  void onAccelCommandReceived(const std::string& topic, const nlohmann::json& data);

  /**
   * @brief 内部状態（速度・位置）を更新し、"vehicle/ego_state" を発行します。
   *
   * @param accel 加速度 [m/s^2]
   */
  void updateState(double accel);

  EventBus& event_bus_;
  double velocity_mps_ = 0.0;  ///< 現在の速度 [m/s]
  double position_m_ = 0.0;    ///< 現在の位置 [m]
  const double dt_sec_ = 0.1;  ///< シミュレーション時間ステップ [s]
};

}  // namespace vehicle
