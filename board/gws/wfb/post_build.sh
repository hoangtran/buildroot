# !/bin/sh

BOARD_DIR="$(dirname $0)"

MKIMAGE=$HOST_DIR/usr/bin/mkimage

cp -f ${BOARD_DIR}/uImage.its ${BINARIES_DIR}/
cp -f ${BOARD_DIR}/u-boot.scr ${BINARIES_DIR}/

mkdir -p ${TARGET_DIR}/boot
${MKIMAGE} -D "-I dts -O dtb -p 2000" -f ${BINARIES_DIR}/uImage.its ${TARGET_DIR}/boot/uImage
