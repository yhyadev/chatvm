#include "vm.hpp"
#include "chunk.hpp"
#include <iostream>

VirtualMachine::VirtualMachine(Chunk c) {
	chunk = c;
	pc = 0;
	halt = false;

	stack = {};
}

void VirtualMachine::run() {
	while (pc < chunk.code.size() && !halt) {
		Instruction current_instruction = chunk.code[pc];

		switch (current_instruction.type) {
		case InstructionType::LoadConstant:
			if (!current_instruction.operand.has_value())
				return;

			stack.push_back(current_instruction.operand.value());
			break;

		case InstructionType::PrintStack:
			std::cout << "Stack :\n";

			for (Value value : stack)
				std::cout << "    " << value << "\n";
			break;

		default:
			break;
		}

		pc++;
	}
}
