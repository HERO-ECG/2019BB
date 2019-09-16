#include "PID.h"
#include "stm32f10x_tim.h"

//限幅函数
float constrain_int32(float amt, float low, float high) 
{
	return ((amt)<(low)?(low):((amt)>(high)?(high):(amt)));
}

//PID初始化函数
void PIDdataInit(struct PID* pidData,float kp,float ki,float kd,float imax,float imin,float outmax,float outmin)
{
	pidData->Imax=imax;
	pidData->Imin=imin;
	pidData->outmax=outmax;
	pidData->outmin=outmin;
	pidData->kP=kp;
	pidData->kI=ki;
	pidData->kD=kd;
	pidData->P=0;
	pidData->I=0;
	pidData->D=0;
	pidData->error=0;
	pidData->last_error=0;
	pidData->derror=0;
	//pidData->set=0;
	pidData->out=0;
}

//PID计算函数
void PIDUpData(struct PID* pidData)
{
	pidData->error = pidData->set - pidData->feedback;
	pidData->derror = pidData->error - pidData->last_error;
	pidData->last_error = pidData->error;
	
	pidData->P = pidData->kP * pidData->error;
	
	pidData->I += pidData->kI * pidData->error;
	pidData->I = constrain_int32(pidData->I, pidData->Imin, pidData->Imax);	
	
	pidData->D = pidData->kD * pidData->derror;
	
}

void ResetI(struct PID* pidData)
{
	pidData->I = 0;
}

void ResetPID(struct PID* pidData)
{
	
	pidData->error=0;
	pidData->derror=0;
	pidData->last_error=0;
	pidData->P=0;
	pidData->I = 0;
	pidData->D=0;
	
	
}

void GetP(struct PID* pidData)
{
	pidData->out = pidData->P;
	pidData->out = constrain_int32(pidData->out, -pidData->outmax, +pidData->outmax);	
}

void GetPI(struct PID* pidData)
{
	pidData->out = pidData->P + pidData->I;
	pidData->out = constrain_int32(pidData->out, -pidData->outmax, +pidData->outmax);	
}

void GetPD(struct PID* pidData)
{
	pidData->out = pidData->P + pidData->D;
	pidData->out = constrain_int32(pidData->out, -pidData->outmax, +pidData->outmax);	
}

void GetPID(struct PID* pidData)
{
	pidData->out = pidData->P + pidData->I + pidData->D;
	pidData->out = constrain_int32(pidData->out, pidData->outmin, pidData->outmax);	
}


