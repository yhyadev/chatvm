#pragma once

#include "value.hpp"

#include <any>
#include <cstddef>
#include <optional>
#include <vector>

enum InstructionType {
	Add,
	Subtract,
	Multiply,
	Divide,
	Modulo,

	Equals,
	NotEquals,
	GreaterThan,
	LessThan,

	PrintStack,
	LoadConstant,
};

struct Instruction {
	std::optional<std::any> operand;
	InstructionType type;
};

class Chunk {
  public:
	std::vector<Instruction> code;

	void write_instruction(InstructionType type,
						   std::optional<std::any> operand);

	size_t add_constant(Value value);
	Value get_constant(size_t index);

  private:
	std::vector<Value> constants;
};
