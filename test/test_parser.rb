require 'minitest/autorun'
$LOAD_PATH << File.expand_path('../../lib', __FILE__)
require 'lib-ruby-parser'

module AssertionHelpers
  def assert_loc(loc, expected_range)
    assert_instance_of(LibRubyParser::Loc, loc)
    assert_equal(loc.begin, expected_range.begin)
    assert_equal(loc.end, expected_range.end)
  end

  def assert_token(token, expected_token_name, expected_range)
    assert_equal(token.token_name, expected_token_name)
    assert_loc(token.loc, expected_range)
  end

  def assert_diagnostic(diagnostic, expected_level, expected_message_class, expected_range)
    assert_instance_of(LibRubyParser::Diagnostic, diagnostic)
    assert_equal(diagnostic.level, expected_level)
    assert_instance_of(expected_message_class, diagnostic.message)
    assert_loc(diagnostic.loc, expected_range)
  end

  def assert_comment(comment, expected_kind, expected_range)
    assert_instance_of(LibRubyParser::Comment, comment)
    assert_equal(comment.kind, expected_kind)
    assert_loc(comment.location, expected_range)
  end

  def assert_magic_comment(magic_comment, expected_kind, expected_key_range, expected_value_range)
    assert_instance_of(LibRubyParser::MagicComment, magic_comment)
    assert_equal(magic_comment.kind, expected_kind)
    assert_loc(magic_comment.key_l, expected_key_range)
    assert_loc(magic_comment.value_l, expected_value_range)
  end
end

