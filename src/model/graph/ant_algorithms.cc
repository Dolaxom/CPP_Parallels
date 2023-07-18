#include "ant_algorithms.h"

#include <chrono>
#include <cmath>
#include <iostream>
#include <stdexcept>

namespace s21 {
S21Algorithms::S21Algorithms()
    : synchronousTime_{0},
      asynchronousTime_{0},
      pheromoneInitial_{0.5},
      antParams_{1.0, 1.0, 4.0, 0.1, 200} {}

void S21Algorithms::S21OutputTimes() const {
  std::cout << "Synchronous time: " << synchronousTime_ << " ns\n"
            << "Asynchronous time: " << asynchronousTime_ << " ns\n"
            << "Difference in time: " << synchronousTime_ - asynchronousTime_
            << " ns.";
}

S21Algorithms::S21TsmResult S21Algorithms::S21SynchronousAntAlgorithm() {
  if (graph_ == nullptr) {
    S21SetPath();
    S21InitPheromoneMatrix();
  }

  S21Solve solve;

  auto startTime = std::chrono::steady_clock::now();

  for (uint32_t i = 0; i < antParams_.iterationsCount; ++i) {

  }

  auto endTime = std::chrono::steady_clock::now();
  auto elapsedNanoseconds =
      std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
  synchronousTime_ = elapsedNanoseconds.count();

  return {};
}

S21Algorithms::S21TsmResult S21Algorithms::S21AsynchronousAntAlgorithm() {
  if (graph_ == nullptr) {
    S21SetPath();
    S21InitPheromoneMatrix();
  }

  auto startTime = std::chrono::steady_clock::now();

  auto endTime = std::chrono::steady_clock::now();
  auto elapsedNanoseconds =
      std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
  asynchronousTime_ = elapsedNanoseconds.count();

  return {};
}

void S21Algorithms::S21SetPath() {
  std::string path;
  std::cout << "Set path for graph_:\n";
  std::cin >> path;

  try {
    graph_ = std::make_unique<S21Graph>(S21Graph::S21LoadGraphFromFile(path));
  } catch (std::logic_error& e) {
    graph_ = nullptr;
    throw e;
  }
}

void S21Algorithms::S21InitPheromoneMatrix() {
  pheromoneMatrix_.resize(graph_->S21Size());
  for (auto& v : pheromoneMatrix_) {
    v.resize(graph_->S21Size());
    std::fill(v.begin(), v.end(), pheromoneInitial_);
  }
}

double S21Algorithms::S21ProbabilityOfMoving(int i, int j, double alpha,
                                             double beta) {
  double tNumerator = std::pow(pheromoneMatrix_.at(i).at(j), alpha);
  double nNumerator = std::pow(1 / (*graph_)(i, j), beta);

  double sum{0.0};
  for (int m = 0; m < graph_->S21Size(); ++m) {
    double tDenominator = std::pow(pheromoneMatrix_.at(i).at(m), alpha);
    double nDenominator = std::pow(1 / (*graph_)(i, m), beta);
    sum += tDenominator * nDenominator;
  }

  return ((tNumerator * nNumerator) / sum);
}

void S21Algorithms::S21PheromoneAddition() {}

}  // namespace s21
