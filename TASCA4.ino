#include <TimerOne.h>
int input; // Declara una variable entera pel valor de cicle de treball desitjat introduit al monitor serie

void setup()
{
  Serial.begin(9600); // Obre un port serial i estableix la data rate a 9600 bits per segon bps
  Timer1.initialize(2000); // Indicar al temporitzador el periode de mostreig expressat en microsegons 500Hz son 2000 microsegons
  Timer1.pwm (9, 0); // Comanda per variar la velocitat del motor pin del motor, cicle inicial. El cicle inicial 0 indica que el motor sinicia aturat.
}

void loop() 
{   
  if (Serial.available () > 0)
  {
    input = Serial.parseInt(); // Llegeix el valor dentrada del monitor serie i el guarda a la variable input
    Timer1.setPwmDuty (9, 10.23*input); // Canvia el cicle de treball del motor segons el valor entrat al monitor serie
  }
}