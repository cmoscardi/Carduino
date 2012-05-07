
void setup(){
  Serial.begin(115200);
  Serial3.begin(115200);
}

void loop(){
  byte versionName[120];
  int i = 0;
  for(i=0;i<120;i++){
    versionName[i]=0;
  }
  
  Serial3.write('S');
  delay(100);
  
  int counter=0;
  while(Serial3.available()==0){
    if(counter>1000){
      break;
    }
    Serial.println("poop");
    counter++;
  }
  
  while(Serial3.available()>0){
    Serial.println("here");
    versionName[i]=Serial3.read();
    i++;
  }
  
  for(i=0;i<120;i++){
    Serial.print(versionName[i]);
  }
  Serial.println("");
  delay(1000);
}
