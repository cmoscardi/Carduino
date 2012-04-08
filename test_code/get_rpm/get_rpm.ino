#define MS_PORT Serial3
#define USB_PORT Serial
#define PIN 53
#define RPM 6
#define ARRAY_SIZE 154

byte table[ARRAY_SIZE];
int rpm;
int rpm2;
int i;
int counter;

void setup(){
  MS_PORT.begin(115200);
  USB_PORT.begin(115200);  
}

void loop(){
  MS_PORT.flush();
  MS_PORT.write('A');
  //int a = (int) 'A';
 // Serial.println(a);
  /*
  MS_PORT.write('a');
  MS_PORT.write(byte(0));
  MS_PORT.write(byte(6));
  */
  counter=0;
  delay(100);
  while(MS_PORT.available()==0){
    Serial.println("not available");
    delay(10);
    ++counter;
    if(counter>100){
        counter=0;
        MS_PORT.write('A');
        //MS_PORT.write(byte(0));
        //MS_PORT.write(byte(6));
    }
  }
  while(MS_PORT.available()<8);
  for(i=0;i<154;i++){
      table[i]=0;
  }
  for(i=0;i<152;i++){
    table[i]= MS_PORT.read();
  }
  rpm= ((table[7]<<8 | table[6]));
  rpm2 = ((table[6]<<8 | table[7]));
    //if(rpm!=0){
      Serial.print("RPM: ");
      Serial.println(rpm);
      Serial.print("RPM2: ");
      Serial.println(rpm2);
   // }
    /*if(rpm>2000){
      digitalWrite(PIN,HIGH);
    }
    else if(rpm!=0&&rpm<3000){
      digitalWrite(PIN,LOW);
   
  }*/
  delay(200);
}
