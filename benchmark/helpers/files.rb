glob = ENV['GLOB']
FILES = Dir[glob].map { |f| [f, File.read(f)] }
