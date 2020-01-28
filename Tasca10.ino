// Tasca 10 Tercera Fase

// Tal com sexpressa a la seguent seccio, el codi daquesta tasca nomes conte algunes modificacions respecte de lanterior. No sinclou tot el programa amb les modificacions, sino que nomes es presenten aquestes ultimes i la seva ubicacio dins el programa base de la Tasca 9

// Inici de la declaracio de les mateixes variables i llibreries, afegintne una nova
#include <TimerOne.h>
float t=0.0; // Declaracio duna variable decimal per poder obtenir les representacions
[...] // Declaracio de la resta de mateixes variables
// Fi de la declaracio de les mateixes variables i llibreries, afegintne una nova

// Modificacio dalgunes de les variables, ara determinades pel metode de ZieglerNichols 
float ki=19.28; 
float kp=5.15;
float kd=0.345;
// Fi de la modificacio de variables

// S'afegeix un canvi a la funcio per poder representar graficament els resultats
void ISR_Inclinacio(){
  t=t+0.002; // Modificacio de la variable t per poder obtenir les representacions grafiques
  [...] // Declaracio de la resta dordres
}
// Fi de la modificacio de variables

// No es realitza cap modificacio a la definicio del setup del programa 
void setup() {}

// Nova definicio del loop del programa, que es veu modificat per complert per poder representar la inclinacio del brac
void loop() {
  
    incl=25;
    incl_bit=map(incl, 0, 100, vmin, vmax);  // Quart proporcional per convertir la variable inclinacio (%) a inclinacio (0-1023)
    Serial.print(t);
    Serial.print(',');
    Serial.print(75);
    Serial.print(',');
    incl_real_perc=map(incl_real, vmin, vmax, 0, 100);
    Serial.print(incl_real_perc);
    Serial.println();
}

// Fi de la modificacio del programa de la Tasca 9 pr realitzar la Tasca 10 