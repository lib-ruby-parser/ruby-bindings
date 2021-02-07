require 'spec_helper'

describe LibRubyParser do
  describe '.parse' do
    it 'parses given input' do
      code = "42"
      options = { buffer_name: "foo", debug: false }
      result = LibRubyParser.parse(code, options)

      expect(result[:ast]).to be_instance_of(LibRubyParser::Int)
      expect(result[:ast].value).to eq("42")
      expect(result[:ast].operator_l).to be_nil
      expect(result[:ast].expression_l).to be_instance_of(LibRubyParser::Range)
      expect(result[:ast].expression_l.begin_pos).to eq(0)
      expect(result[:ast].expression_l.end_pos).to eq(2)
    end
  end
end
