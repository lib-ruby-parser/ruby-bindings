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
    # @param kind [Symbol]
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

  # Base class for all AST nodes
  class Node
  end

  # Base class for all diagnostic messages
  class DiagnosticMessage
  end

  # Input decoded by parser.
  #
  # If your code has magic encoding comment LibRubyParser
  # re-encodes given input and (potentially) operates
  # on a different byte sequence.
  #
  # This is why this input should be used to get source
  # of all locations.
  #
  # Using initial input is wrong as you may get a different
  # source range in a different byte representation.
  class DecodedInput
    # Name of the initial input
    #
    # @return [String]
    attr_accessor :name

    # Array of source lines
    #
    # @return [Array<SourceLine>]
    attr_accessor :lines

    # Re-encoded input string
    #
    # @return [String]
    attr_accessor :bytes
  end

  # Representation of a source line in a source file
  class SourceLine
    # Start of the line (in bytes)
    #
    # @return [Integer]
    attr_accessor :start

    # End of the line (in bytes)
    #
    # @return [Integer]
    attr_accessor :end

    # +true+ if line ends with EOF char (which is true for the last line in the file)
    #
    # @return [true, false]
    attr_accessor :ends_with_eof

    # @param options [Hash]
    # @option options [Integer] :start
    # @option options [Integer] :end
    # @option options [true, false] :ends_with_eof
    def initialize(**options)
      @start = options[:start]
      @end = options[:end]
      @ends_with_eof = options[:ends_with_eof]
    end

    # Default +==+ comparison
    def ==(other)
      start == other.start &&
        self.end == other.end &&
        ends_with_eof == other.ends_with_eof
    end
  end

  # Combination of all data that +LibRubyParser+ can give you
  class ParserResult
    # Abstract Syntax Tree that was constructed from you code.
    # +nil+ if the code gives no AST nodes
    #
    # @return [Node, nil]
    attr_accessor :ast

    # List of tokens returned by a Lexer and consumed by a Parser.
    # Empty unless +:record_tokens+ is set to true.
    #
    # @return [Array<Token>]
    attr_accessor :tokens

    # List of all diagnostics (errors and warings) that
    # have been recorded during lexing and parsing
    #
    # @return [Array<Diagnostic>]
    attr_accessor :diagnostics

    # List of comments extracted from the source code.
    #
    # @return [Array<Comment>]
    attr_accessor :comments

    # List of magic comments extracted from the source code.
    #
    # @return [Array<MagicComment>]
    attr_accessor :magic_comments

    # Input that was used for parsing.
    #
    # Note: this input is not necessary the same byte array that you passed to Parser::parse.
    # If encoding of the input is not +UTF-8+ or +ASCII-8BIT/BINARY+ Parser invokes decoder
    # that usually produces a different sequence of bytes.
    #
    # Pass this data to +Loc#source+, otherwise you’ll get incorrect source ranges.
    #
    # @return [DecodedInput]
    attr_accessor :input
  end

  # Default decoder that is used to re-encode input
  # from non-utf-8 encoding to utf-8
  DEFAULT_DECODER = proc do |encoding, input|
    encoding = Encoding.find(encoding)
    input.force_encoding(encoding).encode('utf-8')
  end

  # Parses given input according to given options
  #
  # @param [String] input
  # @param [Hash] options
  # @option options [String] :buffer_name name of the input file
  # @option options [#call] :decoder (DEFAULT_DECODER) decoder, called with +encoding+ (String) and +input+ (String)
  # @option options [true, false] :record_tokens When set to true Parser records tokens. When set to false ParserResult::tokens is guaranteed to be empty. If you don’t need tokens better set it to false to speed up parsing.
  #
  # @return [ParserResult]
  def self.parse(input, options)
  end
end

require_relative './lib-ruby-parser/nodes'
require_relative './lib-ruby-parser/messages'

require 'rbconfig'

os = RbConfig::CONFIG['host_os']
is_windows = !!(os =~ /mingw/)
is_darwin = !!(os =~ /darwin/)
is_linux = !!(os =~ /linux/)

cpu = RbConfig::CONFIG['host_cpu']
is_x86_64 = cpu == 'x86_64' || cpu == 'x64'
is_arm64 = ['arm64', 'aarch64'].include?(cpu)

ruby_version = Gem::Version.new(RUBY_VERSION).segments.first(2).join('.')

native_dylib_path =
  if is_darwin && is_x86_64
    'x86_64-apple-darwin/lib_ruby_parser'
  elsif is_darwin && is_arm64
    'aarch64-apple-darwin/lib_ruby_parser'
  elsif is_linux && is_x86_64
    'x86_64-unknown-linux-gnu/lib_ruby_parser'
  elsif is_windows && is_x86_64 && ['3.2', '3.1', '3.0'].include?(ruby_version)
    "x86_64-pc-windows-gnu/#{ruby_version}/lib_ruby_parser"
  else
    raise "[lib-ruby-parser] Unsupported os/cpu/ruby-version combination '#{os}'/'#{cpu}'/'#{ruby_version}'"
  end

require_relative "./lib-ruby-parser/native/#{native_dylib_path}"
