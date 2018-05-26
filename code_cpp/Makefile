SYSTEM     = x86-64_osx
LIBFORMAT  = static_pic

#------------------------------------------------------------
#
# When you adapt this makefile to compile your CPLEX programs
# please copy this makefile and set CPLEXDIR and CONCERTDIR to
# the directories where CPLEX and CONCERT are installed.
#
#------------------------------------------------------------

CPLEXDIR      = .
CONCERTDIR    = ./concert

# ---------------------------------------------------------------------
# Compiler selection 
# ---------------------------------------------------------------------

CCC = g++ 

# ---------------------------------------------------------------------
# Compiler options 
# ---------------------------------------------------------------------

CCOPT = -m64 -O -fPIC -fexceptions -DNDEBUG -DIL_STD -std=c++1z

# ---------------------------------------------------------------------
# Link options and libraries
# ---------------------------------------------------------------------

CPLEXBINDIR   = $(CPLEXDIR)/bin/$(BINDIST)
CPLEXLIBDIR   = $(CPLEXDIR)/lib/$(SYSTEM)/$(LIBFORMAT)
CONCERTLIBDIR = $(CONCERTDIR)/lib/$(SYSTEM)/$(LIBFORMAT)

CCLNDIRS  = -L$(CPLEXLIBDIR) -L$(CONCERTLIBDIR)
CCLNFLAGS = -lconcert -lilocplex -lcplex -m64 -lm -lpthread 

# ---------------------------------------------------------------------
# Temporary folder
# ---------------------------------------------------------------------

TARGET = lshaped

all: $(TARGET)

CONCERTINCDIR = $(CONCERTDIR)/include
CPLEXINCDIR   = $(CPLEXDIR)/include

EXINC         = $(CPLEXDIR)/include
EXDATA        = $(CPLEXDIR)/data
EXSRCCPP      = $(CPLEXDIR)/src

CFLAGS  = $(COPT)  -I$(CPLEXINCDIR)
CCFLAGS = $(CCOPT) -I$(CPLEXINCDIR) -I$(CONCERTINCDIR) 

SRC = $(shell find src -name *.cpp)
OBJ = $(SRC:%.cpp=%.o)


# ------------------------------------------------------------

clean :
	/bin/rm -rf $(TARGET)
	/bin/rm -rf *.mps *.ord *.sos *.lp *.sav *.net *.msg *.log *.clp
	/bin/rm -rf $(OBJ)

# ------------------------------------------------------------
#
# The code
#

$(TARGET): $(OBJ)
	$(CCC) $(CCFLAGS) $(CCLNDIRS) -o $(TARGET) $(OBJ) $(CCLNFLAGS)

%.o: %.cpp
	$(CCC) -c $(CCFLAGS) $< -o $@

# Local Variables:
# mode: makefile
# End:
