#ifndef IMU_SENSROS_H
#define IMU_SENSORS_H

#include "app/ahrs.h"

void IMUSensorsInit(void);
const AhrsRotationalShort *IMUSensorsGetGyro(void);
const AhrsRotationalShort *IMUSensorsGetAccelero(void);

void IMUSensorsUpdateGyro(void);
void IMUSensorsUpdateAccelero(void);

#endif
