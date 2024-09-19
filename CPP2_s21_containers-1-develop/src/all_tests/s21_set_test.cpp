#include <gtest/gtest.h>

#include "../s21_containers.h"

TEST(SetTest, InsertAndAccess) {
  s21::Set<int> my_set;
  my_set.insert(1);
  my_set.insert(2);
  my_set.insert(3);

  auto it = my_set.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
}

TEST(SetTest, Erase) {
  s21::Set<int> my_set;
  my_set.insert(1);
  my_set.insert(2);
  my_set.insert(3);

  my_set.erase(2);

  EXPECT_EQ(static_cast<int>(my_set.size()), 2);
  EXPECT_EQ(*my_set.begin(), 1);
  auto it = my_set.begin();
  ++it;
  EXPECT_EQ(*it, 3);
}

TEST(SetTest, Clear) {
  s21::Set<int> my_set;
  my_set.insert(1);
  my_set.insert(2);

  my_set.clear();

  EXPECT_EQ(static_cast<int>(my_set.size()), 0);
  EXPECT_TRUE(my_set.empty());
}

TEST(SetTest, CopyConstructor) {
  s21::Set<int> original_set;
  original_set.insert(1);
  original_set.insert(2);

  s21::Set<int> copied_set = original_set;

  EXPECT_EQ(static_cast<int>(copied_set.size()), 2);
  auto it = copied_set.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
}

TEST(SetTest, MoveConstructor) {
  s21::Set<int> original_set;
  original_set.insert(1);
  original_set.insert(2);

  s21::Set<int> moved_set = std::move(original_set);

  EXPECT_EQ(static_cast<int>(moved_set.size()), 2);
  auto it = moved_set.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  EXPECT_TRUE(original_set.empty());
}

TEST(SetTest, AssignmentOperator) {
  s21::Set<int> original_set;
  original_set.insert(1);
  original_set.insert(2);

  s21::Set<int> assigned_set;
  assigned_set = original_set;

  EXPECT_EQ(static_cast<int>(assigned_set.size()), 2);
  auto it = assigned_set.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
}

TEST(SetTest, MoveAssignmentOperator) {
  s21::Set<int> original_set;
  original_set.insert(1);
  original_set.insert(2);

  s21::Set<int> moved_set;
  moved_set = std::move(original_set);

  EXPECT_EQ(static_cast<int>(moved_set.size()), 2);
  auto it = moved_set.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  EXPECT_TRUE(original_set.empty());
}

TEST(SetTest, Iterator) {
  s21::Set<int> my_set;
  my_set.insert(1);
  my_set.insert(2);
  my_set.insert(3);

  auto it = my_set.begin();
  EXPECT_EQ(*it, 1);

  ++it;
  EXPECT_EQ(*it, 2);

  ++it;
  EXPECT_EQ(*it, 3);

  ++it;
  EXPECT_EQ(it, my_set.end());
}

TEST(SetTest, InsertDuplicateKey) {
  s21::Set<int> my_set;
  my_set.insert(1);
  bool inserted = my_set.insert(1);

  EXPECT_EQ(static_cast<int>(my_set.size()), 1);
  EXPECT_FALSE(inserted);
}

TEST(SetTest, LargeNumberOfElements) {
  s21::Set<int> my_set;
  for (int i = 0; i < 1000; ++i) {
    my_set.insert(i);
  }

  EXPECT_EQ(static_cast<int>(my_set.size()), 1000);
  int i = 0;
  for (auto it = my_set.begin(); it != my_set.end(); ++it, ++i) {
    EXPECT_EQ(*it, i);
  }
}

TEST(SetTest, ClearAndReinsert) {
  s21::Set<int> my_set;
  my_set.insert(1);
  my_set.insert(2);

  my_set.clear();
  EXPECT_EQ(static_cast<int>(my_set.size()), 0);
  EXPECT_TRUE(my_set.empty());

  my_set.insert(3);
  EXPECT_EQ(static_cast<int>(my_set.size()), 1);
  EXPECT_EQ(*my_set.begin(), 3);
}

