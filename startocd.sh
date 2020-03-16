#!/bin/bash

sudo openocd -f /usr/local/share/openocd/scripts/interface/sysfsgpio-raspberrypi.cfg -c "transport select swd" -c "adapter_khz 1000" -f /usr/local/share/openocd/scripts/target/stm32f1x.cfg

