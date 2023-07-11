#ifndef SRC_MODEL_GRAPH_ALGORITHMS_H
#define SRC_MODEL_GRAPH_ALGORITHMS_H

#include <vector>
#include <memory>
#include <string>

#include "graph.h"

namespace s21 {

class S21Algorithms {
  struct S21TsmResult;

 public:
  S21Algorithms();

  S21TsmResult S21SynchronousAntAlgorithm();
  S21TsmResult S21AsynchronousAntAlgorithm();
  void S21OutputTimes() const;

 private:
  std::unique_ptr<S21Graph> graph;
  long long synchronousTime_;
  long long  asynchronousTime_;

  struct S21TsmResult {
    std::vector<int> vertices;
    double distance;
  };

  void S21SetPath();
};

}  // namespace s21

#endif  // SRC_MODEL_GRAPH_ALGORITHMS_H
