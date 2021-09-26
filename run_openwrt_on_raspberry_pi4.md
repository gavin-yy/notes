# build and  run openwrt on raspberry pi4

1. get openwrt source code from github, switch to the version to build.
	```shell
	$ git clone https://github.com/openwrt/openwrt
	$ git branch -a
	# use master branch
	```

2. system prepare. use docker to build image. [about docker](#docker-notes)


3. step in QuickStart page
	```shell
	$ ./scripts/feeds update -a
	$ ./scripts/feeds install -a
	$ make menuconfig
	configure the cpu and target board.
	```

3. build
	```shell
	$ make menuconfig
	```

## docker-notes
install docker on ubuntu: https://docs.docker.com/engine/install/ubuntu/
Try apt install first, if it conflict with local packages. try install from package
    
There is a docker image for openwrt build env.
```shell
https://hub.docker.com/r/p3terx/openwrt-build-env

$ docker pull p3terx/openwrt-build-env
$ docker images
$ docker run \
    -itd \
    --name openwrt-build-env \
    -h P3TERX \
    -p 10022:22 \
    -v ~/open/openwrt:/home/user/openwrt \
    p3terx/openwrt-build-env
    
$ docker restart openwrt-build-env
$ docker exec -it openwrt-build-env /bin/bash

comment:
-p : set NAT rule to iptables. map system's port 10022 to docker's port 22
    on host system run $ssh -p 10022 and can login the system.
    docker network refer: https://www.qikqiak.com/k8s-book/docs/7.Docker%E7%9A%84%E7%BD%91%E7%BB%9C%E6%A8%A1%E5%BC%8F.html

-v: mount the system file to docker

```

## flash image to sd card.
```shell
	lsblk

	gzip -d imagename-factory.img.gz
	dd if=imagename-factory.img of=/dev/sdX bs=2M conv=fsync
	sync
```

I used the offical tools 'Raspberry Pi Imager' provided by raspberry official web page to flash the sd card.


## board bootup
watch system bootup by serial port.
serial port: 115200 8n1


## enable wifi

the default VHT80 doesn't work in our region. change it to VHT20.

```shell
uci set wireless.radio0.disabled=0
uci set wireless.radio0.country='CN'
## iw phy phy0 info; show band1 & band2 supports ht20&ht40
## so default vht80 doesn't work
## refer : https://forum.openwrt.org/t/ac-mode-on-raspberry-pi-4-wifi/65074/33
## error log: ieee80211 phy0: brcmf_cfg80211_start_ap: Set Channel failed: chspec=57386, -52
uci set wireless.radio0.htmode='VHT20'
uci commit wireless
wifi reload
```

## enable bluetooth
1. select kernel module -> other module -> kmod-bluetooth
2. select bluez-utils
3. enable uart to bluetooth chip.
```
modify boot/distroconfig.txt
[pi4]
#dtoverlay=disable-bt
```

4. not use uart as system console.
```shell
# not print system log to uart.
root@OpenWrt:/boot# cat cmdline.txt 
console=serial0,115200 console=tty1 root=/dev/mmcblk0p2 rootfstype=squashfs,ext4 rootwait
change to -->
console=tty1 root=/dev/mmcblk0p2 rootfstype=squashfs,ext4 rootwait

# reboot
```

5. copy bluetooth firmware to board.
```shell
download firmware from: https://github.com/LibreELEC/brcmfmac_sdio-firmware-rpi/tree/master/firmware/brcm
copy BCM43xxx.hcd to /lib/firmware/brcm/
```

6.  attach.
```shell
#hciattach /dev/ttyAMA0 bcm43xx 115200 noflow -
hciattach /dev/ttyAMA0 bcm43xx 921600 noflow -
if it shows timeout, run this command again.

hciconfig hic0 up
```
