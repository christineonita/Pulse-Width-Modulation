// Christine Onita ECE303 Lab/Project 3 Winter 2021

int led = 5; //timer 3
int photocell_array[10]; // will use this to get ten values then find average
int ledd_array[10]; // will use this to get ten values then find average

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600); // baud rate
  pinMode(led, OUTPUT); //initialize pin 5 as output  
  
  TCCR3A=0b10000010; // Initializes all bits in TCCR3A to zero
  TCCR3B=0b00010001; // Set prescalar of 1
  TCNT3=0; // Initializes counter TCNT3 to 0
  ICR3 = 8000;
  OCR3A = 400;
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
  while (OCR3A <= ICR3) {
    delay(3000); // time delay (3 seconds) to get proper transient readings
    
    for (int i = 0; i < 10; i++ ){ // from i=0 to i=9, the voltage is measured (that's ten values for each case)
      photocell_array[i] = analogRead(A0); // records the photocell voltage on a scale of 0 to 1023
      ledd_array[i] = analogRead(led); // records/reads the  voltage on a scale of 0 to 1023
      
    }   
    
    Serial.print("Duty Cycle (%): ");
    float dc = (float) OCR3A/ICR3*100; // duty cycle in % is OCR3A/ICR3*100 
    Serial.println(dc);
    
    Serial.print("LED Circuit Resistor Voltage: ");
    for (int i=0; i<10; i++) 
      Serial.print(String(ledd_array[i]) + " "); // this prints the ten values for the LED Circuit Resistor Voltage
    Serial.println();

    Serial.print("Photocell Circuit Resistor Voltage: ");
    for (int i=0; i<10; i++) 
      Serial.print(String(photocell_array[i]) + " "); // this prints the ten values for the Photocell Circuit Resistor Voltage
    Serial.println();
    Serial.println();
    
    OCR3A += 400; // this would make sure the duty cycle is increased in incremements of 5%
    
  }
}
