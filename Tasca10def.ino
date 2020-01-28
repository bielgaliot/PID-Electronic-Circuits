#include <TimerOne.h> 
float incl; // Variable float per la inclinacio desitjada en percentatge
int incl_bit; // Variable entera per la inclinacio desitjada de 0 a 1024
volatile float v=0; // Variable float per la velocitat de rotacio del motor. 
float incl_real; // Variable float per la inclinacio a la que es troba el motor
float diferencia; // Variable float per lerror entre la posicio desitjada i la real
int vmin= 58;  // Valor minim de voltatge de 0 1023 que dona el potenciometre
int vmax= 394; // Valor maxim de voltatge de 0 1023 que dona el potenciometre
float integ;  // Variable per al control integrador
float der;  // Variable per al control derivador
float diferencia_prev; // Defnicio error de consigna respecte lanterior
float prop; // Variable per al control porporcional
float ki=19.28; // Valor de ki ZN
float kp=5.15; // Valor de kp ZN
float kd=0.345; // Valor de kd ZN
float incl_real_perc;
float t=0.0; // Variable temporal float per les representacions amb MATLAB

void ISR_Inclinacio(){
  incl_real = analogRead(A0);
  diferencia = incl_bit-incl_real;
  prop=kp*diferencia; // Declaracio control proporcional
  integ=integ+diferencia*0.002; // Declaracio control integrador
  der=(diferencia-diferencia_prev)/0.002; // Declaracio control derivatiu
  diferencia_prev=diferencia;
  v = prop + integ*ki + der*kd; // Definicio de la velocitat com la suma de totes les parts del controlador PID
  if (integ*ki>1023) integ = 1023/ki; // Declaracio dun if per evitar saturacions
  if (integ<0) integ = 0;
  if (v>1023) v = 1023;
  if (v<0) v = 0;
  Timer1.setPwmDuty (9,v);
  t=t+0.002; // Per poder obtenir les representacions grafiques
}
void setup() 
{
  Serial.begin(9600);
  Timer1.initialize(2000);
  Timer1.attachInterrupt(ISR_Inclinacio);
  Timer1.pwm(9,0);
}
void loop() {
    incl=25; // Valor desitjat de la inclinacio per la representacio
    incl_bit=map(incl, 0, 100, vmin, vmax);  // Quart proporcional per convertir la variable inclinacio (%) a inclinacio (0-1023)
    Serial.print(t);
    Serial.print(',');
    Serial.print(75);
    Serial.print(',');
    incl_real_perc=map(incl_real, vmin, vmax, 0, 100);
    Serial.print(incl_real_perc);
    Serial.println();
}

