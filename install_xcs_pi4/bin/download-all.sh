#!/bin/bash

USB_PATH="/usb/usbstick/openvario/download/"
DOWNLOAD_PATH="/home/root/.xcsoar"
SAVE_FILE="${USB_PATH}xcs-`date +%F`.tgz"
# SAVE_FILE="${USB_PATH}xcs-all.tgz"
if [ ! -d "${USB_PATH}" ]; then
        mkdir "${USB_PATH}"
fi

if [ -z "$(ls $DOWNLOAD_PATH/* 2>/dev/null)" ]; then
        echo "No files found !!!"
else
        cd ${DOWNLOAD_PATH}
        tar vczf "${SAVE_FILE}" .
fi

echo "Umount Stick ..."
umount /dev/sda1
echo "Done !!"

