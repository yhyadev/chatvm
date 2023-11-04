#pragma once

#include "chunk.hpp"
#include "value.hpp"
#include <vector>

class VirtualMachine {
  public:
	VirtualMachine(Chunk);

	void run();

  private:
	Chunk chunk;
	unsigned long pc;
	bool halt;

	std::vector<Value> stack;
};
