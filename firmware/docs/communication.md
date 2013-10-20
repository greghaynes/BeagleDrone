Communication
=============

The primary communication channel is over serial, using Afproto (see afproto
docs for more information). The first byte in each afproto frame corresponds
to a command type id. Any following data is handled in a command specific
manner.


Commands
--------

Below is a list of command ids and information about each command. Directions
the command can be sent is denoted R if it can be received from drone, and S
if it can be sent to the drone.

#### 0. Log

Direction: RS

###### If received from drone:

The first byte of a log message specifies the message 'level'.

Possible log levels are:
* 0: Debugging
* 1: Notice
* 2: Warning
* 3: Error
* 4: Critical

Any following data is ascii text describing the error.

###### If sent to drone:

The first byte specifies the log level threshold. Only log messages with a log
level at or above this threshold will be sent from the drone.


#### 1. System

Direction: RS

The first byte always specifies a sub-command. The details of each sub command
are outlined below.

###### If received from drone:

Sub-commands:
* 0: Drone transitioned to on state
* 1: Drone transitioned to off state

###### If sent to drone:

Sub-commands:
* 0: Turn on drone
* 1: Turn off drone


#### 2. Navigation

Direction: RS

The first byte always specifies a sub-command. The details of each sub-command
are outlined below.

Sub-commands:

###### If received from drone:


###### If sent to drone:

Sub-commands:

* 0: Set Roll setpoint
* 1: Set Pitch setpoint
* 2: Set Yaw setpoint
* 3: Set X setpoint
* 4: Set Y setpoint
* 5: Set Z setpoint

For information about navigation axes, see navigation doc.
