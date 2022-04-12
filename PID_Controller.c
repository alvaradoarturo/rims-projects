/* 

Name: Arturo Alvarado
Google Doc: https://docs.google.com/document/d/1KYMHHp0NCMUCXUhIZZLzMpJ89cnUliRJADR5CukFwGk/edit?usp=sharing
email: aalva058@ucr.edu
Youtube Vid: https://youtu.be/sO4D0U0EpPo
*/

#include "rims.h"
volatile int TimerFlag = 0;
void TimerISR() {
   TimerFlag = 1;
}


/* PID vars */
// Used to control PID Controller
const float Desired = 100; // Goal controller .. will not change
float Actual = 0;
float Error;
float Deriv;
float Integ = 0;
float ActualPrev = 0;
float Actuator = 0.5;
float ActuatorPrev = 0;
float actuatorMax = 1.3; // NU
const float integMax = 1000; // Will not change
const float integMin = -1000; // Will not change

// Values given in project description
const float Kp = .05;
const float Ki = .001;
const float Kd = 2.5;
const float dt = 0.5; // velcoity of ball

/* System  variables */
// Taken from java code

// var fan = {f:0,m:0.5,a:0}; <- must be seperated into 3 diff fans
float fan_reg = 0.0 ;
const float fan_m = 0.5 ; 
float fan_a = 0.0 ;
const float g = 9.8; // gravity, will not change
// var ball = {pos:0,v:0,a:0,m:0.027}; extract attributes
float ball_pos = 0;
float ball_v = 0;
float ball_a = 0;
const float ball_mass = .03; // Weight of ball, will not oscillate
const float ballMin = 0; // Cannot go below zero
const float ballMax = 200; // Cannot go above
float actuatorMin = 0;

void updateSystem()
{


    fan_a = Actuator;
    fan_reg = fan_m*fan_a; // Fans power * Actuator value
    ball_a = (fan_reg/ball_mass)-g;
    ball_v = ball_v+(ball_a*dt);
    ball_pos = ball_pos+(ball_v*dt);
    if(ball_pos < ballMin)
    {
        ball_v = 0;
        ball_pos = ballMin;
    }
    if(ball_pos > ballMax)
    {
        ball_v = 0;
        ball_pos = ballMax;
    }

    ActuatorPrev = Actuator;
    ActualPrev = Actual;
    Actual = ball_pos;
}
    

enum Controller_STATES{Init,Mode, PID, Manual}Controller_states;
void Controller_Function(){
    switch(Controller_states){ //transitions
      case Init:
         Controller_states = Mode;
         break;
      case Mode:
         if(A0 == 0){
             Controller_states = PID;
         }
         else if(A0 == 1){
              Controller_states = Manual;
         }
         else{
             Controller_states = Mode;
         }
         break;
         
       case PID:
         if(A0 == 0){
             Controller_states = PID;
         }
         else if(A0 == 1){
              Controller_states = Manual;
              
         }
         else{
             Controller_states = Init;
         }
         break;          
       case Manual:
         if(A0 == 0){
             Controller_states = PID;
         }
         else if(A0 == 1){
              Controller_states = Manual;
              
         }
         else{
             Controller_states = Init;
         }
         break;
         
        
        default:
            Controller_states = Init;
            break;
    }
    switch(Controller_states){//actions
      case Init:
         B = 1;
         break;
      case Mode:
         break;
      case PID:
         Error = Desired - Actual;
         printf("Error: &lf\n", Error);
         Deriv = Actual - ActualPrev;
         printf("Deriv: %lf\n", Deriv);
         Integ += Error;
         printf("Integ: %lf \n", Integ);
         
         if(Integ > integMax){
             Integ = integMax;
         }
         if(Integ < integMin){
             Integ = integMin;
         }
         
        Actuator = (Kp*Error) + (Ki*Integ) - (Kd*Deriv);
        if(Actuator < actuatorMin)
            {
               Actuator = actuatorMin;
            }
         if(Actuator > actuatorMax)
            {
               Actuator = actuatorMax;
            } 
         updateSystem();
         if(A1 == 0){
            B = Actual;
         }
         if(A1 == 1){
           if(Actual >= 0 && Actual <=26){
               B = 128;
           }
           else if(Actual >= 27 && Actual <=53){
               B = 64;
           }
           else if(Actual >= 54 && Actual <=80){
               B = 32;
           }           
           else if(Actual >= 81 && Actual <=106){
               B = 16;
           }     
           else if(Actual >= 107 && Actual <=131){
               B = 8;
           }           
           else if(Actual >= 132 && Actual <=156){
               B = 4;
           }     
           else if(Actual >= 157 && Actual <=181){
               B = 2;
           }     
           else{
               B = 1;
           }           
         }         
         break;               
         
       case Manual:
         
       if(A6 == 1 && A7 == 1){
           printf("%s", "Ignoring");
       }
       
       else if(A6 == 1){
         Actuator += .0075;
            if(Actuator < actuatorMin)
               {
                  Actuator = actuatorMin;
               }
            if(Actuator > actuatorMax)
               {
                  Actuator = actuatorMax;
               } 
        }
       else if(A7 == 1){
         Actuator -= .0075;
            if(Actuator < actuatorMin)
               {
                  Actuator = actuatorMin;
               }
            if(Actuator > actuatorMax)
               {
                  Actuator = actuatorMax;
               } 
         }
        else{
               ;
         }    
         updateSystem();
         if(A1 == 0){
            B = Actual;
         }
         if(A1 == 1){
           if(Actual >= 0 && Actual <=26){
               B = 128;
           }
           else if(Actual >= 27 && Actual <=53){
               B = 64;
           }
           else if(Actual >= 54 && Actual <=80){
               B = 32;
           }           
           else if(Actual >= 81 && Actual <=106){
               B = 16;
           }     
           else if(Actual >= 107 && Actual <=131){
               B = 8;
           }           
           else if(Actual >= 132 && Actual <=156){
               B = 4;
           }     
           else if(Actual >= 157 && Actual <=181){
               B = 2;
           }     
           else{
               B = 1;
           }           
         }
         break;
         
       default:
        ;
    }
    
}

void main()
{
   TimerSet(1000);
   TimerOn();

   Controller_states = Init;
   while(1){

      Controller_Function();
      
      while(!TimerFlag);
      TimerFlag=0;
   }
}
