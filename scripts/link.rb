require 'rbconfig'

*src, output = ARGV

def link_dir(dir)
    "-L#{dir}"
end

OS_SPECIFIC_OPTIONS =
    case RbConfig::CONFIG['host_os']
    when /mingw/
        ['-m64', '-luserenv', '-lgmp']
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
    RbConfig::CONFIG['DLDFLAGS'],

    *OS_SPECIFIC_OPTIONS,
    RbConfig::CONFIG['LIBS'],

].join(' ').gsub('$(DEFFILE)', 'lib_ruby_parser_native-x64-mingw32.def')

# script = [
#     'gcc -shared',
#     '-o lib/lib-ruby-parser/lib_ruby_parser_native.so',
#     'main.o',
#     '-lruby-static',
#     '-lruby_parser_c-x86_64-pc-windows-gnu',
#     ' -LC:/hostedtoolcache/windows/Ruby/3.0.3/x64/lib',
#     '-L.',
#     '-Lc-bindings',
#     '-pipe -s -fstack-protector-strong -pipe -s -fstack-protector-strong -Wl,--enable-auto-image-base,--enable-auto-import lib_ruby_parser_native-x64-mingw32.def -m64 -luserenv -lshell32 -lws2_32 -liphlpapi -limagehlp -lshlwapi'
# ].join(' ')

# puts script

if ENV['DRY_RUN']
    puts script
else
    puts script
    system(script)
    exit $?.exitstatus
end
