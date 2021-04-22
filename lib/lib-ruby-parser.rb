# frozen_string_literal: true

module LibRubyParser
  class Loc
    attr_accessor :begin, :end

    def initialize(**options)
      @begin = options[:begin]
      @end = options[:end]
    end
  end

  class Token
    attr_accessor :token_type, :token_name, :token_value, :lex_state_before, :lex_state_after, :loc

    def initialize(**options)
      @token_type = options[:token_type]
      @token_name = options[:token_name]
      @token_value = options[:token_value]
      @lex_state_before = options[:lex_state_before]
      @lex_state_after = options[:lex_state_after]
      @loc = options[:loc]
    end
  end

  class Diagnostic
    attr_accessor :level, :message, :loc

    def initialize(**options)
      @level = options[:level]
      @message = options[:message]
      @loc = options[:loc]
    end
  end

  class Comment
    attr_accessor :location

    def initialize(**options)
      @location = options[:location]
    end
  end

  class MagicComment
    attr_accessor :kind, :key_l, :value_l

    def initialize(**options)
      @kind = options[:kind]
      @key_l = options[:key_l]
      @value_l = options[:value_l]
    end
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
