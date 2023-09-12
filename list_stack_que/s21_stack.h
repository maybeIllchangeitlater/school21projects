#ifndef CPP2_S21_CONTAINERS_SRC_S21_STACK_H_
#define CPP2_S21_CONTAINERS_SRC_S21_STACK_H_

#include "s21_list.h"

namespace S21 {

template <class T, class Container = S21::list<T>>
class stack {
 public:
  using container_type = Container;
  using value_type = typename Container::value_type;
  using size_type = typename Container::size_type;
  using reference = typename Container::reference;
  using const_reference = typename Container::const_reference;

  stack() : head_() {}

  explicit stack(std::initializer_list<value_type> il) : head_(il) {}

  stack(const stack &other) : head_(other.head_) {}

  stack(stack &&other) noexcept : head_(std::move(other.head_)) {}

  stack operator=(const stack &other) {
    head_ = other.head_;
    return *this;
  }
  stack operator=(stack &&other) {
    head_ = other.head_;
    return *this;
  }

  ~stack() {}

  const_reference top() const noexcept { return head_.back(); }

  bool empty() const noexcept { return head_.empty(); }

  size_type size() const noexcept { return head_.size(); }

  void push(const_reference value) { head_.push_back(value); }

  void pop() noexcept { head_.pop_back(); }

  template <typename... Args>
  void insert_many_front(Args &&...args) {
    (head_.push_back(std::forward<Args>(args)), ...);
  }

  void swap(stack &other) { head_.swap(other.head_); }

  constexpr void max_size() const { head_.max_size(); }

 private:
  container_type head_;
};
}  // namespace S21
#endif  // CPP2_S21_CONTAINERS_SRC_S21_STACK_H_
