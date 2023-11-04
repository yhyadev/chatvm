#include "chunk.hpp"
#include "vm.hpp"

int main() {
	Chunk chunk;

	VirtualMachine vm(chunk);

	vm.run();
}
