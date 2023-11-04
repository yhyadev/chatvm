#pragma once

#include "value.hpp"

#include <cstddef>
#include <optional>
#include <vector>

enum InstructionType {
	PrintStack,
	LoadConstant,
	Add,
	Subtract,
	Multiply,
	Divide,
	Modulo
};

struct Instruction {
	InstructionType type;
	std::optional<Value> operand;
};

class Chunk {
  public:
	std::vector<Instruction> code;

	void write_instruction(InstructionType type, Value operand);

	size_t add_constant(Value value);
	Value get_constant(size_t index);

  private:
	std::vector<Value> constants;
};
