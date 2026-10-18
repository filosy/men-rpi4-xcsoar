# men-rpi4-xcsoar

Context menu support and helper tools for running XCSoar on a Raspberry Pi 4. This repository includes scripts for packaging user data, installer/patch archives, and small native utilities for checking DRI/GBM graphics support.

## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Repository structure](#repository-structure)
- [Requirements](#requirements)
- [Quick start](#quick-start)
- [Usage](#usage)
- [Building the diagnostic tools](#building-the-diagnostic-tools)
- [Examples](#examples)
- [Debugging and diagnostics](#debugging-and-diagnostics)
- [Contributing](#contributing)
- [License](#license)
- [To be completed](#to-be-completed)

## Overview
This repository provides a set of helper scripts and packaged resources designed to simplify the installation and maintenance of XCSoar on Raspberry Pi 4 systems. It includes tools for creating backup archives of XCSoar data, installer and patch bundles, and lightweight native utilities to verify graphics support through DRM/GBM/EGL.

## Features
- Shell scripts to package XCSoar data into a tar.gz archive for USB transfer
- Installer and patch archives stored in the repository root
- Small C++ utilities for identifying usable /dev/dri devices and validating GBM/DRM support
- Raspberry Pi 4 oriented setup helpers for OpenVario-style environments

## Repository structure
- README.md — project overview and usage notes
- bin/
  - download-all.sh — creates an archive of XCSoar data and stores it on a USB drive
- install_xcs_pi4/
  - bin/download-all.sh — Raspberry Pi-specific variant of the archive script
  - tools/identify_dri_device/
    - fnd_dri_device.cpp, tst_dri_device.cpp — diagnostic source files
    - fnd_dri_device — compiled utility
    - drm.h — header placeholder / compatibility include
- patch_xcs_inst (1)/ — patch-related helper directory
- *.tgz — installation and patch archives included at the repository root

## Requirements
- Raspberry Pi 4 with a compatible Linux image
- bash or POSIX shell
- sudo access for mounting/unmounting media and opening DRM devices
- For compiling the native diagnostics:
  - build-essential
  - libegl1-mesa-dev
  - libgbm-dev
  - libdrm-dev

## Quick start
Clone the repository:
```bash
git clone https://github.com/filosy/men-rpi4-xcsoar.git
cd men-rpi4-xcsoar
```

Run the main script:
```bash
chmod +x bin/download-all.sh
./bin/download-all.sh
```

Use the Raspberry Pi installer variant:
```bash
chmod +x install_xcs_pi4/bin/download-all.sh
sudo install_xcs_pi4/bin/download-all.sh
```

## Usage
The scripts are intended to:
- inspect a target XCSoar data directory (typically ~/.xcsoar)
- package the directory into a tar.gz archive
- save the archive to an attached USB drive path, such as:
  - /media/usbstick/openvario/download/
  - /usb/usbstick/openvario/download/

If the default paths in your system differ, update the variables at the top of the script before running it.

## Building the diagnostic tools
Navigate to the DRI diagnostic folder and compile the utilities:
```bash
cd install_xcs_pi4/tools/identify_dri_device
g++ -o fnd_dri_device fnd_dri_device.cpp -lEGL -lgbm -ldrm
g++ -o tst_dri_device tst_dri_device.cpp -lEGL -lgbm -ldrm
```

Run them:
```bash
sudo ./fnd_dri_device
sudo ./tst_dri_device
```

Optional argument example:
```bash
sudo ./tst_dri_device /dev/dri/card
```

## Examples
Create an archive of the local XCSoar data directory:
```bash
chmod +x bin/download-all.sh
./bin/download-all.sh
```

Verify the archive was created in the expected USB path:
```bash
ls /media/usbstick/openvario/download/
```

## Debugging and diagnostics
The native C++ utilities are designed to:
- open /dev/dri/cardN devices
- create a GBM device
- query DRM resources using drmModeGetResources()

If a diagnostic fails, check:
- permission to access /dev/dri/*
- the presence of Mesa/GBM/DRM development packages
- whether the correct GPU device is exposed by the kernel
- whether the system has the correct video group permissions

## Contributing
Contributions are welcome. Please:
- open an issue for bugs or feature requests
- use a feature branch for changes
- keep commit messages clear and focused
- submit a pull request with a clear description of the change

## License
This project does not currently specify a license in the repository. Please add a LICENSE file and select an appropriate license before publishing or distributing the project publicly.

## To be completed
The following sections should be completed before the project is considered fully documented:
- detailed description of the .tgz installer and patch packages
- intended installation flow for XCSoar on Raspberry Pi 4
- hardware/software prerequisites for supported setups
- screenshots or diagrams of the deployment environment
- maintainer contact information and repository usage policy
- final license choice and corresponding LICENSE file
