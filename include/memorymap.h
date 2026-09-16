#ifndef MEMORYMAP_H
#define MEMORYMAP_H

#include <array>

unsigned int makeBlock(unsigned int pid, unsigned int payload);

unsigned int getPid(unsigned int block);

unsigned int getPayload(unsigned int block);
 
unsigned int countFreeBlocks(
    const std::array<unsigned int, 16>& memory);

unsigned int* findFreeBlock(
    std::array<unsigned int, 16>& memory);

void allocateBlock(
    unsigned int& block,
    unsigned int pid,
    unsigned int payload);

void freeBlock(unsigned int& block);

#endif  // MEMORYMAP_H
