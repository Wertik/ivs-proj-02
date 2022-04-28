all: calc

calc:
	cmake -B../build -S. && cd ../build && make

run:
	cmake -B../build -S. && cd ../build && make && ./calc

clean:
	rm -r ../build