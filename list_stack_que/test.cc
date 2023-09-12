#include <gtest/gtest.h>

#include <list>
#include <queue>
#include <stack>

#include "s21_list.h"
#include "s21_stack.h"
#include "s21_queue.h"

TEST(ListConstructors, True) {
  S21::list<int> a;
  std::list<int> aa;
  S21::list<int> b(5);
  std::list<int> bb(5);
  ASSERT_EQ(b.front(), bb.front());
  S21::list<int> c{1, 2, 3, 4, 5};
  std::list<int> cc{1, 2, 3, 4, 5};
  ASSERT_EQ(c.back(), cc.back());
  a = a;
  a = c;
  aa = cc;
  ASSERT_EQ(a.front(), aa.front());
  S21::list<int> d(c);
  std::list<int> dd(cc);
  ASSERT_EQ(d.back(), dd.back());
  S21::list<int> e(std::move(d));
  std::list<int> ee(std::move(dd));
  ASSERT_EQ(e.back(), ee.back());
}

TEST(ListConstructorsNoDefaultConstructor, True) {
  S21::list<std::atomic<int>> a;
  std::list<std::atomic<int>> aa;
  ASSERT_EQ(a.size(), aa.size());
  S21::list<std::atomic<int>> b(5);
  S21::list<std::atomic<int>> e(std::move(a));
  std::list<std::atomic<int>> ee(std::move(aa));
  a = b;
  ASSERT_EQ(e.size(), ee.size());

}  // if you want to run vallgrind tests either add gnu flags or comment this
   // test

TEST(PushPop, True) {
  S21::list<int> a{1, 2, 3, 4, 5};
  std::list<int> aa{1, 2, 3, 4, 5};
  a.pop_back();
  a.pop_back();
  a.pop_front();
  aa.pop_back();
  aa.pop_back();
  aa.pop_front();
  ASSERT_EQ(a.front(), aa.front());
  ASSERT_EQ(a.back(), aa.back());
  a.push_back(-7);
  a.push_front(333);
  aa.push_back(-7);
  aa.push_front(333);
  ASSERT_EQ(a.front(), aa.front());
  ASSERT_EQ(a.back(), aa.back());
  for (int i = 0; i < 15; i++) {
    a.pop_front();
    a.pop_back();
  }
  // original list catches BUSIK here kek
  a.push_front(1);
  a.pop_front();
  aa.clear();
  aa.push_front(1);
  aa.pop_front();
  a.push_front(1);
  aa.push_front(1);
  ASSERT_EQ(a.front(), aa.front());
}

TEST(Insert, True) {
  S21::list<int> a{1, 2, 3, 4, 5};
  std::list<int> aa{1, 2, 3, 4, 5};
  auto it = ++a.begin();
  auto stdit = ++aa.begin();
  auto resa = a.insert(it, 33);
  auto resaa = aa.insert(stdit, 33);
  ASSERT_EQ(*resa, *resaa);
  ASSERT_EQ(*(++a.begin()), *(++aa.begin()));
}
TEST(Erase, True) {
  S21::list<int> a{1, 2, 3, 4, 5};
  std::list<int> aa{1, 2, 3, 4, 5};
  auto it = ++a.begin();
  auto stdit = ++aa.begin();
  a.erase(a.end());
  a.erase(it);
  aa.erase(stdit);
  ASSERT_EQ(*(++a.begin()), *(++aa.begin()));
}

TEST(Unique, True) {
  S21::list<int> a{123, 123, 123, 3, -3, 3, 321, 123, 123, 321, 3, 3};
  std::list<int> aa{123, 123, 123, 3, -3, 3, 321, 123, 123, 321, 3, 3};
  a.unique();
  aa.unique();
  auto it = a.begin();
  auto stdit = aa.begin();
  for (std::size_t i = 0; i < a.size(); ++i, ++it, ++stdit) {
    ASSERT_EQ(*it, *stdit);
  }
  S21::list<int> b{1};
  std::list<int> bb{1};
  b.unique();
  bb.unique();
  ASSERT_EQ(b.front(), bb.front());
}

