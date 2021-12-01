major, minor, _patch = Gem::Version.new(RUBY_VERSION).segments
puts "#{major}.#{minor}"
