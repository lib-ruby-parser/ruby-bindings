module LibRubyParser
  class Range
    attr_reader :begin_pos, :end_pos
  end

  class Loc
    attr_reader :begin, :end
  end

  class Token
    attr_reader :token_name, :loc
  end
end

require_relative './lib-ruby-parser/nodes'
require_relative './lib-ruby-parser/lib_ruby_parser_native'
