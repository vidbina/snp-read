BINDIR = bin
SRCDIR = src

RM      = rm -rf
MKDIR   = mkdir -p
GCC     = gcc

client: $(SRCDIR)/client.cpp
	$(MKDIR) $(BINDIR)
	$(GCC) $(SRCDIR)/client.cpp -o $(BINDIR)/$(patsubst %.cpp,%,$(notdir $<))

clean:
	$(RM) $(BINDIR)

all: client

run-client: $(BINDIR)/client
	./$<


.PHONY: all clean run-client
