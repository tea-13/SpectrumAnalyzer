![project_photo](plug.jpg)


# Графический анализатор аудио спектра на Arduino

## Оглавление
* [Возможности проекта](#chapter-1)
* [Детали и ссылки на покупку](#chapter-2)
* [Схема и подключение](#chapter-3)
* [TODO](#chapter-4)

<a id="chapter-1"/>
## Возможности проекта
### TODO

<a id="chapter-2"/>
## Детали и ссылки на покупку
+ Arduino Nano [ссылка](https://clck.ru/324jT7)
+ Oled display 128x64 [ссылка](https://clck.ru/324jUr)
+ MAX9814 [ссылка](https://clck.ru/324jX3)
+ WS2812B [ссылка](https://clck.ru/324jZh)
+ резисторы
	+ 10к **Ω** 3шт
	+ 200 **Ω** 1шт
<a id="chapter-3"/>
## Схема подключения
![scheme](schemes/scheme.png)

| Arduino | MAX9814 |
| ------- | ------- |
| A0 | Out |
| +5v | Vdd |
| GND | GND |

| Arduino | Oled Display |
| ------- | ------------ |
| GND | GND |
| +5v | VDD |
| A5 | SCL |
| A4 | SDA |

| Arduino | WS2812B |
| ------- | ------- |
| +5v | +5v |
| GND | GND |
| D11 | D1 |
<a id="chapter-4"/>
## TODO
