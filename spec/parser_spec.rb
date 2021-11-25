require 'spec_helper'

RSpec.describe LibRubyParser do
  def expect_loc(loc, expected_range)
    expect(loc).to be_instance_of(LibRubyParser::Loc)
    expect(loc.begin).to eq(expected_range.begin)
    expect(loc.end).to eq(expected_range.end)
  end

  describe ':ast' do
    it 'returns ast' do
      result = LibRubyParser.parse('42', {})

      expect(result[:ast]).to be_instance_of(LibRubyParser::Nodes::Int)
      expect(result[:ast].value).to eq('42')
      expect(result[:ast].operator_l).to be_nil
      expect_loc(result[:ast].expression_l, 0...2)
    end
  end

  def expect_token(token, expected_token_name, expected_range)
    expect(token.token_name).to eq(expected_token_name)
    expect_loc(token.loc, expected_range)
  end

  describe ':tokens' do
    it 'is empty when record_tokens: false passed' do
      expect(
        LibRubyParser.parse('42', record_tokens: false)[:tokens]
      ).to eq([])
    end

    it 'contains tokens when record_tokens: true passed' do
      tokens = LibRubyParser.parse('42', record_tokens: true)[:tokens]
      expect(tokens.length).to eq(2)

      expect_token(tokens[0], 'tINTEGER', 0...2)
      expect_token(tokens[1], 'EOF',      2...2)
    end
  end

  def expect_diagnostic(diagnostic, expected_level, expected_message_class, expected_range)
    expect(diagnostic).to be_instance_of(LibRubyParser::Diagnostic)
    expect(diagnostic.level).to eq(expected_level)
    expect(diagnostic.message).to be_instance_of(expected_message_class)
    expect_loc(diagnostic.loc, expected_range)
  end

  describe ':diagnostics' do
    it 'returns a list of diagnostics' do
      diagnostics = LibRubyParser.parse('foo+', {})[:diagnostics]
      expect(diagnostics.length).to eq(1)

      expect_diagnostic(diagnostics[0], :error, LibRubyParser::Messages::UnexpectedToken, 4...4)
      # FIXME: check .render() = 'unexpected END_OF_INPUT'
    end
  end

  def expect_comment(comment, expected_kind, expected_range)
    expect(comment).to be_instance_of(LibRubyParser::Comment)
    expect(comment.kind).to eq(expected_kind)
    expect_loc(comment.location, expected_range)
  end

  describe ':comments' do
    it 'returns a list of comments' do
      code = <<~RUBY
        # one
        # two
        42
      RUBY

      comments = LibRubyParser.parse(code, {})[:comments]
      expect(comments.length).to eq(2)

      expect_comment(comments[0], :inline, 0...6)
      expect_comment(comments[1], :inline, 6...12)
    end
  end

  def expect_magic_comment(magic_comment, expected_kind, expected_key_range, expected_value_range)
    expect(magic_comment).to be_instance_of(LibRubyParser::MagicComment)
    expect(magic_comment.kind).to eq(expected_kind)
    expect_loc(magic_comment.key_l, expected_key_range)
    expect_loc(magic_comment.value_l, expected_value_range)
  end

  describe ':magic_comments' do
    it 'returns a list of magic comments' do
      code = <<~RUBY
        # frozen_string_literal: true
        42
      RUBY

      magic_comments = LibRubyParser.parse(code, {})[:magic_comments]
      expect(magic_comments.length).to eq(1)

      expect_magic_comment(magic_comments[0], :frozen_string_literal, 2...23, 25...29)
    end
  end

  xdescribe ':input' do
    it 'returns decoded input' do
      input = LibRubyParser.parse('42', {})[:input]
      expect(input).to eq('42')
    end
  end

  describe ':token_rewriter' do
    let(:source) do
      "2 + 2"
    end

    context 'when not given' do
      it 'has no effect' do
        result = LibRubyParser.parse(source, record_tokens: true)

        tokens = result[:tokens]
        expect(tokens.length).to eq(4)

        expect_token(tokens[0], 'tINTEGER', 0...1)
        expect_token(tokens[1], 'tPLUS',    2...3)
        expect_token(tokens[2], 'tINTEGER', 4...5)
        expect_token(tokens[3], 'EOF',      5...5)

        expect(result[:ast]).to be_instance_of(LibRubyParser::Nodes::Send)
        expect(result[:ast].recv).to be_instance_of(LibRubyParser::Nodes::Int)
        expect(result[:ast].recv.value).to eq('2')
      end
    end

    xcontext 'when given' do
      it 'rewrites tokens' do
        token_rewriter = proc do |token, input|
          if token.token_value == '2'
            token.token_value = '3'
          end
          { rewritten_token: token }
        end

        result = LibRubyParser.parse(source, record_tokens: true, token_rewriter: token_rewriter)

        tokens = result[:tokens]
        expect(tokens.length).to eq(4)

        expect_token(tokens[0], 'tINTEGER', 0...1)
        expect_token(tokens[1], 'tPLUS',    2...3)
        expect_token(tokens[2], 'tINTEGER', 4...5)
        expect_token(tokens[3], 'EOF',      5...5)

        expect(result[:ast]).to be_instance_of(LibRubyParser::Send)
        expect(result[:ast].recv).to be_instance_of(LibRubyParser::Int)
        expect(result[:ast].recv.value).to eq('3')
      end
    end
  end

  describe ':custom_decoder' do
    let(:source) do
      <<~RUBY.force_encoding('Windows-1251')
        # encoding: Windows-1251
        "\xFF"
      RUBY
    end

    context 'when not given' do
      it 'returns an error for unsupported encoding' do
        result = LibRubyParser.parse(source, {})
        expect(result[:ast]).to be_nil
        expect(result[:diagnostics].length).to eq(1)
        expect(result[:diagnostics][0].message).to be_instance_of(LibRubyParser::Messages::EncodingError)
        expect(result[:diagnostics][0].message.error).to eq('UnsupportedEncoding("Windows-1251")')
      end
    end

    xcontext 'when given' do
      it 'uses it to decode unsupported encoding' do
        called = false

        decoder = proc do |encoding, input|
          called = true
          expect(encoding).to eq('Windows-1251')
          expect(input.encoding).to eq(Encoding::BINARY)
          expect(input.bytes).to eq(source.bytes)

          encoding = Encoding.find(encoding)
          input.force_encoding(encoding).encode('utf-8')
        end

        result = LibRubyParser.parse(source, decoder: decoder)

        expect(called).to eq(true)

        expect(result[:input].encoding).to eq(Encoding::UTF_8)
        expect(result[:input]).to eq(<<~RUBY)
          # encoding: Windows-1251
          "я"
        RUBY

        expect(result[:ast].value.encoding).to eq(Encoding::UTF_8)
        expect(result[:ast].value).to eq("я")
      end
    end
  end

  it 'handles all nodes' do
    source = File.read('spec/fixtures/all_nodes.rb')
    LibRubyParser.parse(source, {})
  end
end
