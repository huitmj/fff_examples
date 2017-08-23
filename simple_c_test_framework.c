#include "fff.h"
#include "c_test_framework.h"

DEFINE_FFF_GLOBALS;

FAKE_VOID_FUNC(io_reset);
FAKE_VALUE_FUNC(unsigned char, io_read, unsigned char);

void setup() {
  RESET_FAKE(io_reset);
  RESET_FAKE(io_read);
  FFF_RESET_HISTORY();
}

void powerOnInit() {
  io_reset();
  io_reset();
}

TEST_F(Test, checkCallCount) {
  powerOnInit();

  ASSERT_EQ(io_reset_fake.call_count,2);
}

TEST_F(Test, singleReturn_checkCallingArgument) {
  io_read_fake.return_val = 0xff;

  assert(io_read(3)==0xff);
  assert(io_read_fake.arg0_val==3);
}

TEST_F(Test,multiReturns) {
  char returnVals[3] = {1,2,3};
  SET_RETURN_SEQ(io_read, returnVals, 3);
  assert(io_read(3)==1);
  assert(io_read(3)==2);
  assert(io_read(3)==3);
}

void main() {
  RUN_TEST(Test, checkCallCount);
  RUN_TEST(Test, singleReturn_checkCallingArgument);
  RUN_TEST(Test, multiReturns);

}