class ParserTest < Minitest::Test
  include AssertionHelpers

  def test_ast
    ast = LibRubyParser.parse('42', {}).ast

    assert_instance_of(LibRubyParser::Nodes::Int, ast)
    assert_equal(ast.value, '42')
    assert_nil(ast.operator_l)
    assert_loc(ast.expression_l, 0...2)
  end

  def test_tokens_empty
    tokens = LibRubyParser.parse('42', record_tokens: false).tokens
    assert_equal(tokens, [])
  end

  def test_tokens_recorded
    tokens = LibRubyParser.parse('42', record_tokens: true).tokens
    assert_equal(tokens.length, 2)

    assert_token(tokens[0], 'tINTEGER', 0...2)
    assert_token(tokens[1], 'EOF',      2...2)
  end

  def test_diagnostics
    diagnostics = LibRubyParser.parse('foo+', {}).diagnostics
    assert_equal(diagnostics.length, 1)

    assert_diagnostic(diagnostics[0], :error, LibRubyParser::Messages::UnexpectedToken, 4...4)
    # FIXME: check .render() = 'unexpected END_OF_INPUT'
  end

  def test_comments
    code = <<~RUBY
      # one
      # two
      42
    RUBY

    comments = LibRubyParser.parse(code, {}).comments
    assert_equal(comments.length, 2)

    assert_comment(comments[0], :inline, 0...6)
    assert_comment(comments[1], :inline, 6...12)
  end

  def test_magic_comments
    code = <<~RUBY
      # frozen_string_literal: true
      42
    RUBY

    magic_comments = LibRubyParser.parse(code, {}).magic_comments
    assert_equal(magic_comments.length, 1)

    assert_magic_comment(magic_comments[0], :frozen_string_literal, 2...23, 25...29)
  end

  def test_input
    input = LibRubyParser.parse('42', name: 'foo.rb').input
    assert_instance_of(LibRubyParser::DecodedInput, input)
    assert_equal(input.name, '(eval)')
    assert_equal(input.bytes, '42')
    assert_equal(input.lines, [LibRubyParser::SourceLine.new(start: 0, end: 2, ends_with_eof: true)])
  end

  def test_token_rewriter_empty
    result = LibRubyParser.parse('2 + 2', record_tokens: true)

    tokens = result.tokens
    assert_equal(tokens.length, 4)

    assert_token(tokens[0], 'tINTEGER', 0...1)
    assert_token(tokens[1], 'tPLUS',    2...3)
    assert_token(tokens[2], 'tINTEGER', 4...5)
    assert_token(tokens[3], 'EOF',      5...5)

    assert_instance_of(LibRubyParser::Nodes::Send, result.ast)
    assert_instance_of(LibRubyParser::Nodes::Int, result.ast.recv)
    assert_equal(result.ast.recv.value, '2')
  end

  def test_token_rewriter_custom
    token_rewriter = proc do |token, input|
      # rewrite all '2' tokens to '3'
      if token.token_value == '2'
        token.token_value = '3'
      end
      {
        rewritten_token: token,
        token_action: :keep,
        lex_state_action: { keep: true }
      }
    end

    result = LibRubyParser.parse('2 + 2', record_tokens: true, token_rewriter: token_rewriter)

    tokens = result.tokens
    assert_equal(tokens.length, 4)

    assert_token(tokens[0], 'tINTEGER', 0...1)
    assert_token(tokens[1], 'tPLUS',    2...3)
    assert_token(tokens[2], 'tINTEGER', 4...5)
    assert_token(tokens[3], 'EOF',      5...5)

    assert_instance_of(LibRubyParser::Nodes::Send, result.ast)
    assert_instance_of(LibRubyParser::Nodes::Int, result.ast.recv)
    assert_equal(result.ast.recv.value, '3')
  end

  SOURCE_WITH_CUSTOM_ENCODING = <<~RUBY.force_encoding('Windows-1251')
    # encoding: Windows-1251
    "\xFF"
  RUBY

  def test_decoded_empty
    src = <<~RUBY.force_encoding('Windows-1251')
      # encoding: Windows-1251
      "\xFF"
    RUBY
    result = LibRubyParser.parse(src, {})

    assert_nil(result.ast)

    assert_equal(result.diagnostics.length, 1)
    diagnostic = result.diagnostics[0]
    assert_instance_of(LibRubyParser::Messages::EncodingError, diagnostic.message)
    assert_equal(diagnostic.message.error, 'UnsupportedEncoding("Windows-1251")')
  end

  def test_decoded_custom
    called = false

    src = SOURCE_WITH_CUSTOM_ENCODING

    decoder = proc do |encoding, input|
      called = true
      assert_equal(encoding, 'Windows-1251')
      assert_equal(input.encoding, Encoding::BINARY)
      assert_equal(input.bytes, src.bytes)

      encoding = Encoding.find(encoding)
      input.force_encoding(encoding).encode('utf-8')
    end

    result = LibRubyParser.parse(src, decoder: decoder)

    assert_equal(called, true)

    assert_equal(result.input.bytes.encoding, Encoding::UTF_8)
    assert_equal(result.input.bytes, <<~RUBY)
      # encoding: Windows-1251
      "я"
    RUBY

    assert_equal(result.ast.value.encoding, Encoding::UTF_8)
    assert_equal(result.ast.value, "я")
  end

  def test_decoder_custom_err
    decoder = proc do |encoding, input|
      raise 'I am the error, fight the power!'
    end

    result = LibRubyParser.parse(SOURCE_WITH_CUSTOM_ENCODING, decoder: decoder)

    assert_nil(result.ast)

    assert_equal(result.diagnostics.length, 1)

    diagnostic = result.diagnostics[0]
    assert_equal(diagnostic.level, :error)
    assert_loc(diagnostic.loc, 12...24)
    assert_instance_of(LibRubyParser::Messages::EncodingError, diagnostic.message)
    assert_equal(diagnostic.message.error, 'DecodingError("I am the error, fight the power!")')
  end

  def test_all_nodes
    source = File.read('test/fixtures/all_nodes.rb')
    decoder = proc do |encoding, input|
      encoding = Encoding.find(encoding)
      input.force_encoding(encoding).encode('utf-8')
    end

    result = LibRubyParser.parse(source, decoder: decoder)
    refute_nil(result.ast)
  end
end
