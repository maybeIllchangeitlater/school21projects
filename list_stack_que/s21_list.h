#ifndef CPP2_S21_CONTAINERS_SRC_S21_LIST_H_
#define CPP2_S21_CONTAINERS_SRC_S21_LIST_H_

#include <algorithm>
#include <cmath>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <limits>
#include <memory>
#include <optional>
#include <type_traits>
#include <utility>

namespace S21 {
template <typename T>
class BlockNodeAllocator;

template <typename T, typename Allocator = BlockNodeAllocator<T>>
class list;

struct BaseNode {
  BaseNode *next_ = nullptr;
  BaseNode *prev_ = nullptr;
  bool free_ = false;
};

template <typename T>
struct Node : public BaseNode {
  T data_;

  explicit Node(T value) : data_(value) {}

  void InsertNode(Node *prev, Node *next) noexcept {
    BaseNode::prev_ = prev;
    BaseNode::next_ = next;
    prev->BaseNode::next_ = this;
    next->BaseNode::prev_ = this;
  }
};

template <typename T>
class BlockNodeAllocator {
 public:
  using value_type = T;
  using size_type = size_t;
  using propagate_on_container_copy_assignmen = std::true_type;
  using propagate_on_container_move_assignment = std::true_type;
  using propagate_on_container_swap = std::true_type;
  using is_always_equal = std::true_type;

  constexpr BlockNodeAllocator() = default;

  ~BlockNodeAllocator() {
    for (size_type i = 0; i < block_counter_; ++i) {
      for (size_type j = 0;
           i == block_counter_ - 1 ? j < node_counter_ : j < kBlock_size_;
           ++j) {
        if (!(i == 0 && j == 0) && !block_[i][j].free_) block_[i][j].data_.~T();
      }
      ::operator delete(block_[i]);
    }
    block_counter_ = 0;
    node_counter_ = 0;
  }

  Node<value_type> *allocate() {
    if (yeet_counter_) return Reuse();

    if (block_counter_ == 0 || node_counter_ == kBlock_size_) AddBlock();

    return &block_[block_counter_ - 1][node_counter_++];
  }

  template <typename... Args>
  void construct(Node<value_type> *spawn, Args &&...args) {
    new (&spawn->data_) T(std::forward<Args>(args)...);
    spawn->free_ = false;
  }

  void destroy(Node<value_type> *yeet) noexcept {
    yeet->data_.~T();
    yeet->free_ = true;
    ++yeet_counter_;
  }

 private:
  constexpr static const size_type kBlock_size_ = 100;

  Node<value_type> *Reuse() noexcept {
    for (size_type i = 0; i < block_counter_; ++i) {
      for (size_type j = 0;
           i == block_counter_ - 1 ? j < node_counter_ : j < kBlock_size_;
           ++j) {
        if (!(i == 0 && j == 0) && block_[i][j].free_) {
          --yeet_counter_;
          block_[i][j].free_ = false;
          return &block_[i][j];
        }
      }
    }
    return nullptr;  // kostyl for no return from non-void function never going
                     // to happen // NodeT()
  }

  void AddBlock() {
    block_[block_counter_] = static_cast<Node<value_type> *>(
        ::operator new(kBlock_size_ * sizeof(Node<value_type>)));
    node_counter_ = 0;
    ++block_counter_;
  }

  Node<value_type> *block_[100];
  size_type block_counter_ = 0;
  size_type node_counter_ = 0;
  size_type yeet_counter_ = 0;
};

template <typename T, typename Allocator>
class list {
 public:
  class LstIteratorConst;
  class LstIterator;

  using value_type = T;
  using size_type = size_t;
  using iterator = LstIterator;
  using const_iterator = LstIteratorConst;
  using reference = T &;
  using const_reference = const T &;
  using pointer = T *;
  using const_pointer = const T *;
  using allocator_type = BlockNodeAllocator<T>;

  class LstIteratorConst {
   public:
    using value_type = T;
    using iterator = LstIterator;
    using const_iterator = LstIteratorConst;
    using reference = T &;
    using const_reference = const T &;
    using pointer = T *;
    using const_pointer = const T *;
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;

    constexpr LstIteratorConst() = default;

    explicit LstIteratorConst(BaseNode *node) : current_(node) {}

    typename list<value_type>::LstIteratorConst &operator++() noexcept {
      current_ = current_->next_;
      return *this;
    }

