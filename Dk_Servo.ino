#include <ESP8266WiFi.h>
#include <Servo.h>

const char* ssid = "Nhom7";
const char* password = "11111111";

WiFiServer server(80);
Servo Ser1; 
Servo Ser2; 
Servo Ser3;
Servo Ser4; 

void setup(){
  Serial.begin(115200); //Default Baud Rate for NodeMCU
  delay(10);
  
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
   
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  // Start the server
  server.begin();
  Serial.println("Server started");
  // Print the IP address
  Serial.println(WiFi.localIP()); 

  pinMode(5, OUTPUT);  digitalWrite(5, 0);    //D1
  pinMode(4, OUTPUT);  digitalWrite(4, 0);    //D2
  pinMode(14, OUTPUT); digitalWrite(14, 0);   //D5
  pinMode(12, OUTPUT); digitalWrite(12, 0);   //D6
  // khoi tao vi tri bat dau cua 4 servo
  Ser1.attach(5,500,2500);  Ser1.write(90);  delay(100);
  Ser2.attach(4,500,2500);  Ser2.write(20);  delay(100);
  Ser3.attach(14,500,2500); Ser3.write(180); delay(100);
  Ser4.attach(12,500,2500); Ser4.write(80);  delay(100);  
}

int val = -1, goc1 = 90, goc2 = 90, goc3 = 180, goc4 = 80;

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) { return; }
  
  // Wait until the client sends some data
  Serial.print("new client ");
  while(!client.available()) {
     delay(1); }
  
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  
  String requests[] = {"/gpio/0", "/gpio/1", "/gpio/2", "/gpio/3", "/gpio/4", "/gpio/5", "/gpio/6", "/gpio/7", "/gpio/8"};
  int values[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
  for (int i = 0; i < sizeof(requests)/sizeof(requests[0]); i++) {
    if (req.indexOf(requests[i]) != -1) {
      val = values[i];
      break;
    }
  }

  if (val == -1) {
    Serial.println("Invalid request");
    client.stop();
    return;
  }
    
  bool check = false; //Kiem tra trang thai hien tai

  switch(val) {
  case 0: Serial.println("Tam dung hoat dong !");
    break;
  case 1:
    if(goc1>=0) {
      goc1 = goc1 - 2;
      Ser1.write(goc1);
      //delay(50);
      Serial.print("Servo 1 = ");
      Serial.println(goc1);
    }
    break;
    
  case 2:
    if(goc1<=180) {
      goc1 = goc1 + 2;
      Ser1.write(goc1);
      //delay(50);
      Serial.print("Servo 1 = ");
      Serial.println(goc1);
    }
    break;
    
  case 3:
    if(goc2>=70) {
      goc2 = goc2 - 2;
      Ser2.write(goc2);
      delay(50);
      Serial.print("Servo 2 = ");
      Serial.println(goc2);
    }
    break;
    
  case 4:
    if(goc2<=180) {
      goc2 = goc2 + 2;
      Ser2.write(goc2);
      delay(50);
      Serial.print("Servo 2 = ");
      Serial.println(goc2);
    }
    break;
    
  case 5:
    if(goc3>=0) {
      goc3 = goc3 - 2;
      Ser3.write(goc3);
      delay(50);
      Serial.print("Servo 3 = ");
      Serial.println(goc3);
    }
    break;
    
  case 6:
    if(goc3<=180) {
      goc3 = goc3 + 2;
      Ser3.write(goc3);
      delay(50);
      Serial.print("Servo 3 = ");
      Serial.println(goc3);
    }
    break;
    
  case 7:
    if(goc4>=80) {
      goc4 = goc4 - 2;
      Ser4.write(goc4);
      delay(50);
      Serial.print("Servo 4 = ");
      Serial.println(goc4);
    }
    break;
    
  case 8:
    if(goc4<=140) {
      goc4 = goc4 + 2;
      Ser4.write(goc4);
      delay(50);
      Serial.print("Servo 4 = ");
      Serial.println(goc4);
    }
    break;
    
  default:
    Serial.println("Invalid input");
}

  client.flush(); }