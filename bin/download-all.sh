#!/bin/bash

USB_PATH="/media/usbstick/openvario/download/"
DOWNLOAD_PATH="${HOME}/.xcsoar"
SAVE_FILE="${USB_PATH}xcs-`date +%Y-%m-%d`.tgz"

sudo mount -a

if [ ! -d "${USB_PATH}" ]; then
        mkdir "${USB_PATH}"
fi

if [ -z "$(ls ${DOWNLOAD_PATH}/* 2>/dev/null)" ]; then
        echo "No files found !!!"
else
        cd ${DOWNLOAD_PATH}
	echo "This will take sone time ..."
        tar czvf ${SAVE_FILE} .
fi

# echo "Umount Stick ..."
# umount /dev/sda1
echo "Done !!"

