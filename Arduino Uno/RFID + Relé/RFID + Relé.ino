//sistema de controle de entrada e saida
#include <SPI.h>
#include <MFRC522.h>
  
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Cria a instacia do  MFRC522.
 
void setup() 
{
  Serial.begin(9600);   // Inicia a saida serial
  SPI.begin();      // Inicia  SPI bus
  mfrc522.PCD_Init();   // Inicia a modulo MFRC522
  Serial.println("Aproxime seu cartão da leitora para liberação...");
  Serial.println();
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
}
 
void loop() 
{
  // começa procura por cartão
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Seleciona o cartao RFID
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Mostra informações do cartão na serial
  Serial.print("UID da tag :");
  String conteudo= "";
  byte letra;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Mensagem : ");
  conteudo.toUpperCase();
 
  if (conteudo.substring(1) == "37 26 91 7A") //UID 1 - chaveiro
    {
    Serial.println("seja bem vindo Antonio");
     Serial.println();
    digitalWrite(2, HIGH); // ativa rele e abre a trava solenoide
    delay(3000);           // espera 3 segundos
    digitalWrite(2, LOW);  // desativa rele e fecha a trava solenoide
    }
    else 
    {
    digitalWrite(3, HIGH);
    delay(1000);
    digitalWrite(3, LOW); 
    delay(1000);
    digitalWrite(3, HIGH); 
    digitalWrite(3, LOW) ;
    }
}
