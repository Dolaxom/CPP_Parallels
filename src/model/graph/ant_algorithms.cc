#include "ant_algorithms.h"

#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <random>
#include <stdexcept>

using value = uint32_t;
using leftBorder = double;
using rightBorder = double;
using interval = std::pair<leftBorder, rightBorder>;

namespace s21 {
S21Algorithms::S21Algorithms()
    : synchronousTime_{0},
      asynchronousTime_{0},
      pheromoneInitial_{0.1},
      antParams_{3.0, 1.0, 4.0, 0.1, 5000} {
  graphGet = std::bind(&S21Graph::operator(), graph_.get(), std::placeholders::_1, std::placeholders::_2);
}

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

  S21TsmResult result;

  uint32_t numAnts = graph_->S21Size();
  uint32_t numVertices = graph_->S21Size();

  int startVertex = 0;
  for (uint32_t i = 0; i < antParams_.iterationsCount; ++i) {
    for (uint32_t ant = 0; ant < numAnts; ++ant) {
      if (startVertex >= numAnts) {
        startVertex = 0;
      }

      std::vector<uint32_t> path;
      double pathLength{};
      path.push_back(startVertex++);

      while (path.size() < numVertices) {
        uint32_t currentVertex = path.back();
        uint32_t nextVertex{};
        // helper for nextVertex
        std::vector<std::pair<value, interval>> valueIntervals;

        // Calculate next vertex
        // Считаем знаменатель из тех, кого нет в path (общий для всех)

        double denominator{0.0};
        for (int m = 0; m < graph_->S21Size(); ++m) {
          if (std::find(path.begin(), path.end(), m) == path.end()) {
            if (graph_->operator()(currentVertex, m) == 0.0) continue;
            double pheromone = std::pow(pheromoneMatrix_[currentVertex][m], antParams_.alpha);
            double length = 1.0 / std::pow(graph_->operator()(currentVertex, m), antParams_.beta);
            denominator += pheromone * length;
          }
        }

        // Считаем каждый P(i, j) кого нет в path и записываем в массив

        double p{0.0};
        for (int m = 0; m < graph_->S21Size(); ++m) {
          if (std::find(path.begin(), path.end(), m) == path.end()) {
            if (graph_->operator()(currentVertex, m) == 0.0) continue;
            double pheromone = std::pow(pheromoneMatrix_[currentVertex][m], antParams_.alpha);
            double length = 1.0 / std::pow(graph_->operator()(currentVertex, m), antParams_.beta);
            p = (pheromone * length) / denominator;

            // Считаем интервайлы и кладём p в массив
            double left, right;
            if (valueIntervals.empty()) {
              left = 0;
            } else {
              left = valueIntervals.back().second.second;
            }
            right = left + p;

            valueIntervals.emplace_back(m, std::make_pair(left, right));
          }
        }

        // Выбираем рандомом точку
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> dis(0.0, 1.0);
        double randomValue = dis(gen);

        // Ищем эту точку
        for (auto& valueInterval : valueIntervals) {
          if (randomValue >= valueInterval.second.first && randomValue <= valueInterval.second.second) {
            nextVertex = valueInterval.first;
          }
        }

        pathLength += graph_->operator()(path.back(), nextVertex);
        path.push_back(nextVertex);
      } // while (path.size() < numVertices)

      // Обновляем феромон
      int it1 = 0;
      int it2 = 1;

      while (it2 != path.size()) {
        pheromoneMatrix_[path[it1]][path[it2]] += (antParams_.q / pathLength);
        ++it1;
        ++it2;
      }

      result.vertices = path;
      result.distance = pathLength;
    } // for (uint32_t ant = 0; ant < numAnts; ++ant)
  } // for (uint32_t i = 0; i < antParams_.iterationsCount; ++i)

  result.distance += graph_->operator()(result.vertices.back(), --startVertex);
  result.vertices.push_back(startVertex);

  return result;
}

S21Algorithms::S21TsmResult S21Algorithms::S21AsynchronousAntAlgorithm() {
  if (graph_ == nullptr) {
    S21SetPath();
    S21InitPheromoneMatrix();
  }

  return {};
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

}  // namespace s21
