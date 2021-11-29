require 'rbconfig'

def include_dir(dir)
    "-I#{dir}"
end

src = ARGV[0]
output = ARGV[1]

cc = RbConfig::CONFIG['CC'].split(' ').first
cc_override = ENV['CC'] || cc

script = [
    RbConfig::CONFIG['CC'].gsub(cc, cc_override),
    include_dir('.'),
    include_dir(RbConfig::CONFIG['rubyarchhdrdir']),
    include_dir(RbConfig::CONFIG['rubyhdrdir']),
    include_dir(RbConfig::CONFIG['includedir']),
    RbConfig::CONFIG['CCDLFLAGS'],
    RbConfig::CONFIG['CFLAGS'],
    "-o #{output} -c",
    ENV['EXTRA_CFLAGS'] || '',
    src
].join(' ')
# .gsub('O3', 'O0 -g')

if ENV['DRY_RUN']
    puts script
else
    puts script
    system(script)
    exit $?.exitstatus
end
