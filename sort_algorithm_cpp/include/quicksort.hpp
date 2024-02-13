#pragma once

#include <vector>

int Partition(std::vector<int> &sequence, const int l, const int r) {
  const int pivot = sequence[r];

  int i = l;
  int j = r - 1;

  while (true) {
    while (sequence[i] < pivot) {
      ++i;
    }

    while (i < j and pivot < sequence[j]) {
      --j;
    }

    if (i >= j) {
      break;
    }

    std::swap(sequence[i], sequence[j]);
  }

  std::swap(sequence[i], sequence[r]);

  return i;
}

void QuickSortRecursive(std::vector<int> &sequence, const int l, const int r) {
  if (l >= r) {
    return;
  }

  const auto p = Partition(sequence, l, r);

  QuickSortRecursive(sequence, l, p - 1);
  QuickSortRecursive(sequence, p + 1, r);
}

void QuickSort(std::vector<int> &sequence) {
  QuickSortRecursive(sequence, 0, sequence.size() - 1);
}
