#ifndef SRC_MODEL_GRAPH_GRAPH_H
#define SRC_MODEL_GRAPH_GRAPH_H

#include <cstdint>
#include <vector>

namespace s21 {

class S21Graph {
 public:
  S21Graph() = delete;
  S21Graph(uint32_t size);

 private:
  std::vector<std::vector<double>> adjacencyMatrix_;

  void initGraph(uint32_t size);
};

}  // namespace s21

#endif  // SRC_MODEL_GRAPH_GRAPH_H
