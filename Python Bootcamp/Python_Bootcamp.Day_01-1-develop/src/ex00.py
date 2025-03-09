import unittest

def add_ingot(purse):
    new_purse = dict(purse)
    if "gold_ingots" in new_purse:
        new_purse["gold_ingots"] += 1
    else:
        new_purse["gold_ingots"] = 1
    return new_purse

def get_ingot(purse):
    new_purse = dict(purse)
    if "gold_ingots" in new_purse and new_purse["gold_ingots"] > 0:
        new_purse["gold_ingots"] -= 1
    return new_purse

def empty(purse):
    return {}


class TestPurseFunctions(unittest.TestCase):
    def test_add_ingot(self):
        purse = {}
        expected = {"gold_ingots": 1}
        self.assertEqual(add_ingot(purse), expected)

        purse = {"gold_ingots": 2}
        expected = {"gold_ingots": 3}
        self.assertEqual(add_ingot(purse), expected)

    def test_get_ingot(self):
        purse = {}
        expected = {}
        self.assertEqual(get_ingot(purse), expected)

        purse = {"gold_ingots": 2}
        expected = {"gold_ingots": 1}
        self.assertEqual(get_ingot(purse), expected)

        purse = {"gold_ingots": 0}
        expected = {"gold_ingots": 0}
        self.assertEqual(get_ingot(purse), expected)

    def test_empty(self):
        purse = {}
        expected = {}
        self.assertEqual(empty(purse), expected)

        purse = {"gold_ingots": 2, "silver_ingots": 3}
        expected = {}
        self.assertEqual(empty(purse), expected)

    def test_add_get_combination(self):
        purse = {}
        expected = {"gold_ingots": 1}
        self.assertEqual(add_ingot(get_ingot(add_ingot(empty(purse)))), expected)

if __name__ == '__main__':
    unittest.main()
