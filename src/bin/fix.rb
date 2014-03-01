#!/usr/bin/env ruby

if(ARGV.length < 2)
	abort "ABORT: Not enough arguments"
end

file = File.open ARGV[0], 'r'

output = "\t.text\n\tjmp main\n"

puts "Loading file..."
file.each do |line|
	output += line
end

file.close

puts "Changing data sections to text sections..."
output.gsub! ".data", ".text"
output.gsub! ".rodata", ".text"

puts "Writing new file..."
file = File.open ARGV[1], 'w'
file.puts output
file.close

puts "Success!"
