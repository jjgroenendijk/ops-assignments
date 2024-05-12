CXX = ${CC}
CXXFLAGS=-g -O0 -Wall -Wextra

EXECUTABLE = sharedQueue
SOURCES = ${wildcard *.c}
HEADERS = ${wildcard *.h}
OBJECTS = ${SOURCES:.c=.o}

# Rule to create .o from .c:
%.o: %.c
	$(CXX) $(CXXFLAGS) -c $< -o $@


.PHONY: all
all: printversion ${EXECUTABLE}

$(EXECUTABLE): $(OBJECTS) buildnumber.num
	$(CXX) $(CXXFLAGS) $(OBJECTS) $(LDXXFLAGS) -o $@
	@echo "-- Build: " $$(cat buildnumber.num)

# Create dependency file compiler option -MM
depend: $(SOURCES)
	$(CXX) $(CXXFLAGS) -MM  $^ > $@



# Buildnumber
buildnumber.num: $(OBJECTS)
	@if ! test -f buildnumber.num; then echo 0 > buildnumber.num; fi
	@echo $$(($$(cat buildnumber.num)+1)) > buildnumber.num

# Create a clean environment
.PHONY: clean
clean:
	$(RM) $(EXECUTABLE) $(OBJECTS)

# Clean up dependency file
.PHONY: clean-depend
clean-depend: clean
	$(RM) depend

printversion:
	${CC} --version |grep ${CC}

