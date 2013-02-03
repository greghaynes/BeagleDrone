# BeagleBareBone
==============

A barebone C OS for the beaglebone


## Why

Robotics projects, specifically drones, often need far more memory than a
typical microcontroller can offer. This is often solved by using a second
computer running a medern operating system in exchange for a massive complexity
hit. Rather than develop two separate code bases, this project aims to use the
BeagleBone as a platform to develop a drone using embedded C without the
resource limitations of a typical microcontroller.


## Dependencies

You require make and an gcc eabi arm cross compiler toolchain to build this
project. Although any method of obtaining the arm-eabi will work equally well,
below are the recommended methods for obtaining the toolchain.

### OS X

I have used jsnyder's ARM EABI Toolchain Builder to great success, it is very
easy to install by following the guide in his github repository:

http://github.com/jsnyder/arm-eabi-toolchain

### Linux

I have not tested jsnyder's toolchain on OS X but it claims to work on linux as
well. On Linux I tend to use esden's summon-arm-toolchain package:

http://github.com/esden/summon-arm-toolchain


## Building

To build the package make sure the arm-none-eabi-\* tools are in your PATH.

Running the command `make` will create a boot.bin, suitable for flashing

