all: build

build: main.cu
	mkdir -p build
	nvcc -arch=sm_20 main.cu -o main
run:
	./build/main