#!/bin/bash

# Installs xcode-coveralls
git clone --recursive https://github.com/macmade/xcode-coveralls.git /tmp/xcode-coveralls
sudo xctool --project /tmp/xcode-coveralls/xcode-coveralls.xcodeproj --scheme xcode-coveralls DSTROOT=/ install
