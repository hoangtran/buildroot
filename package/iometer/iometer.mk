#############################################################
#
# iometer
#
#############################################################
IOMETER_VERSION:=2006_07_27.common-src
IOMETER_SOURCE:=iometer-$(IOMETER_VERSION).zip
IOMETER_SITE:=http://prdownloads.sourceforge.net/iometer/$(IOMETER_SOURCE)?download
IOMETER_DIR:=$(BUILD_DIR)/iometer-$(IOMETER_VERSION)
IOMETER_BINARY:=dynamo
IOMETER_TARGET_BINARY:=usr/bin/dynamo
IOMETER_SUBDIR=src

$(DL_DIR)/$(IOMETER_SOURCE):
	 $(call DOWNLOAD,$(IOMETER_SITE)/$(IOMETER_SOURCE))

iometer-source: $(DL_DIR)/$(IOMETER_SOURCE)

$(IOMETER_DIR)/.unpacked: $(DL_DIR)/$(IOMETER_SOURCE)
	unzip $(DL_DIR)/$(IOMETER_SOURCE) -d $(BUILD_DIR) 
	patch -p1 -d $(IOMETER_DIR) < package/iometer/iometer-2006_07_27.common-src-cross-compile-ppc.patch
	touch $(IOMETER_DIR)/.unpacked

$(IOMETER_DIR)/$(IOMETER_SUBDIR)/$(IOMETER_BINARY): $(IOMETER_DIR)/.unpacked
	CFLAGS="$(TARGET_CFLAGS)" LDFLAGS="$(TARGET_LDFLAGS)" CXX=$(TARGET_CXX) \
		   $(MAKE) -C $(IOMETER_DIR)/$(IOMETER_SUBDIR) -f $(IOMETER_DIR)/$(IOMETER_SUBDIR)/Makefile-Linux.ppc all
	$(STRIPCMD) $(IOMETER_DIR)/$(IOMETER_SUBDIR)/$(IOMETER_BINARY)

$(TARGET_DIR)/$(IOMETER_TARGET_BINARY): $(IOMETER_DIR)/$(IOMETER_SUBDIR)/$(IOMETER_BINARY)
	$(INSTALL) -m 0755 -D $(IOMETER_DIR)/$(IOMETER_SUBDIR)/$(IOMETER_BINARY) $(TARGET_DIR)/$(IOMETER_TARGET_BINARY)

iometer: $(TARGET_DIR)/$(IOMETER_TARGET_BINARY)

iometer-clean:
	rm -f $(TARGET_DIR)/$(IOMETER_TARGET_BINARY)
	-$(MAKE) -C $(IOMETER_DIR) clean

iometer-dirclean:
	rm -rf $(IOMETER_DIR)

#############################################################
#
# Toplevel Makefile options
#
#############################################################
ifeq ($(BR2_PACKAGE_IOMETER),y)
TARGETS+=iometer
endif
