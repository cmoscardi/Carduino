#define MS_PORT Serial3
#define USB_PORT Serial
//index of the smallest pin
#define SMALLEST_PIN
#define MAX_PIN
#define RPM 6
#define ARRAY_SIZE 154
#define BASE_RPM 1000
#define MAX_RPM 12000
int i;


void setup(){
  MS_PORT.begin(115200);
  USB_PORT.begin(115200); 
  for(i=SMALLEST_PIN; i<MAX_PIN ; i++){
    digitalWrite(i,HIGH);
  }
  delay(100);
  for(i=SMALLEST_PIN; i<MAX_PIN ; i++){
    digitalWrite(i, LOW);
  }
  delay(100);
  for(i=SMALLEST_PIN; i<j ; i++){
    digitalWrite(i, HIGH);
    delay(50);
  }
}

int rpm;
int rpm2;
int counter;
byte table[ARRAY_SIZE];

void loop(){
  rpm2 = get_rpm();
  if(rpm2>=(MAX_RPM-400)){
   write_below(MAX_PIN);
   digitalWrite(MAX_PIN, HIGH);
  }
  else if(rpm2>=(MAX_RPM-800)){
    reset_after(MAX_PIN);
    write_below(MAX_PIN-1);
  }
  else if(rpm2>=(MAX_RPM-1200)){
    reset_after(MAX_PIN-1);
    write_below(MAX_PIN-2);
  }
  else if(rpm2>=(MAX_RPM-1600)){
    reset_after(MAX_PIN-1);
    write_below(MAX_PIN-2);
  }
  else if(rpm2>=(MAX_RPM-2000)){
    reset_after(MAX_PIN-1);
    write_below(MAX_PIN-2);
  }
  else if(rpm2>=(MAX_RPM-2400)){
    reset_after(MAX_PIN-1);
    write_below(MAX_PIN-2);
  }
  else if(rpm2>=(MAX_RPM-2800)){
    reset_after(MAX_PIN-1);
    write_below(MAX_PIN-2);
  }
    else if(rpm2>=(MAX_RPM-3200)){
    reset_after(MAX_PIN-1);
    write_below(MAX_PIN-2);
  }
    else if(rpm2>=(MAX_RPM-3600)){
    reset_after(MAX_PIN-1);
    write_below(MAX_PIN-2);
  }
    else if(rpm2>=(MAX_RPM-4000)){
    reset_after(MAX_PIN-1);
    write_below(MAX_PIN-2);
  }
    else if(rpm2>=(MAX_RPM-4400)){
    reset_after(MAX_PIN-1);
    write_below(MAX_PIN-2);
  }
    else if(rpm2>=(MAX_RPM-4800)){
    reset_after(MAX_PIN-1);
    write_below(MAX_PIN-2);
  }
    else if(rpm2>=(MAX_RPM-5200)){
    reset_after(MAX_PIN-1);
    write_below(MAX_PIN-2);
  }
    else if(rpm2>=(MAX_RPM-5600)){
    reset_after(MAX_PIN-1);
    write_below(MAX_PIN-2);
  }
  else if(rpm2>=(MAX_RPM-6000)){
    reset_after(MAX_PIN-1);
    write_below(MAX_PIN-2);
  }
  else if(rpm2>=(MAX_RPM-6400)){
    reset_after(MAX_PIN-1);
    write_below(MAX_PIN-2);
  }
  else if(rpm2>=(MAX_RPM-6800)){
    reset_after(MAX_PIN-1);
    write_below(MAX_PIN-2);
  }
  else if(rpm2>=(MAX_RPM-7200)){
    reset_after(MAX_PIN-1);
    write_below(MAX_PIN-2);
  }
  else if(rpm2>=(MAX_RPM-7600)){
    reset_after(MAX_PIN-1);
    write_below(MAX_PIN-2);
  }
  else if(rpm2>=(MAX_RPM-8000)){
    reset_after(MAX_PIN-1);
    write_below(MAX_PIN-2);
  }
  else if(rpm2>=(MAX_RPM-8000)){
    reset_after(MAX_PIN-1);
    write_below(MAX_PIN-2);
  }
  else if(rpm2>=(MAX_RPM-8400)){
    reset_after(MAX_PIN-1);
    write_below(MAX_PIN-2);
  }
  else if(rpm2>=(MAX_RPM-8800)){
    reset_after(MAX_PIN-1);
    write_below(MAX_PIN-2);
  }
  else if(rpm2>=(MAX_RPM-9200)){
    reset_after(MAX_PIN-1);
    write_below(MAX_PIN-2);
  }
  else if(rpm2>=(MAX_RPM-9600)){
    reset_after(MAX_PIN-1);
    write_below(MAX_PIN-2);
  }
  else if(rpm2>=(MAX_RPM-10000)){
    reset_after(MAX_PIN-1);
    write_below(MAX_PIN-2);
  }
  
}

void write_below(int index){
  for(i=index;i>=SMALLEST_PIN;i--){
    digitalWrite(i,HIGH);
  }
}

void reset_after(int index){
  for(i=index;i<=MAX_PIN;i++){
    digitalWrite(i,LOW);
  }
}

/** TODO: RETURN A VALUE! **/
int get_rpm(){
  MS_PORT.flush();
  MS_PORT.write('A');
  counter=0;
  delay(10);
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
  for(i=0;i<152;i++){
    table[i]= MS_PORT.read();
  }
  rpm= ((table[7]<<8 | table[6]));
  rpm2 = ((table[6]<<8 | table[7]));
      Serial.print("RPM: ");
      Serial.println(rpm);
      Serial.print("RPM2: ");
      Serial.println(rpm2);

  
}

