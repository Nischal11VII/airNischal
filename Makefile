CXX = clang++
CXXFLAGS = -std=c++20

.PHONY: fly
fly: main.cpp
	$(CXX) $(CXXFLAGS) Database.cpp logIn.cpp main.cpp menu.cpp showBook.cpp signUp.cpp -o fly -lncurses
	./fly

.PHONY: clean
clean:
	rm -f fly


