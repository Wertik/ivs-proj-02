VERSION=1.0.0

.PHONY: all calc run install clean

all: calc

calc:
	cmake -B../build -S. && cd ../build && make

run:
	cmake -B../build -S. && cd ../build && make && ./calc

install: calc
	cd ./install && ./install calc $(VERSION)

clean:
	rm -r ../build
	cd ./install && ./clean