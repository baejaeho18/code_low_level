#!/usr/bin/env ruby

fname  = (ARGV.size == 1) ? ARGV[0] : 'sample.rb'

sample = Hash.new { |_, v| v = 0 }
f = File.open(fname)
f.readlines.each { |l| 
  l.each_char { |c| sample[c.downcase] += 1 } 
}

sample.sort.each { |key, val| 
  puts "#{key} : #{val}" if key =~ /[a-z]/ 
}
