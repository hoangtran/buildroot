################################################################################
#
# qcsapi_client
#
################################################################################

QCSAPI_CLIENT_VERSION = v37.4.5.97
QCSAPI_CLIENT_SITE = $(TOPDIR)/lego/qcsapi_client/qcsapi_client_src
QCSAPI_CLIENT_SITE_METHOD = local

define QCSAPI_CLIENT_BUILD_CMDS
	$(MAKE) CC="$(TARGET_CC)" -C $(@D) all
endef

define QCSAPI_CLIENT_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0755 $(@D)/libqcsapi_client.so* $(TARGET_DIR)/usr/lib
	$(INSTALL) -D -m 0755 $(@D)/qcsapi_sockrpc $(TARGET_DIR)/usr/bin
endef

$(eval $(generic-package))
