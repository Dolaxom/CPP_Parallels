#include <iostream>
#include <stdexcept>
#include <chrono>

#include "algorithms.h"

namespace s21 {
S21Algorithms::S21Algorithms() : synchronousTime_{0}, asynchronousTime_{0} {}

void S21Algorithms::S21OutputTimes() const {
  std::cout << "Synchronous time: " << synchronousTime_ << " ns\n"
            << "Asynchronous time: " << asynchronousTime_ << " ns\n"
            << "Difference in time: " << synchronousTime_ - asynchronousTime_
            << " ns.";
}

S21Algorithms::S21TsmResult S21Algorithms::S21SynchronousAntAlgorithm() {
  if (graph == nullptr) {
    S21SetPath();
  }

  auto startTime = std::chrono::steady_clock::now();

  // TODO delete output later
  std::cout << "aboba\n";
  for (int i = 0; i < graph->S21Size(); i++) {
    for (int j = 0; j < graph->S21Size(); j++) {
      std::cout << (*graph)(i, j);
    }
    std::cout << std::endl;
  }

  auto endTime = std::chrono::steady_clock::now();
  auto elapsedNanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
  synchronousTime_ = elapsedNanoseconds.count();

  return {};
}

S21Algorithms::S21TsmResult S21Algorithms::S21AsynchronousAntAlgorithm() {
  if (graph == nullptr) {
    S21SetPath();
  }

  auto startTime = std::chrono::steady_clock::now();

  auto endTime = std::chrono::steady_clock::now();
  auto elapsedNanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
  asynchronousTime_ = elapsedNanoseconds.count();

  return {};
}

void S21Algorithms::S21SetPath() {
  std::string path;
  std::cout << "Set path for graph:\n";
  std::cin >> path;

  try {
    graph = std::make_unique<S21Graph>(S21Graph::S21LoadGraphFromFile(path));
  } catch (std::logic_error &e) {
    graph = nullptr;
    throw e;
  }

}

}  // namespace s21
