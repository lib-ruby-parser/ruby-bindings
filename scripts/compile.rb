require 'rbconfig'

def include_dir(dir)
    "-I #{dir}"
end

puts [
    RbConfig::CONFIG['LDSHARED'],
    include_dir(RbConfig::CONFIG['rubyhdrdir']),
    include_dir(RbConfig::CONFIG['rubyarchhdrdir']),
    RbConfig::CONFIG['CFLAGS'],
    RbConfig::CONFIG['DLDFLAGS'].dup.gsub('$(DEFFILE)', ''),
].join(' ')
