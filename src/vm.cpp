#include "vm.hpp"
#include "chunk.hpp"
#include "value.hpp"

#include <any>
#include <cmath>
#include <iostream>

#include <string>

std::string vmr_as_string(VirtualMachineResult result) {
	switch (result) {
	case VirtualMachineResult::InvalidUnaryOperation:
		return "invalid unary operation";
	case VirtualMachineResult::InvalidArithmeticOperation:
		return "invalid arithmetic operation";
	case VirtualMachineResult::InvalidComparisonOperation:
		return "invalid comparison operation";
	case VirtualMachineResult::InvalidInstruction:
		return "invalid instruction";
	case VirtualMachineResult::Ok:
		return "ok";
	default:
		return "unknown virtual machine result";
	}
}

VirtualMachine::VirtualMachine(Chunk c) : chunk(c) {
	pc = 0;
	halt = false;

	stack = {};
}

VirtualMachineResult VirtualMachine::run() {
	while (pc < chunk.code.size() && !halt) {
		Instruction current_instruction = chunk.code[pc];

		switch (current_instruction.type) {
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

		case InstructionType::Not: {
			VirtualMachineResult result = logical_not_operation();

			if (result != VirtualMachineResult::Ok)
				return result;

			break;
		}

		case InstructionType::Equals: {
			VirtualMachineResult result = equals_operation();

			if (result != VirtualMachineResult::Ok)
				return result;

			break;
		}

		case InstructionType::NotEquals: {
			VirtualMachineResult result = notequals_operation();

			if (result != VirtualMachineResult::Ok)
				return result;

			break;
		}

		case InstructionType::GreaterThan: {
			VirtualMachineResult result = greaterthan_operation();

			if (result != VirtualMachineResult::Ok)
				return result;

			break;
		}

		case InstructionType::LessThan: {
			VirtualMachineResult result = lessthan_operation();

			if (result != VirtualMachineResult::Ok)
				return result;

			break;
		}

		case InstructionType::LoadConstant:
			load_constant(current_instruction.operand.value());
			break;

		case InstructionType::PrintStack:
			print_stack();
			break;

		default:
			return VirtualMachineResult::InvalidInstruction;
		}

		pc++;
	}

	return VirtualMachineResult::Ok;
}

void VirtualMachine::load_constant(std::any operand) {
	size_t index = std::any_cast<size_t>(operand);

	stack.push_back(chunk.get_constant(index));
}

void VirtualMachine::print_stack() {
	std::cout << "Stack :\n";

	for (Value value : stack)
		std::cout << "    " << value_as_string(value) << "\n";
}

VirtualMachineResult VirtualMachine::addition_operation() {
	if (stack.size() < 2)
		return VirtualMachineResult::InvalidArithmeticOperation;

	Value right = stack[stack.size() - 1];
	stack.pop_back();

	Value left = stack[stack.size() - 1];
	stack.pop_back();

	if (!IS_NUMBER(left) || !IS_NUMBER(right))
		return VirtualMachineResult::InvalidArithmeticOperation;

	double rhs = AS_NUMBER(right);

	double lhs = AS_NUMBER(left);

	stack.push_back(NUMBER_VALUE(lhs + rhs));

	return VirtualMachineResult::Ok;
}

VirtualMachineResult VirtualMachine::subtraction_operation() {
	if (stack.size() < 2)
		return VirtualMachineResult::InvalidArithmeticOperation;

	Value right = stack[stack.size() - 1];
	stack.pop_back();

	Value left = stack[stack.size() - 1];
	stack.pop_back();

	if (!IS_NUMBER(left) || !IS_NUMBER(right))
		return VirtualMachineResult::InvalidArithmeticOperation;

	double rhs = AS_NUMBER(right);

	double lhs = AS_NUMBER(left);

	stack.push_back(NUMBER_VALUE(lhs - rhs));

	return VirtualMachineResult::Ok;
}

VirtualMachineResult VirtualMachine::multiplication_operation() {
	if (stack.size() < 2)
		return VirtualMachineResult::InvalidArithmeticOperation;

	Value right = stack[stack.size() - 1];
	stack.pop_back();

	Value left = stack[stack.size() - 1];
	stack.pop_back();

	if (!IS_NUMBER(left) || !IS_NUMBER(right))
		return VirtualMachineResult::InvalidArithmeticOperation;

	double rhs = AS_NUMBER(right);

	double lhs = AS_NUMBER(left);

	stack.push_back(NUMBER_VALUE(lhs * rhs));

	return VirtualMachineResult::Ok;
}

