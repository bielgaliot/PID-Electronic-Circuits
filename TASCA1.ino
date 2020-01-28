#define pot A0  // Sasigna la variable corresponent al pin de la placa
int p;          // Definicio duna variable entera per visualitzar el valor de lectura

void setup() {          
  Serial.begin (9600);   // Obre un port serial i estableix la data rate a 9600 bits per segon bps
}


void loop() {
  p=analogRead(pot); //Llegeix la tensio al pin A0 i es guarda a la variable entera p
  Serial.println(p); // Simprimeix al monitor serie el valor de la variable entera p
}