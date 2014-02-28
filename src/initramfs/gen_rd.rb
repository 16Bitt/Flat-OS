#!/usr/bin/env ruby

if(ARGV.length < 1)
	abort "No files to pack"
end

puts "Writing header..."
output = "\tdd END - $$\n\tdd 0x04206969\n\tdd #{ARGV.length- 1}\n"

puts "Writing lookup table..."
i = 0
while(i < ARGV.length)
	output += "\tdb \"#{ARGV[i]}\",0\n"
	output += "\tdd FILE#{i}\n"
	output += "\tdd #{File.size(ARGV[i])}\n"
	
	i += 1
end

puts "Writing file paths..."
i = 0
while(i < ARGV.length)
	output += "FILE#{i}:\n"
	output += "\t%incbin \"#{ARGV[i]}\"\n"
	
	i += 1
end

puts "Writing footer..."
output += "\tdd 0x04206969"

puts "Completing write to file..."
file = File.new "initrd.asm", 'w'
file.puts output
file.close

puts "Success"
