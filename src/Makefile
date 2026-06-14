# Multi-machine makefile

# ---------------------------------------------------------------------------- #
# Special variables and settings

.DELETE_ON_ERROR:

.DEFAULT_GOAL := all
.SHELLFLAGS := -eu -c

SHELL := /bin/sh
PYTHON := python3

# ---------------------------------------------------------------------------- #
# Command-line options

config ?= relwithdebinfo
enable ?= static

ifeq ($(enable),static)
OBJDIR := Obj_$(config)
else ifeq ($(enable),shared)
OBJDIR := Obj_shared_$(config)
else
$(error ERROR: Invalid enable option "$(enable)". Use "static" or "shared")
endif

# ---------------------------------------------------------------------------- #
# Definitions

EXE := ko

ARLIB := lib$(EXE).a
SHLIB := lib$(EXE).so
LIBLINK := -L. -l$(EXE)

SRC := $(wildcard *.cxx)
OBJ := $(patsubst %.cxx, %.o, $(SRC))

SRCLIB := $(filter-out main.cxx, $(SRC))
OBJLIB := $(filter-out main.o, $(OBJ))

PREFIX := ../build/make
BINDIR := $(PREFIX)/bin
LIBDIR := $(PREFIX)/lib

TPL := $(@:lib-%=%)
TPLDIR := ../lib/$(TPL)

# ---------------------------------------------------------------------------- #
# Build, install, uninstall

.PHONY: all
all:
	@ echo "Gathering build information..."
	@ dirs="MAKE/CUSTOM MAKE/MACHINES MAKE/OPTIONS" ; \
	  found="" ; \
	  for d in $$dirs ; do \
	    if [ -f "$$d/Makefile.$(config)" ] ; then \
	      found="$$d/Makefile.$(config)" ; \
	      break ; \
	    fi ; \
	  done ; \
	  if [ -z "$$found" ] ; then \
	    echo "" ; \
	    echo "ERROR: Makefile.$(config) was not found" \
	         "in MAKE/{CUSTOM,MACHINES,OPTIONS}" ; \
	    exit 1 ; \
	  fi ; \
	  mkdir -p "$(OBJDIR)" ; \
	  { echo "include ../$$found" ; \
	  } > "$(OBJDIR)/Makefile"
ifeq ($(enable),static)
	@ echo ""
	@ echo "Building static library:"
	@ $(MAKE) -C "$(OBJDIR)" \
	  "OBJ = $(OBJLIB)" \
	  "SHLIB =" "SHFLAGS =" "SHLIBFLAGS =" "RPATH_NAME =" "RPATH_DIRS =" \
	  "ARLIB = $(ARLIB)" $(ARLIB)
	@ echo ""
	@ echo "Linking executable:"
	@ $(MAKE) -C "$(OBJDIR)" \
	  "OBJ = main.o" \
	  "SHLIB =" "SHFLAGS =" "SHLIBFLAGS =" "RPATH_NAME =" "RPATH_DIRS =" \
	  "LIB = $(ARLIB)" "LIBLINK = $(LIBLINK)" "EXE = $(EXE)" $(EXE)
else ifeq ($(enable),shared)
	@ echo ""
	@ echo "Building shared library:"
	@ $(MAKE) -C "$(OBJDIR)" \
	  "OBJ = $(OBJLIB)" \
	  "ARLIB =" "AR =" "ARFLAGS =" \
	  "SHLIB = $(SHLIB)" $(SHLIB)
	@ echo ""
	@ echo "Linking executable:"
	@ $(MAKE) -C "$(OBJDIR)" \
	  "OBJ = main.o" \
	  "ARLIB =" "AR =" "ARFLAGS =" \
	  "LIB = $(SHLIB)" "LIBLINK = $(LIBLINK)" "EXE = $(EXE)" $(EXE)
endif

.PHONY: install
install: all
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

