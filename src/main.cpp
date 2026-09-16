#include "memorymap.h"

#include <array>
#include <iostream>


void printMemory(const std::array<unsigned int, 16>& memory) {
    std::cout << "Free blocks: " << countFreeBlocks(memory) << '\n';

    for (std::size_t index = 0; index < memory.size(); ++index) {
        std::cout << "[" << index << "] ";

        if (memory[index] == 0) {
            std::cout << "free\n";
        } else {
            std::cout << "PID " << getPid(memory[index])
                      << ", payload " << getPayload(memory[index]) << '\n';
        }
    }
}

int main() {
    std::array<unsigned int, 16> memory{};

    std::cout << "Initial memory map\n";
    printMemory(memory);

    if (unsigned int* block = findFreeBlock(memory)) {
        allocateBlock(*block, 12, 5);
    }

    if (unsigned int* block = findFreeBlock(memory)) {
        allocateBlock(*block, 7, 9);
    }

    std::cout << "\nAfter two allocations\n";
    printMemory(memory);

    if (unsigned int* block = findFreeBlock(memory)) {
        freeBlock(*block);
    }

    std::cout << "\nAfter freeing the next available block\n";
    printMemory(memory);
}
