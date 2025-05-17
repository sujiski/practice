#pragma once

#include <string>
#include <nlohmann/json.hpp>
#include "acc_simulation/src/common/EventBus.h"

namespace control {

/**
 * @brief ControlService は ACC の有効状態に応じて加減速コマンドを生成するサービスです。
 *
 * ACC が有効な場合は正の加速度（例: 1.0 m/s^2）を、無効な場合は 0.0 m/s^2 を発行します。
 */
class ControlService {
 public:
  /**
   * @brief コンストラクタ。
   *
   * @param event_bus EventBus への参照
   */
  explicit ControlService(EventBus& event_bus);

  /**
   * @brief サービスを初期化し、EventBus へのサブスクライブを開始します。
   */
  void init();

 private:
  /**
   * @brief ACC 有効状態の受信時に呼び出されるコールバック関数。
   *
   * @param topic トピック名（"control/acc_enabled"）
   * @param data JSON データ（例: { "acc_enabled": true }）
   */
  void onAccStatusReceived(const std::string& topic, const nlohmann::json& data);

  EventBus& event_bus_;
  const double acc_value_ = 1.0;  ///< ACC ON 時に出力する加速度（m/s^2）
};

}  // namespace control
