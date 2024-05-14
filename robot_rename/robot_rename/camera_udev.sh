echo  'KERNEL=="ttyACM*", ATTRS{idVendor}=="1bcf", ATTRS{idProduct}=="2281", MODE:="0777", SYMLINK+="camera"' >/etc/udev/rules.d/camera.rules
service udev reload
sleep 2
service udev restart


