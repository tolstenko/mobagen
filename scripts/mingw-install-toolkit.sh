#!/usr/bin/env bash
echo "--------------------------------------------------------------"
echo "Installing toolkit"
echo "--------------------------------------------------------------"
/usr/bin/pacman -Sy --noconfirm base-devel mingw-w64-x86_64-toolchain git subversion mercurial mingw-w64-x86_64-cmake wget curl p7zip
#wget http://sourceforge.net/projects/codeblocks/files/Binaries/Nightlies/2018/CB_20181008_rev11499_win64.7z
