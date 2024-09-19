#include <gtest/gtest.h>

#include "../s21_containers.h"

TEST(MapTest, InsertAndAccess) {
  s21::Map<int, std::string> my_map;
  my_map.insert(1, "one");
  my_map.insert(2, "two");
  my_map.insert(3, "three");

  auto it = my_map.begin();
  EXPECT_EQ(it->second, "one");
  ++it;
  EXPECT_EQ(it->second, "two");
  ++it;
  EXPECT_EQ(it->second, "three");
}

TEST(MapTest, InsertDuplicates) {
  s21::Map<int, std::string> my_map;
  EXPECT_TRUE(my_map.insert(1, "one"));
  EXPECT_FALSE(my_map.insert(1, "uno"));
  EXPECT_TRUE(my_map.insert(2, "two"));
  EXPECT_TRUE(my_map.insert(3, "three"));

  EXPECT_EQ(static_cast<int>(my_map.size()), 3);
}

TEST(MapTest, Erase) {
  s21::Map<int, std::string> my_map;
  my_map.insert(1, "one");
  my_map.insert(2, "two");
  my_map.insert(3, "three");

  my_map.erase(2);

  EXPECT_EQ(static_cast<int>(my_map.size()), 2);
  EXPECT_EQ(my_map.at(1), "one");
  EXPECT_EQ(my_map.at(3), "three");
}

TEST(MapTest, Clear) {
  s21::Map<int, std::string> my_map;
  my_map.insert(1, "one");
  my_map.insert(2, "two");

  my_map.clear();

  EXPECT_EQ(static_cast<int>(my_map.size()), 0);
  EXPECT_TRUE(my_map.empty());
}

TEST(MapTest, CopyConstructor) {
  s21::Map<int, std::string> original_map;
  original_map.insert(1, "one");
  original_map.insert(2, "two");

  s21::Map<int, std::string> copied_map = original_map;

  EXPECT_EQ(static_cast<int>(copied_map.size()), 2);
  EXPECT_EQ(copied_map.at(1), "one");
  EXPECT_EQ(copied_map.at(2), "two");
}

TEST(MapTest, MoveConstructor) {
  s21::Map<int, std::string> original_map;
  original_map.insert(1, "one");
  original_map.insert(2, "two");

  s21::Map<int, std::string> moved_map = std::move(original_map);

  EXPECT_EQ(static_cast<int>(moved_map.size()), 2);
  EXPECT_EQ(moved_map.at(1), "one");
  EXPECT_EQ(moved_map.at(2), "two");
  EXPECT_TRUE(original_map.empty());
}

TEST(MapTest, AssignmentOperator) {
  s21::Map<int, std::string> original_map;
  original_map.insert(1, "one");
  original_map.insert(2, "two");

  s21::Map<int, std::string> assigned_map;
  assigned_map = original_map;

  EXPECT_EQ(static_cast<int>(assigned_map.size()), 2);
  EXPECT_EQ(assigned_map.at(1), "one");
  EXPECT_EQ(assigned_map.at(2), "two");
}

TEST(MapTest, MoveAssignmentOperator) {
  s21::Map<int, std::string> original_map;
  original_map.insert(1, "one");
  original_map.insert(2, "two");

  s21::Map<int, std::string> moved_map;
  moved_map = std::move(original_map);

  EXPECT_EQ(static_cast<int>(moved_map.size()), 2);
  EXPECT_EQ(moved_map.at(1), "one");
  EXPECT_EQ(moved_map.at(2), "two");
  EXPECT_TRUE(original_map.empty());
}

TEST(MapTest, Iterator) {
  s21::Map<int, std::string> my_map;
  my_map.insert(1, "one");
  my_map.insert(2, "two");
  my_map.insert(3, "three");

  auto it = my_map.begin();
  EXPECT_EQ(it->second, "one");

  ++it;
  EXPECT_EQ(it->second, "two");

  ++it;
  EXPECT_EQ(it->second, "three");

  ++it;
  EXPECT_EQ(it, my_map.end());
}

TEST(MapTest, IteratorIncrementDecrement) {
  s21::Map<int, std::string> my_map;
  my_map.insert(1, "one");
  my_map.insert(2, "two");
  my_map.insert(3, "three");

  auto it = my_map.begin();
  EXPECT_EQ(it->second, "one");

  ++it;
  EXPECT_EQ(it->second, "two");

  ++it;
  EXPECT_EQ(it->second, "three");

  --it;
  EXPECT_EQ(it->second, "two");

  --it;
  EXPECT_EQ(it->second, "one");
}

