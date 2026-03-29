#include "Environment.hpp"

namespace domain::model {

Environment::Environment(const Vehicle& ego, const Vehicle& lead)
    : ego_(ego), lead_(lead) {}

Vehicle& Environment::ego() {
    // 自車への参照を返す（状態更新用）
    return ego_;
}

Vehicle& Environment::lead() {
    // 先行車への参照を返す
    return lead_;
}

const Vehicle& Environment::ego() const {
    // 読み取り専用アクセス
    return ego_;
}

const Vehicle& Environment::lead() const {
    // 読み取り専用アクセス
    return lead_;
}

double Environment::distance() const {
    // 車間距離 = 先行車位置 - 自車位置
    // 正であれば前方に存在
    return lead_.get_position() - ego_.get_position();
}

}  // namespace domain::model