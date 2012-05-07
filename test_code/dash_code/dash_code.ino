#define MS_PORT Serial

//smallest tach pin
#define MIN_PIN 2
#define MAX_PIN 9
//highest tach pin
//pins 15 and 16 are 
//the bottom two tach pins
//which is kinda weird

#define BATTERY_PIN 13
#define COOLANT_PIN 14


//the index **AFTER** which
//shift LED will go on.
//Set to a value from 0-9.
//0 will have it blink as soon
//as we get above 2k RPM and
//the first LED lights up.

//9 will blink once we hit
//the VERY top LED.

//7 is the default setting,
//for blinking as soon as 
//we hit the
//red on the tach.
#define SHIFT_AFTER 7

//shift pins
#define SHIFT_MIN 10
#define SHIFT_MAX 12
//
#define BATTERY_WARNING  10 //volts
#define HOT_WARNING  200 //fahrenheit


#define ARRAY_SIZE 154



int i;
int counter;
byte table[ARRAY_SIZE];
boolean shifted; 

//these are variables which
//will be modified by the
//get_rpm() function
//(should pass pointers,
//this is kind of a hack)
//
int coolant_temp;
int battery_voltage;


void initialize_LEDs(){
  //turn pins on

  for(i=2; i<=16 ; i++){
    pinMode(i,OUTPUT);
    digitalWrite(i,HIGH);
  }
  //end turn pins on

  delay(1500);
  for(i=2; i<=16; i++){
    digitalWrite(i, LOW);
  }
  int j;
  for(j=1;j<=10;j++){
    write_below(j);
    delay(120);
  }
  write_below(10);
  for(j=9;j>=0;j--){
    reset_after(j);
    delay(40);
  }
  delay(500);
  for(j=0;j<2;j++){
    shift_on();
    delay(100);
    shift_reset();
    delay(100);
  }
}


void setup(){
 // shifted=false;
  Serial.begin(115200);
 // Serial.println(A0);
  //MS_PORT.begin(115200);
  //  USB_PORT.begin(115200); 
  initialize_LEDs();

}


void loop(){
  delay(50);
  /**
  int k;
  for(k=0;k<=10;k++){
    test_method(k);
    delay(1000);
  }
  for(k=10;k>=0;k--){
    test_method(k);
    delay(1000);
  }   
  test_method(-42);
  delay(3000);
  **/
  
  
  int val = index_of(get_rpm());
  //multiply by .1 because of the
  //megasquirts internal representation 
  if((battery_voltage/10)<BATTERY_WARNING){
    digitalWrite(BATTERY_PIN,HIGH);
  }
  else{
    digitalWrite(BATTERY_PIN,LOW);
  }
  //in fahrenheit
  if((coolant_temp/10)>HOT_WARNING){
    digitalWrite(COOLANT_PIN,HIGH);
  }
  else{
    digitalWrite(COOLANT_PIN,LOW);
  }
  if(val>SHIFT_AFTER){
    //writes below and at the value
    write_below(val);
    //resets after (but not at) value
    reset_after(val);
    shift_on();
  }
  else if(val>0){
    //shift_reset();
    write_below(val);
    reset_after(val);
  }
  else if(val==0){
    reset_all();
  }
  else{ //we got nothing back from the MS
    //this is supposed to indicate error
    digitalWrite(BATTERY_PIN,HIGH);
    digitalWrite(COOLANT_PIN,HIGH);
    shift_on();
    delay(1000);
  }
 
}

void shift_on(){
  for(i = SHIFT_MIN;i <= SHIFT_MAX;i++){
    digitalWrite(i,HIGH);
  }
  //SET BLINKING SPEED HERE
  delay(50);
  for(i = SHIFT_MIN;i <= SHIFT_MAX;i++){
    digitalWrite(i,LOW);
  }
}
  


void shift_reset(){
  for(i=SHIFT_MIN;i<=SHIFT_MAX;i++){
    digitalWrite(i,LOW);
  }
}
void reset_all(){
  for(i=2;i<=16;i++){
    digitalWrite(i,LOW);
  }
}

void test_method(int val){
    if(val>8){
    shift_on();
    //writes below and at the value
    write_below(val);
    //resets after (but not at) value
    reset_after(val);
  }
  else if(val>0){
    shift_reset();
    write_below(val);
    reset_after(val);
  }
  else if(val==0){
    reset_all();
  }
  else{ //we got nothing back from the MS
    digitalWrite(BATTERY_PIN,HIGH);
    digitalWrite(COOLANT_PIN,HIGH);
  }
}

int index_of(unsigned int rpm){
  //if we get no response 
  //light up the BATTERY
  //and COOLANT 
  if(rpm==-42){
    return -1;
  }
  if(rpm<9000){
    //this should be rpm/2000
    //changing to rpm/500 might
    //be useful for testing
    return (rpm/2000);
  }
  else{
    return ((rpm/1000)-4);
  }
}

void write_below(int index){
  for(i=MIN_PIN+(index-3);i>=MIN_PIN;i--){
    digitalWrite(i,HIGH);
  }
  if(index>1){
    digitalWrite(15,HIGH);
    digitalWrite(16,HIGH);
  }
  else { // by logic we're only lighting this pin up
    digitalWrite(15,HIGH);
  }
}

void reset_after(int index){
  for(i=index;i<=MAX_PIN;i++){
    digitalWrite(i,LOW);
  }
  if(index==1){
    digitalWrite(16,LOW);
  }
  else if(index==0){
    digitalWrite(16,LOW);
    digitalWrite(15,LOW);
  }
}

int get_rpm(){
  MS_PORT.flush();
  MS_PORT.write('A');
  
  //counter for retries
  counter=0;
  int retry_count = 0;
  //delay to make sure that
  //MS has responded
  delay(50);
  
  while(MS_PORT.available()==0){
    delay(10);
    ++counter;
    if(retry_count>10){
      //something terrible 
      //has happend
      return -42;
    }
    if(counter>100){
        counter=0;
        MS_PORT.write('A');
        retry_count++;
    }
  }
  for(i=0;i<154;i++){
    table[i]=0;
  }

  while(MS_PORT.available()<28);
  for(i=0;i<154;i++){
    table[i]= MS_PORT.read();
  }
  
  coolant_temp = ((table[22]<<8) | table[23]);
  battery_voltage = ((table[26]<<8) | table[27]);
  MS_PORT.flush();
  return ((table[6]<<8 | table[7]));

}

