def measure(files_count)
  GC.disable
  start = Process.clock_gettime(Process::CLOCK_MONOTONIC)
  yield
  now = Process.clock_gettime(Process::CLOCK_MONOTONIC)
  puts "Time taken: #{now - start} (total files: #{files_count})"
  GC.enable
end
