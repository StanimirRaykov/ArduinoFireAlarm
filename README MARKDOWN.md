Fire Alarm

![A picture containing plant Description automatically
generated](media/2aef790de06bd2cc0a8a39b8d79094c2.png)Станимир Райков, Стелиан
Грозев, Стоян Куцаров

**СЪДЪРЖАНИЕ**

Списък от компоненти...............................................3

Описание.......................................................................5

Блок схема....................................................................8

Електрическа схема....................................................9

Source код...................................................................10

Заключение.................................................................15

**СПИСЪК ОТ КОМПОНЕНТИ**

![Blue LCD Display I2C 16 x 2](media/ebe139473986a7cba842123fc22c3d83.png)![Air
Humidity Sensor - DHT \| MySensors - Create your own Connected Home 
Experience](media/46c057ffc8f20215baa39e470ef82e9d.png)![DEBO GAS2 MQ2:
Developer Boards - Gas Sensor, Gas & Smoke, MQ-2 at reichelt 
elektronik](media/3875e269b267851cba6a886a706e442d.png)![ARDUINO UNO REV3
A000066 ATMEGA328 - eshop-bg.com](media/c3e5a08a1dd02a3675d95fa45f6b2f73.png)** 

**

**СПИСЪК ОТ КОМПОНЕНТИ**

![30pcs 5mm Red Green Round LED Diode Lights Electronic Component Emitting 
Light 714998087997 \|
eBay](media/f6afb75ec6ef0401bea067edc246a71a.png)![PKM17EPPH4002-B0\|Piezoelectric
Sounders / Buzzers\|Sound Components (Buzzer)\| Murata Manufacturing Co.,
Ltd.](media/9ec2f2a8c3ec81436f55ff07242531dc.png)![Potentiometer \| Arduino
Projects](media/1890c9b147efe68499d94db0980abb2e.png)

![Tactiele button 12x12x7,3mm blue - 5 pcs -
Opencircuit](media/d9a63faf039ff7d745599e0809c6a8e8.png)![STECKBOARD S8: Slide
type breadboard, 840 holes at reichelt
elektronik](media/779b5de51ce3da7f4b110e47a1576294.png)**  
**

**ОПИСАНИЕ**

Проектът ни е пожарна аларма, засичаща промени в концентрацията на газове, дим и
температура в контролирана среда. За основа използваме Arduino Uno, а към
breadboard-a са свързани сензорите за газ и температура, LED диодите, buzzer-a,
потенциометърът и бутони за симулация на пожар и рестартиране на алармата.

![A picture containing text, electronics Description automatically
generated](media/fb53d94f745e5c3dbf038c9e54f7dd2e.png)

Когато сензорът засече голяма концентрация на газ подава повече волтаж към
ардуиното, което го изобразява като числова стойност. Забелязахме, че в
различните стаи нормалната концентрация на газове варира, за това добавихме
потенциометър, които променя границата на приемливи нива на газ.

![A picture containing graphical user interface Description automatically
generated](media/21a158a4761b2c2168098dd4568e61f0.jpeg)

За да не трябва да симулираме опасни обстановки по време на тестване, добавихме
бутон, който тества алармата, за да видим дали всичко работи нормално. Освен
това имаме бутон, който я деактивира за определено време.

На LCD дисплея постоянно се виждат нивата на температурата и газовете, за да
може да се направи преценка дали границата на ![Graphical user interface
Description automatically
generated](media/c289737eaa5bcea40b9a337a0502ef95.jpeg)приемливите нива газ
трябва да се променят.

Дисплея показва новото ниво на газ при промяна чрез потенциометъра. Когато
алармата се активира светва червения диод, текстът на дисплея се променя за да
покаже, че има опасност и buzzer-a издава звуков сигнал. Изключва се когато
газът се върне в приемливите граници или се изключи от съответния бутон.

**  
ЕЛЕКТРИЧЕСКА СХЕМА**

Това е електрическата схема на проекта ни. Тя включва вече описаните компоненти.
Някои от тях са малко по-различни от физическите компоненти, с които
разполагахме и заради това и кода на Tinkercad симулацията е по-различен, но
работещ.

**![Diagram, schematic Description automatically
generated](media/1e99baf9c0556aadbedf0a37ecadd682.png)**Link: [TinkerCad
Project](https://www.tinkercad.com/things/73Vmj3uctmr-fire-alarm/editel?sharecode=-ZLLZeEerQ_WBVAjuvz5LY760c4C4uISC7WW1tUkoZA)**

**

**![](media/1b6f6d35aa86781de7103a8c432b5b38.png)БЛОК СХЕМА**

**  
**

**SOURCE CODE**

![Free Download - Ink Arrow Png \| Full Size PNG Download \|
SeekPNG](media/1d3c6db00c8b3ce4d3b513abe0870ea1.png)Това е целият source code за
Arduino Fire Alarm. Всичко в него е описано чрез коментари и чрез тях също се
разбира за неговата функционалност.

**  
**

**ЗАКЛЮЧЕНИЕ**

Създадохме доста функионална пожарна аларма, но единствения значителен
недостатък, за който можем да се досетим е това, че алармата е направена върху
BreadBoard. Ако имахме достъп до 3D принтер можехме да направим кутия и да я
направим доста по-приятна за окото.

![A picture containing plant Description automatically
generated](media/2aef790de06bd2cc0a8a39b8d79094c2.png)
