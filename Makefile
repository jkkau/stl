all:
	mkdir -p build && cd build && cmake .. && make -j

test:
	ctest --output-on-failure

format:
	astyle --style=kr --indent=force-tab=4 *.cc *.hh

clean:
	rm -rf build