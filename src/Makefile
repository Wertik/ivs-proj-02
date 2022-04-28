VERSION=1.0.0
ZIP=xkucik00_xotrad00_xskund02_xvince01.zip
DIRS=mockup plan profiling src
FILES=debugging.png dokumentace.pdf screenshot.png skutecnost.txt hodnoceni.txt README.md .gitignore .editorconfig

.PHONY: all calc pack clean run install

all: calc

calc:
	cmake -B../build -S. && cd ../build && make

pack:
	cd .. && zip -r $(ZIP) $(DIRS) $(FILES)

clean:
	rm -r ../build
	cd ./install && ./clean

run:
	cmake -B../build -S. && cd ../build && make && ./calc

install: calc
	cd ./install && ./install calc $(VERSION)
