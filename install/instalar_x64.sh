#!/bin/bash
# -*- ENCODING: UTF-8 -*-
echo
	sudo apt-get install liballegro4.2-dev
	sudo add-apt-repository ppa:webupd8team/haguichi
	sudo apt-get update
	sudo dpkg -i logmein-hamachi_2.1.0.174-1_amd64
	sudo apt-get install haguichi
	sudo apt-get install libtool
	sudo apt-get install automake
	tar -xvf CUnit-2.1-3.tar
	cd CUnit-2.1-3
	./bootstrap
	./configure --prefix=/usr
	make
	sudo make install
	cd ..
	sudo rm -r CUnit-2.1-3
exit
