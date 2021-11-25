require 'open-uri'
require 'json'

url = ENV.fetch('URL') { abort 'URL env var must be provided.' }.strip
save_as = ENV.fetch('SAVE_AS') { abort 'SAVE_AS env var must be provided' }.strip

File.open(save_as, 'wb') do |file|
    URI.open(url, 'rb') do |asset|
        file.write(asset.read)
    end
end
