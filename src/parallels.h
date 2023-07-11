#ifndef SRC_PARALLELS_H
#define SRC_PARALLELS_H

#include <memory>
#include <string>
#include <vector>

#include "model/graph/algorithms.h"
#include "view/view.h"

namespace s21 {

class S21Parallels {
 public:
  S21Parallels();

 private:
  std::unique_ptr<S21Algorithms> graphAlgorithms_;
  std::unique_ptr<S21View> view_;

  std::vector<std::string> selectorsName_;
  void AddViewComponents();
};

}  // namespace s21

#endif  // SRC_PARALLELS_H