    typename list<value_type>::LstIteratorConst &operator--() noexcept {
      current_ = current_->prev_;
      return *this;
    }

    typename list<value_type>::LstIteratorConst operator++(int) noexcept {
      LstIteratorConst tmp = *this;
      ++(*this);
      return tmp;
    }

    typename list<value_type>::LstIteratorConst operator--(int) noexcept {
      LstIteratorConst tmp = *this;
      --(*this);
      return tmp;
    }

    const_reference operator*() const noexcept {
      return static_cast<Node<value_type> *>(current_)->data_;
    }

    const_pointer operator->() const noexcept {
      return &(static_cast<Node<value_type> *>(current_)->data_);
    }

    bool operator==(const LstIteratorConst &other) const noexcept {
      return current_ == other.current_;
    }

    bool operator!=(const LstIteratorConst &other) const noexcept {
      return current_ != other.current_;
    }

    operator iterator() { return iterator(current_); }

   private:
    friend class list;

    BaseNode *current_;
  };

  class LstIterator {
   public:
    using value_type = T;
    using iterator = LstIterator;
    using const_iterator = LstIteratorConst;
    using reference = T &;
    using const_reference = const T &;
    using pointer = T *;
    using const_pointer = const T *;
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;

    constexpr LstIterator() = default;

    explicit LstIterator(BaseNode *node) : current_(node) {}

    typename list<value_type>::LstIterator &operator++() noexcept {
      current_ = current_->next_;
      return *this;
    }

    typename list<value_type>::LstIterator &operator--() noexcept {
      current_ = current_->prev_;
      return *this;
    }

    typename list<value_type>::LstIterator operator++(int) noexcept {
      LstIterator tmp = *this;
      ++(*this);
      return tmp;
    }

    typename list<value_type>::LstIterator operator--(int) noexcept {
      LstIterator tmp = *this;
      --(*this);
      return tmp;
    }

    operator const_iterator() const { return const_iterator(current_); }

    reference operator*() noexcept {
      return static_cast<Node<value_type> *>(current_)->data_;
    }

    pointer operator->() noexcept {
      return &(static_cast<Node<value_type> *>(current_)->data_);
    }

    bool operator==(const LstIterator &other) const noexcept {
      return current_ == other.current_;
    }
    bool operator!=(const LstIterator &other) const noexcept {
      return current_ != other.current_;
    }

   private:
    friend class list;

    BaseNode *current_;
  };

  list() : list_size_(0) {
    phantom_node_ = allocator_.allocate();
    static_cast<Node<value_type> *>(phantom_node_)
        ->InsertNode(static_cast<Node<value_type> *>(phantom_node_),
                     static_cast<Node<value_type> *>(phantom_node_));
  }

  explicit list(size_type n) : list() {
    for (size_type i = 0; i < n; ++i) {
      if constexpr (!std::is_default_constructible_v<value_type> ||
                    !std::is_copy_constructible_v<value_type>) {
        BaseNode *baza = allocator_.allocate();
        static_cast<Node<value_type> *>(baza)->InsertNode(
            static_cast<Node<value_type> *>(phantom_node_),
            static_cast<Node<value_type> *>(phantom_node_->next_));
      } else {
        push_back(value_type{});
      }
    }
  }

  explicit list(std::initializer_list<value_type> const &items) : list() {
    for (const_reference val : items) push_back(val);
  }

  list(const list &other) : list() {
    for (const_reference val : other) push_back(val);
  }

  list(list &&other)
      : list_size_(other.list_size_),
        phantom_node_(std::move(other.phantom_node_)) {
    other.list_size_ = 0, other.phantom_node_ = nullptr;
  }

  list &operator=(const list &other) {
    if constexpr (std::is_copy_constructible_v<value_type>) {
      if (this != &other) {
        clear();
        for (const_reference val : other) push_back(val);
      }
    }
    return *this;
  }

  list &operator=(list &&other) {
    list_size_ = other.list_size_;
    phantom_node_ = std::move(other.phantom_node_);
    other.list_size_ = 0;
    other.phantom_node_ = nullptr;
    return *this;
  }

  ~list() {}

  friend bool operator<(const list &lhs, const list &rhs) {
    return lhs.list_size_ < rhs.list_size_;
  }

