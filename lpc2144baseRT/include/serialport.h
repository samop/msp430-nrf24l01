#ifndef COMTEST_H
#define COMTEST_H

void vAltStartComTestTasks( unsigned portBASE_TYPE uxPriority, unsigned long ulBaudRate, unsigned portBASE_TYPE uxLED );
portBASE_TYPE xAreComTestTasksStillRunning( void );

#endif


