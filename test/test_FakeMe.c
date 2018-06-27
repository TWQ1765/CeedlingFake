#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <malloc.h>

#include "unity.h"
#include "FakeMe.h"
#include "mock_Number.h"

#define FAIL_WITH_MESSAGE(format, ...)  failWithMessage(__LINE__, format, ## __VA_ARGS__)

char *dataPtr = NULL;
int dataSize = 0;
int idx = 0;

void setUp(void) {}

void tearDown(void) {}

void failWithMessage(int line, const char *format, ...) {
  int size;
  char *buffer;
  va_list args;
  va_start (args, format);
  size = vsnprintf (NULL, 0, format, args);
  buffer = (char *)malloc(size + 1);
  vsnprintf(buffer, size + 1, format, args);
  va_end (args);
  UNITY_TEST_FAIL(line, buffer);
}

int fake_getNumber(int NumCalls) {
  if(idx++ < dataSize) {
    return *(dataPtr ++);
  } else {
    FAIL_WITH_MESSAGE("Error: Array out of bound. Requested number more than %d", dataSize);
  }
  return 0;
}

void setupArrayOfNumbersForGetNumber(char array[], int size) {
  dataPtr = array;
  dataSize = size;
  idx = 0;
  getNumber_StubWithCallback(fake_getNumber);
} 

void test_giveMeNumbers_in_a_sequence_of_6_expect_6_7_8_9_10_11(void) {
  char fakeValues[] = {1, 2, 3, 4, 5, 6};
  char expectedValues[] = {6, 7, 8, 9, 10, 11};
  char values[6];
  
  setupArrayOfNumbersForGetNumber(fakeValues, sizeof(fakeValues) / sizeof(char));
  
  giveMeNumbers(values, 6);
      
  TEST_ASSERT_EQUAL_INT8_ARRAY(expectedValues, values, 6);
}
