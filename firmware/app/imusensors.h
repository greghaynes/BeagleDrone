#ifndef IMU_SENSROS_H
#define IMU_SENSORS_H

#include "app/state.h"

void IMUSensorsInit(void);
const StateRotationalShort *IMUSensorsGetGyro(void);
const StateRotationalShort *IMUSensorsGetAccelero(void);
const StateRotationalShort *IMUSensorsGetMagneto(void);

#endif
