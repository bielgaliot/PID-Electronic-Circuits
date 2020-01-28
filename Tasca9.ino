// Tasca 9 Tercera fase
#include <TimerOne.h> // llibreria obtinguda dAtenea per poder introduir la frequencia de mostreig
float incl; // Definicio duna variable decimal per guardar la inclinacio desitjada en percentatge
int incl_bit; // Definicio duna variable decimal per guardar la inclinacio desitjada de 0 a 1024
volatile float v=0; // Es declara una variable decimal per la velocitat de rotacio del motor. Es recomana la notacio volatile per les variables que canvien de valor en cada execucio
float incl_real; // Definicio duna variable decimal per guardar la inclinacio a la que es troba el motor a un instant determinat
float diferencia; // Definicio duna variable decimal per guardar lerror entre la posicio desitjada i la real
int vmin= 58;  // Valor minim de voltatge de 0 1023 que dona el potenciometre
int vmax= 394; // Valor maxim de voltatge de 0 1023 que dona el potenciometre
float integ; // Declaracio duna variable float per evitar possibles saturacions del valor
float der; // Declaracio duna variable float per evitar posibles saturacions del valor
float diferencia_prev; // Defnicio error de consigna respecte lanterior
float prop; // Declaracio duna variable float per evitar posibles saturacions del valor
float ki=10; // Valor de ki assignat segons experiencies previes al laboratori de control automatic. Al seguent apartat es determinara pel metode de ZieglerNichols
float kp=3; // Valor de kp assignat segons experiencies previes al laboratori de control automatic. Al seguent apartat es determinara pel metode de ZieglerNichols
float kd=0.1; // Valor de kd assignat segons experiencies previes al laboratori de control automatic. Al seguent apartat es determinara pel metode de ZieglerNichols
float t=0.0;
float incl_real_perc;

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
}
// Inici de la definicio del setup del programa
void setup() 
{
  Serial.begin(9600);
  Timer1.initialize(2000);
  Timer1.attachInterrupt(ISR_Inclinacio);
  Timer1.pwm(9,0);
}
// Inici de la definicio del loop del programa
void loop() {
  if(Serial.available()>0)
  {
    incl=Serial.parseInt;
    incl_bit=map(incl, 0, 100, vmin, vmax);  //quart proporcional per convertir la variable inclinacio introduida en (%) a inclinacio (0-1023)
  }
}
// Fi del programa de la Tasca 9 Tercera fase