#!/bin/bash
./rm_symlinks.sh

echo " -- Linking Makefile"
ln -s ../Makefile Makefile
echo " -- Making z_framework folder"
mkdir z_framework
cd z_framework


#### uncomment to link the respective file ####

### zf_term 
for F in zf_term zf_spritesheet zf_rect zf_sprite zf_conversion zf_strings
do
    echo " -- linking $F "
    ln -s ../../../${F}.* .
done
echo " -- Linking sample graphical font .."
cd ..
mkdir data/
ln -s ../../../sample_graphics/font_32 data/font_32
