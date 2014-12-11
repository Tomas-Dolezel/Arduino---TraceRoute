/*
  Ping Example
 
 This example sends an ICMP pings every 500 milliseconds, sends the human-readable
 result over the serial port. 

 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 
 created 30 Sep 2010
 by Blake Foster
 
 modified 11 Dec 2014
 by Tomas Dolezel
 In this example reduced TTL value to get on road router IP
 (
 
 */

#include <SPI.h>         
#include <Ethernet.h>
#include <PingTrace.h>

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED}; // max address for ethernet shield
EthernetClient client; // Initialize the Ethernet client library, get IP  from DHCP
IPAddress pingAddr(81,201,48,195); // ip address to ping

SOCKET pingSocket = 0;

char buffer [256];
ICMPPing ping(pingSocket, (uint16_t)random(0, 255));

void setup() 
{
  // start Ethernet
  Ethernet.begin(mac);
  Serial.begin(9600);
}

void loop()
{
  ICMPEchoReply echoReply = ping(pingAddr, 1, 4); // ping(ping adress, retries, time to live = hops)
 // if (echoReply.status == SUCCESS)  // cannot be used when router respond TIME EXCEEDED (TTL value equals 0) becouse you get BAD_RESPONSE value
  {
    sprintf(buffer,
            "Reply[%d] from: %d.%d.%d.%d: bytes=%d time=%ldms TTL=%d Status=%d",
            echoReply.data.seq,  // sequence is always 0 when BAD_RESPONSE status
            echoReply.addr[0],
            echoReply.addr[1],
            echoReply.addr[2],
            echoReply.addr[3],
            REQ_DATASIZE,
            millis() - echoReply.data.time, // time is working for both PING and TraceRoute (TLL=0) router response
            
            
            echoReply.ttl,   // TTL equals set TTL when TraceRoute(TLL=0) router response
            echoReply.status); // Equals 0 for Ping and 3 for TraceRoute(TLL=0) router response
  }
  //else
 // {
//  sprintf(buffer, "Echo request failed; %d", echoReply.status);
 // }
  Serial.println(buffer);
  delay(10000);
}









