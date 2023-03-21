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
    ruby_version = Gem::Version.new(RUBY_VERSION).segments.first(2).join('.') + '.0'

    headers = "ruby-#{ruby_version}-headers"

    unless Dir.exist?(headers)
        system("wget https://github.com/lib-ruby-parser/ruby-bindings/releases/download/ruby-aarch64-headers/#{headers}.zip")
        system("unzip #{headers}.zip")
    end

    script = [
        'zig cc',
        '--target=aarch64-macos',
        '-I.',
        "-I#{headers}",
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
