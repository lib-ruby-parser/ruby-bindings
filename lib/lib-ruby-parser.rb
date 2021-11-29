# frozen_string_literal: true

module LibRubyParser
  # Representation of any location in the given input
  class Loc
    # Begin of the `Loc` range
    #
    # @return [Integer]
    attr_accessor :begin

    # End of the `Loc` range
    #
    # @return [Integer]
    attr_accessor :end

    # @param [Hash] options
    # @option options [Integer] :begin
    # @option options [Integer] :end
    def initialize(**options)
      @begin = options[:begin] || 0
      @end = options[:end] || 0
    end
  end

  # A token that is emitted by a lexer and consumed by a parser
  class Token
    # Numeric representation of the token type, e.g. +132+ (for example) for +tINTEGER+
    #
    # @return [Integer]
    attr_accessor :token_type

    # String type of the token
    #
    # @return [String]
    attr_accessor :token_name

    # Value of the token, e.g +“42”+ for +42+
    #
    # @return [String]
    attr_accessor :token_value

    # Lex state before token was read
    #
    # @return [Integer]
    attr_accessor :lex_state_before

    # Lex state after token was read
    #
    # @return [Integer]
    attr_accessor :lex_state_after

    # Location of the token
    #
    # @return [Loc]
    attr_accessor :loc

    # @param token_type [Integer]
    # @param token_name [String]
    # @param token_value [String]
    # @param loc [Loc]
    def initialize(token_type:, token_name:, token_value:, loc:)
      @token_type = token_type
      @token_name = token_name
      @token_value = token_value
      @lex_state_before = 0
      @lex_state_after = 0
      @loc = loc
    end
  end

  # Diagnostic message that comes from the parser when there’s an error or warning
  class Diagnostic
    # Level of the diagnostic (+:error+ or +:warning+)
    #
    # @return [Symbol] +:error+ or +:warning+
    attr_accessor :level

    # Message of the diagnostic
    #
    # @return [DiagnosticMessage]
    attr_accessor :message

    # Location of the diagnostic
    #
    # @return [Loc]
    attr_accessor :loc

    # @param level [Symbol]
    # @param message [DiagnosticMessage]
    # @param loc [Loc]
    def initialize(level:, message:, loc:)
      @level = level
      @message = message
      @loc = loc
    end
  end

  # A class that represents a comment in Ruby
  class Comment
    # Location of the comment (starts with # and ends with the last char)
    #
    # @return [Loc]
    attr_accessor :location

    # Kind of the comment (+:inline+ or +:document+ or +:unknown+)
    #
    # @return [Symbol] +:inline+ or +:document+ or +:unknown+
    attr_accessor :kind

    # @param location [Loc]
    # @param location [kind]
    def initialize(location:, kind:)
      @location = location
      @kind = kind
    end
  end

  # Representation of a magic comment in Ruby
  class MagicComment
    # Kind of a magic comment, can be
    #
    # 1. +encoding+
    # 2. +frozen_string_literal+
    # 3. +warn_indent+
    # 4. +shareable_constant_value+
    #
    # @return [Symbol]
    attr_accessor :kind

    # Location of the “key”
    #
    # @example
    #   # encoding: utf-8
    #     ~~~~~~~~
    #
    # @return [Loc]
    attr_accessor :key_l

    # Location of the “value”
    #
    # @example
    #   # encoding: utf-8
    #               ~~~~~
    #
    # @return [Loc]
    attr_accessor :value_l

    # @param kind [Symbol]
    # @param key_l [Loc]
    # @param value_l [Loc]
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

  class ParserResult
    attr_accessor :ast, :tokens, :diagnostics, :comments, :magic_comments, :input
  end
end

require_relative './lib-ruby-parser/nodes'
require_relative './lib-ruby-parser/messages'

require_relative "./lib-ruby-parser/lib_ruby_parser_native"
