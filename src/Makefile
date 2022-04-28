VERSION=1.0.0
ZIP=xkucik00_xotrad00_xskund02_xvince01.zip
DIRS=mockup plan profiling src
FILES=debugging.png dokumentace.pdf screenshot.png skutecnost.txt hodnoceni.txt README.md .git .gitignore .editorconfig

.PHONY: all calc pack clean doc run install

all: calc

setup:
	sudo apt-get install qt5-default

calc:
	cmake -B../build -S. && cd ../build && make

pack: clean
	mkdir -p ../../repo && cp -a ../. ../../repo
	cd ../.. && zip -r $(ZIP) repo
	cd ../.. && rm -rf repo

clean:
	rm -rf ../build
	rm -rf doxygen-gen
	cd install && ./clean

doc:
	doxygen Doxyfile

run:
	cmake -B../build -S. && cd ../build && make && ./calc

install: calc
	cd install && ./install calc $(VERSION)
