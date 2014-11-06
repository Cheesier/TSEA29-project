TSEA29-project
==============

--------------------------- Kontrolcenter ---------------------------------------

Appen som används för debugning/test av KC finns på 
https://play.google.com/store/apps/details?id=at.rtcmanager&hl=en

Notera att för att ansluta till appen så måste man välja "make device visible" *I APPEN*, annars kommer man inte kunna ansluta eftersom appen kommer inte acceptera några inkommende anslutningar. Om det är fallet (ansluter inte efter mer än 5 sekunder), tryck "Cancel" och försök igen.

~~~~~~

De mesta parametrarna finns i "glob.h"

#define REMOTE_DEVICE_ADDRESS "10:D5:42:62:D5:41"
#define REMOTE_SERVICE_UUID "00001101-0000-1000-8000-00805f9b34fb"

BT-address för telefonen/roboten och service ID för appen (och roboten). I början så gjorde jag så att den skannar direkt för service id (och hittar/ansluter till den automatiskt), men det tog typ 30sec varje gång man skulle ansluta. Om det finns behov av scan-funktionen så fixar jag det, inte svårt under linux.
Notera att service ID "00001101-0000-1000-8000-00805f9b34fb" är specifikt till appen

TEXTMODE 
...
//used for testing -- converts char ('0' == 48 --> 0 ) values for msg size and type
//disable this when testing with the actual device
#define TEXTMODE
...
När man testar mot appen först (innan man gör en implementation till roboten så vill man kanske testa var som kommer ut och testa att skicka in mha appen. Därför kan det vara smedidigt att kunna se/läsa det. TEXTMODE gör headern läsligt. Notera följande exempel:

~~KC skickar meddelndet kör frammåt~~
header: Message::T_GO_FORWARD == 1
size: 0
payload: "" (tom)

encodade meddelandet:  char[] = {1,0} -- notera att den kan inte se eftersom char(1) och char(0)=='\0' motsvarar inga "riktiga" siffror

encodade meddelandet efter TEXTMODE : char[] = {1+'0',0+'0'} == {'1','0'} == "10"  <-- läslig i appen!

~~Vi vill skriva ut (echo) "test" i KC~~

header: Message::T_ECHO == 0
size: 4
payload: "test"

encodade meddelandet:  char[] = {0,4} + "test" == {0,4,'t','e','s','t'} <--- svårt att skriva in de första 2 tecken från appen!
encodade meddelandet efter TEXTMODE  char[] = {'0','4'} + "test" == {'0','4','t','e','s','t'} == "04test" <--inga problem att skriva[=

Notera att TEXTMODE har sina begränsningar och kan inte konvertera alla tal mellan 0-255 av uppenbara skäl och är endast avsedd att funka med appen

LINUX -- testa om ett riktigt OS används:)
#ifdef __linux__
#define LINUX
#endif 
