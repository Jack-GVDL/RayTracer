# --------------------------------------------------
# Description
# --------------------------------------------------
# global
# CONFIG_IS_TREE_ENABLE
# CONFIG_IS_EXPORT_RECURSIVE
# CONFIG_IS_ROOT
# MODULE


# --------------------------------------------------
# Config
# do not change below setting
# these setting should be modified in makeconfig.json file
# --------------------------------------------------
CONFIG_IS_EXT_CONFIG_ENABLE	:= true
CONFIG_IS_TREE_ENABLE		:= false
CONFIG_IS_ROOT				:= true
CONFIG_IS_EXPORT_RECURSIVE	:= false


# --------------------------------------------------
# Function
# --------------------------------------------------
rwildcard=$(wildcard $1/$2) $(foreach d,$(wildcard $1/*),$(call rwildcard,$(d),$2))

# function: get_config(config_name, file, ...) -> string
define get_config
   $(eval $(1) $(3)= $(shell $(SHELL_PREFIX) $(PY) $(CONFIG_PARSER_PATH) $(2) $(1) $($(1)) $(SHELL_SUFFIX)))
endef

# function: get_config_return(var_return_to, config_name, file, ...)
define get_config_return
   $(eval $(1) $(4)= $(shell $(SHELL_PREFIX) $(PY) $(CONFIG_PARSER_PATH) $(3) $(2) $($(1)) $(SHELL_SUFFIX)))
endef

# function: get_channel_output(return_to, direction, name, is_path, ...)
# the config name should be CONFIG_IMPORT_$(return_to)
define get_channel_output
   $(eval $(1) $(5)= $(shell $(SHELL_PREFIX) $(MAKE) --f=Makefile_Channel INPUT_CHANNEL_DIRECTION=$(2) INPUT_CHANNEL_NAME=$(3) INPUT_IS_PATH=$(4) $(SHELL_SUFFIX)))
endef

# function module
ifeq ($(OS),Windows_NT)
FOR_START		:= for %%i in (
FOR_DO			:= ) do
FOR_END			:= 
FOR_ITEM		:= %%i

else
FOR_START		:= for i in 
FOR_DO			:= ; do 
FOR_END			:= ; done
FOR_ITEM		:= $$i

endif


# --------------------------------------------------
# Data
# --------------------------------------------------
CONFIG_PARSER_PATH	= Make_Parse.py
CONFIG_JSON_GLOBAL	= makeconfig.json

NODE				= .
CHILD				=
MODULE				= 
WORK_DIR			=

PY					= py
CP					= cp
MAKE				= make


# --------------------------------------------------
# Initiation
# --------------------------------------------------
# config based on host platform
ifeq ($(OS),Windows_NT)
PY				:= py
CP				:= copy
SHELL_PREFIX	:= 
SHELL_SUFFIX	:= 
SPACE_PREFIX	:= 
SPACE_SUFFIX	:=

else
PY				:= python3
CP				:= cp
SHELL_PREFIX	:= sh -c "
SHELL_SUFFIX	:= "
SPACE_PREFIX	:= "
SPACE_SUFFIX	:= "

endif


# read the config from makeconfig
# TODO: find a better way to do this thing, now is too slow
ifeq ($(CONFIG_IS_EXT_CONFIG_ENABLE),false)
else

$(call get_config, CONFIG_IS_TREE_ENABLE,		$(CONFIG_JSON_GLOBAL),	 )
$(call get_config, CONFIG_IS_ROOT,				$(CONFIG_JSON_GLOBAL),	 )
$(call get_config, CONFIG_IS_EXPORT_RECURSIVE,	$(CONFIG_JSON_GLOBAL),	 )
$(call get_config, NODE,						$(CONFIG_JSON_GLOBAL),	 )
$(call get_config, CHILD,						$(CONFIG_JSON_GLOBAL),	 )
$(call get_config, MODULE,						$(CONFIG_JSON_GLOBAL),	 )
$(call get_config, WORK_DIR,					$(CONFIG_JSON_GLOBAL),	 )

endif  # CONFIG_IS_EXT_CONFIG_ENABLE


# --------------------------------------------------
# Operation
# --------------------------------------------------
.PHONY: all
all: child header self


.PHONY: header
header:
#	@echo NODE $(SPACE_PREFIX)		$(SPACE_SUFFIX) $(NODE)
	@echo NODE $(SPACE_PREFIX)      $(SPACE_SUFFIX) $(NODE)


.PHONY: self
self:
# foreach MODULE: $(MAKE) all --f=Makefile_$() --no-print-directory 
	@$(FOR_START) $(MODULE) $(FOR_DO) \
	$(MAKE) all --f=Makefile_$(FOR_ITEM) --no-print-directory \
	$(FOR_END)


.PHONY: child
child:
# foreach CHILD: $(MAKE) all --directory=$() --no-print-directory
	@$(FOR_START) $(CHILD) $(FOR_DO) \
	$(MAKE) --directory=$(WORK_DIR)/$(FOR_ITEM)/config --no-print-directory \
	$(FOR_END)


.PHONY: update
update:
# foreach CHILD: cp ./Makefile ./%() | $(MAKE) all --directory=$() --no-print-directory
	@$(FOR_START) $(CHILD) $(FOR_DO) \
    $(CP) ./Makefile ./$(FOR_ITEM); \
	$(MAKE) update --directory=$(WORK_DIR)/$(FOR_ITEM)/config --no-print-directory \
	$(FOR_END)
	


# --------------------------------------------------
# Helper
# --------------------------------------------------
.PHONY: var_list
var_list:
	@echo CONFIG_IS_EXT_CONFIG_ENABLE $(SPACE_PREFIX)  $(SPACE_SUFFIX) $(CONFIG_IS_EXT_CONFIG_ENABLE)
	@echo CONFIG_IS_EXPORT_RECURSIVE $(SPACE_PREFIX)   $(SPACE_SUFFIX) $(CONFIG_IS_EXPORT_RECURSIVE)
	@echo CONFIG_IS_ROOT $(SPACE_PREFIX)               $(SPACE_SUFFIX) $(CONFIG_IS_ROOT)

	@echo NODE $(SPACE_PREFIX)                         $(SPACE_SUFFIX) $(NODE)
	@echo CHILD $(SPACE_PREFIX)                        $(SPACE_SUFFIX) $(CHILD)
	@echo MODULE $(SPACE_PREFIX)                       $(SPACE_SUFFIX) $(MODULE)
	@echo WORK_DIR $(SPACE_PREFIX)                     $(SPACE_SUFFIX) $(WORK_DIR)

	@echo MAKE $(SPACE_PREFIX)                         $(SPACE_SUFFIX) $(MAKE)


# --------------------------------------------------
# User Operation
# --------------------------------------------------
