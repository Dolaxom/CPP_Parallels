#include "graph.h"

#include <fstream>

namespace s21 {
S21Graph::S21Graph(uint32_t size) { initGraph(size); }

void S21Graph::initGraph(uint32_t size) {
  adjacencyMatrix_.resize(size);

  for (auto& v : adjacencyMatrix_) {
    v.resize(size);
  }
}

double& S21Graph::operator()(int i, int j) {
  return adjacencyMatrix_.at(i).at(j);
}
S21Graph S21Graph::S21LoadGraphFromFile(const std::string& filepath) {
  int size{};

  std::ifstream file(filepath);
  if (!file.is_open()) {
    throw std::invalid_argument("Wrong path to matrix file");
  }

  file >> size;
  S21Graph graph(size);

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      file >> graph(i, j);
    }
  }

  return graph;
}

}  // namespace s21