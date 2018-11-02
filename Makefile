export ROOT_PATH = $(shell pwd)
export SCRIPT_MK = $(ROOT_PATH)/rules/script.mk
include	$(ROOT_PATH)/rules/font.mk
include $(ROOT_PATH)/rules/arch.mk
include	$(ROOT_PATH)/rules/path.mk
include $(ROOT_PATH)/rules/cmd.mk
include $(SCRIPT_MK)
include $(ROOT_PATH)/rules/opensource.mk


#@$(ECHO) $(FGGREEN)rm $(foreach file, $(TMP_FILE), $(shell find -name $(file))) $(NONE) 
TMP_FILE := *.so *.a *.o
clean:
	@$(RM) $(ROOT_PATH)/build/* -rf 		

.PHONY:clean