TEST(Sort, True) {
  S21::list<int> a{123, 123, 123, 3, -3, 3, 321, 123, 123, 321, 3, 3};
  std::list<int> aa{123, 123, 123, 3, -3, 3, 321, 123, 123, 321, 3, 3};
  a.sort();
  aa.sort();
  auto it = a.begin();
  auto stdit = aa.begin();
  for (std::size_t i = 0; i < a.size(); ++i, ++it, ++stdit) {
    ASSERT_EQ(*it, *stdit);
  }
}

TEST(Merge, True) {
  S21::list<int> a{123, 123, 123, 3, -3, 3, 321, 123, 123, 321, 3, 3};
  S21::list<int> b{1231234, 999999, 0, -3, 3, 55};
  std::list<int> aa{123, 123, 123, 3, -3, 3, 321, 123, 123, 321, 3, 3};
  std::list<int> bb{1231234, 999999, 0, -3, 3, 55};
  a.merge(b);
  aa.merge(bb);
  auto it = a.begin();
  auto stdit = aa.begin();
  for (std::size_t i = 0; i < a.size(); ++i, ++it, ++stdit) {
    ASSERT_EQ(*it, *stdit);
  }
  S21::list<int> a1{123, 123, 123, 3, -3, 3, 321, 123, 123, 321, 3, 3};
  S21::list<int> b1{1231234, 999999, 0, -3, 3, 55};
  std::list<int> aa1{123, 123, 123, 3, -3, 3, 321, 123, 123, 321, 3, 3};
  std::list<int> bb1{1231234, 999999, 0, -3, 3, 55};
  a1.sort();
  b1.sort();
  aa1.sort();
  bb1.sort();
  a1.merge(b1);
  aa1.merge(bb1);
  auto it1 = a1.begin();
  auto stdit1 = aa1.begin();
  for (std::size_t i = 0; i < a.size(); ++i, ++it1, ++stdit1) {
    ASSERT_EQ(*it1, *stdit1);
  }
}

TEST(Resize, True) {
  S21::list<int> a{123, 123, 123, 3, -3, 3, 321, 123, 123, 321, 3, 3};
  std::list<int> aa{123, 123, 123, 3, -3, 3, 321, 123, 123, 321, 3, 3};
  a.resize(-1);
  a.resize(140);
  aa.resize(140);
  auto it = a.begin();
  auto stdit = aa.begin();
  for (std::size_t i = 0; i < a.size(); ++i, ++it, ++stdit) {
    ASSERT_EQ(*it, *stdit);
  }
  a.resize(3);
  aa.resize(3);
  it = a.begin();
  stdit = aa.begin();
  for (std::size_t i = 0; i < a.size(); ++i, ++it, ++stdit) {
    ASSERT_EQ(*it, *stdit);
  }
  a.resize(0);
  aa.resize(0);
  ASSERT_EQ(a.empty(), aa.empty());
}

TEST(Reverse, True) {
  S21::list<int> a{123, 123, 123, 3, -3, 3, 321, 123, 123, 321, 3, 3};
  std::list<int> aa{123, 123, 123, 3, -3, 3, 321, 123, 123, 321, 3, 3};
  a.reverse();
  aa.reverse();
  auto it = a.begin();
  auto stdit = aa.begin();
  for (std::size_t i = 0; i < a.size(); ++i, ++it, ++stdit) {
    ASSERT_EQ(*it, *stdit);
  }
  S21::list<int> b{1};
  std::list<int> bb{1};
  b.reverse();
  bb.reverse();
  auto cender = --b.cend();
  ASSERT_EQ(*cender, *bb.begin());
  ASSERT_EQ(b.front(), bb.front());
}

