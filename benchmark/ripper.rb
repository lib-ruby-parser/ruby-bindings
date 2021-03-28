measure(FILES.count) do
  FILES.each do |(filepath, src)|
    Ripper.sexp(src, filepath)
  end
end
