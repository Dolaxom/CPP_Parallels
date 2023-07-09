#include "parallels.h"

namespace s21 {
S21Parallels::S21Parallels()
    : graphAlgorithms_{std::make_unique<S21Algorithms>()},
      view_{std::make_unique<S21View>("Parallels")} {
  S21FillSelectorsName();

  view_->S21AddComponent(selectorsName_.at(0), [this]() {
    graphAlgorithms_->S21SynchronousAntAlgorithm();
  });

  view_->S21AddComponent(selectorsName_.at(1), [this]() {
    graphAlgorithms_->S21AsynchronousAntAlgorithm();
  });

  view_->S21AddComponent(selectorsName_.at(2),
                         [this]() { graphAlgorithms_->S21OutputTimes(); });

  view_->S21Run();
}

void S21Parallels::S21FillSelectorsName() {
  selectorsName_ = {
      "Solving the Traveling Salesman problem with synchronous ant algorithm",
      "Solving the Traveling Salesman problem with asynchronous ant algorithm",
      "Output the execution time of both algorithms"};
}
}  // namespace s21