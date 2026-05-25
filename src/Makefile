# ----- Multi-machine makefile ----------------------------------------------- #

SHELL	= /bin/sh
PYTHON	= python3

# ----- Command-line options (default values and checks) --------------------- #

config	= default
enable	= static
prefix	= ../build/make

ifeq ($(enable),static)
OBJDIR	= Obj_$(config)
else ifeq ($(enable),shared)
OBJDIR	= Obj_shared_$(config)
else
$(error ERROR: Invalid enable option - $(enable))
endif

# ----- Definitions ---------------------------------------------------------- #

EXE	= ko

ARLIB	= lib$(EXE).a
SHLIB	= lib$(EXE).so
LIBLINK	= -L. -l$(EXE)

SRC	= $(wildcard *.cxx)
OBJ	= $(patsubst %.cxx, %.o, $(SRC))

SRCLIB	= $(filter-out main.cxx, $(SRC))
OBJLIB	= $(filter-out main.o, $(OBJ))

BINDIR	= $(prefix)/bin
LIBDIR	= $(prefix)/lib

TPL	= $(@:lib-%=%)
TPLDIR	= ../lib/$(TPL)

# ----- Build the program ---------------------------------------------------- #

all	:
	@ echo "Gathering build information...."
	@ if [ ! -f "MAKE/DEFAULT/Makefile.$(config)" \
	  -a ! -f "MAKE/OPTIONS/Makefile.$(config)" \
	  -a ! -f "MAKE/MACHINES/Makefile.$(config)" \
	  -a ! -f "MAKE/MINE/Makefile.$(config)" ] ; then \
	  echo "" ; \
	  echo "ERROR: Makefile.$(config) was not found" ; exit 1 ; \
	fi
	@ if [ ! -d "$(OBJDIR)" ] ; then mkdir -p "$(OBJDIR)" ; fi
	@ if [ -f "MAKE/DEFAULT/Makefile.$(config)" ] ; \
	  then cp "MAKE/DEFAULT/Makefile.$(config)" "$(OBJDIR)/Makefile" ; fi
	@ if [ -f "MAKE/OPTIONS/Makefile.$(config)" ] ; \
	  then cp "MAKE/OPTIONS/Makefile.$(config)" "$(OBJDIR)/Makefile" ; fi
	@ if [ -f "MAKE/MACHINES/Makefile.$(config)" ] ; \
	  then cp "MAKE/MACHINES/Makefile.$(config)" "$(OBJDIR)/Makefile" ; fi
	@ if [ -f "MAKE/MINE/Makefile.$(config)" ] ; \
	  then cp "MAKE/MINE/Makefile.$(config)" "$(OBJDIR)/Makefile" ; fi
ifeq ($(enable),static)
	@ echo ""
	@ echo "Building static library:"
	@ cd "$(OBJDIR)" && \
	  $(MAKE) $(MAKEFLAGS) "OBJ = $(OBJLIB)" \
	  "SHLIB =" "SHFLAGS =" "SHLIBFLAGS =" "RPATH_NAME =" "RPATH_DIRS =" \
	  "ARLIB = $(ARLIB)" $(ARLIB)
	@ echo ""
	@ echo "Linking executable:"
	@ cd "$(OBJDIR)" && \
	  $(MAKE) $(MAKEFLAGS) "OBJ = main.o" \
	  "SHLIB =" "SHFLAGS =" "SHLIBFLAGS =" "RPATH_NAME =" "RPATH_DIRS =" \
	  "LIB = $(ARLIB)" "LIBLINK = $(LIBLINK)" "EXE = $(EXE)" $(EXE)
else ifeq ($(enable),shared)
	@ echo ""
	@ echo "Building shared library:"
	@ cd "$(OBJDIR)" && \
	  $(MAKE) $(MAKEFLAGS) "OBJ = $(OBJLIB)" \
	  "ARLIB =" "AR =" "ARFLAGS =" \
	  "SHLIB = $(SHLIB)" $(SHLIB)
	@ echo ""
	@ echo "Linking executable:"
	@ cd "$(OBJDIR)" && \
	  $(MAKE) $(MAKEFLAGS) "OBJ = main.o" \
	  "ARLIB =" "AR =" "ARFLAGS =" \
	  "LIB = $(SHLIB)" "LIBLINK = $(LIBLINK)" "EXE = $(EXE)" $(EXE)
endif

# ----- Remove files generated during the build ------------------------------ #

clean	:
	@ echo "Removing build artifacts: $(OBJDIR)"
	@ rm -rf "$(OBJDIR)"

clean-%	:
	@ if [ "$@" = "clean-all" ] ; then \
	  echo "Removing all build artifacts" ; \
	  rm -rf $(wildcard Obj_*) "$(EXE)" "$(ARLIB)" "$(SHLIB)" ; \
	else \
	  echo "ERROR: Invalid clean option - $*" ; exit 1 ; \
	fi

# ----- Generate / view reference manuals ------------------------------------ #

