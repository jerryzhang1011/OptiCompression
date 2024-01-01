# Define the compiler
CXX=g++

# Define any compile-time flags
CXXFLAGS=-Wall -g -std=c++20

# Define the C++ source files
SRCS=main.cc bzip2Modified.cc huffman.cc msd.cc mtf.cc rle.cc bucket_sort.cc bwt.cc binaryDataConvertion.cc

# Define the C++ object files 
OBJS=$(SRCS:.cc=.o)

# Define the executable file 
MAIN=bzip2

.PHONY: depend clean

all:    $(MAIN)
	@echo Program named $(MAIN) has been compiled with C++20 support

$(MAIN): $(OBJS) 
	$(CXX) $(CXXFLAGS) -o $(MAIN) $(OBJS)

.cc.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) *.o *~ $(MAIN)

depend: $(SRCS)
	makedepend $^

# DO NOT DELETE THIS LINE -- make depend needs it