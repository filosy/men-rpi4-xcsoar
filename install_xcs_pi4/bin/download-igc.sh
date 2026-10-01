#!/bin/bash

USB_PATH="/media/usbstick/openvario/logs"
IGC_PATH="${HOME}/.xcsoar/logs"
TSTAMP="${USB_PATH}/last_logs_download"

sudo mount -a

if [ ! -d "${USB_PATH}" ]; then
        mkdir "${USB_PATH}"
fi
if [ ! -e "${TSTAMP}" ]; then
        touch -d2000-01-01 "${TSTAMP}"
fi


if [ -z "$(ls ${IGC_PATH}/*.igc 2>/dev/null)" ]; then
        echo "No files found !!!"
else
        for igcfile in $(find ${IGC_PATH} -type f -newer "${TSTAMP}"); do
                echo ${igcfile}
                cp -p ${igcfile} ${USB_PATH}
        done
fi
cp ${HOME}/.xcsoar/xcsoar.log ${USB_PATH}

touch "${TSTAMP}"
echo 'Done !!'

# umount /media/usbstick
