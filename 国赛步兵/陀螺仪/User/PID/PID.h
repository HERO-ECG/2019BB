#ifndef _PID_H
#define _PID_H
#include "stm32f10x.h"

struct PID
{
	float kP;
	float kI;
	float kD;
	float dt;
	float P;
	float I;
	float D;
	float set;
	float feedback;
	float last_error;
	float error;
	float derror;
	float Imax;
	float Imin;
	float outmax;
	float outmin;
	float out;
};


void PIDdataInit(struct PID* pidData,float kp,float ki,float kd,float imax,float imin,float outmax,float outmin);
void PIDUpData(struct PID* pidData);
void ResetI(struct PID* pidData);
void ResetPID(struct PID* pidData);
void GetP(struct PID* pidData);
void GetPD(struct PID* pidData);
void GetPI(struct PID* pidData);
void GetPID(struct PID* pidData);

extern struct PID pidData_pitch_angle;
extern struct PID pidData_roll_angle;
extern struct PID pidData_yaw_angle;

extern struct PID pidData_pitch_w;
extern struct PID pidData_roll_w;
extern struct PID pidData_yaw_w;

extern struct PID pidData_deep;

#endif
