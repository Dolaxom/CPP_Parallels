#ifndef SRC_VIEW_VIEW_H
#define SRC_VIEW_VIEW_H

#include <cstdint>
#include <functional>
#include <string>
#include <vector>

namespace s21 {

class S21View {
 public:
  S21View() = delete;
  S21View(const S21View& other) = delete;
  S21View(S21View&& other) noexcept;
  explicit S21View(std::string programName);
  ~S21View() = default;

  S21View& operator=(const S21View& other) = delete;
  S21View& operator=(S21View&& other) noexcept;

  void S21Run();
  void S21AddComponent(const std::string& str,
                       const std::function<void()>& func);

 private:
  std::vector<std::pair<std::string, std::function<void()>>>
      interfaceComponents_;
  std::string programName_;

  const uint32_t exitingSelector_;

  void S21Printing();
  void S21ChoiceHandle();
  uint32_t S21MakeChoice();
};

}  // namespace s21

#endif  // SRC_VIEW_VIEW_H
