/**
 * WARNING TO STUDENTS:
 * DO NOT MODIFY THIS FILE IN ANY WAY. DO NOT LET YOUR EDITOR CHANGE THE INDENTATION,
 * OR ADD BLANK LINES, OR ANY OTHER MODIFICATION OF ANY KIND. THE CLASSROOM 50 AUTOGRADER
 * WILL FAIL YOUR SUBMISSION IF YOU MAKE EVEN A SINGLE INSIGNIFICANT CHANGE.
 *
 * THE SAME IS TRUE FOR THE FILE "vcpkg.json" IN THE ROOT OF THIS PROJECT,
 * AND ANY OTHER FILES IN THE "tests" FOLDER.
 */

#include <gtest/gtest.h>

#include <array>

#include "memorymap.h"

// These tests call your functions directly instead of checking printed output.
// EXPECT_* records a failure and continues the test. ASSERT_* records a failure
// and stops the current test when the rest of the test cannot continue safely.



// Purpose: Verify the exact bit layout required for one allocated block.
// Debugging hint: Compare the actual value with (pid << 4) | payload. The
// payload occupies the four low bits, so make sure the shift happens first.
TEST(MemoryMapEncoding, MakeBlockPacksPidAndPayload) {
  EXPECT_EQ(makeBlock(12, 5), ((12u << 4u) | 5u));
}

// Purpose: Verify that getPid removes the four payload bits and returns the
// original process ID.
// Debugging hint: If this fails after MakeBlockPacksPidAndPayload also fails,
// fix makeBlock first. Otherwise, check that the encoded block is shifted right
// by four bits rather than shifted left.
TEST(MemoryMapEncoding, GetPidExtractsPid) {
  EXPECT_EQ(getPid(makeBlock(37, 14)), 37u);
}

// Purpose: Verify that getPayload keeps only the four low bits of a block.
// Debugging hint: The usual mask is 0xF. A mask is important here because a
// right shift would extract the PID instead of the payload.
TEST(MemoryMapEncoding, GetPayloadExtractsLowFourBits) {
  EXPECT_EQ(getPayload(makeBlock(37, 14)), 14u);
}

// Purpose: Count zero-valued blocks while proving that the function does not
// change the array it receives through a const reference.
// Debugging hint: In this setup, 3 of 16 blocks are allocated, so the answer
// must be 13. An allocated block with payload 0 is still nonzero and is not
// free.
TEST(MemoryMap, CountFreeBlocksDoesNotModifyMemory) {
  std::array<unsigned int, 16> memory{};
  memory[0] = makeBlock(1, 3);
  memory[3] = makeBlock(2, 0);
  memory[15] = makeBlock(3, 15);
  const auto original = memory;

  EXPECT_EQ(countFreeBlocks(memory), 13u);
  EXPECT_EQ(memory, original);
}

// Purpose: Find the first available array element and return its actual address.
// Debugging hint: The first free element is memory[1], not just any free
// element. The assignment through *result checks that the returned pointer
// aliases the original array rather than pointing to a temporary copy.
TEST(MemoryMap, FindFreeBlockReturnsFirstFreeElement) {
  std::array<unsigned int, 16> memory{};
  memory[0] = makeBlock(1, 3);
  memory[3] = makeBlock(2, 0);

  unsigned int* result = findFreeBlock(memory);

  ASSERT_EQ(result, &memory[1]);
  *result = makeBlock(9, 4);
  EXPECT_EQ(memory[1], makeBlock(9, 4));
}

// Purpose: Verify the “not found” case: a completely occupied memory map has
// no valid element address to return.
// Debugging hint: The correct result is nullptr. If your function returns a
// pointer, check the free-block test. A block containing PID 1 and payload 0
// is makeBlock(1, 0), which should not be confused with the free value 0.
TEST(MemoryMap, FindFreeBlockReturnsNullptrWhenFull) {
  std::array<unsigned int, 16> memory{};
  memory.fill(makeBlock(1, 0));

  EXPECT_EQ(findFreeBlock(memory), nullptr);
}

// Purpose: Verify reference semantics: allocateBlock must change the caller's
// variable, not a local copy of it.
// Debugging hint: If block is still 0, check the ampersand in the parameter
// type and make sure the function assigns makeBlock(pid, payload) to block.
TEST(MemoryMap, AllocateBlockChangesReferencedBlock) {
  unsigned int block = 0;

  allocateBlock(block, 42, 15);

  EXPECT_EQ(block, makeBlock(42, 15));
}

// Purpose: Verify that freeing a block changes the caller's variable to the
// special value 0 used to represent a free block.
// Debugging hint: If the value does not change, check that block is passed by
// reference and that the function assigns 0 rather than returning 0.
TEST(MemoryMap, FreeBlockClearsReferencedBlock) {
  unsigned int block = makeBlock(42, 15);

  freeBlock(block);

  EXPECT_EQ(block, 0u);
}
