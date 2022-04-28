VERSION=1.0.0
ZIP=xkucik00_xotrad00_xskund02_xvince01.zip

.PHONY: all calc pack clean test doc run install

all: calc profile

setup:
	sudo apt-get install qt5-default
	sudo apt-get install libgtest-dev

calc:
	cmake -B../build -S. && cd ../build && make

pack: clean
	mkdir -p ../../repo && cp -a ../. ../../repo
	cd ../.. && zip -r $(ZIP) repo
	cd ../.. && rm -rf repo

clean:
	rm -rf ../build
	rm -rf ../packages
	rm -rf doxygen-gen
	cd tests && rm -rf CMakeFiles runTests cmake_install.cmake CMakeCache.txt Makefile
	cd profiling && rm -rf stddev gmon.out

test:
	cd tests && cmake CMakeLists.txt && make && ./runTests

doc:
	doxygen Doxyfile

run:
	cmake -B../build -S. && cd ../build && make && ./calc

profile: profiling/profiling.cpp mathlib/mathlib.*
	g++ -pg -g -o profiling/stddev $^

install: calc
	cd install && ./install $< $(VERSION)
