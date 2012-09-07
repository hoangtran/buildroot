#############################################################
#
# iozone
#
#############################################################
IOZONE_VERSION:=398
IOZONE_SOURCE:=iozone3_$(IOZONE_VERSION).tar
IOZONE_SITE:=http://www.iozone.org/src/current
IOZONE_DIR:=$(BUILD_DIR)/iozone3_$(IOZONE_VERSION)/src/current
IOZONE_BINARY:=iozone
IOZONE_TARGET_BINARY:=usr/bin/iozone

$(DL_DIR)/$(IOZONE_SOURCE):
	 $(call DOWNLOAD,$(IOZONE_SITE)/$(IOZONE_SOURCE))

iozone-source: $(DL_DIR)/$(IOZONE_SOURCE)

$(IOZONE_DIR)/.unpacked: $(DL_DIR)/$(IOZONE_SOURCE)
	tar -C $(BUILD_DIR) -xf $(DL_DIR)/$(IOZONE_SOURCE)
	$(SED) "s,cc,$(TARGET_CC)," $(IOZONE_DIR)/makefile
	touch $(IOZONE_DIR)/.unpacked

$(IOZONE_DIR)/$(IOZONE_BINARY): $(IOZONE_DIR)/.unpacked
	$(MAKE) -C $(IOZONE_DIR) linux-powerpc
	$(STRIPCMD) $(IOZONE_DIR)/$(IOZONE_BINARY)

$(TARGET_DIR)/$(IOZONE_TARGET_BINARY): $(IOZONE_DIR)/$(IOZONE_BINARY)
	$(INSTALL) -m 0755 -D $(IOZONE_DIR)/$(IOZONE_BINARY) $(TARGET_DIR)/$(IOZONE_TARGET_BINARY)

iozone: $(TARGET_DIR)/$(IOZONE_TARGET_BINARY)

iozone-clean:
	rm -f $(TARGET_DIR)/$(IOZONE_TARGET_BINARY)
	-$(MAKE) -C $(IOZONE_DIR) clean

iozone-dirclean:
	rm -rf $(IOZONE_DIR)

#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_IOZONE),y)
TARGETS+=iozone
endif
