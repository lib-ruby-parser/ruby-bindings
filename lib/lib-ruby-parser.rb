# frozen_string_literal: true

module LibRubyParser
  class Loc
    attr_accessor :begin, :end

    def initialize(**options)
      @begin = options[:begin] || 0
      @end = options[:end] || 0
    end
  end

  class Token
    attr_accessor :token_type, :token_name, :token_value, :lex_state_before, :lex_state_after, :loc

    def initialize(
      token_type:,
      token_name:,
      token_value:,
      loc:
    )
      @token_type = token_type
      @token_name = token_name
      @token_value = token_value
      @lex_state_before = 0
      @lex_state_after = 0
      @loc = loc
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

  class Node
  end

  class DiagnosticMessage
  end
end

require_relative './lib-ruby-parser/nodes'
require_relative './lib-ruby-parser/messages'

# require_relative "./lib-ruby-parser/lib_ruby_parser_native"
