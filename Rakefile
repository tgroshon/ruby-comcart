require "bundler/gem_tasks"
require "rake/testtask"
require "rake/extensiontask"

spec = Gem::Specification.load('comcart.gemspec')
Rake::ExtensionTask.new('comcart', spec)

task :default => :spec
