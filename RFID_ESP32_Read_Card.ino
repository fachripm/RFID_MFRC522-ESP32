/* ESP32_TIPE-C + RFID RC522
~RFID PIN :
 [ SS   = 5    ]
 [ SCK  = 18   ]
 [ MOSI = 23   ]
 [ MISO = 19   ]
 [ IRQ  = -    ]
 [ GND  = GND  ]
 [ RST  = 27   ]
 [ VCC  = 3.3V ]
*/

#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN  5  // RFID GPIO5 
#define RST_PIN 27 // RFID GPIO27 

MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(115200);
  SPI.begin(); // init SPI bus
  rfid.PCD_Init(); // init MFRC522

  Serial.println("Tap an RFID/NFC tag on the RFID-RC522 reader");
}

void loop() {
  if (rfid.PICC_IsNewCardPresent()) { // new tag is available
    if (rfid.PICC_ReadCardSerial()) { // NUID has been readed
      MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
      Serial.print("RFID/NFC Tag Type: ");
      Serial.println(rfid.PICC_GetTypeName(piccType));

      // print UID in Serial Monitor in the hex format
      Serial.print("UID:");
      for (int i = 0; i < rfid.uid.size; i++) {
        Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
        Serial.print(rfid.uid.uidByte[i], HEX);
      }
      Serial.println();
      Serial.println(" ");
      
      rfid.PICC_HaltA(); // halt PICC
      rfid.PCD_StopCrypto1(); // stop encryption on PCD
    }
  }
  delay(500);
}
