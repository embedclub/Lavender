#!/bin/sh

export buildHome=/home/yang/ws/audio/build
export LIBDIR=$buildHome/lib
export LDFLAGS=-L$buildHome/lib 
export LD_LIBRARY_PATH=$buildHome/lib
export LD_RUN_PATH=$LIBDIR
export PKG_CONFIG_PATH=$buildHome/lib
sudo apt-get install intltool libtool libjson-c-dev libsndfile1-dev \
 help2man texinfo autogen g++-arm-linux-gnueabihf bison elfutils

############## cross-compile json-c GIT for pulseaudio-6.0 ##########
#cd json-c/
#git pull
#make clean
#./autogen.sh
#./configure --host=arm-linux-gnueabihf --prefix=$buildHome
#make install
#cd ..
############ endof json-c ##############

########### corss-compile libtool GIT for pulseaudio-6.0 #######
#cd libtool/
#git pull
#make clean
#./configure --host=arm-linux-gnueabihf --prefix=$buildHome
#make install
#cd ..
############ endof libtool ##############


############ cross-compile python2.7.11 for alsa-lib ##########
#cd Python-2.7.11/
#make distclean
#./configure
#make python Parser/pgen
#mv python hostpython
#mv Parser/pgen Parser/hostpgen
#make distclean
#./configure --host=arm-linux-gnueabihf --build=arm --prefix=$buildHome --disable-ipv6 ac_cv_file__dev_ptmx=no ac_cv_file__dev_ptc=no --enable-shared 
#make HOSTPYTHON=./hostpython HOSTPGEN=./Parser/hostpgen BLDSHARED="arm-linux-gnueabihf-gcc -shared"
#make install HOSTPYTHON=./hostpython BLDSHARED="arm-linux-gnueabihf-gcc -shared"
#cd ..


############ cross-compile alsa-lib GIT for libsndfile #########
#cd alsa-lib/
#git pull
#make clean
#./gitcompile --host=arm-linux-gnueabihf --prefix=$buildHome --disable-python
#make install
#cd ..
########## endof alsa #######################


############ cross-compile libsndfile GIT for pulseaudio-6.0 ####
#cd libsndfile/
#git pull
#make clean
#./autogen.sh
#./configure --host=arm-linux-gnueabihf --prefix=$buildHome
#make install
#cd ..
########### endof libsndfile ###########


########## cross-compile expat-code GIT for libdbus ######
#cd expat-code_git/expat
#git pull
#make clean
#./buildconf.sh
#./configure --host=arm-linux-gnueabihf --prefix=$buildHome
#make install
#cd ../../
######### endof expat-code ##############


########## cross-compile libffi GIT for glib ##############
#cd libffi/
#git pull
#make clean
#./autogen.sh
#./configure --host=arm-linux-gnueabihf --prefix=$buildHome
#make install
#cd ../
#sudo cp $buildHome/lib/libffi.so* /usr/arm-linux-gnueabihf/lib/
######### endof libffi #################

########## cross-compile zlib GIT for glib ##################
#cd zlib/
#git pull
#make clean
#export INSTALLDIR=$buildHome
#export PATH=$INSTALLDIR/bin:$PATH
#export TARGETMACH=arm-linux-gnueabihf
#export BUILDMACH=i686-pc-linux-gnu
#export CROSS=arm-linux-gnueabihf
#export CC=${CROSS}-gcc
#export LD=${CROSS}-ld
#export AS=${CROSS}-as
#./configure --prefix=$buildHome
#make install
#cd ..
######### endof zlib ###################

########## cross-compule glib GIT for libdbus #############
#export LIBFFI_LIBS=$buildHome/lib/libffi.la
#export LIBFFI_CFLAGS=$buildHome/lib/libffi-3.99999/include
#export ZLIB_CFLAGS=$buildHome/include
#export ZLIB_LIBS=$buildHome/lib
#
#cd glib/
#git pull
#make distclean
#./autogen.sh
#cp ../Makefile.in gobject/Makefile.in
#./configure --host=arm-linux-gnueabihf --prefix=$buildHome glib_cv_stack_grows=yes \
#glib_cv_uscore=yes ac_cv_func_posix_getpwuid_r=no \
#ac_cv_func_posix_getgrgid_r=no --with-libiconv=no --without-pcre --enable-xattr=no \
#CFLAGS=-I$LIBFFI_CFLAGS ZLIB_CFLAGS=-I$ZLIB_CFLAGS ZLIB_LIBS="-lz -L$buildHome/lib" 
#make install
#cd ..
######### endof glib ############


########## cross-compile libdbus GIT for pulseaudio-6.0 ####
#cd dbus/
#git pull
#make clean
#./autogen.sh
#./configure --host=arm-linux-gnueabihf --prefix=$buildHome
#make install
#cd ..
######### endof libdbus ########

########### cross-compile libavahi GIT for pulseaudio-6.0 ####
#cd avahi/
#git pull
#make clean
#./autogen.sh
#./configure --host=arm-linux-gnueabihf --prefix=$buildHome --with-distro=none --disable-qt3 \
# --disable-qt4 --disable-gdbm --disable-libdaemon --disable-mono --disable-xmltoman --disable-manpages
#make install
#cd ..

########### cross-compile openssl-1.0.2 for pulseaudio-6.0 ####
#rm -rf openssl-1.0.2f/
#tar xvf openssl-1.0.2f.tar.gz
#cd openssl-1.0.2f/
#./Configure -fPIC --openssldir=$buildHome shared os/compiler:arm-linux-gnueabihf-gcc
#make install
#cd ..
######### endof openssl #######


########## cross-compile  pulseaudio-6.0 ####################
#sudo cp $buildHome/include/openssl/opensslconf.h /usr/include/openssl/
#
#rm -rf pulseaudio-6.0/
#tar xvf pulseaudio-6.0.tar.xz
#cd pulseaudio-6.0/
#./configure --host=arm-linux-gnueabihf --without-caps --prefix=$buildHome \
#CFLAGS="-fomit-frame-pointer" \
#LIBSNDFILE_CFLAGS=-I$buildHome/include \
#LIBSNDFILE_LIBS="-lsndfile -L$buildHome/lib" \
#LIBOPENSSL_CFLAGS=-I$buildHome/include \
#LIBOPENSSL_LIBS=$buildHome/lib
#make install
#cd ..
######### endof pulseaudio-6.0 #####


############ cross-compile elfutils GIT for bluez ##########
#cd elfutils/
#git pull
#make clean
#autoreconf -f -i
#./configure --host=arm-linux-gnueabihf --prefix=$buildHome \
# --enable-maintainer-mode CFLAGS=-I$buildHome/include
#make install


########## cross-compile bluez GIT #######################
cd bluez/
git pull
make clean
./bootstrap-configure --host=arm-linux-gnueabihf --prefix=$buildHome \
 CFLAGS=-I$buildHome/include







