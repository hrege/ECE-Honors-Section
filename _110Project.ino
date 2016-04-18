void setup() {
  initWiFi();
  
  int i = 0;
  for(i = 0; i < 10; i++){
    String mystring = "entry,";
    mystring = mystring + i;
    Serial.println(mystring);
    add_line_to_sheet(mystring);
  }
}

void loop() {
 
}


