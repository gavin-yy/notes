
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
	install: https://docs.docker.com/engine/install/ubuntu/
	1. try apt install first, if conflict with local packages. try #install from package
	
	

## flash image to sd card.



## board bootup


## enable wifi


## enable bluetooth

