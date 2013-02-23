#ifndef PLATFORM_PWMSS_H
#define PLATFORM_PWMSS_H

void EPWM2PinMuxSetup(unsigned int pinid);
void PWMSSTBClkEnable(unsigned int instance);
void PWMSSModuleClkConfig(unsigned int instanceNum);

#endif
