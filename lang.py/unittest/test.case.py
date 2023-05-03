#!/usr/bin/env python

import unittest
import random

class TestSequenceFunctions(unittest.TestCase):
  def setUp(self):
    self.seq = range(10)

  def test_shuffle(self):
    random.shuffle(self.seq)
    self.seq.sort()
    self.assertEqual(self.seq, range(10))

  def test_choice(self):
    element = random.choice(self.seq)
    self.assertTrue(element in self.seq)

  def test_sample(self):
    self.assertRaises(ValueError, random.sample, self.seq, 20)
    for element in random.sample(self.seq, 5):
        self.assertTrue(element in self.seq)

if __name__ == '__main__':
  unittest.main()

  #suite = unittest.TestLoader().loadTestsFromTestCase(TestSequenceFunctions)
  #unittest.TextTestRunner(verbosity=2).run(suite)
