
// defines pins numbers
const int trigPin = 9;
const int echoPin = 10;
const int PumpPos= 11;
const int PumpNeg=  12;
const int garden=  7;
const int mois=A3;
const int pn=A1;
const int pn1=A2;

// defines variables
long duration;
int distance;
int auth=0;// Authorization flag for the pump.
int authg=0;// Authorization flag for the garden pump.
int mflg=0;
void setup() {
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
pinMode(mois, INPUT);// Input from moisture sensor 
Serial.begin(9600); // Starts the serial communication
        
pinMode(13, OUTPUT);
}
char data = 0; // This is the buffer    
void loop() {
int sensorValue = analogRead(mois);
 
  

  if(Serial.available() > 0)      // Send data only when you receive data:
   {
      data = Serial.read();        //Read the incoming data & store into data
      Serial.print(data);          //Print Value inside data in Serial monitor
      Serial.print("\n");        
      if(data == 'L')              // Checks whether value of data is equal to 1
         digitalWrite(13, HIGH);   //If value is 1 then LED turns ON
      else if(data == 'l')         //  Checks whether value of data is equal to 0
         digitalWrite(13, LOW);
      else if(data=='g'){
          if(sensorValue<300){
            Serial.println("Garden dryness : Very Dry");
            
            }
          else if(sensorValue>=301 && sensorValue<=450){
              Serial.println("Garden dryness : Dry");
              }
          else if(sensorValue>=451 && sensorValue<=530){
              Serial.println("Garden dryness : Optimal");
              }
          else if(sensorValue>=531 && sensorValue<=650){
              Serial.println("Garden dryness : Well Watered");
              }

              
          else if(sensorValue>=651){
              Serial.println("Garden dryness : Over watered");
              }
          Serial.flush();
        }
        else if(data=='G'){
          if(sensorValue<510){
            Serial.print("Garden dryness : ");
            Serial.println(sensorValue);
            }
          else if(sensorValue>=510 && sensorValue<=570){
              Serial.print("Garden dryness : ");
              Serial.println(sensorValue);
              }
          else if(sensorValue>=571 && sensorValue<=600){
              Serial.print("Garden dryness : ");
              Serial.println(sensorValue);
              }
          else if(sensorValue>=601 && sensorValue<=650){
              Serial.print("Garden dryness : ");
              Serial.println(sensorValue);
              }
          else if(sensorValue>=651){
              Serial.print("Garden dryness : ");
              Serial.println(sensorValue);
              }
          Serial.flush();
        }
        else if(data=='t'){
            Serial.print("Level of tank is : ");
            if(distance<5){
              Serial.println("Full");
              }
            else if(distance >=5 && distance <=9){
                Serial.println("Mid  Tank");
                
                }
            else{
                  Serial.println("WARNING Dry Tank");
                  }
            Serial.flush();
        } 
        else if(data=='T'){
            Serial.print("Level of tank is : ");
            if(distance<3){
              Serial.println(distance);
              }
              else if(distance >=3 && distance <=6){
                Serial.println(distance);
                
                }
                else{
                  Serial.println(distance);
                  }
            Serial.flush();
        } 
        else if(data=='p'){
            auth=1;
            analogWrite(pn,0);
			analogWrite(pn1,0);
  
        } 
        else if(data=='P'){
            auth=0;
            analogWrite(pn,180);
			analogWrite(pn1,0);
			mflg=0;
        } 
            
        else if(data=='0'){
            authg=0;
            digitalWrite(garden, LOW);
        } 
        else if(data=='1'){
            authg=0;
            digitalWrite(garden, HIGH);
        } 
       
   }
		// Clears the trigPin
		delay(1000);
		digitalWrite(trigPin, LOW);
		delayMicroseconds(2);
		// Sets the trigPin on HIGH state for 10 micro seconds
		digitalWrite(trigPin, HIGH);
		delayMicroseconds(10);
		digitalWrite(trigPin, LOW);
		// Reads the echoPin, returns the sound wave travel time in microseconds
		duration = pulseIn(echoPin, HIGH);
		// Calculating the distance
		distance= duration*0.034/2;
		if(distance<=9 && sensorValue<=530 && authg==0){
		  digitalWrite(garden, HIGH);
		 }
		else{
			 digitalWrite(garden, LOW);
		}
		if(distance>=7 && auth==0){
		  analogWrite(pn,180);
		  analogWrite(pn1,0);
		  mflg=0;
		}
		else if(distance<7 && auth==0){
		  analogWrite(pn,0);
		  analogWrite(pn1,0);
		  String dis=String(distance);
		 if(mflg==0){ Serial.print( "Motor stpd. Lvl: ");
		  Serial.println(distance);}
		  mflg=1;
		  Serial.flush();
		}  
}
