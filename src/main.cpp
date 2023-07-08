#include <iostream>
#include "view/view.h"
#include "model/graph/graph.h"

void printAboba() {
  std::cout << "Aboba aboba aboba\n";
}

void printFlex() {
  std::cout << "Flex Flex Flex\n";
}

int main() {
  s21::S21Graph graph = s21::S21Graph::S21LoadGraphFromFile("test.txt");

  s21::S21View view("Parallels");
  view.S21AddComponent("Print aboba", printAboba);
  view.S21AddComponent("Print flex", printFlex);
  view.S21Run();

  return 0;
}
