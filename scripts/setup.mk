ifeq ($(OS), Windows_NT)
	DETECTED_OS = windows
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S), Linux)
		DETECTED_OS = linux
	else
		ifeq ($(UNAME_S), Darwin)
			DETECTED_OS = darwin
		else
			DETECTED_OS = unknown
		endif
	endif
endif

ifndef BUILD_ENV
	BUILD_ENV = debug
endif

ifeq ($(BUILD_ENV), debug)
	TARGET_DIR = target/debug
else
	TARGET_DIR = target/release
endif
