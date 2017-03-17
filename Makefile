all: *.cpp
	g++ -std=c++11 *.cpp -lreadline -Wextra -Wall -Wpedantic -Werror -o duk

clean:
	rm -f *.o *.a duk
