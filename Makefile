#CXX := clang++
hackasm_SRCDIR := src
hackasm_BUILDDIR := build
hackasm_TARGET := target/hackasm
hackasm_TEST_TARGET := target/tester

hackasm_SRCEXT := cpp
hackasm_SOURCES := $(shell find $(hackasm_SRCDIR) -type f -name *.$(hackasm_SRCEXT))
hackasm_OBJECTS := $(patsubst $(hackasm_SRCDIR)/%,$(hackasm_BUILDDIR)/%,$(hackasm_SOURCES:.$(hackasm_SRCEXT)=.o))
CXXFLAGS += -g -Wall -std=c++11 -stdlib=libc++
LDFLAGS += -lboost_unit_test_framework -lboost_system -L $(BOOST_LIBS)/lib
LIB :=
INC := -I headers -I $(BOOST_LIBS)/include

$(hackasm_TARGET): $(hackasm_OBJECTS)
	@echo " Linking..."
	@echo " $(CXX) $^ -o $(hackasm_TARGET) $(LIB)"; $(CXX) $^ -o $(hackasm_TARGET) $(LIB) $(LDFLAGS)

$(hackasm_BUILDDIR)/%.o: $(hackasm_SRCDIR)/%.$(hackasm_SRCEXT)
	@mkdir -p $(hackasm_BUILDDIR)
	@echo " $(CXX) $(CXXFLAGS) $(INC) -c -o $@ $<"; $(CXX) $(CXXFLAGS) $(INC) -c -o $@ $<

test:
	$(CXX) $(CXXFLAGS) $(INC) test/driver.cpp test/utility.cpp $(LIB) -o $(hackasm_TEST_TARGET) build/parser.o build/symbol_table.o $(LDFLAGS)

clean:
	@echo " Cleaning...";
	@echo " $(RM) $(hackasm_BUILDDIR) $(hackasm_TARGET)"; $(RM) $(hackasm_TARGET) $(hackasm_TEST_TARGET)

.PHONY: clean
