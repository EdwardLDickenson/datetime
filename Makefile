cc = clang++
inc = "../LazyTest"
flags = -Wall -std=c++17 -I $(inc)


all:
	$(cc) $(flags) main.cpp -o main

clean:
	rm *.csv main
