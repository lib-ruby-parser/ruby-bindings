require 'rbconfig'

*src, output = ARGV

def link_dir(dir)
    "-L#{dir}"
end

OS_SPECIFIC_OPTIONS =
    case RbConfig::CONFIG['host_os']
    when /mingw/
        ['-m64', '-luserenv']
    else
        []
    end

puts [
    RbConfig::CONFIG['LDSHARED'],
    "-o #{output}",
    *src,

    link_dir(RbConfig::CONFIG['libdir']),
    RbConfig::CONFIG['LDFLAGS'],
    RbConfig::CONFIG['DLDFLAGS'],

    *OS_SPECIFIC_OPTIONS,
    RbConfig::CONFIG['LIBRUBYARG'],
    RbConfig::CONFIG['LIBS'],

].join(' ').gsub('$(DEFFILE)', 'lib_ruby_parser_native-x64-mingw32.def')
