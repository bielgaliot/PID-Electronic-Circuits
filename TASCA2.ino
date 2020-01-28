#define pin A0 // Sasigna la variable corresponent al pin de la placa
int pot_min = 0;  // Es defineix una variable entera pel valor de tensio minima
int pot_max = 274;  // Es defineix una variable entera pel valor de tensio maxima
int pot;  // Es declara una variable entera pot
float perc; // Es defineix una variable decimal pel valor del percentatge

void setup() {
  Serial.begin(9600); 
}

void loop() {
  pot = analogRead(pin); // Llegeix la tensio al pin A0 i es guarda a la variable entera pot
  perc = 100*((float)pot-pot_min)/(pot_max - pot_min); //Expressa el valor de la tensio en percentatge respecte del valor maxim i minim
  Serial.println(perc); // Simprimeix al monitor serie el valor de la variable perc
}