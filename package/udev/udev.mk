#############################################################
#
# udev
#
#############################################################
UDEV_VERSION = 170
UDEV_SOURCE = udev-$(UDEV_VERSION).tar.bz2
UDEV_SITE = $(BR2_KERNEL_MIRROR)/linux/utils/kernel/hotplug/
UDEV_INSTALL_STAGING = YES
UDEV_INSTALL_TARGET=YES

UDEV_CONF_ENV += \
	PKG_CONFIG_PATH=$(STAGING_DIR)/usr/share/pkgconfig 

UDEV_CONF_OPT+= \
	--disable-introspection \
	--disable-gtk-doc \
	--disable-gtk-doc-html \
	--with-pci-ids-path=$(STAGING_DIR)/usr/share/ \
	--with-usb-ids-path=$(STAGING_DIR)/usr/share/ \
	--disable-udev_acl \
	--disable-gudev \
	--disable-introspection \
	--disable-keymap

UDEV_DEPENDENCIES= usbutils pciutils

ifeq ($(BR2_PACKAGE_SYSTEMD),y)
	UDEV_CONF_OPT += --with-systemdsystemunitdir=/lib/systemd/system/
endif

define UDEV_INSTALL_INITSCRIPT
	$(INSTALL) -m 0755 package/udev/S10udev $(TARGET_DIR)/etc/init.d/S10udev
endef

UDEV_POST_INSTALL_TARGET_HOOKS += UDEV_INSTALL_INITSCRIPT

$(eval $(call AUTOTARGETS))