TEST(SetTest, EmptySet) {
  s21::Set<int> my_set;
  EXPECT_TRUE(my_set.empty());
  EXPECT_EQ(static_cast<int>(my_set.size()), 0);
}

TEST(SetTest, EraseNonExistentKey) {
  s21::Set<int> my_set;
  my_set.insert(1);
  my_set.insert(2);

  my_set.erase(3);  // Erase non-existent key
  EXPECT_EQ(static_cast<int>(my_set.size()), 2);
  EXPECT_EQ(*my_set.begin(), 1);
  auto it = my_set.begin();
  ++it;
  EXPECT_EQ(*it, 2);
}

TEST(SetTest, IteratorEquality) {
  s21::Set<int> my_set;
  my_set.insert(1);
  my_set.insert(2);

  auto it1 = my_set.begin();
  auto it2 = my_set.begin();

  EXPECT_EQ(it1, it2);
  ++it1;
  EXPECT_NE(it1, it2);
  ++it2;
  EXPECT_EQ(it1, it2);
}

TEST(SetTest, NestedSet) {
  s21::Set<s21::Set<int>> nested_set;
  s21::Set<int> inner_set;
  inner_set.insert(1);
  inner_set.insert(2);
  nested_set.insert(inner_set);

  auto it = nested_set.begin();
  EXPECT_EQ(static_cast<int>((*it).size()), 2);
  EXPECT_EQ(*(*it).begin(), 1);
}

TEST(SetTest, IteratorIncrementDecrement) {
  s21::Set<int> my_set;
  my_set.insert(1);
  my_set.insert(2);
  my_set.insert(3);

  auto it = my_set.begin();
  EXPECT_EQ(*it, 1);

  ++it;
  EXPECT_EQ(*it, 2);

  ++it;
  EXPECT_EQ(*it, 3);

  --it;
  EXPECT_EQ(*it, 2);

  --it;
  EXPECT_EQ(*it, 1);
}

TEST(SetTest, AssignToSelf) {
  s21::Set<int> my_set;
  my_set.insert(1);
  my_set.insert(2);

  // Simulate self-assignment without triggering the compiler warning
  s21::Set<int>& ref_set = my_set;
  my_set = ref_set;

  EXPECT_EQ(static_cast<int>(my_set.size()), 2);
  auto it = my_set.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
}

TEST(SetTest, FindNode) {
  s21::Set<int> my_set;
  my_set.insert(1);
  my_set.insert(2);
  my_set.insert(3);

  auto node = my_set.findNodePublic(2);
  ASSERT_NE(node, nullptr);
  EXPECT_EQ(node->data, 2);
}

TEST(SetTest, EraseRootNode) {
  s21::Set<int> my_set;
  my_set.insert(2);
  my_set.insert(1);
  my_set.insert(3);

  my_set.erase(2);
  EXPECT_EQ(static_cast<int>(my_set.size()), 2);
  auto it = my_set.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 3);
}

TEST(SetTest, InsertMany) {
  s21::Set<int> my_set;
  auto results = my_set.insert_many(1, 2, 3, 2, 1);

  EXPECT_EQ(static_cast<int>(my_set.size()), 3);
  EXPECT_EQ(static_cast<int>(results.size()), 5);
  EXPECT_EQ(*results[0].first, 1);
  EXPECT_EQ(*results[1].first, 2);
  EXPECT_EQ(*results[2].first, 3);
  EXPECT_EQ(*results[3].first, 2);
  EXPECT_EQ(*results[4].first, 1);
  EXPECT_TRUE(results[0].second);
  EXPECT_TRUE(results[1].second);
  EXPECT_TRUE(results[2].second);
  EXPECT_FALSE(results[3].second);
  EXPECT_FALSE(results[4].second);
}