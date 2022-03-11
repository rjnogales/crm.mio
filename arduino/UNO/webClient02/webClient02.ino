#include <EtherCard.h>

static byte mymac[] = { 0xDD, 0xDD, 0xDD, 0x00, 0x01, 0x05 };
static byte myip[] = { 192, 168, 2, 10 };

byte Ethernet::buffer[700];
static uint32_t timer;

const char website[] PROGMEM = "www.pasted.co";
const char dataLocationC[] = "/2434bc64";

// called when the client request is complete
static void my_callback (byte status, word off, word len) {
  Serial.println(">>>");
  Ethernet::buffer[off+300] = 0;
  Serial.print((const char*) Ethernet::buffer + off);
  Serial.println("...");
}

void setup () {
  Serial.begin(57600);
  Serial.println(F("\n[webClient]"));

  if (ether.begin(sizeof Ethernet::buffer, mymac) == 0) 
    Serial.println(F("Failed to access Ethernet controller"));
  if (!ether.dhcpSetup())
    Serial.println(F("DHCP failed"));

  ether.printIp("IP:  ", ether.myip);
  ether.printIp("GW:  ", ether.gwip);  
  ether.printIp("DNS: ", ether.dnsip);  

  if (!ether.dnsLookup(website))
    Serial.println("DNS failed");
    
  ether.printIp("SRV: ", ether.hisip);
}

void loop () {
  ether.packetLoop(ether.packetReceive());
  
  if (millis() > timer) {
    timer = millis() + 5000;
    Serial.println();
    Serial.print("<<< REQ ");

    // ether.browseUrl(PSTR(dataLocationC), "", website, my_callback); // No funciona en IDE Standard
    ether.browseUrl(PSTR("/2434bc64"), "", website, my_callback);  // En entorno IDE
  }
}
