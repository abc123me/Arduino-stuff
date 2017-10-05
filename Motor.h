#ifndef MOTOR_HEADERS
#define MOTOR_HEADERS
/*---Getters/Setters---*/
void setMotorsEnabled(bool enabled);
bool areMotorsEnabled();
/*----Motor control----*/
void motorInitiate();
void allMotorStop();
void motor1Stop();
void motor2Stop();
void motor1Forward();
void motor2Forward();
void motor1Backward();
void motor2Backward();
#endif
