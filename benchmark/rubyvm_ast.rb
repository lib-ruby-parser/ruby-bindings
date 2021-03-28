unless defined?(RubyVM::AbstractSyntaxTree)
  puts "This benchmark requires RubyVM::AbstractSyntaxTree, upgrade Ruby to run it"
  exit 1
end

require 'pp'

$VERBOSE = nil

def walk(tree)
  return unless tree.respond_to?(:children)
  tree.children.each { |child| walk(child) }
  true
end

measure(FILES.count) do
  FILES.each do |(filepath, src)|
    walk RubyVM::AbstractSyntaxTree.parse(src)
  rescue SyntaxError => e
    # ignore
  end
end
