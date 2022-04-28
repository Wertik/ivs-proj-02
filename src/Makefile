VERSION=1.0.0
NAME=xkucik00_xotrad00_xskund02_xvince01
ZIP=$(NAME).zip
DIRS=mockup plan profiling src
FILES=debugging.png dokumentace.pdf screenshot.png skutecnost.txt hodnoceni.txt README.md .git .gitignore .editorconfig

.PHONY: all calc pack clean run install

all: calc

calc:
	cmake -B../build -S. && cd ../build && make

pack: clean
	mkdir -p ../../repo && cp -a ../. ../../repo
	cd ../.. && zip -r $(ZIP) repo
	cd ../.. && rm -rf repo

clean:
	rm -rf ../build
	cd install && ./clean

run:
	cmake -B../build -S. && cd ../build && make && ./calc

install: calc
	cd install && ./install calc $(VERSION)
