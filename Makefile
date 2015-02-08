#CXX := clang++
hackasm_SRCDIR := src
hackasm_TEST_SRCDIR := test
hackasm_EXPERIMENTAL_SRCDIR := experimentals
hackasm_BUILDDIR := build
hackasm_TARGET_DIR := target
hackasm_TARGET := target/hackasm
hackasm_TEST_TARGET := target/tester
hackasm_EXPERIMENTAL_TARGET := target/experimentals

hackasm_SRCEXT := cpp
hackasm_SOURCES := $(shell find $(hackasm_SRCDIR) -type f -name *.$(hackasm_SRCEXT))
hackasm_TEST_SOURCES := $(shell find $(hackasm_TEST_SRCDIR) -type f -name *.$(hackasm_SRCEXT))
hackasm_EXPERIMENTAL_SOURCES := $(shell find $(hackasm_EXPERIMENTAL_SRCDIR) -type f -name *.$(hackasm_SRCEXT))
hackasm_OBJECTS := $(patsubst $(hackasm_SRCDIR)/%,$(hackasm_BUILDDIR)/%,$(hackasm_SOURCES:.$(hackasm_SRCEXT)=.o))
hackasm_TEST_OBJECTS := $(shell find $(hackasm_BUILDDIR) -type f -name *.o ! -name main.o)
CXXFLAGS += -g -Wall -std=c++11 -stdlib=libc++ -O3 -flto
LDFLAGS += -lboost_unit_test_framework -lboost_system -L $(BOOST_LIBS)/lib
LIB :=
INC := -I headers -I $(BOOST_LIBS)/include

$(hackasm_TARGET): $(hackasm_OBJECTS)
	@echo " Linking..."
	@echo " $(CXX) $^ -o $(hackasm_TARGET) $(LIB)"; $(CXX) $^ -o $(hackasm_TARGET) $(LIB)

$(hackasm_BUILDDIR)/%.o: $(hackasm_SRCDIR)/%.$(hackasm_SRCEXT)
	@mkdir -p $(hackasm_BUILDDIR)
	@echo " $(CXX) $(CXXFLAGS) $(INC) -c -o $@ $<"; $(CXX) $(CXXFLAGS) $(INC) -c -o $@ $<

tester:
	$(CXX) $(CXXFLAGS) $(INC) $(hackasm_TEST_SOURCES) $(LIB) -o $(hackasm_TEST_TARGET) $(hackasm_TEST_OBJECTS) $(LDFLAGS)

clean:
	@echo " Cleaning...";
	@echo " $(RM) $(hackasm_BUILDDIR)/* $(hackasm_TARGET_DIR)/*"; $(RM) -r $(hackasm_BUILDDIR)/* $(hackasm_TARGET_DIR)/*

experimentals:
	@echo "Building experimental code...";
	@echo " $(CXX) $(CXXFLAGS) $(INC) $(hackasm_EXPERIMENTAL_SOURCES) $(LIB) -o $(hackasm_EXPERIMENTAL_TARGET) $(LDFLAGS)"
	$(CXX) $(CXXFLAGS) $(INC) $(hackasm_EXPERIMENTAL_SOURCES) $(LIB) -o $(hackasm_EXPERIMENTAL_TARGET) $(LDFLAGS)

.PHONY: clean
