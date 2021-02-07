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

  class Diagnostic
    attr_reader :level, :message, :range
  end

  class Comment
    attr_reader :location
  end

  class MagicComment
    attr_reader :kind, :key_l, :value_l
  end
end

require_relative './lib-ruby-parser/nodes'
require_relative './lib-ruby-parser/lib_ruby_parser_native'
