#include "./value.h"

#include <iomanip>
#include <memory>
#include <sstream>
#include <string>

std::string BooleanValue::toString() const {
    return value ? "#t" : "#f";
}

std::string NumericValue::toString() const {
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

std::string SymbolValue::toString() const {
    return value;
}

std::string StringValue::toString() const {
    std::ostringstream oss;
    oss << std::quoted(value);
    return oss.str();
}

std::string NilValue::toString() const {
    return "()";
}

std::string PairValue::toString() const {
    std::ostringstream oss;
    oss << "(";

    ValuePtr current = std::make_shared<PairValue>(*this);
    while (true) {
        auto pair = std::dynamic_pointer_cast<PairValue>(current);
        if (pair) {  // 是PairValue
            oss << pair->left_value->toString();
            current = pair->right_value;
        } else {  // 是NilValue或其他类型
            if (std::dynamic_pointer_cast<NilValue>(current)) {  // 是NilValue
                break;
            } else {  // 是其他类型
                oss << " . " << current->toString();
                break;
            }
        }

        // 如果右值是另一个 PairValue，添加空格分隔
        if (std::dynamic_pointer_cast<PairValue>(current)) {
            oss << " ";
        }
    }
    oss << ")";
    return oss.str();
}