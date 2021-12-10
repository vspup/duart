#
# This file is the startapp recipe.
#

SUMMARY = "Simple startapp application"
SECTION = "PETALINUX/apps"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://startapp \
	"

S = "${WORKDIR}"

FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

inherit update-rc.d

INITSCRIPT_NAME = "startapp"
INITSCRIPT_PARAMS = "start 99 S ."

do_install() {
       install -d ${D}/${sysconfdir}/init.d
       install -m 0755 ${S}/startapp ${D}${sysconfdir}/init.d/startapp
}
FILES_${PN} += "${sysconfdir}/*"
