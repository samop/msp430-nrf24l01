#ifndef _H_PROJECT
#define _H_PROJECT
#define TRIAC BIT6 //P2.6
#define ZEROCROSS BIT1 //P1.1

#define CE BIT3 //P1.3
#define CSN BIT4 //P1.4

#define MIN_ANGLE 100
#define MAX_ANGLE 8000
//#define ANGLE_STEP 400


#define HALF_PERIOD 10000


#define TRUE 1
#define FALSE 0
#define ON 1
#define OFF 0
#define TIMERCAP 1
#define TIMERCOMP 0
#define TIMERWAIT 1
#define TIMERIDLE 0
/*
typedef struct st_state {
 char cap=TIMERCAP;
 char timer_mode=TIMERIDLE;
 char power=OFF;
 unsigned int target_angle;
 unsigned int angle;
 int speed=5;
} st_state;

*/


typedef struct st_state {
 char cap;
 char timer_mode;
 char power;
 unsigned int target_angle;
 unsigned int angle;
 unsigned int preset_angle;
 int speed;
 int softstart;
} st_state;




#endif
