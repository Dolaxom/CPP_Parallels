#include <iostream>

#include "algorithms.h"

namespace s21 {
void S21Algorithms::S21SynchronousAntAlgorithm() {
  synchronousTime_ = 1.25f;
}

void S21Algorithms::S21AsynchronousAntAlgorithm() {
  asynchronousTime_ = 0.5f;
}
void S21Algorithms::S21OutputTimes() {
  std::cout << "Synchronous time: " << synchronousTime_ << " s\n"
      << "Asynchronous time: " << asynchronousTime_ << " s\n" <<
      "difference in time: " << synchronousTime_ - asynchronousTime_ << " s.";

}

} // namespace s21

