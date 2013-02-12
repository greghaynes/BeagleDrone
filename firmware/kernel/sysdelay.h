#ifndef SYSDELAY_H
#define SYSDELAY_H

void SysDelayTimerSetup(void);
void Sysdelay(unsigned int milliSec);
void SysStartTimer(unsigned int milliSec);
void SysStopTimer(void);
unsigned int SysIsTimerElapsed(void);

#endif
