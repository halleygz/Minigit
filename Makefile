CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -I"C:/Users/hp/scoop/apps/openssl/current/include"
SRC = $(wildcard src/*.cpp) $(wildcard src/*/*.cpp) $(wildcard src/*/*/*.cpp)
OUT = minigit
LDFLAGS = -L"C:/Users/hp/scoop/apps/openssl/current/lib" -lssl -lcrypto

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(OUT)

test: $(OUT)
	@echo "Running sample tests..."
	@./$(OUT) init
	@touch testfile.txt
	@echo "Hello MiniGit!" > testfile.txt
	@./$(OUT) add testfile.txt
	@echo "Tests done."