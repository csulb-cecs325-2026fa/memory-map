#include "memorymap.h"
// TODO: Return the PID and payload packed into one unsigned int.
unsigned int makeBlock(unsigned int pid, unsigned int payload) {
    return 0;
}

// TODO: Recover the PID from an encoded block.
unsigned int getPid(unsigned int block) {
    return 0;
}

// TODO: Recover the four-bit payload from an encoded block.
unsigned int getPayload(unsigned int block) {
    return 0;
}

// TODO: Count the free blocks without modifying the memory map.
unsigned int countFreeBlocks(
    const std::array<unsigned int, 16>& memory) {
    return 0;
}

// TODO: Return the address of the first free block, or nullptr if none exists.
unsigned int* findFreeBlock(
    std::array<unsigned int, 16>& memory) {
    return nullptr;
}

// TODO: Store an encoded block in the referenced memory block.
void allocateBlock(
    unsigned int& block,
    unsigned int pid,
    unsigned int payload) {
}

// TODO: Mark the referenced memory block as free.
void freeBlock(unsigned int& block) {
}
