#include <iostream>

#include "algorithms.h"

namespace s21 {
S21Algorithms::S21Algorithms() : synchronousTime_{0.0}, asynchronousTime_{0.0} {}

void S21Algorithms::S21OutputTimes() const {
  std::cout << "Synchronous time: " << synchronousTime_ << " s\n"
            << "Asynchronous time: " << asynchronousTime_ << " s\n"
            << "Difference in time: " << synchronousTime_ - asynchronousTime_
            << " s.";
}

S21Algorithms::S21TsmResult S21Algorithms::S21SynchronousAntAlgorithm() {

  return {};
}

S21Algorithms::S21TsmResult S21Algorithms::S21AsynchronousAntAlgorithm() {
  return {};
}

}  // namespace s21
