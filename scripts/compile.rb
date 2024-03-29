require 'rbconfig'

def include_dir(dir)
    "-I#{dir}"
end

src = ARGV[0]
output = ARGV[1]

puts [
    RbConfig::CONFIG['CC'],
    include_dir('.'),
    include_dir(RbConfig::CONFIG['rubyarchhdrdir']),
    include_dir(RbConfig::CONFIG['rubyhdrdir']),
    include_dir(RbConfig::CONFIG['includedir']),
    RbConfig::CONFIG['CCDLFLAGS'],
    RbConfig::CONFIG['CFLAGS'],
    "-o #{output} -c",
    src
].join(' ')
