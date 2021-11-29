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

    def initialize(level:, message:, loc:)
      @level = level
      @message = message
      @loc = loc
    end
  end

  class Comment
    attr_accessor :location, :kind

    def initialize(location:, kind:)
      @location = location
      @kind = kind
    end
  end

  class MagicComment
    attr_accessor :kind, :key_l, :value_l

    def initialize(kind:, key_l:, value_l:)
      @kind = kind
      @key_l = key_l
      @value_l = value_l
    end
  end

  class Node
  end

  class DiagnosticMessage
  end

  class DecodedInput
    attr_accessor :name, :lines, :bytes
  end

  class SourceLine
    attr_accessor :start, :end, :ends_with_eof

    def initialize(**options)
      @start = options[:start]
      @end = options[:end]
      @ends_with_eof = options[:ends_with_eof]
    end

    def ==(other)
      start == other.start &&
        self.end == other.end &&
        ends_with_eof == other.ends_with_eof
    end
  end
end

require_relative './lib-ruby-parser/nodes'
require_relative './lib-ruby-parser/messages'

require_relative "./lib-ruby-parser/lib_ruby_parser_native"
