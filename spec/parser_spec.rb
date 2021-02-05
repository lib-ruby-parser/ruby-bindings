require 'spec_helper'

describe LibRubyParser do
  describe '.parse' do
    it 'parses given input' do
      code = "2 + 2"
      options = { buffer_name: "foo", debug: false }
      result = LibRubyParser.parse(code, options)
      p result
    end
  end
end
