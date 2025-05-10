#ifndef VALUE_H
#define VALUE_H

#include <memory>
#include <string>

/*
    We need to implement abstract `Value` class and its subclasses, including:
    - BooleanValue: for boolean values.
    - NumericValue: for numbers, using `double`.
    - StringValue: for string-type values.
    - NilValue: for empty tables.
    - SymbolValue: for symbol names.
    - PairValue: for the pairs, composed of left-side part and right-side part,
   both using `std::shared_ptr`.
*/

/**
 * @brief Abstract base class for all value types
 */
class Value {
public:
    virtual ~Value() = default;

    /**
     * @brief Converts the value to its string representation.
     * 
     * @return A string representing the value.
     */
    virtual std::string toString() const = 0;
};

using ValuePtr = std::shared_ptr<Value>;

/**
 * @brief Boolean value
 */
class BooleanValue : public Value {
private:
    bool value;

public:
    BooleanValue(bool v): value(v) {}
    std::string toString() const override;
};


/**
 * @brief NumericValue
 * 
 */
class NumericValue : public Value {
private:
    double value;

public:
    NumericValue(double v): value(v) {}
    std::string toString() const override;
};

/**
 * @brief StringValue
 * 
 */
class StringValue : public Value{
private:
    std::string value;

public:
    StringValue(std::string v): value(v) {}
    std::string toString() const override;
};

/**
 * @brief NilValue
 * 
 */
class NilValue : public Value{
public:
    NilValue() {}
    std::string toString() const override;
};

/**
 * @brief SymbolValue
 * 
 */
class SymbolValue : public Value{
private:
    std::string value;

public:
    SymbolValue(std::string v): value(v) {}
    std::string toString() const override;
};

/**
 * @brief PairValue
 * 
 */
class PairValue : public Value{
private:
    std::shared_ptr<Value> left_value, right_value;

public:
    PairValue(std::shared_ptr<Value> left, std::shared_ptr<Value> right) : left_value(left), right_value(right) {}
    std::string toString() const override;
};
#endif