# frozen_string_literal: true

module LibRubyParser
  class Loc
    attr_reader :begin, :end
  end

  class Token
    attr_reader :token_name, :loc
  end

  class Diagnostic
    attr_reader :level, :message, :loc
  end

  class Comment
    attr_reader :location
  end

  class MagicComment
    attr_reader :kind, :key_l, :value_l
  end
end

require_relative './lib-ruby-parser/nodes'

require 'rbconfig'
host_os = RbConfig::CONFIG['host_os']
platform =
  case host_os
  when /mswin|msys|mingw|cygwin|bccwin|wince|emc/
    'windows'
  when /darwin|mac os/
    'darwin'
  when /linux/
    'linux'
  else
    raise NotImplementedError, "Unsupported host_os: #{host_os.inspect}"
  end

require_relative "./lib-ruby-parser/lib_ruby_parser_native_#{platform}"
