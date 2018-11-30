# Управление RGB лентой на ESP8266 через Web интерфэйс
![photo](http://www.imageup.ru/img25/3225605/esprgb.jpg)
## Описание проекта
##### Управление:
* Из любого устройства умеющий на борту WIFI
либо подключенные через Ethernet кабель

##### Особенности:
- Используется протокол `Websocket`
- Длительность срабатывания не более `200мс`
- Возможность асинхронного управления
- Удобный colorpicker
- Плавная смена цветов

## Материалы и компоненты
- ESP8266
- RGB-светодиодная лента
- Три NPN-транзистора 2N2222 (или эквиваленты)
- Три резистора на 1кОм
- 12-вольтовый источник питания
- Провода-перемычки
- Один из последних версий Arduino IDE вместе с :
   - [Пакеты для ESP8266](https://github.com/esp8266/Arduino)
   - [ESP8266FS плагин файловой системы](https://github.com/esp8266/arduino-esp8266fs-plugin) (используется для загрузки HTML, JS, CSS файлов в ESP)
    - Библиотека Websockets (доступно из менеджера библиотек)
## Схема подключения
![scheme](http://www.imageup.ru/img25/3224933/esp-rgb.jpg)
## Установка
- Подключить ESP8266 к вашему компьютеру
- Открыть `ESP8266-RGB.ino` и обновить сетевые настройки для вашей сети 
- Загрузить скетч
- В верхнем меню IDE выберите инструменты - > ESP8266 Sketch Upload, чтобы загрузить веб-файлы из каталога `data`.
- Откройте монитор последовательного порта (при успешном подключении отобразиться ваш IP).
- Перейдите по IP-адресу
