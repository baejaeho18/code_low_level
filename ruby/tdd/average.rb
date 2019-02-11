#!/usr/bin/env ruby

require "test/unit"

class Array
  def sum *a
    a.reduce(0, :+)
  end
  
  def average(*a)
    return 0 if a.length == 0
    return sum(*a) / a.length
  end
end

class TestAccumulator < Test::Unit::TestCase
  def setup
    @acc = []
  end
  
  def test_sum
    assert_equal(0,  @acc.sum())
    assert_equal(0,  @acc.sum(0))
    assert_equal(7,  @acc.sum(1, 2, 4))
    assert_equal(10, @acc.sum(1, 2, 4, 3))
  end
  
  def test_average
    assert_equal(0,  @acc.average())
    assert_equal(0,  @acc.average(0, 0, 0))
    assert_equal(2,  @acc.average(1, 2, 3))
    assert_equal(3,  @acc.average(3, 3, 3))
    assert_equal(10, @acc.average(9, 10, 11))
  end
end
