#include <assert.h>
#include "fff.h"

DEFINE_FFF_GLOBALS;

FAKE_VOID_FUNC(io_reset);
FAKE_VALUE_FUNC(unsigned char, io_read, unsigned char);

void powerOnInit() {
  io_reset();
  io_reset();
}

void checkCallCount() {
  powerOnInit();

  assert(io_reset_fake.call_count==2);
}

void singleReturn_checkCallingArgument() {
  io_read_fake.return_val = 0xff;

  assert(io_read(3)==0xff);
  assert(io_read_fake.arg0_val==3);
}

void multiReturns() {
  char returnVals[3] = {1,2,3};
  SET_RETURN_SEQ(io_read, returnVals, 3);
  assert(io_read(3)==1);
  assert(io_read(3)==2);
  assert(io_read(3)==3);
}

void main() {
  checkCallCount();
  singleReturn_checkCallingArgument();
  multiReturns();

}
