//C++
#define RED_LED 13
#define YELLOW_LED 12
#define GREEN_LED 11
#define BUTTON 2
#define POTENTI_PIN A0


// OUTPUT: LEDs use digital pins 5-7 for multi color LED
int red = 6;
int green = 5;
int blue = 4;
int buttonPin = 2;

int potPin = A0;
int potVal = 0;

int redVal = 0;
int grnVal = 0;
int bluVal = 0;

void setup() {

  Serial.begin(9600);
  Serial.setTimeout(10);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(POTENTI_PIN, INPUT);
  pinMode(BUTTON, INPUT); 
}


void loop() {

  digitalWrite(GREEN_LED, HIGH);

  potVal = analogRead(potPin);  // read the potentiometer value


  if (potVal < 341)  // Lowest third of the potentiometer's range (0-340)
  {
    potVal = (potVal * 3) / 4;  // To value 255
    redVal = 256 - potVal;      //Red value depends on 256 minus the Potenti Value.
    grnVal = potVal;            //green value depends on potVal
    bluVal = 1;                 // Blue’s basically off here
  } else if (potVal < 682)      // This is the range from 341-681
  {
    potVal = ((potVal - 341) * 3) / 4;
    redVal = 1;             // Red off
    grnVal = 256 - potVal;  // Green from full and then decreases
    bluVal = potVal;        // blue value depends on the value given.
  } else                    // Upper third of potentiometer's range (682-1023)
  {
    potVal = ((potVal - 683) * 3) / 4;  // gets to 0-255
    redVal = potVal;                    // Red increases as value increases
    grnVal = 1;                         // Green is now basically off here
    bluVal = 256 - potVal;              // Blue goes from maximum to lower
  }

  Serial.println(potVal);
  analogWrite(red, redVal);  // Write values to LED pins
  analogWrite(green, grnVal);
  analogWrite(blue, bluVal);

  Serial.println(analogRead(POTENTI_PIN));
  double potenti = analogRead(POTENTI_PIN);
  double divsi = (potenti / 1023);
  int brightness = divsi * 255;
  Serial.println("brightness");
  Serial.println(brightness);
  analogWrite(YELLOW_LED, brightness);  // brightness of LED

  // Flash Yellow LED 7 times
  for (int i = 0; i < 7; i++) {
    digitalWrite(YELLOW_LED, HIGH);
    delay(250);  // On for 0.25 seconds
    digitalWrite(YELLOW_LED, LOW);
    delay(250);  // Off for 0.25 seconds
  }
Serial.println("button pressed?");
Serial.println(digitalRead(BUTTON));
  // Check if the button is pressed and flash the green LED 7 times
  if (digitalRead(BUTTON) == 1) {
    Serial.println("button pressed");

    for (int i = 0; i < 7; i++) {
      digitalWrite(RED_LED, HIGH);
      delay(250);  // On for 0.25 seconds
      digitalWrite(GREEN_LED, LOW);
      delay(100);  // Off for 0.25 seconds
      digitalWrite(RED_LED, LOW);

    }
  }
  delay(500);


  if (Serial.available() > 0) {
    String color = Serial.readString();  //Reads the command i put in
    Serial.print("color: ");             //prints color: and then the color I wrote
    Serial.println(color);




    // Turns on LED depending on the color I type.
    if (color == "yellow") {
      digitalWrite(YELLOW_LED, HIGH);
      digitalWrite(GREEN_LED, LOW);
      digitalWrite(RED_LED, LOW);

    } else if (color == "green") {
      digitalWrite(YELLOW_LED, LOW);
      digitalWrite(GREEN_LED, HIGH);
      digitalWrite(RED_LED, LOW);

    } else if (color == "red") {
      digitalWrite(YELLOW_LED, LOW);
      digitalWrite(GREEN_LED, LOW);
      digitalWrite(RED_LED, HIGH);
      
    } else if (color == "off") {
      digitalWrite(YELLOW_LED, LOW);
      digitalWrite(GREEN_LED, LOW);
      digitalWrite(RED_LED, LOW);
    }
  }
}
