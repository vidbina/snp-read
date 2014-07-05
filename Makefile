BINDIR = bin
SRCDIR = src

RM      = rm -rf
MKDIR   = mkdir -p
GCC     = gcc

BINS    = client \
					server
FILES   = $(patsubst %,$(SRC)/%.cpp,$(BINS))

$(BINDIR)/server: $(SRCDIR)/server.cpp
	$(MKDIR) $(BINDIR)
	$(GCC) $(SRCDIR)/server.cpp -o $(BINDIR)/$(patsubst %.cpp,%,$(notdir $<))

$(BINDIR)/client: $(SRCDIR)/client.cpp
	$(MKDIR) $(BINDIR)
	$(GCC) $(SRCDIR)/client.cpp -o $(BINDIR)/$(patsubst %.cpp,%,$(notdir $<))

clean:
	$(RM) $(BINDIR)

all: client

run-server: $(BINDIR)/server
	./$<

run-client: $(BINDIR)/client
	./$<


.PHONY: all clean run-client
