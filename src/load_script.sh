#!/bin/sh
# $Id: load_script.sh, v 1.0.0 2010/08/29 John Exp $
module="sleep-mod"
device="sleepy_module"
mode="664" #read and write 


#More than likely this driver will get a major dynamically, 
#so invocation of insmod can be replaced by this script.

#If you get Permission denied, it's because the permissions
#for the file first have to be set to executable, and by 
#default the permissions for new files are set o read and 
#write only. 
#Group: Since distributions do it differently, look for wheel,
#or use staff.
if grep -q '^staff:' /etc/group; then	
	group="staff"
else
	group="wheel"
fi


#Invoke insmod with all arguments we got, and use a path name,
#as insmod doesn't look in '.' by default.
#This installs our loadable module into the running kernel.
/sbin/insmod ./$module.ko $* || exit 1

#Get the driver major.
major=$(awk "\$2==\"$device\" {print \$1}" /proc/devices)

#Remove the stale nodes.
rm -f /dev/${device}0
mknod /dev/${device}0 c ${major} 0


#Create symbolic link, now just refer to /dev/${device}
ln -sf /dev/${devic}0 /dev/${device}
chgrp $group /dev/${device}0
chmod $mode /dev/${device}0 