VirtualMachineResult VirtualMachine::division_operation() {
	if (stack.size() < 2)
		return VirtualMachineResult::InvalidArithmeticOperation;

	Value right = stack[stack.size() - 1];
	stack.pop_back();

	Value left = stack[stack.size() - 1];
	stack.pop_back();

	if (!IS_NUMBER(left) || !IS_NUMBER(right))
		return VirtualMachineResult::InvalidArithmeticOperation;

	double rhs = AS_NUMBER(right);

	double lhs = AS_NUMBER(left);

	stack.push_back(NUMBER_VALUE(lhs / rhs));

	return VirtualMachineResult::Ok;
}

VirtualMachineResult VirtualMachine::modulo_operation() {
	if (stack.size() < 2)
		return VirtualMachineResult::InvalidArithmeticOperation;

	Value right = stack[stack.size() - 1];
	stack.pop_back();

	Value left = stack[stack.size() - 1];
	stack.pop_back();

	if (!IS_NUMBER(left) || !IS_NUMBER(right))
		return VirtualMachineResult::InvalidArithmeticOperation;

	double rhs = AS_NUMBER(right);

	double lhs = AS_NUMBER(left);

	stack.push_back(NUMBER_VALUE(fmod(lhs, rhs)));

	return VirtualMachineResult::Ok;
}

VirtualMachineResult VirtualMachine::logical_not_operation() {
	if (stack.size() < 1)
		return VirtualMachineResult::InvalidUnaryOperation;

	Value right = stack[stack.size() - 1];
	stack.pop_back();

	switch (right.type) {
	case ValueType::Null:
		stack.push_back(BOOLEAN_VALUE(true));
	case ValueType::Boolean:
		stack.push_back(BOOLEAN_VALUE(!AS_BOOLEAN(right)));
		break;
	case ValueType::Number:
		stack.push_back(BOOLEAN_VALUE(!AS_NUMBER(right)));
		break;
	default:
		stack.push_back(BOOLEAN_VALUE(false));
		break;
	}

	return VirtualMachineResult::Ok;
}

VirtualMachineResult VirtualMachine::equals_operation() {
	if (stack.size() < 2)
		return VirtualMachineResult::InvalidComparisonOperation;

	Value right = stack[stack.size() - 1];
	stack.pop_back();

	Value left = stack[stack.size() - 1];
	stack.pop_back();

	stack.push_back(BOOLEAN_VALUE(left == right));

	return VirtualMachineResult::Ok;
}

VirtualMachineResult VirtualMachine::notequals_operation() {
	if (stack.size() < 2)
		return VirtualMachineResult::InvalidComparisonOperation;

	Value right = stack[stack.size() - 1];
	stack.pop_back();

	Value left = stack[stack.size() - 1];
	stack.pop_back();

	stack.push_back(BOOLEAN_VALUE(left != right));

	return VirtualMachineResult::Ok;
}

VirtualMachineResult VirtualMachine::greaterthan_operation() {
	if (stack.size() < 2)
		return VirtualMachineResult::InvalidComparisonOperation;

	Value right = stack[stack.size() - 1];
	stack.pop_back();

	Value left = stack[stack.size() - 1];
	stack.pop_back();

	if (!IS_NUMBER(right) || !IS_NUMBER(left))
		return VirtualMachineResult::InvalidComparisonOperation;

	stack.push_back(BOOLEAN_VALUE(left > right));

	return VirtualMachineResult::Ok;
}

VirtualMachineResult VirtualMachine::lessthan_operation() {
	if (stack.size() < 2)
		return VirtualMachineResult::InvalidComparisonOperation;

	Value right = stack[stack.size() - 1];
	stack.pop_back();

	Value left = stack[stack.size() - 1];
	stack.pop_back();

	if (!IS_NUMBER(right) || !IS_NUMBER(left))
		return VirtualMachineResult::InvalidComparisonOperation;

	stack.push_back(BOOLEAN_VALUE(left < right));

	return VirtualMachineResult::Ok;
}
