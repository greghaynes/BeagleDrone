Communication
=============

The primary communication channel is over serial, using Afproto (see afproto
docs for more information). The first byte in each afproto frame corresponds
to a command type id. Any following data is handled in a command specific
manner. There is no differentiation is made between commands sent to the drone
and commands sent from the drone, although many commands can only be sent in
one of the directions.


Commands
--------

Below is a list of command ids and information about that command. Directions
the command can be sent is denoted R if it can be received from drone, and S
if it can be sent to the drone.

#### 0. Log

Direction: RS

###### If received:

The first byte of a log message specifies the message 'level'.

Possible log levels are:
* 0: Debugging
* 1: Notice
* 2: Warning
* 3: Error
* 4: Critical

Any following data is ascii text describing the error.

###### If sent:

The first byte specifies the log level threshold. Only log messages with a log
level at or above this threshold will be sent from the drone.


#### 1. System


#### 2. Navigation

