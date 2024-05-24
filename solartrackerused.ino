//Servo motor library 
#include <Servo.h>
//Initialize variables
int  mode = 0;
int axe = 0;            
int buttonState1 = 0;    
int buttonState2  = 0;   
int prevButtonState1 = 0;
int prevButtonState2 = 0; 
 
int ldrtopr=  A0;                // top-right LDR                          
int ldrtopl = A1;               // top-left LDR                          
int ldrbotr = A2;               //  bottom-right LDR                     
int ldrbotl = A3;               // bottom-left  LDR                   
int topl = 0;
int topr = 0; 
int botl = 0;
int  botr = 0;
int serrl=90;
int serud=90;

//Declare two servos
Servo servo_updown;
Servo servo_rightleft;

int  threshold_valuerl=10;
int  threshold_valueud=5;           //measurement sensitivity

unsigned long previousMillis = 0;  // Variable to store the previous time the function was called
const long interval = 10000; 
void setup()
{
  Serial.begin(9600);                                //serial connection setup  //opens  serial port, sets data rate to 9600 bps
  Serial.println("CLEARDATA");                       //clear  all data that’s been place in already
  Serial.println("LABEL,t,voltage,current,power,Mode");   //define the column headings (PLX-DAQ command)

  pinMode(12, INPUT);              //Mode  switch Button
  pinMode(11, INPUT);              //Axis switch
  pinMode(A4,  INPUT);              //Potentiometer for right-left movement and for up-down movement
  
  servo_updown.attach(5);             //Servo motor up-down movement
  servo_rightleft.attach(3); 
  servo_updown.write(90);
  servo_rightleft.write(90);         //Servo motor right-left movement


//     buttonState1 = digitalRead(12);
//   if (buttonState1 != prevButtonState1)  {
//     if (buttonState1 == HIGH) {
//       //Change mode and ligh up the correct  indicator  
//       if (mode == 1) {
//         mode = 0;
//       } else {
//         mode = 1;
//       }
//     }
//   }
//   prevButtonState1 = buttonState1;
//   delay(50); // Wait for 50 millisecond(s)
//    char  Mode;
//   if (mode == 0) {
//     Mode='M';
//     Serial.println(Mode);   //send Mode "Manual" to serial port    
//     // manualsolartracker();
//   } else { // mode automatic
//     Mode = 'A';
//     Serial.println(Mode);      
//     // automaticsolartracker(); //send Mode "Automatic" to serial port
//     } 
 }



void loop()
{
   automaticsolartracker();
  unsigned long currentMillis = millis();  // Get the current time
  
  // Check if it's time to run the function
  if (currentMillis - previousMillis >= interval) {
    // Save the current time for the next iteration
    previousMillis = currentMillis;
    
    // Call your function here
      // automaticsolartracker();

    power();
  }
  
  delay(200);
  // if (Serial.available() > 0) {
  //   // Read the incoming byte
  //   char incomingByte = Serial.read();
  //   if (incomingByte= 'r'){
  //     servo_rightleft.write(0);
  //     servo_updown.write(90);
  //     // Serial.println("reset");
  //     delay(5000);
  //   }
    // Perform actions based on the received character
    
  //}

//  pv_power();
// char  Mode;
//     float volt = analogRead(A5)*5.0/1023;
//     float voltage = 2*volt;                //  Volt=(R1/R1+R2)*Voltage / R1=R2=10Ohms  => voltage=2*volt)
//     float current = voltage/20;            //  I=voltage/(R1+R2) 
//     float power  = voltage*current;
    // Serial.print("DATA,TIME,"); // PLX-DAQ command
    // Serial.print(voltage);    //send the voltage to serial port
    // Serial.print(",");
    // Serial.print(current);    //send the current to serial port
    // Serial.print(",");
    // Serial.print(power);  //send the power to serial port
    // Serial.print(",");
     
//    Serial.println(Mode);      
}
void power() {
  // Read the analog sensor value from pin A4
  int sensorValue = analogRead(A4);
  int curValue = analogRead(A5);


  // Print the sensor value to the serial monitor
 
  float voltage;
  voltage= float(sensorValue) /1024 *10;
      Serial.print("values:");       //capturing analog value of bot left LDR
      Serial.print(topr);
      Serial.print("a");
      Serial.print(topl);
      Serial.print("a");
      Serial.print(botr);
      Serial.print("a");
      Serial.print(botl);



  Serial.print("voaltage Value: ");
  Serial.print(voltage);
  Serial.print(" ");
  Serial.print("current value: ");
  Serial.print(curValue);
  Serial.print(" ");
  Serial.print("servo:");
  Serial.print(serrl);
  Serial.print(" ");
  Serial.println(serud);
  delay(100);

  // Add a small delay to avoid flooding the serial monitor
  // Adjust the delay as needed
}

