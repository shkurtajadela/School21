import unittest

from ex00 import add_ingot, empty

def split_booty(*purses):
    total_ingots = sum(purse.get("gold_ingots", 0) for purse in purses)
    
    booty = [empty({}) for _ in range(3)]
    
    for i in range(total_ingots):
        index = i % 3 
        booty[index] = add_ingot(booty[index])
    
    return booty


class TestSplitBooty(unittest.TestCase):
    
    def test_split_booty_equal_purses(self):
        purses = [{"gold_ingots": 9}]
        expected_booty = [{"gold_ingots": 3}, {"gold_ingots": 3}, {"gold_ingots": 3}]
        self.assertEqual(split_booty(*purses), expected_booty)

    def test_split_booty_extra_ingots(self):
        purses = [{"gold_ingots": 3}, {"gold_ingots": 2}, {"apples": 10}]
        expected_booty = [{"gold_ingots": 2}, {"gold_ingots": 2}, {"gold_ingots": 1}]
        self.assertEqual(split_booty(*purses), expected_booty)

    def test_split_booty_empty_purses(self):
        purses = [{}, {}, {}]
        expected_booty = [{}, {}, {}]
        self.assertEqual(split_booty(*purses), expected_booty)

    def test_split_booty_no_gold_ingots(self):
        purses = [{"silver_ingots": 3}, {"copper_ingots": 3}, {"platinum_ingots": 3}]
        expected_booty = [{}, {}, {}]
        self.assertEqual(split_booty(*purses), expected_booty)


if __name__ == '__main__':
    unittest.main()