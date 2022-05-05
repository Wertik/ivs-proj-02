VERSION=1.1.0
NAME=xkucik00_xotrad00_xskund02_xvince01
ZIP=$(NAME).zip

.PHONY: all calc pack clean test doc run install

all: calc profile

setup:
	sudo apt-get install qt5-default
	sudo apt-get install libgtest-dev
	sudo apt-get install doxygen

calc:
	cmake -B../build -S. && cd ../build && make

pack: dirs clean
	mkdir -p ../../$(NAME)/repo && cp -a ../. ../../$(NAME)/repo
	cd ../.. && zip -r $(ZIP) $(NAME)
	cd ../.. && rm -rf $(NAME)

dirs: doc install
	mkdir -p ../../$(NAME)/doc && cp -a doxygen-gen ../../$(NAME)/doc
	mkdir -p ../../$(NAME)/install && cp -a ../packages/calc/calc_$(VERSION)_all.deb ../../$(NAME)/install

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