TEST(Swap, True) {
  S21::list<int> a1{123, 123, 123, 3, -3, 3, 321, 123, 123, 321, 3, 3};
  S21::list<int> b1{1231234, 999999, 0, -3, 3, 55};
  std::list<int> aa1{123, 123, 123, 3, -3, 3, 321, 123, 123, 321, 3, 3};
  std::list<int> bb1{1231234, 999999, 0, -3, 3, 55};
  a1.swap(b1);
  aa1.swap(bb1);
  auto it = a1.begin();
  auto stdit = aa1.begin();
  for (std::size_t i = 0; i < a1.size(); ++i, ++it, ++stdit) {
    ASSERT_EQ(*it, *stdit);
  }
  it = b1.begin();
  stdit = bb1.begin();
  for (std::size_t i = 0; i < b1.size(); ++i, ++it, ++stdit) {
    ASSERT_EQ(*it, *stdit);
  }
}

TEST(Insert_many, True) {
  S21::list<int> a{123, 123, 123, 3, -3, 3, 321, 123, 123, 321, 3, 3};
  a.insert_many_back(-7, 0, 22);
  a.insert_many_front(1, 13, 37);
  auto it = a.begin();
  for (int i = 0; i < 4; ++i, ++it) {
  }
  a.insert_many(it, 21, 42);
  it = a.begin();
  for (std::size_t i = 0; i < a.size(); ++i, ++it) {
    if (i == 0) {
      ASSERT_EQ(*it, 22);
    }
    if (i == 1) {
      ASSERT_EQ(*it, 0);
    }
    if (i == 2) {
      ASSERT_EQ(*it, -7);
    }
    if (i == a.size() - 3) {
      ASSERT_EQ(*it, 1);
    }
    if (i == a.size() - 2) {
      ASSERT_EQ(*it, 13);
    }
    if (i == a.size() - 1) {
      ASSERT_EQ(*it, 37);
    }
    if (i == 4) {
      ASSERT_EQ(*it, 21);
    }
    if (i == 5) {
      ASSERT_EQ(*it, 42);
    }
  }
  a.max_size();
}

TEST(Stack, True) {
  S21::stack<int> a;
  std::stack<int> aa;
  S21::stack<int> c(a);
  std::stack<int> cc(aa);
  a = c;
  c = std::move(a);
  S21::stack<int> e(std::move(c));
  std::stack<int> ee(std::move(cc));
  S21::stack<int>
      f{1, 2, 3, 4,
        5, 6, 7};  // default stack cant do it but that's kind of weird
  a.push(7);
  aa.push(7);
  ASSERT_EQ(a.top(), aa.top());
  a.push(22);
  aa.push(22);
  ASSERT_EQ(a.top(), aa.top());
  a.push(-7);
  aa.push(-7);
  ASSERT_EQ(a.top(), aa.top());
  a.pop();
  aa.pop();
  ASSERT_EQ(a.top(), aa.top());
  a.swap(e);
  aa.swap(ee);
  ASSERT_EQ(a.size(), aa.size());
  ASSERT_EQ(a.empty(), true);
  a.max_size();
}

TEST(Huehue, True) {
  S21::queue<int> a;
  std::queue<int> aa;
  a.push(7);
  aa.push(7);
  ASSERT_EQ(a.back(), aa.back());
  ASSERT_EQ(a.front(), aa.front());
  a.push(-7);
  aa.push(-7);
  ASSERT_EQ(a.back(), aa.back());
  ASSERT_EQ(a.front(), aa.front());
  a.push(77);
  aa.push(77);
  ASSERT_EQ(a.back(), aa.back());
  ASSERT_EQ(a.front(), aa.front());
  a.pop();
  aa.pop();
  ASSERT_EQ(a.back(), aa.back());
  ASSERT_EQ(a.front(), aa.front());
  S21::queue<int> b(a);
  std::queue<int> bb(aa);
  ASSERT_EQ(b.back(), bb.back());
  ASSERT_EQ(b.front(), bb.front());
  S21::queue<int> c(std::move(b));
  std::queue<int> cc(std::move(bb));
  ASSERT_EQ(c.back(), cc.back());
  ASSERT_EQ(c.front(), cc.front());
  ASSERT_EQ(c.size(), cc.size());
  ASSERT_EQ(c.empty(), cc.empty());
  S21::queue<int> f{1, 2, 3, 4, 5, 6, 7};
  a.swap(c);
  aa.swap(cc);
  ASSERT_EQ(c.front(), cc.front());
  a = a;
  a = std::move(a);
}

