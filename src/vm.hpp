#pragma once

#include "chunk.hpp"
#include "value.hpp"

#include <string>
#include <vector>

enum VirtualMachineResult {
	InvalidUnaryOperation,
	InvalidArithmeticOperation,
	InvalidComparisonOperation,
	InvalidInstruction,
	Ok,
};

std::string vmr_as_string(VirtualMachineResult);

class VirtualMachine {
  public:
	VirtualMachine(Chunk);

	VirtualMachineResult run();

	VirtualMachineResult addition_operation();
	VirtualMachineResult subtraction_operation();
	VirtualMachineResult multiplication_operation();
	VirtualMachineResult division_operation();
	VirtualMachineResult modulo_operation();

	VirtualMachineResult logical_not_operation();

	VirtualMachineResult equals_operation();
	VirtualMachineResult notequals_operation();
	VirtualMachineResult greaterthan_operation();
	VirtualMachineResult lessthan_operation();

	void load_constant(std::any);
	void print_stack();

  private:
	Chunk chunk;
	unsigned long pc;
	bool halt;

	std::vector<Value> stack;
};
