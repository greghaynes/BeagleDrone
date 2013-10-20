Navigation
==========

This document gives an overview of conventions and high-level properties of
the navigation components.

Reference Frames
----------------

Reference frames correspond to those outlined in "Introduction to Modern
Navigation Systems" by Esmat Bekir. A brief summary is below.

#### Inertial Frame

This frame has its origin at Earth center, but does not rotate with it.

* X points toward north pole with origin at earth center.
* Y and Z plane is at the equator.

#### Earth-Fixed Frame

This frame has its origin at Earth center, and rotates with the earth.

* X points toward north pole with origin at earth center.
* Y points at the equator and is perpendicular to the Z axis.
* Z points at the intersection of the Greenwich Meridian and the equator.

#### Navigation Frame

This frame has its origin on the surface of the earth at its closest point
to the drone.

* The X Y plane is tangent to the Earth surface.
* X points North
* Y points East
* The Z axis is normal to the surface of the Earth and intersects the center
  of the drone. It points in toward the center of the earth.

#### Body Frame

This frame has its origin at the center of the drone and rotates with it.

* The X axis points forward
* The Y axis points down the 'right wing' (imagine a fixed wing craft)
* The Z axis points downwards

Rotations
---------

Roll, Pitch, Yaw is typically specified relative to the Body Frame

* Yaw is a rotation about the X axis and happens first.
* Pitch is a rotation about the Y axis and happens second.
* Roll is a rotation about the Z axis and happens third.
