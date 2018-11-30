#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>
#include <FS.h>

#define LED_RED     12 // D6
#define LED_GREEN   13 // D7
#define LED_BLUE    15 // D8

const char* ssid = "ssid"; // имя вашей сети
const char* password = "password"; // пароль вашей сети

IPAddress Ip(192,168,1,10); //IP-адрес для ESP8266
IPAddress Gateway(192,168,1,1); // IP-адрес шлюза (роутера)
IPAddress Subnet(255,255,255,0); // маска подсети, диапазон IP-адресов в локальной сети

//инициализация websockets на 81 порту и веб-сервера
WebSocketsServer webSocket(81); //создаем объект webSocket
ESP8266WebServer server(80);

void setup(){
  Serial.begin(9600);

  WiFi.config(Ip, Gateway, Subnet); //настройка конфигураций вашей сети
  WiFi.begin(ssid, password);
  Serial.println("");

//повторяем запрос подключения
  while (WiFi.status() != WL_CONNECTED){ 
    delay(500);
    Serial.print(".");
   }

    Serial.print("IP address: ");
    Serial.println(WiFi.localIP()); 

//    server.on("/", [](){server.send(200, "text/html", WebPage);});

    server.onNotFound([](){
    if(!handleFileRead(server.uri()))//при неудачном чтении файла отправляем клиенту код ошибки
      server.send(404, "text/plain", "FileNotFound");
    });

    server.begin();

    SPIFFS.begin();

    webSocket.begin();
    webSocket.onEvent(webSocketEvent); //метод onEvent вызывает функцию webSocketEvent при получении данных через WebSocket    
}

void loop() {
  //обработка входящих запросов HTTP или WebSockets
    webSocket.loop();
    server.handleClient();
}

//функция обработки входящих сообщений
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length){
  
   if(type == WStype_CONNECTED){
      IPAddress ip = webSocket.remoteIP(num); 
    }
    
     if(type == WStype_TEXT){
      if(payload[0] == '#'){
        
        //преобразуем в 24 битное цветовое число
        uint32_t rgb = (uint32_t) strtol((const char *) &payload[1], NULL, 16);

        Serial.println(rgb);

        //регулируем яркость ШИМ сигналом
        //преобразуем 24 бит по 8 бит на канал 
        analogWrite(LED_RED, abs(0 + (rgb >> 16) & 0xFF));
        analogWrite(LED_GREEN, abs(0 + (rgb >>  8) & 0xFF));
        analogWrite(LED_BLUE, abs(0 + (rgb >>  0) & 0xFF));
   
      }
   } 
}

// функция принимает URL-адрес и ищет файл в файловой системе
// затем отправляет его
bool handleFileRead(String path){
  if(path.endsWith("/")) path += "index.html";
  if(SPIFFS.exists(path)){
    File file = SPIFFS.open(path, "r");
    size_t sent = server.streamFile(file, "text/html");
    file.close();
    return true;
  }
  return false;
}
