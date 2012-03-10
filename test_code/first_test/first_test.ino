
void setup(){
  Serial.begin(9600);
  Serial2.begin(115200);
}

void loop(){
  byte versionName[120];
  int i = 0;
  for(i=0;i<120;i++){
    versionName[i]=0;
  }
  
  Serial2.write('S');
  delay(100);
  
 
  
  while(Serial2.available()>0){
    versionName[i]=Serial2.read();
    i++;
  }
  
  for(i=0;i<120;i++){
    Serial.print(versionName[i]);
  }
  Serial.print("\n");
  delay(1000);
}
