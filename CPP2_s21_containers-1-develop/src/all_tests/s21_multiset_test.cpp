#include <gtest/gtest.h>

#include "../s21_containersplus.h"

TEST(MultiSetTest, InsertAndAccess) {
  s21::MultiSet<int> my_multiset;
  my_multiset.insert(1);
  my_multiset.insert(2);
  my_multiset.insert(3);

  auto it = my_multiset.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
}

TEST(MultiSetTest, InsertDuplicates) {
  s21::MultiSet<int> my_multiset;
  my_multiset.insert(1);
  my_multiset.insert(1);
  my_multiset.insert(2);
  my_multiset.insert(3);

  EXPECT_EQ(static_cast<int>(my_multiset.size()), 4);
}

TEST(MultiSetTest, Erase) {
  s21::MultiSet<int> my_multiset;
  my_multiset.insert(1);
  my_multiset.insert(2);
  my_multiset.insert(3);

  my_multiset.erase(2);

  EXPECT_EQ(static_cast<int>(my_multiset.size()), 2);
  EXPECT_EQ(*my_multiset.begin(), 1);
  auto it = my_multiset.begin();
  ++it;
  EXPECT_EQ(*it, 3);
}

TEST(MultiSetTest, Clear) {
  s21::MultiSet<int> my_multiset;
  my_multiset.insert(1);
  my_multiset.insert(2);

  my_multiset.clear();

  EXPECT_EQ(static_cast<int>(my_multiset.size()), 0);
  EXPECT_TRUE(my_multiset.empty());
}

TEST(MultiSetTest, CopyConstructor) {
  s21::MultiSet<int> original_multiset;
  original_multiset.insert(1);
  original_multiset.insert(2);

  s21::MultiSet<int> copied_multiset = original_multiset;

  EXPECT_EQ(static_cast<int>(copied_multiset.size()), 2);
  auto it = copied_multiset.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
}

TEST(MultiSetTest, MoveConstructor) {
  s21::MultiSet<int> original_multiset;
  original_multiset.insert(1);
  original_multiset.insert(2);

  s21::MultiSet<int> moved_multiset = std::move(original_multiset);

  EXPECT_EQ(static_cast<int>(moved_multiset.size()), 2);
  auto it = moved_multiset.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  EXPECT_TRUE(original_multiset.empty());
}

TEST(MultiSetTest, AssignmentOperator) {
  s21::MultiSet<int> original_multiset;
  original_multiset.insert(1);
  original_multiset.insert(2);

  s21::MultiSet<int> assigned_multiset;
  assigned_multiset = original_multiset;

  EXPECT_EQ(static_cast<int>(assigned_multiset.size()), 2);
  auto it = assigned_multiset.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
}

TEST(MultiSetTest, MoveAssignmentOperator) {
  s21::MultiSet<int> original_multiset;
  original_multiset.insert(1);
  original_multiset.insert(2);

  s21::MultiSet<int> moved_multiset;
  moved_multiset = std::move(original_multiset);

  EXPECT_EQ(static_cast<int>(moved_multiset.size()), 2);
  auto it = moved_multiset.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  EXPECT_TRUE(original_multiset.empty());
}

TEST(MultiSetTest, Iterator) {
  s21::MultiSet<int> my_multiset;
  my_multiset.insert(1);
  my_multiset.insert(2);
  my_multiset.insert(3);

  auto it = my_multiset.begin();
  EXPECT_EQ(*it, 1);

  ++it;
  EXPECT_EQ(*it, 2);

  ++it;
  EXPECT_EQ(*it, 3);

  ++it;
  EXPECT_EQ(it, my_multiset.end());
}

TEST(MultiSetTest, IteratorIncrementDecrement) {
  s21::MultiSet<int> my_multiset;
  my_multiset.insert(1);
  my_multiset.insert(2);
  my_multiset.insert(3);

  auto it = my_multiset.begin();
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

TEST(MultiSetTest, FindNode) {
  s21::MultiSet<int> my_multiset;
  my_multiset.insert(1);
  my_multiset.insert(2);
  my_multiset.insert(3);

  auto node = my_multiset.findNodePublic(2);
  ASSERT_NE(node, nullptr);
  EXPECT_EQ(node->data, 2);
}

TEST(MultiSetTest, EraseRootNode) {
  s21::MultiSet<int> my_multiset;
  my_multiset.insert(2);
  my_multiset.insert(1);
  my_multiset.insert(3);

  my_multiset.erase(2);
  EXPECT_EQ(static_cast<int>(my_multiset.size()), 2);
  auto it = my_multiset.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 3);
}

TEST(MultiSetTest, InsertMany) {
  s21::MultiSet<int> my_multiset;
  auto results = my_multiset.insert_many(1, 2, 3, 2, 1);

  EXPECT_EQ(static_cast<int>(my_multiset.size()), 5);
  EXPECT_EQ(static_cast<int>(results.size()), 5);
  EXPECT_EQ(*results[0].first, 1);
  EXPECT_EQ(*results[1].first, 2);
  EXPECT_EQ(*results[2].first, 3);
  EXPECT_EQ(*results[3].first, 2);
  EXPECT_EQ(*results[4].first, 1);
  EXPECT_TRUE(results[0].second);
  EXPECT_TRUE(results[1].second);
  EXPECT_TRUE(results[2].second);
  EXPECT_TRUE(results[3].second);
  EXPECT_TRUE(results[4].second);
}
