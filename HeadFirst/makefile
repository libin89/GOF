# target file name, if not define PROGRAM, will use default value.
PROGRAM = test

# this macro which files will be compiled
DEFS = BEVERAGE

## Stable Section: usually no need to be changed. But you can add more.
##==========================================================================
SHELL   = /bin/sh
EMPTY   =
SPACE   = $(EMPTY) $(EMPTY)
ifeq ($(PROGRAM),)
  CUR_PATH_NAMES = $(subst /,$(SPACE),$(subst $(SPACE),_,$(CURDIR)))
  PROGRAM = $(word $(words $(CUR_PATH_NAMES)),$(CUR_PATH_NAMES))
  ifeq ($(PROGRAM),)
    PROGRAM = a.out
  endif
endif

# The source file types (headers excluded).
# .c indicates C source files, and others C++ ones.
SRCEXTS = .c .C .cc .cpp .CPP .c++ .cxx .cp

# The header file types.
INCEXTS = .h .H .hh .hpp .HPP .h++ .hxx .hp

# The directories in which source files reside.
# If not specified, only the current directory will be serached.
SRCDIRS = .
INCDIRS = .
# if has other directorys, need to add them
SRCDIRS += ./util
INCDIRS += ./util

# The directories which objects will be generated to
OBJDIR = .
# The command used to delete or move file.
RM     = rm -rf
#MV_OBJ = mv -f $(OBJS) ./build/obj
MV_OBJ = 
#MV_EXE = mv -f $(PROGRAM) ./build/exe	
MV_EXE = 

# The C/C++ program compiler.
CC = gcc
CXX = g++
MY_LIBS =
# The pre-processor and compiler options.
MY_CFLAGS = -pthread -Iutil -D$(DEFS)
# The pre-processor options used by the cpp (man cpp for more).
CPPFLAGS  = -Wall -Wno-strict-aliasing
# The pre-processor and compiler options.
# Users can override those variables from the command line.
CFLAGS  = -g -O2
CXXFLAGS = -g -O2
# The options used in linking as well as in any direct use of ld.
LDFLAGS   =

