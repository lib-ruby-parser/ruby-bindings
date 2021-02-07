require 'spec_helper'

describe LibRubyParser do
  describe ':ast' do
    it 'returns ast' do
      result = LibRubyParser.parse('42', {})

      expect(result[:ast]).to be_instance_of(LibRubyParser::Int)
      expect(result[:ast].value).to eq('42')
      expect(result[:ast].operator_l).to be_nil
      expect(result[:ast].expression_l).to be_instance_of(LibRubyParser::Range)
      expect(result[:ast].expression_l.begin_pos).to eq(0)
      expect(result[:ast].expression_l.end_pos).to eq(2)
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
      expect(diagnostics[0].range).to be_instance_of(LibRubyParser::Range)
      expect(diagnostics[0].range.begin_pos).to eq(4)
      expect(diagnostics[0].range.end_pos).to eq(4)
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
      expect(comments[0].location).to be_instance_of(LibRubyParser::Range)
      expect(comments[0].location.begin_pos).to eq(0)
      expect(comments[0].location.end_pos).to eq(6)

      expect(comments[1]).to be_instance_of(LibRubyParser::Comment)
      expect(comments[1].location).to be_instance_of(LibRubyParser::Range)
      expect(comments[1].location.begin_pos).to eq(6)
      expect(comments[1].location.end_pos).to eq(12)
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
      expect(magic_comments[0].key_l).to be_instance_of(LibRubyParser::Range)
      expect(magic_comments[0].key_l.begin_pos).to eq(2)
      expect(magic_comments[0].key_l.end_pos).to eq(23)
      expect(magic_comments[0].value_l).to be_instance_of(LibRubyParser::Range)
      expect(magic_comments[0].value_l.begin_pos).to eq(25)
      expect(magic_comments[0].value_l.end_pos).to eq(29)
    end
  end

  describe ':input' do
    it 'returns decoded input' do
      input = LibRubyParser::parse('42', {})[:input]
      expect(input).to eq('42')
    end
  end

end