TEST(BigListReuseTest, True) {
  S21::list<int> a;
  for (size_t i = 0; i < 102; ++i) {
    a.push_front(i % 2 * 3);
    a.push_back(i / 2 - i % 3);
  }
  a.pop_back();
  a.pop_back();
  a.pop_back();
  a.push_front(6);
  a.push_back(1);
}

TEST(IteratorOperators, True) {
  S21::list<int> a{1, 2, 3, 4, 5, 6, 7};
  std::list<int> aa{1, 2, 3, 4, 5, 6, 7};
  auto ita = a.begin();
  auto itaa = aa.begin();
  ASSERT_EQ(*(ita++), *(itaa++));
  ASSERT_EQ(*ita, *itaa);
  ASSERT_EQ(*(ita--), *(itaa--));
  ASSERT_EQ(*ita, *itaa);
  const S21::list<int> a1{1, 2, 3, 4, 5, 6, 7};
  const std::list<int> aa1{1, 2, 3, 4, 5, 6, 7};
  auto ita1 = a1.cbegin();
  auto itaa1 = aa1.cbegin();
  ASSERT_EQ(*(ita1++), *(itaa1++));
  ASSERT_EQ(*ita1, *itaa1);
  ASSERT_EQ(*(ita1--), *(itaa1--));
  ASSERT_EQ(*ita1, *itaa1);
  ASSERT_EQ(a1.begin() == a1.begin(), true);
  S21::list<std::string> str{"biba", "booba", "aboba"};
  auto strit = str.begin();
  ASSERT_EQ(strit->compare(*strit), 0);
  const S21::list<std::string> str1{"biba", "booba", "aboba"};
  auto strit1 = str1.begin();
  ASSERT_EQ(strit1->compare(*strit1), 0);
}

TEST(Splice, True) {
  S21::list<int> a{1, 2, 3, 4, 5, 6, 7};
  std::list<int> aa{1, 2, 3, 4, 5, 6, 7};
  S21::list<int> b{-1, -2, -33};
  std::list<int> bb{-1, -2, -33};
  a.splice(a.begin(), b);
  aa.splice(aa.begin(), bb);
  auto it = aa.begin();
  for (const auto val : a) {
    ASSERT_EQ(val, *it++);
  }
}

