CXX = g++
SRC = main.cpp
CXXFLAGS = -std=c++20

ifeq ($(OS),Windows_NT)
    EXE = build\uber_rider_flow.exe
    MKDIR = if not exist build mkdir build
    RM = if exist $(EXE) del $(EXE)
else
    EXE = build/uber_rider_flow.out
    MKDIR = mkdir -p build
    RM = rm -f $(EXE)
endif

all:
	@$(MKDIR)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(EXE)

clean:
	$(RM)

