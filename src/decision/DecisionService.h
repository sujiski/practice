#pragma once

#include <string>
#include <nlohmann/json.hpp>
#include "acc_simulation/src/common/EventBus.h"

namespace decision {

/**
 * @brief DecisionService はセンサ情報から追従走行を行うべきかどうかを判断するサービスです。
 *
 * センサデータ（速度）を受け取り、一定の条件（例: 速度 > 20 m/s）を満たす場合に
 * ACC を有効にする信号を生成して EventBus に publish します。
 */
class DecisionService {
 public:
  /**
   * @brief コンストラクタ。
   *
   * @param event_bus EventBus への参照
   */
  explicit DecisionService(EventBus& event_bus);

  /**
   * @brief サービスを初期化し、EventBus へのサブスクライブを開始します。
   */
  void init();

 private:
  /**
   * @brief センサデータ受信時のコールバック関数。
   *
   * @param topic トピック名（"vehicle/speed"）
   * @param data センサデータ（JSON形式）
   */
  void onSensorDataReceived(const std::string& topic, const nlohmann::json& data);

  EventBus& event_bus_;
  const double speed_threshold_ = 20.0;  ///< 追従を開始する速度閾値（m/s）
};

}  // namespace decision
