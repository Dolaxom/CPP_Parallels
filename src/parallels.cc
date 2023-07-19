#include "parallels.h"

namespace s21 {
S21Parallels::S21Parallels() {
  graphAlgorithms_ = std::make_unique<S21Algorithms>();
  view_ = std::make_unique<S21View>("Parallels");

  AddViewComponents();
  view_->S21Run();
}

void S21Parallels::AddViewComponents() {
  view_->S21AddComponent("Solving the Traveling Salesman problem with synchronous ant algorithm", [this]() {
    graphAlgorithms_->S21SynchronousAntAlgorithm();
  });

  view_->S21AddComponent("Solving the Traveling Salesman problem with asynchronous ant algorithm", [this]() {
    graphAlgorithms_->S21AsynchronousAntAlgorithm();
  });

  view_->S21AddComponent("Output the execution time of both algorithms", [this]() {
    graphAlgorithms_->S21OutputTimes();
  });
}
}  // namespace s21