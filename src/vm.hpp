#pragma once

#include "chunk.hpp"
#include "value.hpp"

#include <string>
#include <vector>

enum VirtualMachineResult { Ok, InvalidArithmeticOperation };

std::string virtual_machine_result_as_string(VirtualMachineResult);

class VirtualMachine {
  public:
	VirtualMachine(Chunk);

	VirtualMachineResult run();

	void load_constant(Value);
	void print_stack();

	VirtualMachineResult addition_operation();
	VirtualMachineResult subtraction_operation();
	VirtualMachineResult multiplication_operation();
	VirtualMachineResult division_operation();
	VirtualMachineResult modulo_operation();

  private:
	Chunk chunk;
	unsigned long pc;
	bool halt;

	std::vector<Value> stack;
};
