#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define H_ARRAYSIZE(a)                                                         \
  ((sizeof(a) / sizeof(*(a))) /                                                \
   static_cast<size_t>(!(sizeof(a) % sizeof(*(a)))))

/* A structure used for representing mountain */
struct Rectangle {
  int begins;
  int ends;
  int height;
};

int resolve(const char *input) {
  if (input == NULL)
    return 0;

  int number;
  sscanf(input, "%d\n", &number);
  input += 2;

  // check input
  if (number < 0)
    return -1;

  int curLength = 0;        // The longest we can go at the current mountain if not consider the following
  int curHeight = 0;        // The current height we stay at
  int totalHeight = 0;      // How much we go up and down
  Rectangle rect;
  for (int i = 0; i < number; ++i) {
    // Read mountain information
    sscanf(input, "%d,%d,%d\n", &rect.begins, &rect.ends, &rect.height);
    input += 6;

    // check input
    if (rect.begins < 0 || rect.ends < 0 || rect.height < 0)
      return -1;

    if (rect.ends > curLength) {
      // mountain partily acrross
      if (rect.begins <= curLength) {
        // If the next mountain comes before or at the current ends,
        // we only need walk the differnece of two mountain.
        totalHeight += abs(rect.height - curHeight);
      }
      else {
        // Otherwise, we need first go down and the go up.
        totalHeight += (curHeight + rect.height);
      }
      curHeight = rect.height;
      curLength = rect.ends;
    } else {
      // A mountain fully cover anothers
      if (rect.height > curHeight)
        totalHeight += 2 * (rect.height - curHeight);
    }
  }

  totalHeight += curHeight;     // Go down from the last mountain

  return totalHeight + curLength;
}

int main(int argc, char *argv[]) {
  const char *input[] = {
      "3\n1,3,2\n2,4,4\n6,7,5\n", // The giving example
      "1\n1,2,1\n",
      "2\n1,2,1\n2,3,2",
      "3\n1,2,1\n2,3,2\n3,6,1",
      "4\n1,2,1\n2,3,2\n3,6,1\n5,8,2",
      "5\n1,2,1\n2,3,2\n3,6,1\n5,8,2\n7,9,1",
      "1\n0,1,1",
      "2\n0,1,1\n2,4,3",
      "3\n0,1,1\n2,4,3\n3,5,1",
      "4\n0,1,1\n2,4,3\n3,5,1\n5,6,1",
      "5\n0,1,1\n2,4,3\n3,5,1\n5,6,1\n6,8,3",
      // TODO please add more test case here
      "0\n",

      // invalid input
      "-1\n0,1,1",
      "1\n0,1,-1",

      // mountain fully cover anothers
      "3\n0,5,1\n1,2,2\n3,4,2",
      "3\n0,5,1\n1,2,2\n3,5,2",
      "3\n0,5,5\n1,2,2\n3,4,2",   // maybe no sense

      // two mountain starts at the same point
      // or ends at the same point
      "2\n0,1,1\n0,2,2",
      "2\n0,1,2\n0,2,1",
      "2\n0,2,1\n1,2,2",
  };
  int expectedSteps[] = {25, 4, 7, 10, 14, 15, 3, 12, 13, 14, 20, 0, -1, -1, 11, 11, 15, 6, 6, 6};
  for (size_t i = 0; i < H_ARRAYSIZE(input); ++i) {
    assert(resolve(input[i]) == expectedSteps[i]);
  }
  return 0;
}
