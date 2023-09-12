#ifndef CPP2_S21_CONTAINERS_SRC_S21_QUEUE_H_
#define CPP2_S21_CONTAINERS_SRC_S21_QUEUE_H_

#include "s21_list.h"

namespace S21 {

template <class T, class Container = S21::list<T>>
class queue {
 public:
  using container_type = Container;
  using value_type = typename Container::value_type;
  using size_type = typename Container::size_type;
  using reference = typename Container::reference;
  using const_reference = typename Container::const_reference;

  queue() : head_() {}

  explicit queue(std::initializer_list<value_type> il) : head_(il) {}

  queue(const queue &other) : head_(other.head_) {}

  queue(queue &&other) : head_(std::move(other.head_)) {}

  queue operator=(const queue &other) {
    head_ = other.head_;
    return *this;
  }
  queue operator=(queue &&other) {
    head_ = other.head_;
    return *this;
  }
  ~queue() {}

  const_reference front() const noexcept { return head_.front(); }

  const_reference back() const noexcept { return head_.back(); }

  bool empty() const noexcept { return head_.empty(); }

  size_type size() const noexcept { return head_.size(); }

  void push(const_reference value) { head_.push_back(value); }

  void pop() noexcept { head_.pop_front(); }

  template <typename... Args>
  void insert_many_front(Args &&...args) {
    (head_.push_back(std::forward<Args>(args)), ...);
  }

  void swap(queue &other) { head_.swap(other.head_); }

  constexpr void max_size() const noexcept { head_.max_size(); }

 private:
  container_type head_;
};
}  // namespace S21
#endif  // CPP2_S21_CONTAINERS_SRC_S21_QUEUE_H_
