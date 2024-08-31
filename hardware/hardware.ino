#include<ESP8266WiFi.h>
#include<SoftwareSerial.h>
#include<WiFiClient.h>
#include<ESP8266WebServer.h>
#include<Wire.h>
void printDetail(uint8_t type, int value);
const char* ssid = "Galaxy A10s";
const char* password = "12345678";
ESP8266WebServer server(80);
int a=0,p1=0,s1=0,s2=0,s3=0;
int p2 = 0, p3 = 0,total=0;
int c1 = 350, c2 = 1000, c3 = 746;
SoftwareSerial myserial(D1,D2);
int sw=D2;
String page = "";

void setup()
{
  Serial.begin(115200);
  pinMode(sw, INPUT);
  while (!Serial) {
; // wait for serial port to connect. Needed for native USB port only
}
  
 
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("connecting...");
  }
  Serial.print(WiFi.localIP());
  server.on("/", []()
  {
    page = "<html><head><title>Power consumption</title></head><style type=\"text/css\">";
    page += "table{border-collapse: collapse;} th, td {border: 2px solid black; color: black;} th {background-color: transparent;} table, tr, td {border: 2px solid black; font-size: x-large;}";
    page += "text-align:center;border-style: groove;border-color: rgb(255,0,0);}</style><body><center>";
    page += "<h1>Power Consumption</h1><br><br><table style=\"width: 1200px;height: 450px;\"><tr>";
    page += "<th>Appliances</th><th>Time Operated (hr)</th><th>Power Rating</th><th>Power Consumed</th></tr><tr><td>Washing Machine</td><td>" + String(p1) + "</td><td>" + String(c1) + "</td><td>" + String(s1) + "</td></tr>";
    page += "<tr><td>Iron Box</td><td>" + String(p2) + "</td><td>" + String(c2) + "</td><td>" + String(s2) + "</td></tr><tr><td>Motor</td><td>" + String(p3) + "</td><td>" + String(c3) + "</td><td>" + String(s3) + "</td>";
    page += "</tr></table><br><H3>Total power consumption is </H3>"+String(total)+"<br><input type=\"button\" name=\"Pay Online Now\" value=\"Visit Our Website\" style=\"width: 200px;height: 50px\"></center></body></html>";
    page += "<meta http-equiv=\"refresh\" content=\"2\">";
    server.send(200, "text/html", page);
  });
  server.begin();
}


void loop() {
  int sw_status = digitalRead(sw);
  if(sw_status==LOW){
    
    Serial.println("NO");
    delay(1000);
  }else{
    s1=p1+s1;
    s2=p2+s2;
    s3=p3+s3;
    total=s1+s2+s3;
    delay(1000);
    Serial.println("blah");
    p1=p1+1;
  }
if (Serial.available()) {
Serial.write(Serial.read());
}
  
server.handleClient();
}
