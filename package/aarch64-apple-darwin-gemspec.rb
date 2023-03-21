# frozen_string_literal: true

require_relative 'lib/lib-ruby-parser/version'

Gem::Specification.new do |spec|
  spec.name          = 'lib-ruby-parser'
  spec.version       = LibRubyParser::VERSION
  spec.licenses      = ['MIT']
  spec.authors       = ['Ilya Bylich']
  spec.email         = ['ibylich@gmail.com']

  spec.summary       = 'Ruby parser written in Rust.'
  spec.description   = 'Ruby bindings for lib-ruby-parser.'
  spec.homepage      = 'https://github.com/lib-ruby-parser/ruby-bindings'

  spec.required_ruby_version = Gem::Requirement.new('>= 2.6.0')
  spec.platform              = 'arm64-darwin'

  spec.metadata['homepage_uri'] = spec.homepage
  spec.metadata['source_code_uri'] = 'https://github.com/lib-ruby-parser/ruby-bindings'

  spec.files = [
    'README.md',
    'lib-ruby-parser.gemspec',
    'lib/lib-ruby-parser.rb',
    'lib/lib-ruby-parser/version.rb',
    'lib/lib-ruby-parser/messages.rb',
    'lib/lib-ruby-parser/nodes.rb',
    'lib/lib-ruby-parser/native/aarch64-apple-darwin/3.2/lib_ruby_parser.bundle',
    'lib/lib-ruby-parser/native/aarch64-apple-darwin/3.1/lib_ruby_parser.bundle',
    'lib/lib-ruby-parser/native/aarch64-apple-darwin/3.0/lib_ruby_parser.bundle',
  ]
  spec.bindir        = 'exe'
  spec.executables   = spec.files.grep(%r{\Aexe/}) { |f| File.basename(f) }
  spec.require_paths = ['lib']
end
