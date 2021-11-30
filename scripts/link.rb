require 'rbconfig'

*src, output = ARGV

def link_dir(dir)
    "-L#{dir}"
end

OS_SPECIFIC_OPTIONS =
    case RbConfig::CONFIG['host_os']
    when /mingw/
        ['-m64', '-luserenv', '-Wl,-undefined,dynamic_lookup']
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

if ENV['DRY_RUN']
    puts script
else
    puts script
    system(script)
    exit $?.exitstatus
end
