
#define SMALLEST_PIN 40
#define MAX_PIN 43
#define RPM 6
#define ARRAY_SIZE 154
#define BASE_RPM 1000
#define MAX_RPM 12000
int i;


void setup(){
   
  for(i=SMALLEST_PIN; i<=MAX_PIN ; i++){
    pinMode(i,OUTPUT);
    digitalWrite(i,HIGH);
  }
  delay(2000);
  for(i=SMALLEST_PIN; i<=MAX_PIN ; i++){
    digitalWrite(i, LOW);
  }
  delay(1000);
   for(i=SMALLEST_PIN; i<=MAX_PIN ; i++){
    digitalWrite(i, HIGH);
  }
  delay(1000);
     for(i=SMALLEST_PIN; i<=MAX_PIN ; i++){
    digitalWrite(i, LOW);
  }
  delay(1000);
  int j;
  for(j=0;j<3;j++){
  
    for(i=SMALLEST_PIN; i<=MAX_PIN ; i++){
    digitalWrite(i, HIGH);
    delay(100);
  }
  for(i=MAX_PIN; i>=SMALLEST_PIN ; i--){
    digitalWrite(i, LOW);
    delay(100);
  }
  }
}

void loop(){

}
