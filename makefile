.PHONY: main
main:
	cmake -B build;
	cmake --build build --target CG_hw1;
	mv ./build/bin/CG_hw1 ./CG_hw1