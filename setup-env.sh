#!/bin/bash

export PATH=/home/roedy/workspace/petchatz/build/x86_64/gcc_arm-linux-gnueabihf/bin:${PATH}
export ARCH=arm
export CPU=armv7l
export MARCH=armv7-a
export MTUNE=cortex-a9
export HOST=arm-linux-gnueabihf
export CROSS_COMPILE=${HOST}-
export ROOTFS=/home/roedy/workspace/petchatz/build/armv7l/petchatz/root
export CONF_ARGS="--host=${HOST} --with-sysroot=${ROOTFS} --prefix=/usr --sysconfdir=/etc --localstatedir=/var --with-gnu-ld"
export CONFIGURE="./configure ${CONF_ARGS}"
export CFLAGS="-march=${MARCH} -mtune=${MTUNE} --sysroot=${ROOTFS} -mfloat-abi=hard -mfpu=neon -ftree-vectorize -ffast-math "
export CXXFLAGS="${CFLAGS}"
export CPPFLAGS="${CFLAGS}"
export LDFLAGS="-march=${MARCH} -mtune=${MTUNE} --sysroot=${ROOTFS}"
