#include <TimerOne.h> // Llibreria obtinguda dAtenea por poder introduir frequencia de mostreig
#define pin A0
int pot_min = 0;  // Es defineix una variable entera pel valor de tensio minima
int pot_max = 274;  // Es defineix una variable entera pel valor de tensio maxima
volatile int pot;  // Es declara una variable entera pot. La notacio volatile es recomana per variables que canvien de valor en cada execusio
volatile float perc; // Es defineix una variable decimal pel valor del percentatge. La notacio volatile es recomana per variables que canvien de valor en cada execusio

// Inici de la declaracio de la funcio per obtenir la lectura del potenciometre en percentatge
void ISR_inclinacio (void)
{
  pot = analogRead(pin);
  perc = 100*((float)pot-pot_min)/(pot_max - pot_min);
}

void setup()
{
  Serial.begin(9600); // Obre un port serial i estableix la data rate a 9600 bits per segon bps
  Timer1.initialize(2000); // Indicar al temporitzador el periode de mostreig expressat en microsegons 500Hz son 2000 microsegons
  Timer1.attachInterrupt(ISR_inclinacio);  // Comanda per realitzar la lectura del potenciometre executa la funcio que se li introdueix
}

void loop() 
{
  Serial.println(perc); // Imprimeix el valor del percentatge. Es podria haver ubicat dins la funcio ISR_inclinacio pero no es recomanable
}