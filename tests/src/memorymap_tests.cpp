#include <gtest/gtest.h>

#include <array>

#include "memorymap.h"

TEST(MemoryMapEncoding, MakeBlockPacksPidAndPayload) {
  EXPECT_EQ(makeBlock(12, 5), ((12u << 4u) | 5u));
}

TEST(MemoryMapEncoding, GetPidExtractsPid) {
  EXPECT_EQ(getPid(makeBlock(37, 14)), 37u);
}

TEST(MemoryMapEncoding, GetPayloadExtractsLowFourBits) {
  EXPECT_EQ(getPayload(makeBlock(37, 14)), 14u);
}

TEST(MemoryMap, CountFreeBlocksDoesNotModifyMemory) {
  std::array<unsigned int, 16> memory{};
  memory[0] = makeBlock(1, 3);
  memory[3] = makeBlock(2, 0);
  memory[15] = makeBlock(3, 15);
  const auto original = memory;

  EXPECT_EQ(countFreeBlocks(memory), 13u);
  EXPECT_EQ(memory, original);
}

TEST(MemoryMap, FindFreeBlockReturnsFirstFreeElement) {
  std::array<unsigned int, 16> memory{};
  memory[0] = makeBlock(1, 3);
  memory[3] = makeBlock(2, 0);

  unsigned int* result = findFreeBlock(memory);

  ASSERT_EQ(result, &memory[1]);
  *result = makeBlock(9, 4);
  EXPECT_EQ(memory[1], makeBlock(9, 4));
}

TEST(MemoryMap, FindFreeBlockReturnsNullptrWhenFull) {
  std::array<unsigned int, 16> memory{};
  memory.fill(makeBlock(1, 0));

  EXPECT_EQ(findFreeBlock(memory), nullptr);
}

TEST(MemoryMap, AllocateBlockChangesReferencedBlock) {
  unsigned int block = 0;

  allocateBlock(block, 42, 15);

  EXPECT_EQ(block, makeBlock(42, 15));
}

TEST(MemoryMap, FreeBlockClearsReferencedBlock) {
  unsigned int block = makeBlock(42, 15);

  freeBlock(block);

  EXPECT_EQ(block, 0u);
}