SRCS = $(foreach dir,$(SRCDIRS),$(wildcard $(addprefix $(dir)/*,$(SRCEXTS))))
INCS = $(foreach dir,$(INCDIRS),$(wildcard $(addprefix $(dir)/*,$(INCEXTS))))
SRCS_CXX = $(filter-out %.c,$(SRCS))
OBJS = $(addprefix $(OBJDIR)/,$(addsuffix .o, $(basename $(SRCS))))

## Define some useful variables.
DEP_OPT = $(shell if `$(CC) --version | grep -i "GCC" >/dev/null`; then \
                  echo "-MM"; else echo "-M"; fi )
               
DEPEND      = $(CC)  $(DEP_OPT) $(MY_CFLAGS) $(CFLAGS) $(CPPFLAGS)
DEPEND.d    = $(subst -g ,,$(DEPEND))
COMPILE.c   = $(CC)  $(MY_CFLAGS) $(CFLAGS)   $(CPPFLAGS) -c
COMPILE.cxx = $(CXX) $(MY_CFLAGS) $(CXXFLAGS) $(CPPFLAGS) -c
LINK.c      = $(CC)  $(MY_CFLAGS) $(CFLAGS)   $(CPPFLAGS) $(LDFLAGS)
LINK.cxx    = $(CXX) $(MY_CFLAGS) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS)

all:$(PROGRAM)

# Rules for creating dependency files (.d).
#------------------------------------------
$(OBJDIR)/%.d:%.c
	@echo Create dependency for $<
	@if [ ! -d $(OBJDIR)/$(dir $<) ]; then mkdir -p  $(OBJDIR)/$(dir $<); fi; \
	rm -rf $@; \
	$(DEPEND.d) $< > $@.$$$$; \
	sed 's,^.*\.o[ :]*,$@ $(patsubst %.d, %.o, $@) : ,g' < $@.$$$$ > $@; \
	#sed 's,\($(notdir $*)\)\.o[ :]*,$(OBJDIR)/\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -rf $@.$$$$

$(OBJDIR)/%.d:%.C
	@if [ ! -d $(OBJDIR)/$(dir $<) ]; then mkdir -p  $(OBJDIR)/$(dir $<); fi;
	@echo -n $(dir $<) > $@
	@$(DEPEND.d) $< >> $@

$(OBJDIR)/%.d:%.cc
	@if [ ! -d $(OBJDIR)/$(dir $<) ]; then mkdir -p  $(OBJDIR)/$(dir $<); fi;
	@echo -n $(dir $<) > $@
	@$(DEPEND.d) $< >> $@

$(OBJDIR)/%.d:%.cpp
	@if [ ! -d $(OBJDIR)/$(dir $<) ]; then mkdir -p  $(OBJDIR)/$(dir $<); fi;
	@echo -n $(dir $<) > $@
	@$(DEPEND.d) $< >> $@

$(OBJDIR)/%.d:%.CPP
	@if [ ! -d $(OBJDIR)/$(dir $<) ]; then mkdir -p  $(OBJDIR)/$(dir $<); fi;
	@echo -n $(dir $<) > $@
	@$(DEPEND.d) $< >> $@

$(OBJDIR)/%.d:%.c++
	@if [ ! -d $(OBJDIR)/$(dir $<) ]; then mkdir -p  $(OBJDIR)/$(dir $<); fi;
	@echo -n $(dir $<) > $@
	@$(DEPEND.d) $< >> $@

$(OBJDIR)/%.d:%.cp
	@if [ ! -d $(OBJDIR)/$(dir $<) ]; then mkdir -p  $(OBJDIR)/$(dir $<); fi;
	@echo -n $(dir $<) > $@
	@$(DEPEND.d) $< >> $@

$(OBJDIR)/%.d:%.cxx
	@if [ ! -d $(OBJDIR)/$(dir $<) ]; then mkdir -p  $(OBJDIR)/$(dir $<); fi;
	@echo -n $(dir $<) > $@
	@$(DEPEND.d) $< >> $@

sinclude $(OBJS:.o=.d)

$(OBJDIR)/%.o:%.c #自动去VPATH指定的目录查找，指定多个路径 写成VPATH = src:src1:src2
	@if [ ! -d $(OBJDIR)/$(dir $<) ]; then mkdir -p  $(OBJDIR)/$(dir $<); fi;
	$(COMPILE.c) $< -o $@

$(OBJDIR)/%.o:%.C
	@if [ ! -d $(OBJDIR)/$(dir $<) ]; then mkdir -p  $(OBJDIR)/$(dir $<); fi;
	$(COMPILE.cxx) $< -o $@

$(OBJDIR)/%.o:%.cc
	@if [ ! -d $(OBJDIR)/$(dir $<) ]; then mkdir -p  $(OBJDIR)/$(dir $<); fi;
	$(COMPILE.cxx) $< -o $@

$(OBJDIR)/%.o:%.cpp
	@if [ ! -d $(OBJDIR)/$(dir $<) ]; then mkdir -p  $(OBJDIR)/$(dir $<); fi;
	$(COMPILE.cxx) $< -o $@

$(OBJDIR)/%.o:%.CPP
	@if [ ! -d $(OBJDIR)/$(dir $<) ]; then mkdir -p  $(OBJDIR)/$(dir $<); fi;
	$(COMPILE.cxx) $< -o $@

$(OBJDIR)/%.o:%.c++
	@if [ ! -d $(OBJDIR)/$(dir $<) ]; then mkdir -p  $(OBJDIR)/$(dir $<); fi;
	$(COMPILE.cxx) $< -o $@

$(OBJDIR)/%.o:%.cp
	@if [ ! -d $(OBJDIR)/$(dir $<) ]; then mkdir -p  $(OBJDIR)/$(dir $<); fi;
	$(COMPILE.cxx) $< -o $@

$(OBJDIR)/%.o:%.cxx
	@if [ ! -d $(OBJDIR)/$(dir $<) ]; then mkdir -p  $(OBJDIR)/$(dir $<); fi;
	$(COMPILE.cxx) $< -o $@


# Rules for generating the executable.
#-------------------------------------
$(PROGRAM):$(OBJS)
ifeq ($(SRC_CXX),)              # C program
	$(LINK.c)   $(OBJS) $(MY_LIBS) -o $@
	@echo Type ./$@ to execute the program.
	$(MV_OBJ)
	$(MV_EXE)
else                            # C++ program
	$(LINK.cxx) $(OBJS) $(MY_LIBS) -o $@
	@echo Type ./$@ to execute the program.
	$(MV_OBJ)
	$(MV_EXE)
endif

.PHONY: clean show

# Show variables (for debug use only.)
show:
	@echo 'PROGRAM     :' $(PROGRAM)
	@echo 'SRCDIRS     :' $(SRCDIRS)
	@echo 'HDRDIRS     :' $(INCDIRS)
	@echo 'HEADERS     :' $(INCS)
	@echo 'SOURCES     :' $(SRCS)
	@echo 'SRC_CXX     :' $(SRCS_CXX)
	@echo 'OBJS        :' $(OBJS)
	@echo 'DEPS        :' $(DEPS)
	@echo 'DEPEND      :' $(DEPEND)
	@echo 'COMPILE.c   :' $(COMPILE.c)
	@echo 'COMPILE.cxx :' $(COMPILE.cxx)
	@echo 'link.c      :' $(LINK.c)
	@echo 'link.cxx    :' $(LINK.cxx)

clean:
	$(RM) $(OBJS) $(PROGRAM) $(OBJS:.o=.d) *.exe
