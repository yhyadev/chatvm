#include "chunk.hpp"

#include <cstddef>

void Chunk::write_instruction(InstructionType type,
							  std::optional<std::any> operand) {
	code.push_back(Instruction{type, operand});
}

size_t Chunk::add_constant(Value value) {
	constants.push_back(value);

	return constants.size() - 1;
}

Value Chunk::get_constant(size_t index) { return constants[index]; }
