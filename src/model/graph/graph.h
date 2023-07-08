#ifndef SRC_MODEL_GRAPH_GRAPH_H
#define SRC_MODEL_GRAPH_GRAPH_H

#include <cstdint>
#include <vector>
#include <string>

namespace s21 {

class S21Graph {
 public:
  S21Graph() = delete;
  explicit S21Graph(uint32_t size);
  double& operator()(int i, int j);

  static S21Graph S21LoadGraphFromFile(const std::string& filepath);

 private:
  std::vector<std::vector<double>> adjacencyMatrix_;

  void initGraph(uint32_t size);
};

}  // namespace s21

#endif  // SRC_MODEL_GRAPH_GRAPH_H
