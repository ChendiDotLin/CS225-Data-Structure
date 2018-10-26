
CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi

all : testimage testscene
testscene : testscene.o png.o rgbapixel.o image.o scene.o
	$(LD) testscene.o png.o rgbapixel.o image.o scene.o  $(LDFLAGS) -o testscene

testimage : testimage.o png.o rgbapixel.o image.o
	$(LD) testimage.o png.o rgbapixel.o image.o $(LDFLAGS) -o testimage

testscene.o : testscene.cpp png.h rgbapixel.h scene.h image.h
	$(CXX) $(CXXFLAGS) testscene.cpp

testimage.o : testimage.cpp png.h rgbapixel.h image.h
	$(CXX) $(CXXFLAGS) testimage.cpp

png.o : png.cpp png.h rgbapixel.h image.h
	$(CXX) $(CXXFLAGS) png.cpp

rgbapixel.o : rgbapixel.h rgbapixel.h
	$(CXX) $(CXXFLAGS) rgbapixel.cpp

image.o : png.h image.h 
	$(CXX) $(CXXFLAGS) image.cpp

scene.o : png.h image.h scene.h
	$(CXX) $(CXXFLAGS) scene.cpp

clean :
	- rm -f *.o testimage testscene;
