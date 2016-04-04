void setup() {
  initWiFi();
}

void loop() {
  String mystring = "hello";
  mystring = mystring + ", goodbye";
  add_line_to_sheet(mystring);
}


