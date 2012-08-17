#############################################################
#
# bzip2
#
#############################################################
XDD_VERSION:=013007
XDD_SOURCE:=xdd65.$(XDD_VERSION).tgz
XDD_SITE:=http://openbsd.mirrors.tds.net/pub/FreeBSD/distfiles
XDD_INSTALL_STAGING=NO

define XDD_BUILD_CMDS
	$(TARGET_MAKE_ENV) \
	CFLAGS="$(TARGET_CFLAGS)" LDFLAGS="$(TARGET_LDFLAGS)" $(MAKE) -C $(@D)  \
	CC="$(TARGET_CC)" RANLIB="$(TARGET_RANLIB)" AR="$(TARGET_AR)"
endef

define XDD_INSTALL_STAGING_CMDS
	$(TARGET_MAKE_ENV) \
	$(MAKE) DESTDIR=$(STAGING_DIR) -C $(@D) install 
endef

define XDD_INSTALL_TARGET_CMDS
	$(TARGET_MAKE_ENV) $(TARGET_CONFIGURE_OPTS) \
	$(MAKE) DESTDIR=$(TARGET_DIR) -C $(@D) install 
endef

define XDD_CLEAN_CMDS
	rm -f $(addprefix $(TARGET_DIR),/usr/bin/xdd \
					/usr/bin/timeserver \
					/usr/bin/gettime)
	rm -f $(addprefix $(STAGING_DIR),/usr/bin/xdd \
					/usr/bin/timeserver \
					/usr/bin/gettime)
	-$(MAKE) -C $(@D) clean
endef

$(eval $(generic-package))
