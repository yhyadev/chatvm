#include "chunk.hpp"
#include "vm.hpp"
#include <iostream>

int main() {
	Chunk chunk;

	VirtualMachine vm(chunk);

	VirtualMachineResult result = vm.run();

	if (result != VirtualMachineResult::Ok) {
		std::cerr << "vm error: " << virtual_machine_result_as_string(result)
				  << "\n";
	}
}
