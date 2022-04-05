/*
 
 This example uses DNS, by assigning the Ethernet client with a MAC address,

 IP address, and DNS address.

 Circuit:

 * Ethernet shield attached to pins 10, 11, 12, 13 

 */

#include <SPI.h>
#include <Ethernet.h>

// assign a MAC address for the ethernet controller.
// fill in your address here:
byte mac[] = {
  0xA8, 0x61, 0x0A, 0xAE, 0x81, 0x95
};
String MAC = "Host: A8:61:0A:AE:81:95";
// Set the static IP address to use if the DHCP fails to assign

// HOME
//IPAddress ip(192, 168, 1, 58);
// CS
IPAddress ip(192, 168, 2, 74);

// HOME
//IPAddress myDns(192, 168, 1, 1);
// CS
IPAddress myDns(192, 168, 2, 1);


// initialize the library instance:

EthernetClient client;

// HOME
//char server[] = "192.168.1.54";  // also change the Host line in httpRequest()
// CS
char server[] = "192.168.2.75";  // also change the Host line in httpRequest()
int port = 3700;

unsigned long lastConnectionTime = 0;           // last time you connected to the server, in milliseconds

const unsigned long postingInterval = 10*1000;  // delay between updates, in milliseconds

void setup() {

  // You can use Ethernet.init(pin) to configure the CS pin

  //Ethernet.init(10);  // Most Arduino shields

  //Ethernet.init(5);   // MKR ETH shield

  //Ethernet.init(0);   // Teensy 2.0

  //Ethernet.init(20);  // Teensy++ 2.0

  //Ethernet.init(15);  // ESP8266 with Adafruit Featherwing Ethernet

  //Ethernet.init(33);  // ESP32 with Adafruit Featherwing Ethernet

  // start serial port:

  Serial.begin(9600);

  while (!Serial) {

    ; // wait for serial port to connect. Needed for native USB port only

  }

  // start the Ethernet connection:

  Serial.println("Initialize Ethernet with DHCP:");

  if (Ethernet.begin(mac) == 0) {

    Serial.println("Failed to configure Ethernet using DHCP");

    // Check for Ethernet hardware present

    if (Ethernet.hardwareStatus() == EthernetNoHardware) {

      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");

      while (true) {

        delay(1); // do nothing, no point running without Ethernet hardware

      }

    }

    if (Ethernet.linkStatus() == LinkOFF) {

      Serial.println("Ethernet cable is not connected.");

    }

    // try to configure using IP address instead of DHCP:

    Ethernet.begin(mac, ip, myDns);

    Serial.print("My IP address: ");

    Serial.println(Ethernet.localIP());

  } else {

    Serial.print("  DHCP assigned IP ");

    Serial.println(Ethernet.localIP());

  }

  // give the Ethernet shield a second to initialize:

  delay(1000);
}

void loop() {

  // if there's incoming data from the net connection.

  // send it out the serial port.  This is for debugging

  // purposes only:

  if (client.available()) {

    char c = client.read();

    Serial.write(c);

  }

  // if ten seconds have passed since your last connection,

  // then connect again and send data:

  if (millis() - lastConnectionTime > postingInterval) {

    httpRequest();

  }

}

// this method makes a HTTP connection to the server:
void httpRequest() {

  // close any connection before send a new request.

  // This will free the socket on the WiFi shield

  client.stop();

  // if there's a successful connection:

  if (client.connect(server, port)) {

    Serial.println("connecting...");

    // send the HTTP GET request:

    client.println("GET / HTTP/1.1");

    //client.println("Host: A8:61:0A:AE:81:95");
    client.println(MAC);

    client.println("User-Agent: arduino-ethernet");

    client.println("Connection: close");

    client.println();

    // note the time that the connection was made:

    lastConnectionTime = millis();

  } else {

    // if you couldn't make a connection:

    Serial.println("connection failed");

  }
}
