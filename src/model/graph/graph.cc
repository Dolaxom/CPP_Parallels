#include "graph.h"

#include <fstream>
#include <limits>
#include <stdexcept>

namespace s21 {
S21Graph::S21Graph(uint32_t size) { initGraph(size); }

void S21Graph::initGraph(uint32_t size) {
  adjacencyMatrix_.resize(size);

  for (auto& v : adjacencyMatrix_) {
    v.resize(size);
  }
}

double& S21Graph::operator()(uint32_t i, uint32_t j) {
  return adjacencyMatrix_.at(i).at(j);
}

S21Graph S21Graph::S21LoadGraphFromFile(const std::string& filepath) {
  int32_t size{};

  std::ifstream file(filepath);
  if (!file.is_open()) {
    throw std::invalid_argument("Wrong path to matrix file");
  }

  file >> size;
  if (size >= std::numeric_limits<int>::max() || size <= 0) {
    throw std::runtime_error("Invalid graph size");
  }
  S21Graph graph(size);

  for (int32_t i = 0; i < size; i++) {
    for (int32_t j = 0; j < size; j++) {
      file >> graph(i, j);
    }
  }

  return graph;
}

uint32_t S21Graph::S21Size() const { return adjacencyMatrix_.size(); }

}  // namespace s21