doc-%	:
	@ if [ "$@" = "doc-tex" ] ; then \
	  echo "ERROR: doc-tex not implemented" ; exit 1 ; \
	elif [ "$@" = "doc-man" ] ; then \
	  echo "Loading the man page" ; sleep 1 ; \
	  man ../doc/man/ko.1 ; \
	else \
	  echo "ERROR: Invalid doc option - $*" ; exit 1 ; \
	fi

# ----- Build the program and copy files to a location for use --------------- #

install	: all
	@ mkdir -p "$(BINDIR)" "$(LIBDIR)"
ifeq ($(enable),static)
	@ echo ""
	@ echo "Installing $(EXE) in $(BINDIR)"
	@ install -c "$(OBJDIR)/$(EXE)" "$(BINDIR)"
	@ echo "Installing $(ARLIB) in $(LIBDIR)"
	@ install -c "$(OBJDIR)/$(ARLIB)" "$(LIBDIR)"
else ifeq ($(enable),shared)
	@ echo ""
	@ echo "Installing $(EXE) in $(BINDIR)"
	@ install -c "$(OBJDIR)/$(EXE)" "$(BINDIR)"
	@ echo "Installing $(SHLIB) in $(LIBDIR)"
	@ install -c "$(OBJDIR)/$(SHLIB)" "$(LIBDIR)"
endif


# ----- Build external libraries --------------------------------------------- #

lib-%	:
	@ if [ "$@" = "lib-all" ] ; then \
	  for d in ../lib/* ; do \
	    if [ -d $$d ] ; then \
	      if [ -f $$d/Install.py ] ; then \
	        ( cd $$d && "$(PYTHON)" "Install.py" $(args) ) || exit 1 ; \
	      else \
	        echo "ERROR: Install.py does not exist in $$d" ; exit 1 ; \
	      fi ; \
	    fi ; \
	  done ; \
	elif [ -d "$(TPLDIR)" ] ; then \
	  if [ -f "$(TPLDIR)/Install.py" ] ; then \
	    ( cd "$(TPLDIR)" && "$(PYTHON)" "Install.py" $(args) ) || exit 1 ; \
	  else \
	    echo "ERROR: Install.py does not exist in $(TPLDIR)" ;  exit 1 ; \
	  fi ; \
	else \
	  echo "ERROR: Invalid lib option - $(TPL)" ; exit 1 ; \
	fi ; touch main.cxx

# ----- Create a tar file of the source files -------------------------------- #

tar	: clean-all
	@ echo "Creating ../$(EXE)_src.tar.gz"
	@ tar -czf "../$(EXE)_src.tar.gz" -C ".." "src"

# ----- Brief help message --------------------------------------------------- #

help	:
	@ echo "Execute any of the following commands from within the src directory:"
	@ echo ""
	@ echo "make [all]                   build the program with default settings"
	@ echo "make [all] [config=CONFIG]   build the program using CONFIG"
	@ echo "make install [config=CONFIG] build and install the program using CONFIG"
	@ echo ""
	@ echo "make clean [config=CONFIG]   delete build artifacts for CONFIG"
	@ echo "make clean-all               delete all build artifacts"
	@ echo ""
	@ echo "make doc-tex                 create the latex documentation"
	@ echo "make doc-man                 show the man page"
	@ echo ""
	@ echo "make lib-package             print the help message for package in ../lib"
	@ echo "make lib-package args=\"...\"  download/build/install package in ../lib"
	@ echo "make lib-all args=\"...\"      download/build/install all packages in ../lib"
	@ echo ""
	@ echo "make tar                     create a tar file of the source files"
	@ echo ""
	@ echo "CONFIG (default: config=default) is this option from src/MAKE/DEFAULT:"
	@ echo ""
	@ files=$$(ls MAKE/DEFAULT/Makefile.* 2>/dev/null) ; \
	  for file in $$files ; do head -1 $$file ; done
	@ echo ""
	@ echo "... or one of these options from from src/MAKE/OPTIONS:"
	@ echo ""
	@ files=$$(ls MAKE/OPTIONS/Makefile.* 2>/dev/null) ; \
	  for file in $$files ; do head -1 $$file ; done
	@ echo ""
	@ echo "... or one of these options from src/MAKE/MACHINES:"
	@ echo ""
	@ files=$$(ls MAKE/MACHINES/Makefile.* 2>/dev/null) ; \
	  for file in $$files ; do head -1 $$file ; done
	@ echo ""
	@ echo "... or one of these options from src/MAKE/MINE:"
	@ echo ""
	@ files=$$(ls MAKE/MINE/Makefile.* 2>/dev/null) ; \
	  for file in $$files ; do head -1 $$file ; done
	@ echo ""
	@ echo "... or a new Makefile.config can be created and placed in src/MAKE/MINE for use"

# ----- Developer / maintainer tools ----------------------------------------- #

check	?=
fix	?=

format	:
ifneq ($(check),)
	@ clang-format --verbose --style=file $(check)
endif
ifneq ($(fix),)
	@ clang-format --verbose --style=file -i $(fix)
endif

# ----- End of the makefile -------------------------------------------------- #
