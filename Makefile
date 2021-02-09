TARGET=asm

PREFIX := build/

OBJDIR := $(PREFIX)obj
DEPDIR := $(PREFIX)dep
SRCDIR := src

INCLUDE := -I include


## Arguments
CXXDEP   ?= -MMD -MP -MF $(@:$(SRCDIR)/%.cpp=$(DEPDIR)/%.d)
LDFLAGS  ?=
CXXFLAGS ?= -c -Wall -Wextra -std=gnu++11 $(INCLUDE) $(CXXDEP)

SRCS := $(wildcard $(SRCDIR)/*.cpp)

### Targets
.PHONY: all clean test

all: $(TARGET)
clean:
	$(RM) $(DEPDIR)/* $(OBJDIR)/* $(TARGET)
test: $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
	# required arguments are 'ARGS' 'TEST'

$(TARGET): $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
	@echo "link    [$@]"
	@$(CXX) -o $@ $(LDFLAGS) $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@echo "compile [$*]"
	@$(CXX) -o $@ $(CXXFLAGS) $(SRCDIR)/$*.cpp

# Source Dependencies
-include $(SRCS:$(SRCDIR)/%.cpp=$(DEPDIR)/%.d)