  void clear() {
    while (list_size_) pop_back();
  }

  reference front() {
    return static_cast<Node<value_type> *>(phantom_node_->next_)->data_;
  }

  const_reference front() const {
    return static_cast<Node<value_type> *>(phantom_node_->next_)->data_;
  }

  reference back() {
    return static_cast<Node<value_type> *>(phantom_node_->prev_)->data_;
  }

  const_reference &back() const {
    return static_cast<Node<value_type> *>(phantom_node_->prev_)->data_;
  }

  size_type size() const { return list_size_; }

  bool empty() const { return !(list_size_); }

  iterator begin() { return iterator(phantom_node_->next_); }

  iterator end() { return iterator(phantom_node_); }

  const_iterator begin() const { return const_iterator(phantom_node_->next_); }

  const_iterator end() const { return const_iterator(phantom_node_); }

  const_iterator cbegin() const { return const_iterator(phantom_node_->next_); }

  const_iterator cend() const { return const_iterator(phantom_node_); }

  void push_back(const_reference value) {
    Node<value_type> *new_node = allocator_.allocate();
    allocator_.construct(new_node, value);
    if (!list_size_) {
      new_node->InsertNode(static_cast<Node<value_type> *>(phantom_node_),
                           static_cast<Node<value_type> *>(phantom_node_));
    } else {
      new_node->InsertNode(
          static_cast<Node<value_type> *>(phantom_node_->prev_),
          static_cast<Node<value_type> *>(phantom_node_));
      phantom_node_->prev_ = new_node;
    }
    ++list_size_;
  }

  void pop_back() noexcept {
    if (list_size_) {
      Node<value_type> *tmp =
          static_cast<Node<value_type> *>(phantom_node_->prev_->prev_);
      tmp->next_ = phantom_node_;
      allocator_.destroy(static_cast<Node<value_type> *>(phantom_node_->prev_));
      phantom_node_->prev_ = tmp;
      --list_size_;
      if (!list_size_) {
        phantom_node_->next_ = tmp;
      }
    }
  }

  void push_front(const_reference value) {
    Node<value_type> *new_node = allocator_.allocate();
    allocator_.construct(new_node, value);
    if (!list_size_) {
      new_node->InsertNode(static_cast<Node<value_type> *>(phantom_node_),
                           static_cast<Node<value_type> *>(phantom_node_));
    } else {
      new_node->InsertNode(
          static_cast<Node<value_type> *>(phantom_node_),
          static_cast<Node<value_type> *>(phantom_node_->next_));
      phantom_node_->next_ = new_node;
    }
    ++list_size_;
  }

  void pop_front() noexcept {
    if (list_size_) {
      Node<value_type> *tmp =
          static_cast<Node<value_type> *>(phantom_node_->next_->next_);
      tmp->prev_ = static_cast<Node<value_type> *>(phantom_node_);
      allocator_.destroy(static_cast<Node<value_type> *>(phantom_node_->next_));
      static_cast<Node<value_type> *>(phantom_node_)->next_ = tmp;
      --list_size_;
      if (!list_size_) {
        static_cast<Node<value_type> *>(phantom_node_)->prev_ = tmp;
      }
    }
  }

  void resize(int counter) {
    if (counter < 0) return;
    size_type count = static_cast<int>(counter);
    if (count == list_size_) return;
    if (count == 0) clear();
    while (count < list_size_) pop_back();
    while (count > list_size_) push_back(T{});
  }

  void erase(iterator target) noexcept {
    if (target.current_ == phantom_node_) return;
    target.current_->prev_->next_ = target.current_->next_;
    target.current_->next_->prev_ = target.current_->prev_;
    allocator_.destroy(static_cast<Node<value_type> *>(target.current_));
    --list_size_;
  }

  iterator insert(iterator target, const_reference value) {
    Node<value_type> *new_node = allocator_.allocate();
    allocator_.construct(new_node, value);
    new_node->InsertNode(
        static_cast<Node<value_type> *>(target.current_->prev_),
        static_cast<Node<value_type> *>(target.current_));
    ++list_size_;
    return --target;
  }

