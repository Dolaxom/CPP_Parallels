#ifndef SRC_MODEL_GRAPH_ALGORITHMS_H
#define SRC_MODEL_GRAPH_ALGORITHMS_H

#include <memory>
#include <string>
#include <vector>

#include "graph.h"

namespace s21 {

class S21Algorithms {
  struct S21TsmResult;
  struct S21AntAlgorithmParameters;

 public:
  S21Algorithms();

  S21TsmResult S21SynchronousAntAlgorithm();
  S21TsmResult S21AsynchronousAntAlgorithm();
  void S21OutputTimes() const;

 private:
  std::unique_ptr<S21Graph> graph_;
  std::vector<std::vector<double>> pheromoneMatrix_;
  long long synchronousTime_;
  long long asynchronousTime_;
  double pheromoneInitial_;

  void S21SetPath();
  void S21InitPheromoneMatrix();
  double S21ProbabilityOfMoving(int i, int j, double alpha, double beta);
  void S21PheromoneAddition();

  struct S21TsmResult {
    std::vector<int> vertices;
    double distance;
  };

  struct S21Solve {
    std::vector<uint32_t> route;
    double pathLength;
    double pheromone;
  };

  struct S21AntAlgorithmParameters {
    double alpha;
    double beta;
    double q;
    double p;
    uint32_t iterationsCount;
  };

  S21AntAlgorithmParameters antParams_;
};

}  // namespace s21

#endif  // SRC_MODEL_GRAPH_ALGORITHMS_H
