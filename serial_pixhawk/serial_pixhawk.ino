#include <mavlink.h>
#include <SoftwareSerial.h>

SoftwareSerial pixhawk(0, 1); // RX, TX

void setup()  {
  // define pin modes for tx, rx:
  pinMode(0, INPUT);
  pinMode(1, OUTPUT);
  // set the data rate for the SoftwareSerial port
  pixhawk.begin(57600);
  Serial.begin(57600);
}

void loop() {

  mavlink_status_t status;
  mavlink_message_t msg;
  int chan = MAVLINK_COMM_0;
  
  while(pixhawk.available() > 0)
  {
    uint8_t byte = pixhawk.read();
    if (mavlink_parse_char(chan, byte, &msg, &status))
    {
    Serial.print("Received message with ID ");
    Serial.print(msg.msgid);
    Serial.print(" sequence: ");
    Serial.print(msg.seq);
    Serial.print(" from component ");
    Serial.print(msg.compid);
    Serial.print(" of system ");
    Serial.println(msg.sysid);
    // ... DECODE THE MESSAGE PAYLOAD HERE ...
    }
  }
}

