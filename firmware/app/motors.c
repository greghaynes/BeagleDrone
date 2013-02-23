#include "motors.h"
#include "kernel/hw/soc_AM335x.h"
#include "kernel/platform/pwmss.h"
#include "kernel/drivers/ehrpwm.h"

#define CLOCK_DIV_VAL                 (10)
#define SOC_EHRPWM_2_MODULE_FREQ      (100000000)

void MotorsInit(void) {
    PWMSSModuleClkConfig(2);
    EPWM2PinMuxSetup(4);
    PWMSSTBClkEnable(2);

    EHRPWMTimebaseClkConfig(SOC_EPWM_2_REGS,
                            SOC_EHRPWM_2_MODULE_FREQ/CLOCK_DIV_VAL,
                            SOC_EHRPWM_2_MODULE_FREQ);

   /* Configure the period of the output waveform */
    EHRPWMPWMOpFreqSet(SOC_EPWM_2_REGS,
                       SOC_EHRPWM_2_MODULE_FREQ/CLOCK_DIV_VAL,
                       (unsigned int)(SOC_EHRPWM_2_MODULE_FREQ/CLOCK_DIV_VAL)/0xFF,
                       (unsigned int)EHRPWM_COUNT_UP,
                       (bool)EHRPWM_SHADOW_WRITE_DISABLE);

    /* Disable synchronization*/
    EHRPWMTimebaseSyncDisable(SOC_EPWM_2_REGS);

    /* Disable syncout*/
    EHRPWMSyncOutModeSet(SOC_EPWM_2_REGS, EHRPWM_SYNCOUT_DISABLE);

    /* Configure the emulation behaviour*/
    EHRPWMTBEmulationModeSet(SOC_EPWM_2_REGS, EHRPWM_STOP_AFTER_NEXT_TB_INCREMENT);

    /* Configure Counter compare cub-module */
    /* Load Compare A value */
    EHRPWMLoadCMPA(SOC_EPWM_2_REGS,
                   50,
                   (bool)EHRPWM_SHADOW_WRITE_DISABLE,
                   (unsigned int)EHRPWM_COMPA_NO_LOAD,
                   (bool)EHRPWM_CMPCTL_OVERWR_SH_FL);

    /* Load Compare B value */
    EHRPWMLoadCMPB(SOC_EPWM_2_REGS,
                   200,
                   (bool)EHRPWM_SHADOW_WRITE_DISABLE,
                   (unsigned int) EHRPWM_COMPB_NO_LOAD,
                   (bool)EHRPWM_CMPCTL_OVERWR_SH_FL);

    /* Configure Action qualifier */
    /* Toggle when CTR = CMPA */
    EHRPWMConfigureAQActionOnB(SOC_EPWM_2_REGS,
                               EHRPWM_AQCTLB_ZRO_DONOTHING,
                               EHRPWM_AQCTLB_PRD_DONOTHING,
                               EHRPWM_AQCTLB_CAU_EPWMXBTOGGLE,
                               EHRPWM_AQCTLB_CAD_DONOTHING,
                               EHRPWM_AQCTLB_CBU_DONOTHING,
                               EHRPWM_AQCTLB_CBD_DONOTHING,
                               EHRPWM_AQSFRC_ACTSFB_DONOTHING);

    /* Bypass dead band sub-module */
    EHRPWMDBOutput(SOC_EPWM_2_REGS, EHRPWM_DBCTL_OUT_MODE_BYPASS);

    /* Disable Chopper sub-module */
    EHRPWMChopperDisable(SOC_EPWM_2_REGS);

    /* Disable trip events */
    EHRPWMTZTripEventDisable(SOC_EPWM_2_REGS,(bool)EHRPWM_TZ_ONESHOT);
    EHRPWMTZTripEventDisable(SOC_EPWM_2_REGS,(bool)EHRPWM_TZ_CYCLEBYCYCLE);

    /* Event trigger */
    /* Generate interrupt every 3rd occurance of the event */
    EHRPWMETIntPrescale(SOC_EPWM_2_REGS, EHRPWM_ETPS_INTPRD_THIRDEVENT);
    /* Generate event when CTR = CMPB */
    EHRPWMETIntSourceSelect(SOC_EPWM_2_REGS, EHRPWM_ETSEL_INTSEL_TBCTREQUCMPBINC);

    /* Disable High resolution capability */
    EHRPWMHRDisable(SOC_EPWM_2_REGS);

}
