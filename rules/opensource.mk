iw-tool : $(OPEN_SOURCE_PATH)/iw_3.17.orig.tar.xz
	@$(call openSourcePrepare,$<,$@)
	@tar -xvf $< -C $(BUILD_BASE_PATH)/$@ 1>/dev/null
	@$(CD) $(BUILD_BASE_PATH)/$@/;$(MV) * .$@;$(MV) .$@ $@
	$(CD) $(BUILD_BASE_PATH)/$@/$@; \
	make $(CFLAGS);make install; 
	
termcap : $(OPEN_SOURCE_PATH)/termcap-1.3.1.tar.gz
	$(call openSourcePrepare,$<,$@)
	@tar zxvf $< -C $(BUILD_BASE_PATH)/$@ 1>/dev/null
	@$(CD) $(BUILD_BASE_PATH)/$@/;$(MV) * .$@;$(MV) .$@ $@
	$(CD) $(BUILD_BASE_PATH)/$@/$(call listDirectory, $(BUILD_BASE_PATH)/$@/); 
		./configure \
		--host=$(PLATFORM) --target=$(PLATFORM) \
		--prefix=$(INSTALL_PREFIX_PATH)/$@ \
		--x-includes=$(INSTALL_HEAD_FILE_PATH)/$@; \
	make $(CFLAGS);make install

libpcap : $(OPEN_SOURCE_PATH)/libpcap-1.9.0.tar.gz
	@$(call openSourcePrepare,$<,$@)
	@tar -xvf $< -C $(BUILD_BASE_PATH)/$@ 1>/dev/null
	@$(CD) $(BUILD_BASE_PATH)/$@/;$(MV) * .$@;$(MV) .$@ $@
	$(CD) $(BUILD_BASE_PATH)/$@/$@; \
		./configure --with-pcap=linux \
		--host=$(PLATFORM) --target=$(PLATFORM) \
		--prefix=$(INSTALL_PREFIX_PATH)/$@ \
		--bindir=$(INSTALL_BIN_PATH)/ \
		--sbindir=$(INSTALL_BIN_PATH)/ \
		--libexecdir=$(INSTALL_EXE_PATH)/ \
		--libdir=$(INSTALL_SHARED_LIB_PATH)/ \
		--includedir=$(INSTALL_HEAD_FILE_PATH)/$@ \
		; make $(CFLAGS);make install; \
		$(MV) $(INSTALL_BIN_PATH)/pcap-config $(INSTALL_BIN_PATH)/../i686/$(PLATFORM)-pcap-config
tcpdump : $(OPEN_SOURCE_PATH)/tcpdump_4.9.2.orig.tar.gz
	@$(call openSourcePrepare,$<,$@)
	@tar -xvf $< -C $(BUILD_BASE_PATH)/$@ 1>/dev/null
	@$(CD) $(BUILD_BASE_PATH)/$@/;$(MV) * .$@;$(MV) .$@ $@
	$(CD) $(BUILD_BASE_PATH)/$@/$@; \
		./configure  \
		--host=$(PLATFORM) --target=$(PLATFORM) \
		--prefix=$(INSTALL_PREFIX_PATH)/$@ \
		--bindir=$(INSTALL_BIN_PATH)/ \
		--sbindir=$(INSTALL_BIN_PATH)/ \
		--libexecdir=$(INSTALL_EXE_PATH)/ \
		--libdir=$(INSTALL_SHARED_LIB_PATH)/ \
		--includedir=$(INSTALL_HEAD_FILE_PATH)/$@ \
		; \
	make $(CFLAGS);make install
	
texinfo : $(OPEN_SOURCE_PATH)/texinfo-6.5.tar
	@$(call openSourcePrepare,$<,$@)
	@tar -xvf $< -C $(BUILD_BASE_PATH)/$@ 1>/dev/null
	@$(CD) $(BUILD_BASE_PATH)/$@/;$(MV) * .$@;$(MV) .$@ $@
	$(CD) $(BUILD_BASE_PATH)/$@/$@; \
		./configure \
		--host=$(PLATFORM) --target=$(PLATFORM) \
		--prefix=$(INSTALL_PREFIX_PATH)/$@ \
		--bindir=$(INSTALL_BIN_PATH)/ \
		--sbindir=$(INSTALL_BIN_PATH)/ \
		--libexecdir=$(INSTALL_EXE_PATH)/ \
		--libdir=$(INSTALL_SHARED_LIB_PATH)/ \
		--includedir=$(INSTALL_HEAD_FILE_PATH)/$@ \
		; \
	make $(CFLAGS);make install
	
gdb : $(OPEN_SOURCE_PATH)/gdb-8.0.1.tar.gz
	$(call openSourcePrepare,$<,$@)
	@tar zxvf $< -C $(BUILD_BASE_PATH)/$@ 1>/dev/null
	@$(CD) $(BUILD_BASE_PATH)/$@/;$(MV) * .$@;$(MV) .$@ $@
	$(CD) $(BUILD_BASE_PATH)/$@/$@; \
		./configure \
		--host=$(PLATFORM) --target=$(PLATFORM) \
		--prefix=$(INSTALL_PREFIX_PATH)/$@ \
		--bindir=$(INSTALL_BIN_PATH)/ \
		--sbindir=$(INSTALL_BIN_PATH)/ \
		--libexecdir=$(INSTALL_EXE_PATH)/ \
		--libdir=$(INSTALL_SHARED_LIB_PATH)/ \
		--includedir=$(INSTALL_HEAD_FILE_PATH)/$@ \
		; \
	make $(CFLAGS);make install
	
host-gdb : $(OPEN_SOURCE_PATH)/gdb-8.0.1.tar.gz
	$(call openSourcePrepare,$<,$@)
	@tar zxvf $< -C $(BUILD_BASE_PATH)/$@ 1>/dev/null
	@$(CD) $(BUILD_BASE_PATH)/$@/;$(MV) * .$@;$(MV) .$@ $@
	$(CD) $(BUILD_BASE_PATH)/$@/$@; \
		./configure --target=$(PLATFORM) \
		--program-prefix=host- --program-suffix=-$(ARCH) \
		--prefix=$(INSTALL_PREFIX_PATH)/$@ \
		--bindir=$(INSTALL_BIN_PATH)/ \
		--sbindir=$(INSTALL_BIN_PATH)/ \
		--libexecdir=$(INSTALL_EXE_PATH)/ \
		--libdir=$(INSTALL_SHARED_LIB_PATH)/ \
		--includedir=$(INSTALL_HEAD_FILE_PATH)/$@ \
		-v; \
	make $(CFLAGS);make install
	
valgrind : $(OPEN_SOURCE_PATH)/valgrind-3.12.0.tar
	$(call openSourcePrepare,$<,$@)
	@tar xvf $< -C $(BUILD_BASE_PATH)/$@ 1>/dev/null
	@$(CD) $(BUILD_BASE_PATH)/$@/;$(MV) * .$@;$(MV) .$@ $@
	$(CD) $(BUILD_BASE_PATH)/$@/$@; \
		./configure \
		--host=$(PLATFORM) --target=$(PLATFORM) \
		--prefix=$(INSTALL_PREFIX_PATH)/$@ \
		--bindir=$(INSTALL_BIN_PATH)/ \
		--sbindir=$(INSTALL_BIN_PATH)/ \
		--libexecdir=$(INSTALL_EXE_PATH)/ \
		--libdir=$(INSTALL_SHARED_LIB_PATH)/ \
		--includedir=$(INSTALL_HEAD_FILE_PATH)/$@ \
		; \
	make $(CFLAGS);make install
