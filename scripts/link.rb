require 'rbconfig'

*src, output = ARGV

if ENV['TARGET'] == 'aarch64-apple-darwin'
    script = [
        'zig',
        'build-lib',
        '-target aarch64-macos',
        '-dynamic',
        '-fallow-shlib-undefined',
        *src,
        "-femit-bin=#{output}"
    ].join(' ')
    puts script
    system(script)
    exit $?.exitstatus
end

def link_dir(dir)
    "-L#{dir}"
end

win = false
OS_SPECIFIC_OPTIONS =
    case RbConfig::CONFIG['host_os']
    when /mingw/
        win = true
        ['-m64', '-luserenv', '-lbcrypt']
    else
        []
    end

cc = RbConfig::CONFIG['LDSHARED'].split(' ').first
cc_override = ENV['CC'] || cc

script = [
    RbConfig::CONFIG['LDSHARED'].gsub(cc, cc_override),
    "-o #{output}",
    *src,

    ENV['EXTRA_CFLAGS'] || '',

    link_dir(RbConfig::CONFIG['libdir']),
    RbConfig::CONFIG['LDFLAGS'],
    '-Wl,-undefined,dynamic_lookup',
    RbConfig::CONFIG['DLDFLAGS'],

    *OS_SPECIFIC_OPTIONS,
    win ? RbConfig::CONFIG['LIBRUBYARG'] : '',
    RbConfig::CONFIG['LIBS'],

].join(' ').gsub('$(DEFFILE)', 'lib_ruby_parser-x64-mingw32.def')

if ENV['DRY_RUN']
    puts script
else
    puts script
    system(script)
    exit $?.exitstatus
end
