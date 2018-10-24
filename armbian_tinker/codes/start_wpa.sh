#!/bin/bash

sudo systemctl start wpa_supplicant.service
sudo wpa_supplicant -i wlan0 -c/etc/wpa_supplicant/wpa_supplicant.conf -D wext 
