#include "graph.h"

namespace s21 {
S21Graph::S21Graph(uint32_t size) { initGraph(size); }

void S21Graph::initGraph(uint32_t size) {
  adjacencyMatrix_.resize(size);

  for (auto& v : adjacencyMatrix_) {
    v.resize(size);
  }
}
}  // namespace s21