.PHONY: uninstall
uninstall:
	@ echo "Uninstalling $(EXE) from $(BINDIR)"
	@ rm -rf -- "$(BINDIR)/$(EXE)"
	@ echo "Uninstalling libraries from $(LIBDIR)"
	@ rm -rf -- "$(LIBDIR)/$(ARLIB)" "$(LIBDIR)/$(SHLIB)"

# ---------------------------------------------------------------------------- #
# Cleanup

.PHONY: clean
clean:
	@ echo "Removing build artifacts: $(OBJDIR)"
	@ rm -rf -- "$(OBJDIR)"

.PHONY: clean-all
clean-all:
	@ echo "Removing all build artifacts"
	@ rm -rf -- $(wildcard Obj_*) "$(EXE)" "$(ARLIB)" "$(SHLIB)"

.PHONY: distclean
distclean: clean-all
	@ echo "Removing all installed files"
	@ rm -rf -- "$(BINDIR)/$(EXE)"
	@ rm -rf -- "$(LIBDIR)/$(ARLIB)" "$(LIBDIR)/$(SHLIB)"
	@ echo "Removing install directories"
	@ rmdir "$(BINDIR)" 2>/dev/null || true
	@ rmdir "$(LIBDIR)" 2>/dev/null || true

# ---------------------------------------------------------------------------- #
# Documentation

.PHONY: man
man:
	@ echo "Loading the man page" ; sleep 1 ; man ../doc/man/ko.1

.PHONY: tex
tex:
	@ echo "ERROR: tex documentation not implemented" ; exit 1

# ---------------------------------------------------------------------------- #
# Packaging and distribution

.PHONY: tar
tar:
	@ echo "Creating ../$(EXE)_src.tar.gz"
	@ tar -czf "../$(EXE)_src.tar.gz" -C ".." \
	  --exclude="src/Obj_*" \
	  --exclude="src/$(EXE)" \
	  --exclude="src/$(ARLIB)" \
	  --exclude="src/$(SHLIB)" \
	  "src"

# ---------------------------------------------------------------------------- #
# Help and utilities

.PHONY: help
help:
	@ echo "A short multi-machine build system how-to"
	@ echo ""
	@ echo "General usage from inside src:"
	@ echo ""
	@ echo "  make [TARGET] [config=CONFIG] [enable=static|shared]"
	@ echo ""
	@ echo "Targets:"
	@ echo ""
	@ echo "  all                    build the program (default)"
	@ echo "  install                build and install to prefix"
	@ echo "  uninstall              remove installed files from prefix"
	@ echo ""
	@ echo "  clean                  delete Obj_<config> build artifacts"
	@ echo "  clean-all              delete all Obj_* build artifacts"
	@ echo "  distclean              clean-all + uninstall + remove prefix"
	@ echo ""
	@ echo "  man                    view the man page (../doc/man/ko.1)"
	@ echo "  tex                    create latex documentation (not yet implemented)"
	@ echo ""
	@ echo "  tar                    create ../<exe>_src.tar.gz of src/ only"
	@ echo ""
	@ echo "  lib-all [args=...]     download/build/install all packages in ../lib"
	@ echo "  lib-<name> [args=...]  download/build/install <name> from ../lib"
	@ echo ""
	@ echo "Options:"
	@ echo ""
	@ echo "  config=CONFIG          build configuration (default: relwithdebinfo)"
	@ echo "  enable=MODE            static (default) or shared"
	@ echo ""
	@ echo "Available build configurations:"
	@ for d in MAKE/CUSTOM MAKE/MACHINES MAKE/OPTIONS ; do \
	  if ls "$$d"/Makefile.* 2>/dev/null >/dev/null 2>&1 ; then \
	  printf "\n  From %s:\n\n" "$$d" ; \
	  for f in "$$d"/Makefile.* ; do \
	    desc=$$(head -1 "$$f" | sed 's/^# //' || echo "No description available") ; \
	    printf "  %s\n" "$$desc" ; \
	  done ; \
	  fi ; \
	done

lib-%:
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

# ----- End of the makefile -------------------------------------------------- #
