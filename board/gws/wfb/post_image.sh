# !/bin/sh

BOARD_DIR="$(dirname $0)"

MKIMAGE=$HOST_DIR/usr/bin/mkimage

cp -f ${BOARD_DIR}/uRamdisk.its ${BINARIES_DIR}/

${MKIMAGE} -D "-I dts -O dtb -p 2000" -f ${BINARIES_DIR}/uRamdisk.its ${BINARIES_DIR}/uRamdisk
