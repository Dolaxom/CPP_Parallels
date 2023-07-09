#include "parallels.h"

#include "model/graph/algorithms.h"
#include "view/view.h"

namespace s21 {
S21Parallels::S21Parallels() {
  S21FillSelectorsName();

  graphAlgorithms_ = std::make_unique<S21Algorithms>();
  view_ = std::make_unique<S21View>("Parallels");
  view_->S21AddComponent(selectorsName_.at(0), [this]() {
    graphAlgorithms_->S21SynchronousAntAlgorithm();
  });

  view_->S21AddComponent(selectorsName_.at(1), [this]() {
    graphAlgorithms_->S21AsynchronousAntAlgorithm();
  });

  view_->S21AddComponent(selectorsName_.at(2), [this]() {
    graphAlgorithms_->S21OutputTimes();
  });

  view_->S21Run();
}

void S21Parallels::S21FillSelectorsName() {
  selectorsName_.emplace_back(
      "Solving the Traveling Salesman problem with synchronous ant algorithm");
  selectorsName_.emplace_back(
      "Solving the Traveling Salesman problem with asynchronous ant algorithm");
  selectorsName_.emplace_back("Output the execution time of both algorithms");
}
}  // namespace s21