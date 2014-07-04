BINDIR = bin

client: client.cpp
	mkdir -p $(BINDIR)
	gcc client.cpp -o $(BINDIR)/$(patsubst %.cpp, %, $<)

all: client

.PHONY: all
