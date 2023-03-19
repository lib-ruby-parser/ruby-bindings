require 'rbconfig'

def include_dir(dir)
    "-I#{dir}"
end

src = ARGV[0]
output = ARGV[1]

cc = RbConfig::CONFIG['CC'].split(' ').first
cc_override = ENV['CC'] || cc

def run(script)
    puts script
    system(script)
    exit $?.exitstatus
end

if ENV['TARGET'] == 'aarch64-apple-darwin'
    unless Dir.exist?('ruby-3.0-arm64-headers')
        system('wget https://github.com/lib-ruby-parser/ruby-bindings/releases/download/ruby-3.0-arm64-headers/ruby-3.0-arm64-headers.zip')
        system('unzip ruby-3.0-arm64-headers.zip')
    end

    script = [
        'zig cc',
        '--target=aarch64-macos',
        '-I.',
        '-Iruby-3.0-arm64-headers',
        '-fno-common',
        '-fdeclspec',
        '-O3',
        '-fno-fast-math',
        '-ggdb3',
        '-pipe',
        "-o #{output}",
        '-c',
        src
    ].join(' ')
    run(script)
end

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
    run(script)
end
