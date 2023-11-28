.PHONY: main
main:
	cmake -B build;
	cmake --build build --target CG_hw4;
	mv ./build/bin/CG_hw4 ./CG_hw4
