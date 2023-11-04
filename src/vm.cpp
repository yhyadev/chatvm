#include "vm.hpp"
#include "chunk.hpp"

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
		default:
			break;
		}

		pc++;
	}
}
