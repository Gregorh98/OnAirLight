#include <ESP8266WiFi.h>

const char* ssid = "Hastings";
const char* password = "**********";
const char* host = "192.168.0.217"; //it will tell you the IP once it starts up
                                        //just write it here afterwards and upload
int relay = D3;


WiFiServer server(301); //just pick any port number you like

void setup() {
  Serial.begin(115200);
  delay(10);
Serial.println(WiFi.localIP());
  // prepare GPIO2
  pinMode(relay, OUTPUT);
  digitalWrite(relay, LOW);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
}

void toggle()
{
  digitalWrite(relay, HIGH);
  delay(50);
  digitalWrite(relay, LOW);
  delay(50);
}

void l_on()
{
  toggle();
}

void l_off()
{
  toggle();
  toggle();
}

void loop() {
  // Check if a client has connected
  
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  while (!client.available()) {
    delay(1);
  }

  // Read the first line of the request
  String req = client.readStringUntil('\r');
  client.flush();

  // Match the request
  if (req.indexOf("") != -10) {  //checks if you're on the main page

    if (req.indexOf("/OFF") != -1) { //checks if you clicked OFF
      l_off();
      Serial.println("You clicked OFF");
    }
    if (req.indexOf("/ON") != -1) { //checks if you clicked ON
      l_on();
      Serial.println("You clicked ON");
    }
  }

  else {
    Serial.println("invalid request");
   client.stop();
    return;
  }

  // Prepare the response
  String s = "HTTP/1.1 200 OK\r\n";
  s += "Content-Type: text/plain\r\n\r\n";
  s += "OK";

  client.flush();


  // Send the response to the client
  client.print(s);
  delay(1);


  
}
