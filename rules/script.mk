define showMakeInfo
@$(ECHO) $(FGCYAN)"host" $(HOST) $(NONE)
@$(ECHO) $(FGCYAN)"CC" $(CC) $(NONE)
@$(ECHO) $(FGCYAN)"IFLAGS" $(IFLAGS) $(NONE)
@$(ECHO) $(FGCYAN)"CFLAGS" $(CFLAGS) $(NONE)
@$(ECHO) $(FGCYAN)"CCFLAGS" $(CCFLAGS) $(NONE)
@$(ECHO) $(FGCYAN)"LDFLAGS" $(LDFLAGS) $(NONE)
@$(ECHO) $(FGCYAN)"Executable file path:" $(INSTALL_EXE_PATH) $(NONE)
@$(ECHO) $(FGCYAN)"Binary file path:" $(INSTALL_BIN_PATH) $(NONE)
@$(ECHO) $(FGCYAN)"Dynamic library path:" $(INSTALL_SHARED_LIB_PATH) $(NONE)
@$(ECHO) $(FGCYAN)"Static library path:" $(INSTALL_STATIC_LIB_PATH) $(NONE)
@$(ECHO) $(FGCYAN)"Kernel object path:" $(INSTALL_KERNEL_OBJECT_PATH) $(NONE)
@$(ECHO) $(FGCYAN)"Head file path:" $(INSTALL_HEAD_FILE_PATH)$(NONE) $(NONE)
endef

#创建指定目录
define creatDir
@$(ECHO) $(FGCYAN)creat ${1} $(NONE)
$(shell mkdir -p ${1})
endef	

#进入指定目录，并且执行该目录下Makefile
define makeDirectory
@$(ECHO) $(FGGREEN)$(MAKE) $(ROOT_PATH)/$(1) $(2)$(NONE)
$(CD) $(ROOT_PATH)/$(1); $(MAKE) $(2);
endef

#获取指定目录下的所有文件夹名称，不包括文件
define listDirectory
$(shell ls -l $(1) |awk '/^d/ {print $$NF}')
endef

define openSourcePrepare
$(call showMakeInfo)
$(foreach dir, $(INSTALL_ALL_PATH), $(call creatDir, $(dir)))
$(call creatDir, $(DEPEND_HEAD_FILE_PATH)/$(2))
$(call creatDir, $(BUILD_BASE_PATH)/$(2))
endef