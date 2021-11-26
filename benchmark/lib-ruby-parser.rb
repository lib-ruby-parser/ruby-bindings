filelist = File.read(ENV['FILELIST_PATH']).split("\n")
files = filelist.map { |filepath| File.read(filepath) }
require 'ripper'

$: << File.expand_path('../../lib', __FILE__)
require 'lib-ruby-parser'

GC.disable

def now
    Process.clock_gettime(Process::CLOCK_MONOTONIC)
end

start = now
files.each do |file|
    LibRubyParser.parse(file, {})
end

puts "#{now - start}"
