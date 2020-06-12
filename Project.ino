String input = "";
// Soil moisture
#define sensorPinA A0
#define sensorPinB A1
double sensorValueA = 0;
double sensorValueB = 0;
//Water pump
#define waterPumpPin 7
String inputW = "";
//temp sensor
#define tempPinA A4
#define tempPinB A5
int tempValueA = 0;
double voltageA, temperatureA;
int tempValueB = 0;
double voltageB, temperatureB;
//light sensor
#define lightPinA A2
#define lightPinB A3
int lightValueA;
int lightValueB;
//leds
#define redPinA 12
#define greenPinA 11
#define redPinB 10
#define greenPinB 9  
#define bluePin 8     

void setup() {
  pinMode(waterPumpPin, OUTPUT);
  pinMode(redPinA, OUTPUT);
  pinMode(greenPinA, OUTPUT);
  pinMode(redPinB, OUTPUT);
  pinMode(greenPinB, OUTPUT);
  pinMode(bluePin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.println("--> Enter 'i' to display info: ");
  while (Serial.available() == 0) { //Wait for user input
  }

  if (Serial.available() > 0) { // check if something enters the serial buffer
    input = Serial.readString();
    input.trim(); //removing empty spaces
    Serial.println(input + "\n");
    if ( input.equals("i") ) {
      Serial.println("Fetching Data...Please Wait..\n");
      delay(1000);
      //---------------------- soil moisture code ----------------------
      sensorValueA = analogRead(sensorPinA); //Reading soil moisture value of plant A
      sensorValueB = analogRead(sensorPinB); //Reading soil moisture value of plant B
      //Soil status
      boolean isdryA = false;
      boolean isdryB = false;
      String soilStatusA = "";
      String soilStatusB = "";
      //Status of soil A
      if (sensorValueA < 750)
        soilStatusA = "Soil is moist... no need for watering";
      else if (sensorValueA > 750) {
        soilStatusA = "Soil is dry... needs watering";
        isdryA = true;
      }
      //Status of soil B
      if (sensorValueB < 750)
        soilStatusB = "Soil is moist... no need for watering";
      else if (sensorValueB > 750) {
        soilStatusB = "Soil is dry... needs watering";
        isdryB = true;
      }
      
      //---------------------- temp sensor code ----------------------
      //getting temp of A
      int tempValueA = analogRead(tempPinA);
      voltageA = tempValueA * (5000 / 1024.0); // in millivolts]
      voltageA = voltageA - 500; // using TMP36
      temperatureA = voltageA / 10; //convert millivolts to Celsius
      //getting temp of B
      int tempValueB = analogRead(tempPinB);
      voltageB = tempValueB * (5000 / 1024.0); // in millivolts
      voltageB = voltageB - 500; // using TMP36
      temperatureB = voltageB / 10; //convert millivolts to Celsius
      //Temp status
      String tempStatusA = "";
      String tempStatusB = "";
      //Temp status of A
      if (temperatureA <= 15)
        tempStatusA = "The Weather is cold";
      else if (temperatureA > 15 && temperatureA <= 23)
        tempStatusA = "The Weather is warm";
      else if (temperatureA > 23)
        tempStatusA = "The Weather is hot";
      //Temp status of B
      if (temperatureB <= 15)
        tempStatusB = "The Weather is cold";
      else if (temperatureB > 15 && temperatureB <= 23)
        tempStatusB = "The Weather is warm";
      else if (temperatureB > 23)
        tempStatusB = "The Weather is hot";

      //---------------------- light sensor code ----------------------
      lightValueA = analogRead(lightPinA);
      lightValueB = analogRead(lightPinB);
      //Light status
      String lightStatusA = "";
      String lightStatusB = "";
      //Status of soil A
      if (lightValueA <= 290)
        lightStatusA = "It is dim... Plant A needs light";
      else if (lightValueA > 290)
        lightStatusA = "It is bright... Plant A has sufficient light";
      //Status of soil B
      if (lightValueB <= 290)
        lightStatusB = "It is dim... Plant B needs light";
      else if (lightValueB > 290)
        lightStatusB = "It is bright... Plant B has sufficient light";

      //---------------------- leds code ----------------------
      if(isdryA)
        digitalWrite(redPinA, HIGH);
      else
        digitalWrite(greenPinA, HIGH);
      if(isdryB)
        digitalWrite(redPinB, HIGH);
      else
        digitalWrite(greenPinB, HIGH);
      
      //---------------------- displaying output code ----------------------
      Serial.println("-------------------------");
      //Showing the details of plant A
      Serial.println("🌿 Plant A 🌿 ");
      Serial.print("- 🌱 Soil Moisture Value: ");
      Serial.print(sensorValueA);
      Serial.print(" || ");
      Serial.println(soilStatusA);
      Serial.print("- 🌡 Temperature: ");
      Serial.print(temperatureA);
      Serial.print(" Celsius");
      Serial.print(" || ");
      Serial.println(tempStatusA);
      Serial.print("- ☀ Light: ");
      Serial.print(lightValueA);
      Serial.print(" || ");
      Serial.println(lightStatusA);
      Serial.println("-------------------------");
      //Showing the details of plant B
      Serial.println("🌿 Plant B 🌿 ");
      Serial.print("- 🌱 Soil Moisture Value: ");
      Serial.print(sensorValueB);
      Serial.print(" || ");
      Serial.println(soilStatusB);
      Serial.print("- 🌡 Temperature: ");
      Serial.print(temperatureB);
      Serial.print(" Celsius");
      Serial.print(" || ");
      Serial.println(tempStatusB);
      Serial.print("- ☀ Light: ");
      Serial.print(lightValueB);
      Serial.print(" || ");
      Serial.println(lightStatusB);
      Serial.println("-------------------------\n");

      //---------------------- water pump code ----------------------
      //if A or B are dry but not both
      if (isdryA ^ isdryB) {
        if(isdryA){
          Serial.println("⚠ Plants A is dry");
          Serial.println("--> Do you want to water plant A (y/n): ");
        }
        else if(isdryB){
          Serial.println("⚠ Plants B is dry");
          Serial.println("--> Do you want to water plant B (y/n): ");
        }
        while (Serial.available() == 0) { //Wait for user input
        }
        if (Serial.available() > 0) { // check if something enters the serial buffer
          inputW = Serial.readString();
          inputW.trim(); //removing empty spaces
          Serial.println(inputW + "\n");
          if ( inputW.equals("y") ){
            //water pump count down
            digitalWrite(bluePin, HIGH); //it is reapeted(high and low) for blinking effect
            Serial.println("\nBe ready, Pumping Water in 3 seconds...\n");
            delay(3000);
            digitalWrite(bluePin, LOW);
            Serial.print("3..");
            delay(1000);
            digitalWrite(bluePin, HIGH);
            Serial.print("2..");
            delay(1000);
            digitalWrite(bluePin, LOW);
            Serial.println("1..\n");
            delay(1000);
            digitalWrite(bluePin, HIGH);
            digitalWrite(waterPumpPin, HIGH);
            delay(4000);
            digitalWrite(bluePin, LOW);
            digitalWrite(waterPumpPin, LOW);
            Serial.println("Finished Watering\n");
          }
          else if ( inputW.equals("n") )
            Serial.println("OK... Don't forget to water it later\n");
          else { // if input != y or n
            Serial.println("-------------------------");
            Serial.println("Invalid Input!");
            Serial.println("-------------------------\n");
          }
        }
      }
      //else if both A and B are dry
      else if (isdryA && isdryB) {
        Serial.println("⚠ Plants A and B are dry");
        Serial.println("--> Do you want to water plant A and B (y/n): ");
        while (Serial.available() == 0) { //Wait for user input
        }
        if (Serial.available() > 0) { // check if something enters the serial buffer
          inputW = Serial.readString();
          inputW.trim(); //removing empty spaces
          Serial.println(inputW + "\n");
          if ( inputW.equals("y") ){
            Serial.println("Water will pump 2 times");
            //water pump count down
            digitalWrite(bluePin, HIGH);//it is reapeted(high and low) for blinking effect
            Serial.println("1- Be ready, Pumping Water in 3 seconds...\n");
            delay(3000);
            digitalWrite(bluePin, LOW);
            Serial.print("3..");
            delay(1000);
            digitalWrite(bluePin, HIGH);
            Serial.print("2..");
            delay(1000);
            digitalWrite(bluePin, LOW);
            Serial.println("1..\n");
            delay(1000);
            digitalWrite(bluePin, HIGH);
            digitalWrite(waterPumpPin, HIGH);
            delay(2000);
            digitalWrite(bluePin, LOW);
            digitalWrite(waterPumpPin, LOW);
            Serial.println("2- Be ready, Pumping Water in 3 seconds...\n");
            delay(3000);
            digitalWrite(bluePin, HIGH);
            Serial.print("3..");
            delay(1000);
            digitalWrite(bluePin, LOW);
            Serial.print("2..");
            delay(1000);
            digitalWrite(bluePin, HIGH);
            Serial.print("1..\n");
            delay(1000);
            digitalWrite(waterPumpPin, HIGH);
            delay(4000);
            digitalWrite(bluePin, LOW);
            digitalWrite(waterPumpPin, LOW);
            Serial.println("Finished Watering\n");
          }
          else if ( inputW.equals("n") )
            Serial.println("OK... Don't forget to water them later\n");
            
          else { // if input != y or n
            Serial.println("-------------------------");
            Serial.println("Invalid Input!");
            Serial.println("-------------------------\n");
          }
        }
      }
      else{
        Serial.print("Both plants have suffient amount of water!\n");
        delay(3000);
      }
      //turning off leds
      digitalWrite(redPinA, LOW);
      digitalWrite(greenPinA, LOW);
      digitalWrite(redPinB, LOW);
      digitalWrite(greenPinB, LOW);
    }
    else { // if input != i
      Serial.println("-------------------------");
      Serial.println("Invalid Input!");
      Serial.println("-------------------------\n");
    }
  
    delay(2000);
    // indicates end of current request and beginning of a new one
    Serial.println("____________________________________________________________________________________________________\n");
  }
}
