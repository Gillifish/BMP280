#! /bin/bash

if [ -d "/Volumes/RPI-RP2" ]; then
    cp build/BMP280.uf2 /Volumes/RPI-RP2
    echo "Upload successful..."
else
    echo "Could not find Pico Volume..."
fi