void  automaticsolartracker(){
  
     //capturing analog values of each LDR
     topr= analogRead(ldrtopr);         //capturing analog value of top right LDR
     topl= analogRead(ldrtopl);         //capturing analog value of top left LDR
     botr= analogRead(ldrbotr);         //capturing analog value of bot right LDR
     botl= analogRead(ldrbotl);  
      // Serial.print("values:");       //capturing analog value of bot left LDR
      // Serial.print(topr);
      // // Serial.print("\t");
      // Serial.print(topl);
      // // Serial.print("\t");
      // Serial.print(botr);
      // // Serial.print("\t");
      // Serial.print(botl);
      // Serial.print("\t");
      // Serial.print("servo:");
      // Serial.print(serrl);
      // // Serial.print("\t");
      // Serial.print(serud);

      // Serial.println(" ");


    // calculating average
    //biasing 
    // botl=botl+20;
     botr=botr-5;
    //  botr=botr-20;
     int avgtop = (topr + topl) / 2;     //average  of top LDRs
     int avgbot = (botr + botl) / 2;     //average of bottom LDRs
     int avgleft = (topl + botl) / 2;    //average of left LDRs
     int avgright  = (topr + botr) / 2;   //average of right LDRs
      // Serial.print("a");
      // Serial.print(avgright);
      // Serial.print("a");
      // Serial.print(avgleft);
    //Get the different  
     int diffelev = avgtop-avgbot ;      //Get the different average betwen  LDRs top and LDRs bot
     int diffazi = avgright-avgleft;
         //Get the different  average betwen LDRs right and LDRs left
            //  Serial.print("diffelev:");

    // Serial.print(diffelev);
    // Serial.print("b");
    //     Serial.print(diffazi);


    //left-right movement of  solar tracker
     
      if (abs(diffazi) >= threshold_valuerl){        //Change  position only if light difference is bigger then the threshold_value
       if  (diffazi < 0) {
        if (serrl> 0) {
          serrl=serrl - 2;
          servo_rightleft.write(serrl);
          // Serial.println("move rl +");
        }
      }
      if (diffazi >  0) {
        if (serrl  < 180 ) {
          serrl=serrl + 2;
          servo_rightleft.write(serrl);
          // Serial.println("move rl -");

        }
      }
      delay(300);
    }
             
      //up-down movement of solar tracker
      if (abs(diffazi) < threshold_valuerl){
           threshold_valuerl=50; 
      if (abs(diffelev) >= threshold_valueud){    //Change position only if light  difference is bigger then thethreshold_value
       if (diffelev > 0) {
        if  (serud > 45) {
          serud=serud  - 2;
          servo_updown.write(serud);
          // Serial.println("move ud -");
        }
      }
      if (diffelev <  0) {
        if (serud  < 135) {
          serud=serud  + 2;
          servo_updown.write(serud);
          // Serial.println("move ud +");
        }
      }
      delay(400);
    } 
      }      
 }  

void manualsolartracker(){
  buttonState2  = digitalRead(13);
  if (buttonState2 != prevButtonState2) {
    if (buttonState2  == HIGH) {
      //Change mode and ligh up the correct indicator  
      if  (axe == 1) {
        axe = 0;
      } else {
        axe = 1;
      }
    }
  }
  prevButtonState2 = buttonState2;
  delay(50); // Wait for 50  millisecond(s)
  if (axe == 0) {     //control right-left movement
    servo_rightleft.write(map(analogRead(A4),  0, 1023, 0, 180));
  } else { // //control up-down movement
    servo_updown.write(map(analogRead(A4),  0, 1023, 0, 180));
  } 
}