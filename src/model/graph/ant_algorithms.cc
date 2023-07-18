#include "ant_algorithms.h"

#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <random>
#include <stdexcept>

namespace s21 {
S21Algorithms::S21Algorithms()
    : synchronousTime_{0},
      asynchronousTime_{0},
      pheromoneInitial_{0.5},
      antParams_{1.0, 1.0, 4.0, 0.1, 200} {}

void S21Algorithms::S21OutputTimes() const {
  std::cout << "Synchronous time: " << synchronousTime_ << " ns\n"
            << "Asynchronous time: " << asynchronousTime_ << " ns\n"
            << "Difference in time: " << synchronousTime_ - asynchronousTime_
            << " ns.";
}

S21Algorithms::S21TsmResult S21Algorithms::S21SynchronousAntAlgorithm() {
  if (graph_ == nullptr) {
    S21SetPath();
    S21InitPheromoneMatrix();
  }

  uint32_t antsCount = graph_->S21Size();
  std::vector<S21Solve> solve(antsCount);

  auto startTime = std::chrono::steady_clock::now();

  for (uint32_t i = 0; i < antParams_.iterationsCount; ++i) {
    for (uint32_t ant = 0; ant < antsCount; ++ant) {
      std::vector<uint32_t> tabu = {0};         // Start with vertex 0
      std::vector<uint32_t> availableVertices;  // Corrected initialization

      for (uint32_t j = 1; j < graph_->S21Size(); ++j) {  // Start from 1, not 0
        availableVertices.push_back(j);
      }

      while (availableVertices.size() > 0) {
        uint32_t currentVertex = tabu.back();
        std::vector<std::pair<double, double>> probabilityResults;

        // Calculate probabilities of moving to available vertices
        double totalProbability = 0.0;
        for (uint32_t j : availableVertices) {
          double probability = S21ProbabilityOfMoving(
              currentVertex, j, antParams_.alpha, antParams_.beta, tabu);
          probabilityResults.emplace_back(totalProbability,
                                          totalProbability + probability);
          totalProbability += probability;
        }

        // Choose the next vertex based on probabilities
        double randomValue = (double)rand() / RAND_MAX;
        uint32_t nextVertex =
            availableVertices[0];  // Default to the first available vertex
        for (uint32_t j = 0; j < probabilityResults.size(); ++j) {
          if (randomValue >= probabilityResults[j].first &&
              randomValue < probabilityResults[j].second) {
            nextVertex = availableVertices[j];
            break;
          }
        }

        // Move to the next vertex and update tabu and availableVertices
        tabu.push_back(nextVertex);
        availableVertices.erase(
            std::remove(availableVertices.begin(), availableVertices.end(),
                        nextVertex),
            availableVertices.end());
      }

      // Calculate the total path length for the ant's route
      double totalPathLength = 0.0;
      for (uint32_t j = 1; j < tabu.size(); ++j) {
        totalPathLength += (*graph_)(tabu[j - 1], tabu[j]);
      }

      solve[ant] = {std::move(tabu), totalPathLength,
                    antParams_.q / totalPathLength};
    }

    // Update pheromone matrix
    S21PheromoneAddition(solve);

    if (i == antParams_.iterationsCount - 1) continue;
    for (auto& s : solve) s.route.clear();
  }

  // Find the best solution
  double bestDistance = std::numeric_limits<double>::max();
  std::vector<uint32_t> bestRoute;

  for (const auto& s : solve) {
    if (s.pathLength < bestDistance) {
      bestDistance = s.pathLength;
      bestRoute = s.route;
    }
  }

  // Return the best result
  S21TsmResult result;
  result.distance = bestDistance;
  result.vertices = bestRoute;

  auto endTime = std::chrono::steady_clock::now();
  auto elapsedNanoseconds =
      std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
  synchronousTime_ = elapsedNanoseconds.count();

  return result;
}

void S21Algorithms::S21PheromoneAddition(const std::vector<S21Solve>& solve) {
  for (const auto& s : solve) {
    for (uint32_t i = 0; i < s.route.size() - 1; ++i) {
      uint32_t from = s.route[i];
      uint32_t to = s.route[i + 1];
      pheromoneMatrix_[from][to] += s.pheromone;
      pheromoneMatrix_[to][from] +=
          s.pheromone;  // Assuming the graph is undirected
    }
  }
}

double S21Algorithms::S21ProbabilityOfMoving(
    int i, int j, double alpha, double beta,
    const std::vector<uint32_t>& tabu) {
  double pheromone = pheromoneMatrix_[i][j];
  double distance = (*graph_)(i, j);

  if (pheromone == 0.0) {
    pheromone = 0.0001;
  }

  if (std::find(tabu.begin(), tabu.end(), j) != tabu.end()) {
    return 0.0;
  }

  double probability =
      std::pow(pheromone, alpha) * std::pow(1.0 / distance, beta);

  return probability;
}

void S21Algorithms::S21SetPath() {
  std::string path;
  std::cout << "Set path for graph_:\n";
  std::cin >> path;

  try {
    graph_ = std::make_unique<S21Graph>(S21Graph::S21LoadGraphFromFile(path));
  } catch (std::logic_error& e) {
    graph_ = nullptr;
    throw e;
  }
}

void S21Algorithms::S21InitPheromoneMatrix() {
  pheromoneMatrix_.resize(graph_->S21Size());
  for (auto& v : pheromoneMatrix_) {
    v.resize(graph_->S21Size());
    std::fill(v.begin(), v.end(), pheromoneInitial_);
  }
}

S21Algorithms::S21TsmResult S21Algorithms::S21AsynchronousAntAlgorithm() {
  return {};
}

}  // namespace s21
