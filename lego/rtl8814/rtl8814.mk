################################################################################
#
# rtl8814
#
################################################################################

RTL8814_VERSION = v1.6_20151022.001
RTL8814_SOURCE = rtl8194_driver_$(RTL8814_VERSION).tar.gz
RTL8814_SITE = http://mirror.greenwavereality.com/lego
#RTL8814_VERSION = v1.6_20151022
#RTL8814_SITE_METHOD=local
#RTL8814_SITE = board/auklet/wifi/RTL8814
RTL8814_BASENAME = rtl8194_driver_$(RTL8814_VERSION)_$(RTL8814_VERSION)
RTL8814_LICENSE = GPLv2
RTL8814_LICENSE_FILES = COPYING

RTL8814_DEPENDENCIES = linux

# Analogous code exists in linux/linux.mk. Basically, the generic
# package infrastructure handles downloading and applying remote
# patches. Local patches are handled depending on whether they are
# directories or files.
RTL8814_PATCHES = $(call qstrip,$(BR2_TARGET_RTL8814_PATCH))
RTL8814_PATCH = $(filter ftp://% http://% https://%,$(RTL8814_PATCHES))

define RTL8814_APPLY_LOCAL_PATCHES
	for p in $(filter-out ftp://% http://% https://%,$(RTL8814_PATCHES)) ; do \
		if test -d $$p ; then \
			$(APPLY_PATCHES) $(@D) $$p \*.patch || exit 1 ; \
		else \
			$(APPLY_PATCHES) $(@D) `dirname $$p` `basename $$p` || exit 1; \
		fi \
	done
endef
RTL8814_POST_PATCH_HOOKS += RTL8814_APPLY_LOCAL_PATCHES

RTL8814_MODULE_SUBDIRS = driver/rtl8192cd
RTL8814_MODULE_MAKE_OPTS = \
	KSRC=$(LINUX_DIR)

$(eval $(kernel-module))
$(eval $(generic-package))