TEST(MapTest, FindNode) {
  s21::Map<int, std::string> my_map;
  my_map.insert(1, "one");
  my_map.insert(2, "two");
  my_map.insert(3, "three");

  auto node = my_map.findNodePublic(2);
  ASSERT_NE(node, nullptr);
  EXPECT_EQ(node->data.second, "two");
}

TEST(MapTest, EraseRootNode) {
  s21::Map<int, std::string> my_map;
  my_map.insert(2, "two");
  my_map.insert(1, "one");
  my_map.insert(3, "three");

  my_map.erase(2);
  EXPECT_EQ(static_cast<int>(my_map.size()), 2);
  EXPECT_EQ(my_map.at(1), "one");
  EXPECT_EQ(my_map.at(3), "three");
}

TEST(MapTest, InsertMany) {
  s21::Map<int, std::string> my_map;
  auto results =
      my_map.insert_many(std::make_pair(1, "one"), std::make_pair(2, "two"),
                         std::make_pair(3, "three"), std::make_pair(2, "dos"),
                         std::make_pair(1, "uno"));

  EXPECT_EQ(static_cast<int>(my_map.size()), 3);
  EXPECT_EQ(static_cast<int>(results.size()), 5);
  EXPECT_EQ(results[0].first->second, "one");
  EXPECT_EQ(results[1].first->second, "two");
  EXPECT_EQ(results[2].first->second, "three");
  EXPECT_EQ(results[3].first->second, "two");
  EXPECT_EQ(results[4].first->second, "one");
  EXPECT_TRUE(results[0].second);
  EXPECT_TRUE(results[1].second);
  EXPECT_TRUE(results[2].second);
  EXPECT_FALSE(results[3].second);
  EXPECT_FALSE(results[4].second);
}

TEST(MapTest, MultipleInserts) {
  s21::Map<int, std::string> my_map;
  my_map.insert(10, "ten");
  my_map.insert(20, "twenty");
  my_map.insert(30, "thirty");
  my_map.insert(40, "forty");

  EXPECT_EQ(static_cast<int>(my_map.size()), 4);
  EXPECT_EQ(my_map.at(10), "ten");
  EXPECT_EQ(my_map.at(20), "twenty");
  EXPECT_EQ(my_map.at(30), "thirty");
  EXPECT_EQ(my_map.at(40), "forty");
}

TEST(MapTest, EraseNonExistent) {
  s21::Map<int, std::string> my_map;
  my_map.insert(1, "one");
  my_map.insert(2, "two");
  my_map.erase(3);  // Erasing a non-existent key

  EXPECT_EQ(static_cast<int>(my_map.size()), 2);
  EXPECT_EQ(my_map.at(1), "one");
  EXPECT_EQ(my_map.at(2), "two");
}

TEST(MapTest, ClearAndReinsert) {
  s21::Map<int, std::string> my_map;
  my_map.insert(1, "one");
  my_map.insert(2, "two");

  my_map.clear();
  EXPECT_TRUE(my_map.empty());

  my_map.insert(3, "three");
  EXPECT_EQ(static_cast<int>(my_map.size()), 1);
  EXPECT_EQ(my_map.at(3), "three");
}

TEST(MapTest, ComplexKey) {
  s21::Map<std::pair<int, int>, std::string> my_map;
  my_map.insert({1, 1}, "one-one");
  my_map.insert({2, 2}, "two-two");

  EXPECT_EQ(static_cast<int>(my_map.size()), 2);
  EXPECT_EQ(my_map.at({1, 1}), "one-one");
  EXPECT_EQ(my_map.at({2, 2}), "two-two");
}

TEST(MapTest, LargeNumberOfElements) {
  s21::Map<int, int> my_map;
  for (int i = 0; i < 1000; ++i) {
    my_map.insert(i, i * 2);
  }

  EXPECT_EQ(static_cast<int>(my_map.size()), 1000);
  for (int i = 0; i < 1000; ++i) {
    EXPECT_EQ(my_map.at(i), i * 2);
  }
}

TEST(MapTest, IteratorEquality) {
  s21::Map<int, std::string> my_map;
  my_map.insert(1, "one");
  my_map.insert(2, "two");

  auto it1 = my_map.begin();
  auto it2 = my_map.begin();

  EXPECT_EQ(it1, it2);
  ++it1;
  EXPECT_NE(it1, it2);
}

TEST(MapTest, NestedMap) {
  s21::Map<int, s21::Map<int, std::string>> nested_map;
  nested_map.insert(1, s21::Map<int, std::string>());
  nested_map[1].insert(1, "one");

  EXPECT_EQ(static_cast<int>(nested_map.size()), 1);
  EXPECT_EQ(nested_map.at(1).at(1), "one");
}