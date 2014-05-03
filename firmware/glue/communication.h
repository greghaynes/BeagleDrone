#ifndef GLUE_COMMUNICATION_H
#define GLUE_COMMUNICATION_H

void CommunicationHwInit(void);

int CommunicationTrySendChar(unsigned char ch);

int CommunicationTryGetChar(unsigned char *dest);

void CommunicationIntEnableRead(void);

void CommunicationIntDisableWrite(void);

void CommunicationIntEnableWrite(void);

void CommunicationIntRegisterHandler(void (*isr)(void));

#endif
