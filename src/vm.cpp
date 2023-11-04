#include "vm.hpp"
#include "chunk.hpp"

#include <iostream>

#include <string>

std::string virtual_machine_result_as_string(VirtualMachineResult result) {
	switch (result) {
	case VirtualMachineResult::Ok:
		return "ok";
	case VirtualMachineResult::InvalidArithmeticOperation:
		return "invalid arithmetic operation";

	default:
		return "unknown virtual machine result";
	}
}

VirtualMachine::VirtualMachine(Chunk c) {
	chunk = c;
	pc = 0;
	halt = false;

	stack = {};
}

VirtualMachineResult VirtualMachine::run() {
	while (pc < chunk.code.size() && !halt) {
		Instruction current_instruction = chunk.code[pc];

		switch (current_instruction.type) {
		case InstructionType::LoadConstant:
			load_constant(current_instruction.operand.value());
			break;

		case InstructionType::PrintStack:
			print_stack();
			break;

		case InstructionType::Add: {
			VirtualMachineResult result = addition_operation();

			if (result != VirtualMachineResult::Ok)
				return result;

			break;
		}

		case InstructionType::Subtract: {
			VirtualMachineResult result = subtraction_operation();

			if (result != VirtualMachineResult::Ok)
				return result;

			break;
		}

		case InstructionType::Multiply: {
			VirtualMachineResult result = multiplication_operation();

			if (result != VirtualMachineResult::Ok)
				return result;

			break;
		}

		case InstructionType::Divide: {
			VirtualMachineResult result = division_operation();

			if (result != VirtualMachineResult::Ok)
				return result;

			break;
		}
		case InstructionType::Modulo: {
			VirtualMachineResult result = modulo_operation();

			if (result != VirtualMachineResult::Ok)
				return result;

			break;
		}
		}

		pc++;
	}

	return VirtualMachineResult::Ok;
}

void VirtualMachine::load_constant(Value operand) { stack.push_back(operand); }

void VirtualMachine::print_stack() {
	std::cout << "Stack :\n";

	for (Value value : stack)
		std::cout << "    " << value << "\n";
}

VirtualMachineResult VirtualMachine::addition_operation() {
	if (stack.size() < 2)
		return InvalidArithmeticOperation;

	Value right = stack[stack.size()];
	stack.pop_back();

	Value left = stack[stack.size()];
	stack.pop_back();

	stack.push_back(left + right);

	return VirtualMachineResult::Ok;
}

VirtualMachineResult VirtualMachine::subtraction_operation() {
	if (stack.size() < 2)
		return InvalidArithmeticOperation;

	Value right = stack[stack.size()];
	stack.pop_back();

	Value left = stack[stack.size()];
	stack.pop_back();

	stack.push_back(left - right);

	return VirtualMachineResult::Ok;
}

VirtualMachineResult VirtualMachine::multiplication_operation() {
	if (stack.size() < 2)
		return InvalidArithmeticOperation;

	Value right = stack[stack.size()];
	stack.pop_back();

	Value left = stack[stack.size()];
	stack.pop_back();

	stack.push_back(left * right);

	return VirtualMachineResult::Ok;
}

VirtualMachineResult VirtualMachine::division_operation() {
	if (stack.size() < 2)
		return InvalidArithmeticOperation;

	Value right = stack[stack.size()];
	stack.pop_back();

	Value left = stack[stack.size()];
	stack.pop_back();

	stack.push_back(left / right);

	return VirtualMachineResult::Ok;
}

VirtualMachineResult VirtualMachine::modulo_operation() {
	if (stack.size() < 2)
		return InvalidArithmeticOperation;

	Value right = stack[stack.size()];
	stack.pop_back();

	Value left = stack[stack.size()];
	stack.pop_back();

	stack.push_back((long long)left % (long long)right);

	return VirtualMachineResult::Ok;
}
