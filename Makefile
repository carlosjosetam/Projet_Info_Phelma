TARGET=as-mips
DIRNAME=`basename $(PWD)`
CC=`which gcc`
LD=`which gcc`
RM=`which rm` -f
DOXYGEN=`which doxygen`

SRCDIR=src
INCDIR=include
TESTDIR=testing
DOCDIR=doc

GARBAGE=*~ $(SRCDIR)/*~ $(INCDIR)/*~ $(TESTDIR)/*~

INCLUDE=-I$(INCDIR)

# Pour activer les sorties INFO_MSG, ajouter -DVERBOSE aux CFLAGS
CFLAGS=-Wall -ansi $(INCLUDE)
LFLAGS=-lm

CFLAGS_DBG=$(CFLAGS) -g -DDEBUG -Wall
CFLAGS_RLS=$(CFLAGS)

SRC=$(wildcard $(SRCDIR)/main.c)
SRC+=$(wildcard $(SRCDIR)/global.c)
SRC+=$(wildcard $(SRCDIR)/structures/*.c)
SRC+=$(wildcard $(SRCDIR)/analyse_lexicale/*.c)
SRC+=$(wildcard $(SRCDIR)/analyse_gramatical/*.c)

OBJ_DBG=$(SRC:.c=.dbg)
OBJ_RLS=$(SRC:.c=.rls)


all :
	@echo "in " $(DIRNAME)
	@echo ""
	@echo "Usage:"
	@echo ""
	@echo "make debug   => build DEBUG   version"
	@echo "make release => build RELEASE version"
	@echo "make clean   => clean everything"
	@echo "make archive => produce an archive for the deliverable"

debug   : $(OBJ_DBG)
	$(LD) $^ $(LFLAGS) -o $(TARGET)

debug_run   : $(OBJ_DBG)
	$(LD) $^ $(LFLAGS) -o $(TARGET)
	./as-mips tests/test_Automate_data.s

release : $(OBJ_RLS)
	$(LD) $^ $(LFLAGS) -o $(TARGET)

release_run : $(OBJ_RLS)
	$(LD) $^ $(LFLAGS) -o $(TARGET)
	./as-mips tests/test_Automate_data.s

%.dbg : %.c
	$(CC) $< $(CFLAGS_DBG) -c -o $(basename $<).dbg

%.rls : %.c
	$(CC) $< $(CFLAGS_RLS) -c -o $(basename $<).rls

docu :
	$(DOXYGEN)

clean :
	$(RM) $(TARGET) $(SRCDIR)/*.orig $(SRCDIR)/*.dbg $(SRCDIR)/*.rls $(GARBAGE)
	$(RM) -r $(DOCDIR)/*

archive :
	make clean
	cd .. && tar -czvf as-mips-`whoami`-`date +%d-%m-%H-%M`.tgz $(DIRNAME) && cd $(DIRNAME)
