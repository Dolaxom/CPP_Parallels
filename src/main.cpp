#include <iostream>
#include "view/view.h"
#include "model/graph/graph.h"
#include "model/graph/algorithms.h"

int main() {
  s21::S21Graph graph = s21::S21Graph::S21LoadGraphFromFile("test.txt");
  s21::S21Algorithms algorithm{};

  s21::S21View view("Parallels");
  view.S21AddComponent("Solving the Traveling Salesman problem with synchronous ant algorithm", [&algorithm]() { algorithm.S21SynchronousAntAlgorithm(); });
  view.S21AddComponent("Solving the Traveling Salesman problem with asynchronous ant algorithm", [&algorithm]() { algorithm.S21AsynchronousAntAlgorithm(); });
  view.S21AddComponent("Output the execution time of both algorithms", [&algorithm]() { algorithm.S21OutputTimes(); });

  view.S21Run();

  return 0;
}
