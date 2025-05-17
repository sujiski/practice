#include "acc_simulation/src/common/EventBus.h"


/**
 * @brief 指定したトピックにデータを発行し、全サブスクライバに通知します。
 *
 * @param topic トピック名
 * @param data 通知するデータ（JSON形式）
 */
void EventBus::publish(const std::string& topic, const Json& data) {
  // 登録されたコールバックがあれば、全て呼び出す
  if (subscribers_.count(topic)) {
    for (auto& cb : subscribers_[topic]) {
      cb(topic, data);
    }
  }
}

/**
 * @brief 指定したトピックへのデータ受信時に呼び出されるコールバック関数を登録します。
 *
 * @param topic トピック名
 * @param callback 受信時に呼び出す関数（トピック名と JSON データを引数に取る）
 */
void EventBus::subscribe(const std::string& topic, Callback callback) {
  // トピックに対するコールバックリストに追加
  subscribers_[topic].emplace_back(callback);
}
