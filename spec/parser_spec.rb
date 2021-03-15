require 'spec_helper'

describe LibRubyParser do
  describe ':ast' do
    it 'returns ast' do
      result = LibRubyParser.parse('42', {})

      expect(result[:ast]).to be_instance_of(LibRubyParser::Int)
      expect(result[:ast].value).to eq('42')
      expect(result[:ast].operator_l).to be_nil
      expect(result[:ast].expression_l).to be_instance_of(LibRubyParser::Loc)
      expect(result[:ast].expression_l.begin).to eq(0)
      expect(result[:ast].expression_l.end).to eq(2)
    end
  end

  describe ':tokens' do
    it 'is empty when record_tokens: false passed' do
      expect(
        LibRubyParser::parse('42', record_tokens: false)[:tokens]
      ).to eq([])
    end

    it 'contains tokens when record_tokens: true passed' do
      tokens = LibRubyParser::parse('42', record_tokens: true)[:tokens]
      expect(tokens.length).to eq(2)

      expect(tokens[0].token_name).to eq('tINTEGER')
      expect(tokens[0].loc.begin).to eq(0)
      expect(tokens[0].loc.end).to eq(2)

      expect(tokens[1].token_name).to eq('EOF')
      expect(tokens[1].loc.begin).to eq(2)
      expect(tokens[1].loc.end).to eq(2)
    end
  end

  describe ':diagnostics' do
    it 'returns a list of diagnostics' do
      diagnostics = LibRubyParser::parse('foo+', {})[:diagnostics]
      expect(diagnostics.length).to eq(1)

      expect(diagnostics[0]).to be_instance_of(LibRubyParser::Diagnostic)
      expect(diagnostics[0].level).to eq(:error)
      expect(diagnostics[0].message).to eq('unexpected END_OF_INPUT')
      expect(diagnostics[0].loc).to be_instance_of(LibRubyParser::Loc)
      expect(diagnostics[0].loc.begin).to eq(4)
      expect(diagnostics[0].loc.end).to eq(4)
    end
  end

  describe ':comments' do
    it 'returns a list of comments' do
      code = <<~RUBY
        # one
        # two
        42
      RUBY

      comments = LibRubyParser::parse(code, {})[:comments]
      expect(comments.length).to eq(2)

      expect(comments[0]).to be_instance_of(LibRubyParser::Comment)
      expect(comments[0].location).to be_instance_of(LibRubyParser::Loc)
      expect(comments[0].location.begin).to eq(0)
      expect(comments[0].location.end).to eq(6)

      expect(comments[1]).to be_instance_of(LibRubyParser::Comment)
      expect(comments[1].location).to be_instance_of(LibRubyParser::Loc)
      expect(comments[1].location.begin).to eq(6)
      expect(comments[1].location.end).to eq(12)
    end
  end

  describe ':magic_comments' do
    it 'returns a list of magic comments' do
      code = <<~RUBY
        # frozen_string_literal: true
        42
      RUBY

      magic_comments = LibRubyParser::parse(code, {})[:magic_comments]
      expect(magic_comments.length).to eq(1)

      expect(magic_comments[0]).to be_instance_of(LibRubyParser::MagicComment)
      expect(magic_comments[0].kind).to eq(:frozen_string_literal)
      expect(magic_comments[0].key_l).to be_instance_of(LibRubyParser::Loc)
      expect(magic_comments[0].key_l.begin).to eq(2)
      expect(magic_comments[0].key_l.end).to eq(23)
      expect(magic_comments[0].value_l).to be_instance_of(LibRubyParser::Loc)
      expect(magic_comments[0].value_l.begin).to eq(25)
      expect(magic_comments[0].value_l.end).to eq(29)
    end
  end

  describe ':input' do
    it 'returns decoded input' do
      input = LibRubyParser::parse('42', {})[:input]
      expect(input).to eq('42')
    end
  end

  describe ':token_rewriter' do
    context 'when given' do
      it 'throws an error' do
        expect {
          LibRubyParser::parse('foo', token_rewriter: 42)
        }.to raise_error(
          NotImplementedError,
          ':token_rewriter is currently unsupported, please open an issue on https://github.com/lib-ruby-parser/ruby-bindings if you need this feature'
        )
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
        decoder = proc do |decoding, input|
          "foo"
        end

        result = LibRubyParser::parse(source, {})
        expect(result[:ast]).to be_nil
        expect(result[:diagnostics].length).to eq(1)
        expect(result[:diagnostics][0].message).to eq('encoding error: UnsupportedEncoding("WINDOWS-1251")')
      end
    end

    context 'when given' do
      it 'uses it to decode unsupported encoding' do
        called = false

        decoder = proc do |encoding, input|
          called = true
          expect(encoding).to eq('WINDOWS-1251')
          expect(input.encoding).to eq(Encoding::BINARY)
          expect(input.bytes).to eq(source.bytes)

          encoding = Encoding.find(encoding)
          input.force_encoding(encoding).encode('utf-8')
        end

        result = LibRubyParser::parse(source, decoder: decoder)

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
end
