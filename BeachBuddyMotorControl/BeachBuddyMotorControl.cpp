#include "BeachBuddyMotorControl.h"

MotorControl::MotorControl()
{
	pinMode(S1, OUTPUT);
	pinMode(S2, OUTPUT); 
	pinMode(M1, OUTPUT);
	pinMode(M2, OUTPUT); 
  digitalWrite(S1,LOW);   
  digitalWrite(S2,LOW);  
}

void MotorControl::stop (void){
  digitalWrite(S1,0); 
  digitalWrite(M1,LOW);    
  digitalWrite(S2,0);   
  digitalWrite(M2,LOW);
}

void MotorControl::advance(unsigned char a, unsigned char b)          //Move forward
{
  //Serial.println("C6");
  //Serial.println("Motor left");
  //Serial.println(a, HEX);
  //Serial.println(a, DEC);
      
  //Serial.println("Motor right");
  //Serial.println(b, HEX);
  //Serial.println(b, DEC); 
      
  analogWrite (S1,a);      //PWM Speed Control
  digitalWrite(M1,HIGH);
  //Serial.println("C7");    
  //Serial.println(digitalRead(M1));
  analogWrite (S2,b);    
  digitalWrite(M2,LOW);
  //Serial.println("C8");
  //Serial.println(digitalRead(M1));
}

void MotorControl::back_off (unsigned char a, unsigned char b)          //Move backward
{
  analogWrite (S1,a);
  digitalWrite(M1,LOW);   
  analogWrite (S2,b);    
  digitalWrite(M2,HIGH);
}

void MotorControl::turn_L (unsigned char a,unsigned char b)             //Turn Left
{
  analogWrite (S1,a);
  digitalWrite(M1,HIGH);    
  analogWrite (S2,b);    
  digitalWrite(M2,HIGH);
}

void MotorControl::turn_R (unsigned char a,unsigned char b)             //Turn Right
{
  analogWrite (S1,a);
  digitalWrite(M1,LOW);    
  analogWrite (S2,b);    
  digitalWrite(M2,LOW);
}

void MotorControl::MotorProcessRxData(unsigned long Command, unsigned char d1, unsigned char d2, unsigned char a,unsigned char b)
{
  if(Command==0x0)
  {
    if(d1==1&&d2==1)
    {
      Command=MOTOR_CMD_DIR_FORWARD;
    }
    else if(d1==0&&d2==0)
    {
      Command=MOTOR_CMD_DIR_BACKWARD;
    }
    else if(d1==1&&d2==0)
    {
      Command=MOTOR_CMD_DIR_RIGHT;
    }
    else if(d1==0&&d2==1)
    {
     Command=MOTOR_CMD_DIR_LEFT; 
    }
  }
  switch(Command){

    case MOTOR_CMD_DIR_FORWARD:
      
      advance(a,b);
    break;
    case MOTOR_CMD_DIR_RIGHT:
      turn_R(a,b);
    break;
    case MOTOR_CMD_DIR_LEFT:
      turn_L(a,b);
    break;
    case MOTOR_CMD_DIR_BACKWARD:
      //Serial.println("C3");
      back_off(a,b);
    break;
    case MOTOR_CMD_MOV_STOP:
      stop();
    break;
    case MOTOR_CMD_ACC_LIGHT:
    break;
    case MOTOR_CMD_ACC_HORN:
    break;
    default:
    break;
  }
}