TEST(ListOfString, True) {
  S21::list<std::string> a;
  std::list<std::string> aa;
  a.push_front("let's");
  aa.push_back("let's");
  a.push_front(" celebrate ");
  aa.push_back(" celebrate ");
  a.push_front("and suck ");
  aa.push_back("and suck ");
  a.push_front("some ");
  aa.push_back("some ");
  a.push_front("dick");
  aa.push_back("dick");
  a.push_front("!");
  aa.push_back("!");
  a.reverse();
  auto it = a.begin();
  for (const auto val : aa) {
    ASSERT_EQ(val, *it++);
  }
  a.sort();
  it = a.begin();
  aa.sort();
  for (const auto val : aa) {
    ASSERT_EQ(val, *it++);
  }
  a.pop_front();
  a.pop_back();
  a.push_front("it gets ");
  a.push_back(" bigger ");
  a.push_back("when I pull");
  aa.pop_front();
  aa.pop_back();
  aa.push_front("it gets ");
  aa.push_back(" bigger ");
  aa.push_back("when I pull");
  a.sort();
  it = a.begin();
  aa.sort();
  for (const auto val : aa) {
    ASSERT_EQ(val, *it++);
  }
}
TEST(ListOfLists, True) {
  S21::list<S21::list<std::string>> ohshit;
  std::list<std::list<std::string>> whatishedoing;
  S21::list<std::string> justwhy{"our dad",       "told",   "us not",
                                 "to be ashamed", "of our", "dicks"};
  std::list<std::string> amidoingthisshit{"our dad",       "told",   "us not",
                                          "to be ashamed", "of our", "dicks"};
  ohshit.push_back(justwhy);
  whatishedoing.push_back(amidoingthisshit);
  justwhy.clear();
  amidoingthisshit.clear();
  justwhy.insert_many_front("let's", "celebrate", "and suck", "some dick");
  amidoingthisshit.push_back("let's");
  amidoingthisshit.push_back("celebrate");
  amidoingthisshit.push_back("and suck");
  amidoingthisshit.push_back("some dick");
  ohshit.push_back(justwhy);
  whatishedoing.push_back(amidoingthisshit);
  justwhy.clear();
  amidoingthisshit.clear();
  justwhy.insert_many_front("dungeon", "master");
  amidoingthisshit.push_back("dungeon");
  amidoingthisshit.push_back("master");
  ohshit.push_back(justwhy);
  whatishedoing.push_back(amidoingthisshit);
  auto it = ohshit.begin();
  auto sit = whatishedoing.begin();
  for (size_t outer = 0; outer < ohshit.size(); ++outer, ++it, ++sit) {
    auto init = it->begin();
    auto insit = sit->begin();
    for (size_t inner = 0; inner < it->size(); ++inner, ++init, ++insit) {
      ASSERT_EQ(*init, *insit);
    }
  }
  whatishedoing.sort();
  ohshit.pop_back();
  ohshit.push_back(justwhy);
  ohshit.sort();
  sit = whatishedoing.begin();
  it = ohshit.begin();
  for (size_t outer = 0; outer < ohshit.size(); ++outer, ++it, ++sit) {
    auto init = it->begin();
    auto insit = sit->begin();
    for (size_t inner = 0; inner < it->size(); ++inner, ++init, ++insit) {
      ASSERT_EQ(*init, *insit);
    }
  }
}
TEST(ListOfListsMixed, True) {
  S21::list<std::list<std::string>> ohshit;
  std::list<S21::list<std::string>> whatishedoing;
  S21::list<std::string> justwhy{"our dad",       "told",   "us not",
                                 "to be ashamed", "of our", "dicks"};
  std::list<std::string> amidoingthisshit{"our dad",       "told",   "us not",
                                          "to be ashamed", "of our", "dicks"};
  ohshit.push_back(amidoingthisshit);
  whatishedoing.push_back(justwhy);
  justwhy.clear();
  amidoingthisshit.clear();
  justwhy.insert_many_front("let's", "celebrate", "and suck", "some dick");
  amidoingthisshit.push_back("let's");
  amidoingthisshit.push_back("celebrate");
  amidoingthisshit.push_back("and suck");
  amidoingthisshit.push_back("some dick");
  ohshit.push_back(amidoingthisshit);
  whatishedoing.push_back(justwhy);
  justwhy.clear();
  amidoingthisshit.clear();
  justwhy.insert_many_front("dungeon", "master");
  amidoingthisshit.push_back("dungeon");
  amidoingthisshit.push_back("master");
  ohshit.push_back(amidoingthisshit);
  whatishedoing.push_back(justwhy);
  auto it = ohshit.begin();
  auto sit = whatishedoing.begin();
  for (size_t outer = 0; outer < ohshit.size(); ++outer, ++it, ++sit) {
    auto init = it->begin();
    auto insit = sit->begin();
    for (size_t inner = 0; inner < it->size(); ++inner, ++init, ++insit) {
      ASSERT_EQ(*init, *insit);
    }
  }
  whatishedoing.sort();
  ohshit.pop_back();
  ohshit.push_back(amidoingthisshit);
  ohshit.sort();
  it = ohshit.begin();
  sit = whatishedoing.begin();
  for (size_t outer = 0; outer < ohshit.size(); ++outer, ++it, ++sit) {
    auto init = it->begin();
    auto insit = sit->begin();
    for (size_t inner = 0; inner < it->size(); ++inner, ++init, ++insit) {
      ASSERT_EQ(*init, *insit);
    }
  }
}


int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
