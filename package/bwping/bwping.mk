#############################################################
#
# bwping
#
#############################################################
BWPING_VERSION = 1.4
BWPING_SOURCE = bwping-$(BWPING_VERSION).tar.gz
BWPING_SITE = http://sourceforge.net/projects/bwping/files
BWPING_INSTALL_STAGING = YES
BWPING_INSTALL_TARGET = YES

$(eval $(autotools-package))
