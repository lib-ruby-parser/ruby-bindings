measure(FILES.count) do
  FILES.each do |(filepath, src)|
    LibRubyParser.parse(src, buffer_name: filepath)
  end
end
