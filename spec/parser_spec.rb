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
end
