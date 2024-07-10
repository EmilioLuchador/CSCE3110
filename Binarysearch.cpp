// Binary Search in C++
#include<vector>

#include <iostream>

#include<ctime>

#include<random>

#include<algorithm>

#include<unistd.h>

using namespace std;

int binarySearch(int array[], int x, int low, int high) {
  if (high >= low) {
    int mid = low + (high - low) / 2;

    // If found at mid, then return it
    if (array[mid] == x)
      return mid;

    // Search the left half
    if (array[mid] > x)
      return binarySearch(array, x, low, mid - 1);

    // Search the right half
    return binarySearch(array, x, mid + 1, high);
  }

  return -1;
}

int main(void) {
  srand(time_t(0));

  //generate(v.begin(), v.end(), rand);

  clock_t _start = clock();
  int array[2500];
  for (int i=0;i<(sizeof(array)/sizeof(int));i++) {
    array[i]=i;
  }
  int x = 1;
  int n = sizeof(array) / sizeof(array[0]);
  int result = binarySearch(array, x, 0, n - 1);
  if (result == -1)
    printf("Not found\n");
  else
    printf("Element is found at index %d\n", result);
  clock_t _end = clock();
  std::cout << "Time taken for searching " << sizeof(array)/sizeof(int) << " item n: " << ((_end - _start)/CLOCKS_PER_SEC) << " seconds" << std::endl;

}