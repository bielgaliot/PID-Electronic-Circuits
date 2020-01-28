#include <TimerOne.h>
int incl; //inclinacio desitjada en %
int incl_bit; //inclinacio desitjada de 0 a 1023
volatile float v=0; //velocitat de rotacio del motor
float incl_real; //Inclinacio a la que es troba el motor a un instant determinat
float diferencia; //error entre la posicio desitjada i la real
int vmin= 58;  //valor minim de voltatge de 0 a 1023 que dona el potenciometre
int vmax= 394; //valor maxim de voltatge de 0 a 1023 que dona el potenciometre
float kp=6; //valor aleatori de kp (segons experiencies previes a altres assignatures)

void ISR_Inclinacio()
{
  incl_real = analogRead(A0);
  diferencia = incl_bit-incl_real; //calcul de l error entre la posicio desitjada i la real
  v=kp*diferencia;                 //aplicacio de la kp
  if (v>1023) v = 1023;            //control d errors al voltatge que se li dona al motor
  if (v<0) v = 0;
  Timer1.setPwmDuty (9,v);
}

void setup() 
{
  Serial.begin(9600);
  Timer1.initialize(2000);
  Timer1.attachInterrupt(ISR_Inclinacio);
  Timer1.pwm(9,0);
}

void loop() 
{
  if(Serial.available()>0)
  {
    incl=Serial.parseInt();
    incl_bit=map(incl, 0, 100, vmin, vmax);  //quart proporcional per convertir la variable inclinacio (%) a inclinacio (0-1023)
    
  }
}
