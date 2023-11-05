#include "value.hpp"

std::string value_as_string(Value value) {
	switch (value.type) {
	case ValueType::Null:
		return "null";
	case ValueType::Boolean:
		return AS_BOOLEAN(value) ? "true" : "false";
	case ValueType::Number:
		return std::to_string(AS_NUMBER(value));
	default:
		return "<unknown value>";
	}
}

bool Value::operator==(Value v) const {
	if (type != v.type)
		return false;

	switch (type) {
	case ValueType::Null:
		if (IS_NULL(v))
			return true;
		return false;
	case ValueType::Boolean:
		return AS_BOOLEAN(*this) == AS_BOOLEAN(v);
	case ValueType::Number:
		return AS_NUMBER(*this) == AS_NUMBER(v);
	default:
		return false;
	}
}

bool Value::operator!=(Value v) const {
	if (type == v.type)
		return false;

	switch (type) {
	case ValueType::Null:
		if (IS_NULL(v))
			return false;
		return true;
	case ValueType::Boolean:
		return AS_BOOLEAN(*this) != AS_BOOLEAN(v);
	case ValueType::Number:
		return AS_NUMBER(*this) != AS_NUMBER(v);
	default:
		return true;
	}
}

bool Value::operator>(Value v) const {
	if (!IS_NUMBER(*this) || !IS_NUMBER(v))
		return false;

	return AS_NUMBER(*this) > AS_NUMBER(v);
}

bool Value::operator<(Value v) const {
	if (!IS_NUMBER(*this) || !IS_NUMBER(v))
		return false;

	return AS_NUMBER(*this) < AS_NUMBER(v);
}
