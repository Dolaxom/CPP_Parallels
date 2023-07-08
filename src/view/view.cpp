#include "view.h"

#include <iostream>
#include <stdexcept>

namespace s21 {
S21View::S21View(std::string programName)
    : programName_{std::move(programName)}, exitingSelector_{0} {
  std::cout << programName_ << std::endl << std::endl;
}

S21View::S21View(S21View &&other) noexcept : exitingSelector_{0} {
  this->interfaceComponents_ = other.interfaceComponents_;
  this->programName_ = other.programName_;
  other.interfaceComponents_.clear();
  other.programName_.clear();
}

S21View &S21View::operator=(S21View &&other) noexcept {
  this->interfaceComponents_ = other.interfaceComponents_;
  this->programName_ = other.programName_;
  other.interfaceComponents_.clear();
  other.programName_.clear();
  return *this;
}

void S21View::S21Run() {
  try {
    while (true) {
      S21Printing();
      S21ChoiceHandle();
    }
  } catch (...) {
    std::cout << "bye :p";
  }
}

void S21View::S21Printing() {
  if (interfaceComponents_.empty()) {
    throw std::out_of_range("You can't display an empty interface");
  }

  int i{0};
  for (auto &element : interfaceComponents_) {
    std::cout << ++i << ": " << element.first << '\n';
  }
  std::cout << "0: Exit the program\n"
            << "Make a choice:\n";
}

uint32_t S21View::S21MakeChoice() {
  uint32_t result;
  std::cin >> result;
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  return result;
}

void S21View::S21ChoiceHandle() {
  uint32_t choice = S21MakeChoice();
  if (choice == exitingSelector_) {
    throw std::exception();
  }

  --choice;  // Numbering in the interface starts with 1

  try {
    if (choice >= interfaceComponents_.size()) {
      throw std::out_of_range("This menu item is not available");
    }
    interfaceComponents_[choice].second();
  } catch (std::exception &e) {
    std::cerr << e.what() << '\n';
  }

  std::cout << "\n=----------=\n";
}

void S21View::S21AddComponent(const std::string &str,
                              const std::function<void()> &func) {
  interfaceComponents_.emplace_back(str, func);
}

}  // namespace s21