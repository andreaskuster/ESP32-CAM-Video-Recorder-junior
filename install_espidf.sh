#!/bin/sh
# run this script to install esp-idf and arduino-esp32 using: source install_espidf.sh
echo "installing esp-idf..."
if [ ! -d "esp-idf" ] ; then
  git clone https://github.com/espressif/esp-idf.git
fi
(
  cd esp-idf || exit
  git checkout 1d7068e4b
  git submodule update --init --recursive
  ./install.sh
)

echo "esp-idf installed"

echo "installing adruino-esp32..."
if [ ! -d "components" ] ; then
    mkdir -p components
fi

(
  cd components || exit
  if [ ! -d "arduino" ] ; then
    git clone https://github.com/espressif/arduino-esp32.git arduino
  fi
  (
    cd arduino || exit
    git checkout master
    git submodule update --init --recursive
  )
)
echo "arduino-esp32 installed"
# set env variables
. ./esp-idf/export.sh
