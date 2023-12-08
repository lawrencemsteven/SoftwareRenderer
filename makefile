.PHONY: main
main:
	cmake -B build;
	cmake --build build --target CG_hw5;
	mv ./build/bin/CG_hw5 ./CG_hw5
