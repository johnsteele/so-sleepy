#!/bin/sh

module="sleep-mod"
device="sleepy_module"

#Invoke rmmod with all arguments we got.
/sbin/rmmod $module $* || exit 1

#Remove the stale nodes.
rm -f /dev/${device} /dev/${device}0

