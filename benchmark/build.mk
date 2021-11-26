BASE_BENCHMARK_URL = https://github.com/lib-ruby-parser/bench/releases/download/v0.0.1

define download_latest_bench_asset
$(call download_file,$(BASE_BENCHMARK_URL)/$(1),$(2))
endef

benchmark/download:
	@echo "Downloading repos.zip..."
	$(call download_latest_bench_asset,repos.zip,benchmark/repos.zip)
	@echo "Unpacking repos.zip..."
	unzip --help
	ls -l benchmark/repos.zip
	unzip -q benchmark/repos.zip -d benchmark

	@echo "Downloading Rust parser..."
	$(call download_latest_bench_asset,$(BENCHMARK_RUNNER_ASSET_NAME),benchmark/rust-parser)
	chmod +x benchmark/rust-parser

	@echo "Downloading Ruby parser..."
	$(call download_latest_bench_asset,ruby-parser.rb,benchmark/ruby-parser.rb)

BENCHMARK_ASSETS = \
	benchmark/repos \
	benchmark/filelist \
	benchmark/repos.zip \
	benchmark/ruby-parser.rb \
	benchmark/rust-parser \
	benchmark/stats

benchmark/clear:
	rm -rf $(BENCHMARK_ASSETS)

define run_benchmark
cd benchmark && FILELIST_PATH=filelist $(1)
endef

benchmark/compare:
	$(call run_benchmark, ./rust-parser)
	$(call run_benchmark, ruby ruby-parser.rb)
	$(call run_benchmark, ruby lib-ruby-parser.rb)

BENCHMARK_RECORDING = $(TARGET).benchmark-out
benchmark/record:
	echo "Rust:" > $(BENCHMARK_RECORDING)
	$(call run_benchmark, ./rust-parser >> ../$(BENCHMARK_RECORDING))
	echo "Ripper:" >> $(BENCHMARK_RECORDING)
	$(call run_benchmark, ruby ruby-parser.rb >> ../$(BENCHMARK_RECORDING))
	echo "lib-ruby-parser-rb:" >> $(BENCHMARK_RECORDING)
	$(call run_benchmark, ruby lib-ruby-parser.rb >> ../$(BENCHMARK_RECORDING))
