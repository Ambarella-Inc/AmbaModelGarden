# Copyright (C) 2023 Ambarella International LP

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://apache-2.0.txt;md5=3b83ef96387f14655fc854ddc3c6bd57"

# No information for SRC_URI yet (only an external source tree was specified)
SRC_URI = ""

DEPENDS += "opencv json-c"
RDEPENDS:${PN} += "opencv json-c"

EXTRADEPS = "AMBA_SOC!=s6lm AMBA_CAVALRY_ARCH=cavalry_v2 unselect"
EXTRADEPS += "&&?board &&??ambcavalry-header &&??ambvideo-header"
EXTRADEPS += "&&??libnnctrl &&??libcavalrymem &&??libvproc &&??libeazyai"

inherit ambaenv
inherit ambadebug
inherit weakdep
inherit sanity

# Set this option as 1 for APP debug purpose
INHIBIT_PACKAGE_STRIP="0"

# NOTE: this is a Makefile-only piece of software, so we cannot generate much of the
# recipe automatically - you will need to examine the Makefile yourself and ensure
# that the appropriate arguments are passed in.

do_configure () {
	# Specify any needed configure commands here
	:
}

do_compile () {
	# You will almost certainly need to add additional arguments here
	oe_runmake -f amba.mk
}

do_install () {
	# NOTE: unable to determine what to put here - there is a Makefile but no
	# target named "install", so you will need to define this yourself
	oe_runmake -f amba.mk install
}

FILES:${PN} += "${bindir}"
