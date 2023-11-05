#pragma once

#include <string>
enum ValueType {
	Null,
	Boolean,
	Number,
};

struct Value {
	ValueType type;
	union {
		bool boolean;
		double number;
	} as;

	bool operator==(Value) const;
	bool operator!=(Value) const;
	bool operator>(Value) const;
	bool operator<(Value) const;
};

#define NULL_VALUE (Value{.type = ValueType::Null, .as = {.number = 0}})
#define BOOLEAL_VALUE(b)                                                       \
	(Value{.type = ValueType::Boolean, .as = {.boolean = b}})
#define NUMBER_VALUE(n) (Value{.type = ValueType::Number, .as = {.number = n}})

#define AS_BOOLEAN(v) ((v).as.boolean)
#define AS_NUMBER(v) ((v).as.number)

#define IS_NULL(v) ((v).type == ValueType::Null)
#define IS_BOOLEAN(v) ((v).type == ValueType::Boolean)
#define IS_NUMBER(v) ((v).type == ValueType::Number)

std::string value_as_string(Value);
