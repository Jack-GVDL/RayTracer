# --------------------------------------------------
# Description
# --------------------------------------------------
# ...


# --------------------------------------------------
# Config
# --------------------------------------------------
CONFIG_IS_EXT_CONFIG_ENABLE	:= true
CONFIG_IS_PRINT_WARNING		:= false
CONFIG_IS_TREE_ENABLE		:= false
CONFIG_IS_COMPILE_ENABLE	:= false
CONFIG_IS_ARCHIVE_ENABLE	:= false
CONFIG_IS_LINK_ENABLE 		:= false
CONFIG_IS_C_STANDALONE		:= false
CONFIG_MACHINE				:= invalid
CONFIG_IS_ROOT				:= true


# --------------------------------------------------
# Function
# --------------------------------------------------
rwildcard=$(wildcard $1/$2) $(foreach d,$(wildcard $1/*),$(call rwildcard,$(d),$2))


# --------------------------------------------------
# Data
# --------------------------------------------------
CONFIG_PY_PATH 		= ./makeparse.py
CONFIG_JSON_PATH	= ./makeconfig.json

CONFIG_EXPORT		=
CONFIG_EXPORT		+= CONFIG_IS_PRINT_WARNING CONFIG_IS_TREE_ENABLE 
CONFIG_EXPORT		+= CONFIG_IS_COMPILE_ENABLE CONFIG_IS_ARCHIVE_ENABLE CONFIG_IS_LINK_ENABLE 
CONFIG_EXPORT		+= CONFIG_IS_C_STANDALONE CONFIG_MACHINE
CONFIG_EXPORT		+= NODE_NAME CHILD_PATH
CONFIG_EXPORT		+= ASM_PATH SRC_PATH OBJ_PATH BIN_PATH SCRIPT_PATH
CONFIG_EXPORT		+= AR_FILE LD_FILE BIN_FILE OBJ_FILE
CONFIG_EXPORT_ARG	= 

NODE_NAME			=
CHILD_PATH 			= 

CC					= gcc
CPP					= g++
LD					= ld
ASM					= nasm
AR					= ar
PY					= python3
MAKE 				= make

C_MACRO 			= -D
C_FLAGS 			= -c -Wall -ggdb -gstabs+ -I include
CPP_MACRO			=
CPP_FLAGS			= -Wall
ASM_FLAGS 			= -f elf -g -F stabs
LD_FLAGS 			= 
AR_FLAGS			= 

ASM_PATH 			= .
SRC_PATH 			= .
OBJ_PATH			= .
BIN_PATH			= .
SCRIPT_PATH			= .

AR_FILE				=
BIN_FILE			=
LD_FILE				=
OBJ_FILE 			=
EXT_OBJ_FILE 		= 
EXT_AR_FILE			=


# --------------------------------------------------
# Initiation
# --------------------------------------------------

# read the config from makeconfig
# TODO: find a better way to do this thing, now is too slow
ifeq ($(CONFIG_IS_EXT_CONFIG_ENABLE),false)
else

ifeq ($(OS),Windows_NT)
else
$(eval CONFIG_IS_TREE_ENABLE=$(shell 	sh -c "$(PY) $(CONFIG_PY_PATH) CONFIG_IS_TREE_ENABLE 	$(CONFIG_IS_TREE_ENABLE)"))
$(eval CONFIG_IS_COMPILE_ENABLE=$(shell sh -c "$(PY) $(CONFIG_PY_PATH) CONFIG_IS_COMPILE_ENABLE $(CONFIG_IS_COMPILE_ENABLE)"))
$(eval CONFIG_IS_ARCHIVE_ENABLE=$(shell sh -c "$(PY) $(CONFIG_PY_PATH) CONFIG_IS_ARCHIVE_ENABLE $(CONFIG_IS_ARCHIVE_ENABLE)"))
$(eval CONFIG_IS_LINK_ENABLE=$(shell 	sh -c "$(PY) $(CONFIG_PY_PATH) CONFIG_IS_LINK_ENABLE 	$(CONFIG_IS_LINK_ENABLE)"))
$(eval CONFIG_IS_C_STANDALONE=$(shell 	sh -c "$(PY) $(CONFIG_PY_PATH) CONFIG_IS_C_STANDALONE 	$(CONFIG_IS_C_STANDALONE)"))
$(eval CONFIG_MACHINE=$(shell 			sh -c "$(PY) $(CONFIG_PY_PATH) CONFIG_MACHINE 			$(CONFIG_MACHINE)"))

$(eval NODE_NAME=$(shell 	sh -c "$(PY) $(CONFIG_PY_PATH) NODE_NAME 	$(NODE_NAME)"))
$(eval CHILD_PATH=$(shell 	sh -c "$(PY) $(CONFIG_PY_PATH) CHILD_PATH 	$(CHILD_PATH)"))

$(eval ASM_PATH=$(shell 	sh -c "$(PY) $(CONFIG_PY_PATH) ASM_PATH 	$(ASM_PATH)"))
$(eval SRC_PATH=$(shell 	sh -c "$(PY) $(CONFIG_PY_PATH) SRC_PATH 	$(SRC_PATH)"))
$(eval OBJ_PATH=$(shell 	sh -c "$(PY) $(CONFIG_PY_PATH) OBJ_PATH 	$(OBJ_PATH)"))
$(eval BIN_PATH=$(shell 	sh -c "$(PY) $(CONFIG_PY_PATH) BIN_PATH 	$(BIN_PATH)"))
$(eval SCRIPT_PATH=$(shell 	sh -c "$(PY) $(CONFIG_PY_PATH) SCRIPT_PATH 	$(SCRIPT_PATH)"))

$(eval AR_FILE=$(shell 		sh -c "$(PY) $(CONFIG_PY_PATH) AR_FILE 		$(AR_FILE)"))
$(eval LD_FILE=$(shell 		sh -c "$(PY) $(CONFIG_PY_PATH) LD_FILE 		$(LD_FILE)"))
$(eval BIN_FILE=$(shell 	sh -c "$(PY) $(CONFIG_PY_PATH) BIN_FILE 	$(BIN_FILE)"))
$(eval OBJ_FILE=$(shell 	sh -c "$(PY) $(CONFIG_PY_PATH) OBJ_FILE 	$(OBJ_FILE)"))
endif  # OS

endif  # CONFIG_IS_EXT_CONFIG_ENABLE

# set the export config variable
CONFIG_EXPORT_ARG := $(foreach p,$(CONFIG_EXPORT),$(p)="$($(p))")
# export $(CONFIG_EXPORT)

# config machine
ifeq ($(CONFIG_MACHINE),x386)
OBJ_PATH 	:= $(OBJ_PATH)_x386
C_FLAGS 	:= $(C_FLAGS) -m32
LD_FLAGS	:= $(LD_FLAGS) -m elf_i386

else ifeq ($(CONFIG_MACHINE),x64)
OBJ_PATH 	:= $(OBJ_PATH)_x64
C_FLAGS 	:= $(C_FLAGS)
LD_FLAGS	:= $(LD_FLAGS)

endif

# config standalone
ifeq ($(CONFIG_IS_C_STANDALONE),true)
C_MACRO 	:= $(C_MACRO) __ANN_STANDALONE=1
C_FLAGS 	:= $(C_FLAGS) -nostdinc -fno-builtin -fno-stack-protector -fno-pie
LD_FLAGS 	:= $(LD_FLAGS) -nostdlib

else
C_MACRO 	:= $(C_MACRO) __ANN_STANDALONE=0
C_FLAGS 	:= $(C_FLAGS)
LD_FLAGS 	:= $(LD_FLAGS)

endif

# config path and file
# TODO: fix this later
OBJ_FILE 		:= $(foreach p,$(OBJ_FILE),./$(OBJ_PATH)/$(p))
EXT_OBJ_FILE	:= $(foreach p,$(CHILD_PATH),$(call rwildcard,$(p)/$(OBJ_PATH),*.o))
#EXT_AR_FILE 	+= $(foreach p,$(CHILD_PATH),./$(p)/$(shell sh -c "$(MAKE) info_archive --directory=$(p) --no-print-directory"))


# --------------------------------------------------
# Operation
# --------------------------------------------------
# c file
$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
#	@echo CC "		" $(NODE_NAME)/$(<)
	@echo CC "      " $(NODE_NAME)/$(<)
	@$(CC) $(C_FLAGS) $(C_MACRO) $(<) -o $(@)


# cpp fie
$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cpp
#	@echo CPP "		" $(NODE_NAME)/%(<)
	@echo CPP "     " $(NODE_NAME)/$(<)
	@$(CPP) $(CPP_FLAGS) $(CPP_MACRO) $(<) -o $(@)


# s file
$(OBJ_PATH)/%.o: $(ASM_PATH)/%.s
#	@echo ASM "		" $(NODE_NAME)/$(<)
	@echo ASM "     " $(NODE_NAME)/$(<)
	@$(ASM) $(ASM_FLAGS) $(<) -o $(@)


.PHONY: all
all:
#	@echo MAKE "	" $(NODE_NAME)
	@echo MAKE "    " $(NODE_NAME)

    ifeq ($(CONFIG_IS_TREE_ENABLE),true)
	@$(MAKE) make_child --no-print-directory CONFIG_IS_EXT_CONFIG_ENABLE=true
    endif

	@$(MAKE) make_self 	-j4 --no-print-directory CONFIG_IS_EXT_CONFIG_ENABLE=true


.PHONY: make_child
make_child:
	@for d in $(CHILD_PATH); \
	do \
		$(MAKE) all --directory=$$d --no-print-directory CONFIG_IS_ROOT=false;	\
	done


.PHONY: make_self
make_self: compile_self archive_self link_self

# backup: below code is too slow
#    # compile
#    ifeq ($(CONFIG_IS_COMPILE_ENABLE),true)
#	@$(MAKE) compile_self --no-print-directory CONFIG_IS_EXT_CONFIG_ENABLE=true
#    endif
#
#    # archive
#    ifeq ($(CONFIG_IS_ARCHIVE_ENABLE),true)
#	@$(MAKE) archive_self --no-print-directory CONFIG_IS_EXT_CONFIG_ENABLE=true
#    endif
#
#    # link
#    ifeq ($(CONFIG_IS_LINK_ENABLE),true)
#	@$(MAKE) link_self    --no-print-directory CONFIG_IS_EXT_CONFIG_ENABLE=true
#    endif


.PHONY: compile_self
ifeq ($(CONFIG_IS_COMPILE_ENABLE),true)
compile_self: $(OBJ_FILE)

else
compile_self:

endif


.PHONY: archive_self
ifeq ($(CONFIG_IS_ARCHIVE_ENABLE),true)
archive_self:
#	@echo AR "		" $(NODE_NAME)/$(OBJ_PATH)/$(AR_FILE)
	@echo AR "      " $(NODE_NAME)/$(OBJ_PATH)/$(AR_FILE)
	@$(AR) cr ./$(OBJ_PATH)/$(AR_FILE) $(OBJ_FILE) $(EXT_AR_FILE)
	
else
archive_self:

endif


.PHONY: link_self
ifeq ($(CONFIG_IS_LINK_ENABLE),true)
link_self:
#	@echo LD "		" $(NODE_NAME)/$(SCRIPT_PATH)/$(LD_FILE)
	@echo LD "      " $(NODE_NAME)/$(SCRIPT_PATH)/$(LD_FILE)
	@$(LD) $(LD_FLAGS) -T ./$(SCRIPT_PATH)/$(LD_FILE) $(OBJ_FILE) $(EXT_OBJ_FILE) $(EXT_AR_FILE) -o ./$(BIN_PATH)/$(BIN_FILE)

else
link_self:

endif


.PHONY: update
update:
#	@echo UPDATE "	" $(NODE_NAME)
	@echo UPDATE "  " $(NODE_NAME)

	@for d in $(CHILD_PATH); \
	do \
		cp ./Makefile ./$$d/Makefile; \
		$(MAKE) update --directory=$$d --no-print-directory CONFIG_IS_ROOT=false; \
	done


.PHONY: clean
clean:
#	@echo CLEAN	"	" $(NODE_NAME)
	@echo CLEAN	"   " $(NODE_NAME)

ifeq ($(CONFIG_IS_TREE_ENABLE),false)
    ifeq ($(CONFIG_IS_PRINT_WARNING),true)
	@echo Warning: Tree disabled
    endif

else
	@for d in $(CHILD_PATH); \
	do \
		$(MAKE) clean --directory=$$d --no-print-directory CONFIG_IS_ROOT=false;	\
	done

endif

ifeq ($(CONFIG_IS_ROOT),false)
	@rm $(OBJ_PATH)/*
endif


# --------------------------------------------------
# Info Operation
# --------------------------------------------------
.PHONY: info_archive
info_archive:
	@echo $(OBJ_PATH)/$(AR_FILE)


# --------------------------------------------------
# Helper
# --------------------------------------------------
.PHONY: var_list
var_list:
	@echo CONFIG_IS_TREE_ENABLE "		" $(CONFIG_IS_TREE_ENABLE)
	@echo CONFIG_IS_COMPILE_ENABLE "	" $(CONFIG_IS_COMPILE_ENABLE)
	@echo CONFIG_IS_LINK_ENABLE "		" $(CONFIG_IS_LINK_ENABLE)
	@echo CONFIG_IS_C_STANDALONE "		" $(CONFIG_IS_C_STANDALONE)
	@echo CONFIG_MACHINE "				" $(CONFIG_MACHINE)

	@echo NODE_NAME "			" $(NODE_NAME)
	@echo CHILD_PATH "       	" $(CHILD_PATH)
	@echo CONFIG_EXPORT "		" $(CONFIG_EXPORT)
	@echo CONFIG_EXPORT_ARG "	" $(CONFIG_EXPORT_ARG)

	@echo CC "               	" $(CC)
	@echo CPP "                 " $(CPP)
	@echo LD "               	" $(LD)
	@echo ASM "              	" $(ASM)
	@echo MAKE "             	" $(MAKE)

	@echo C_MACRO "          	" $(C_MACRO)
	@echo C_FLAGS "          	" $(C_FLAGS)
	@echo CPP_MACRO "           " $(CPP_MACRO)
	@echo CPP_FLAGS "           " $(CPP_FLAGS)
	@echo ASM_FLAGS "        	" $(ASM_FLAGS)
	@echo LD_FALGS "        	" $(LD_FALGS)

	@echo ASM_PATH "         	" $(ASM_PATH)
	@echo SRC_PATH "         	" $(SRC_PATH)
	@echo OBJ_PATH "         	" $(OBJ_PATH)
	@echo SCRIPT_PATH "         " $(SCRIPT_PATH)

	@echo AR_FILE "				" $(AR_FILE)
	@echo BIN_FILE "			" $(BIN_FILE)
	@echo LD_FILE "				" $(LD_FILE)
	@echo OBJ_FILE "			" $(OBJ_FILE)
	@echo EXT_OBJ_FILE "		" $(EXT_OBJ_FILE)
	@echo EXT_AR_FILE "			" $(EXT_AR_FILE)


# --------------------------------------------------
# User Operation
# --------------------------------------------------
.PHONY custom_link: all
	@$(CPP) $(CPP_FLAGS) $(CPP_MACRO) $(OBJ_FILE) $(EXT_OBJ_FILE) RayTracer.cpp main.cpp -o ./$(BIN_PATH)/$(BIN_FILE)
	@./bin/Tracer > output.ppm
