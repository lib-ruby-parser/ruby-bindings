# frozen_string_literal: true

require 'bundler/gem_tasks'

task :compile do
  sh 'make attached-bundle'
end

require 'rspec/core/rake_task'
RSpec::Core::RakeTask.new(:spec)

task default: %i[compile spec]
