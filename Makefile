#
# Makefile for assignment 2 of the Compiler Construction course.
# LIACS, Leiden University.
#

CC        = gcc
CXX       = g++
LEX       = lex
YACC      = yacc

WARNINGS  = -Wall -ansi
OTHERS    = -g
DEFINES   = -DDEBUG
IDIRS     = -I.

CFLAGS    = $(WARNINGS) $(OTHERS) $(DEFINES) $(IDIRS) -lc++
LFLAGS    = -l 
YFLAGS    = --defines --debug --verbose
LDFLAGS   = -g
LOADLIBS  = -ll -ly

#
# If you want to add another C/C++ file to the compiler, add the name of the
# corresponding .o file to the OBJFILES macro below in Makefile.in:
#
OBJFILES  = debug.o
OBJDIR    = gen/
OBJS      = $(addprefix $(OBJDIR),$(OBJFILES))

# Precompiled object files
POBJFILES = types.o SyntaxTree.o Node.o Symbol.o SymbolTable.o Scope.o
POBJDIR   = obj/64/
POBJS     = $(addprefix $(POBJDIR),$(POBJFILES))

IMPORTANT	= comp.[hly] *.h *.c *.cc \
		  Makefile

.PHONY: all first clean backup dirs showdeps

all: Makefile comp

# To be executed before the very first build
first: dirs

Makefile: Makefile.in
	./config.status

# Dependency stuff
comp: $(OBJDIR)y.tab.o $(OBJDIR)lex.yy.o $(OBJS) $(POBJS)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LOADLIBS)

$(OBJDIR)y.tab.c: comp.y 
	$(YACC) $(YFLAGS) $< -o $(OBJDIR)y.tab.c

$(OBJDIR)lex.yy.c: comp.l 
	$(LEX) $(LFLAGS) -o$@ $<

clean:	
	rm -f $(OBJDIR){lex.yy.c,y.tab.*,y.output,*.o} *~ comp \
	    `find . -name core -o -name \*\.bak`

backup:
	tar cfz ../CoCo-`date +'%y%m%d-%H%M'`.tar.gz $(IMPORTANT)

dirs:
	mkdir gen

# Show dependencies between .c files
showdeps:
	$(CXX) -MM *.c *.cc

# Dependency stuff
$(OBJDIR)lex.yy.o: $(OBJDIR)lex.yy.c $(OBJDIR)y.tab.h
	$(CXX) $(CFLAGS) -c -o $@ $<

$(OBJDIR)y.tab.o: $(OBJDIR)y.tab.c
	$(CXX) $(CFLAGS) -c -o $@ $<

$(OBJDIR)%.o: %.c
	$(CXX) $(CFLAGS) -c -o $@ $<

$(OBJDIR)%.o: %.cc
	$(CXX) $(CFLAGS) -c -o $@ $<
