EXENAME= sorting
OBJS = main.o core.o

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi

all : $(EXENAME)

$(EXENAME) : $(OBJS)
			 $(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

main.o : main.cpp core.h
			$(CXX) $(CXXFLAGS) main.cpp

core.o : core.cpp core.h
			$(CXX) $(CXXFLAGS) core.cpp

clean :
			  -rm -f *.o $(EXENAME)
