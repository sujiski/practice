#pragma once

#include <functional>
#include <string>
#include <unordered_map>
#include <vector>
#include <nlohmann/json.hpp>


/**
 * @brief EventBus はサービス間の疎結合な通信を実現する Pub/Sub メッセージバスです。
 *
 * このクラスはトピック名に基づいて JSON 形式のメッセージを配信します。
 * 各サービスは EventBus にトピックごとのコールバックを登録し、
 * 他サービスが発行するデータを受け取ることができます。
 */
class EventBus {
 public:
  using Json = nlohmann::json;

  /**
   * @brief サブスクライバに JSON データを通知します。
   *
   * @param topic 通知するトピック名
   * @param data トピックに対応するデータ（JSON形式）
   */
  void publish(const std::string& topic, const Json& data);

  /**
   * @brief 指定トピックに対するコールバック関数を登録します。
   *
   * @param topic 登録するトピック名
   * @param callback トピック受信時に呼ばれる関数
   */
  void subscribe(const std::string& topic, std::function<void(const std::string&, const Json&)> callback);

 private:
  // トピックごとのコールバック関数リスト
  std::unordered_map<std::string, std::vector<std::function<void(const std::string&, const Json&)>>> subscribers_;
};
