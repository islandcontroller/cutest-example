# Project name (can be overridden by PROJ_NAME=... make ...)
PROJ_NAME ?= $(shell basename $(CURDIR))

# Compiler options
CCDEFS 	:= -D_UNIT_TEST_ -DCUTEST_PROJECT_NAME="\"$(PROJ_NAME)\""
CCFLAGS := -Wall

# Linker options
LDFLAGS := -z execstack

# Auto-detect include dirs
INCLUDE := $(shell find -type d -not -path '.' -not -path './.*')

# Auto-detect sources and generate object names
SRCS := $(shell find -name '*.c')
OBJS := $(SRCS:%.c=%.o)

# Used libraries
LIBS := cutest

# Compile object files
%.o: %.c
	gcc $(CCFLAGS) $(CCDEFS) $(addprefix -I,$(INCLUDE)) -c $< -o $@

# Link into executable
$(PROJ_NAME): $(OBJS)
	gcc $^ $(LDFLAGS) $(addprefix -l,$(LIBS)) -o $@

# 'all' build target
all: $(PROJ_NAME)
	./$<

# 'clean' build target
clean:
	@rm -rf $(PROJ_NAME) $(OBJS) report.html