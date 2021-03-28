export RUBYOPT="-Ilib -Ibenchmark/helpers -rfiles -rmeasure -rripper -rlib-ruby-parser"

echo "Running ripper ..."
ruby benchmark/ripper.rb

echo "Running RubyVM::AbstractSyntaxTree ..."
ruby benchmark/rubyvm_ast.rb

echo "Running lib-ruby-parser ..."
ruby benchmark/lib-ruby-parser.rb
