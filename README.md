BeagleDrone
==============

An Open Source drone platform using the BeagleBone (black).

[![Build Status](https://travis-ci.org/greghaynes/BeagleDrone.png)](https://travis-ci.org/greghaynes/BeagleDrone)

## Goals

We are developing a well tested drone control application which is able to be
run independently of the target device. This will allow us to rapidly develop
advanced control and state estimation techniques which we can have high
confidence will work on target devices meeting predefined criteria.

We are also developing a driver layer for this application to allow it to be
run on the BeagleBone Black. This device should have enough computing and
memory resources, as well as sufficient peripherals for most drone
applications.


## Communication

We primarily communicate on irc in #beagledrone @ freenode. Please join in at
any time!


## Developer Documentation

Information for developers can be found on our [wiki](https://github.com/greghaynes/BeagleDrone/wiki).

# Firmware

The firmware directory contains the code which runs on the beagleboard.

## Dependencies

You require make and an gcc eabi arm cross compiler toolchain to build this
project. Although any method of obtaining the arm-eabi will work equally well,
below are the recommended methods for obtaining the toolchain.

## Toolchain

Please visit https://launchpad.net/gcc-arm-embedded to obtain an arm toolchain
for your platform. Ubuntu users may want to instead visit
https://launchpad.net/~terry.guo/+archive/gcc-arm-embedded for a package
installation.

## Building

To build the package make sure the arm-none-eabi-\* tools are in your PATH.

Running the command `make` will create a boot.bin, suitable for flashing


## Flashing

I have yet to find a pleasant method for flashing. Currently, I use an SD card
with U-Boot (comes on standard beaglebone linux image). I run the `loady`
command at the U-Boot prompt, and use yterminal protocol (via minicom) to
send the boot.bin. I then execute `go 0x82000000` to run the binary.

## Testing

Change directory into firmware/tests. Run 'make'.

# Client

The client is run on a PC and can be used to communicated with the drone.

## Dependencies

Qt5, g++ and CMake are required to build and run the client;

## Building

To build the client run the following commands

`cd client; cmake .; make`
