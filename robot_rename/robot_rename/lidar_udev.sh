echo  'KERNEL=="ttyACM*", ATTRS{idVendor}=="1a86", ATTRS{idProduct}=="55d4",ATTRS{serial}=="0001", MODE:="0777", GROUP:="dialout", SYMLINK+="N10_lidar"' >/etc/udev/rules.d/lidar.rules
service udev reload
sleep 2
service udev restart


