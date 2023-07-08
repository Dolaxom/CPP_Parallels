#ifndef SRC_MODEL_GRAPH_ALGORITHMS_H
#define SRC_MODEL_GRAPH_ALGORITHMS_H

namespace s21 {

class S21Algorithms {
 public:
  S21Algorithms() = default;

  void S21SynchronousAntAlgorithm();
  void S21AsynchronousAntAlgorithm();
  void S21OutputTimes();

 private:
  float synchronousTime_;
  float asynchronousTime_;
};

}  // namespace s21

#endif  // SRC_MODEL_GRAPH_ALGORITHMS_H