  void unique() noexcept {
    if (list_size_ < 2) return;
    Node<value_type> *current =
        static_cast<Node<value_type> *>(phantom_node_->next_);
    Node<value_type> *prev = static_cast<Node<value_type> *>(phantom_node_);
    while (current->next_ != phantom_node_) {
      if (current->data_ ==
          static_cast<Node<value_type> *>(current->next_)->data_) {
        Node<value_type> *next_node =
            static_cast<Node<value_type> *>(current->next_);
        prev->next_ = next_node;
        next_node->prev_ = prev;
        allocator_.destroy(current);
        current = next_node;
        --list_size_;
      } else {
        prev = current;
        current = static_cast<Node<value_type> *>(current->next_);
      }
    }
  }

  void reverse() noexcept {
    if (list_size_ < 2) return;
    Node<value_type> *current =
        static_cast<Node<value_type> *>(phantom_node_->next_);
    Node<value_type> *prev = nullptr;
    Node<value_type> *next = nullptr;
    while (current != phantom_node_) {
      next = static_cast<Node<value_type> *>(current->next_);
      prev = static_cast<Node<value_type> *>(current->prev_);
      current->next_ = prev;
      current->prev_ = next;
      current = next;
    }
    Node<value_type> *tmp =
        static_cast<Node<value_type> *>(phantom_node_->next_);
    static_cast<Node<value_type> *>(phantom_node_)->next_ =
        static_cast<Node<value_type> *>(phantom_node_->prev_);
    static_cast<Node<value_type> *>(phantom_node_)->prev_ = tmp;
  }

  void sort(std::less<value_type> cmp = std::less<value_type>{}) {
    typename list<value_type>::iterator it_begin = begin();
    typename list<value_type>::iterator it_ends = end();
    MergeSort(it_begin, it_ends, cmp);
  }

  void merge(list &other) noexcept {
    Node<value_type> *tmp =
        static_cast<Node<value_type> *>(phantom_node_->next_);
    Node<value_type> *tmpo =
        static_cast<Node<value_type> *>(other.phantom_node_->next_);
    while (tmp != phantom_node_ && tmpo != other.phantom_node_) {
      if (tmp->data_ >= tmpo->data_) {
        Node<value_type> *temp = tmpo;
        tmpo = static_cast<Node<value_type> *>(tmpo->next_);
        temp->InsertNode(static_cast<Node<value_type> *>(tmp->prev_), tmp);
      } else {
        tmp = static_cast<Node<value_type> *>(tmp->next_);
      }
    }
    while (tmpo != other.phantom_node_) {
      Node<value_type> *temp = tmpo;
      tmpo = static_cast<Node<value_type> *>(tmpo->next_);
      temp->InsertNode(static_cast<Node<value_type> *>(phantom_node_->prev_),
                       static_cast<Node<value_type> *>(phantom_node_));
      phantom_node_->prev_ = temp;
    }
    list_size_ += other.list_size_;
    other.list_size_ = 0;
  }

  constexpr void splice(const_iterator pos, list &other) noexcept {
    pos.current_->prev_->next_ = other.phantom_node_->next_;
    other.phantom_node_->next_->prev_ = pos.current_->prev_;
    pos.current_->prev_ = other.phantom_node_->prev_;
    other.phantom_node_->prev_->next_ = pos.current_;
    list_size_ += other.list_size_;
    other.list_size_ = 0;
  }

  void swap(list &other) { std::swap(*this, other); }

  constexpr size_type max_size() const {
    return std::numeric_limits<size_type>::max() / sizeof(value_type);
  }

  template <typename... Args>
  void insert_many_front(Args &&...args) {
    (push_back(std::forward<Args>(args)), ...);
  }

  template <typename... Args>
  void insert_many_back(Args &&...args) {
    (push_front(std::forward<Args>(args)), ...);
  }

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args) {
    auto iter = (insert(pos, std::forward<Args>(args)), ...);
    return iter;
  }

 private:
  void MergeSort(iterator begin, iterator last, std::less<value_type> cmp) {
    const auto n = std::distance(begin, last);
    if (n > 1) {
      const auto middle = std::next(begin, n / 2);
      MergeSort(begin, middle, cmp);
      MergeSort(middle, last, cmp);
      std::inplace_merge(begin, middle, last, cmp);
    }
  }

  size_type list_size_ = 0;
  BaseNode *phantom_node_;
  allocator_type allocator_;
};
}  // namespace S21
#endif  // CPP2_S21_CONTAINERS_SRC_S21_LIST_H_
// nihuyz ne delat'+
