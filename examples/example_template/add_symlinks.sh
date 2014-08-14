#!/bin/bash
./rm_symlinks.sh

echo " -- Linking Makefile"
ln -s ../Makefile Makefile
echo " -- Making z_framework folder"
mkdir z_framework
cd z_framework


#### uncomment to link the respective file ####

### zf_term 
echo " -- Linking zf_term .."
ln -s ../../../zf_term.* .
echo " -- Linking zf_spritesheet .."
ln -s ../../../zf_spritesheet.* .
cd ..
echo " -- Linking sample graphical font .."
ln -s ../../sample_graphics/font_32 data/font_32
