# Template-ECU-of-an-Electricity-Car
Taslak-TÜBİTAK EFFICIENCY CHALLANGE yarışması için Elektrikli Araçların Araç Kontrol Sistemi
Template-Electricity Car ECU for TÜBİTAK EFFICIENCY CHALLANGE

TR

Herkese merhaba arkadaşlar. 2023 Senesinde yapmış olduğum ECU taslak çalışmalarını gelecekte yarışacak gerek üniversite gerek de lise öğrencileri için taslak olması ve fikir almaları için burada paylaşmak istiyorum. Çünkü Bilginin paylaştıkça çoğalacağını biliyorum.
Özellikler:

-Bilgisayar ile Veri Haberleşmesi ve verilerin kaydedilmesi
-Gösterge Paneli
-Hücrelerin Voltaj Okuması
-Hücrelerin Sıcaklık Okuması
-Batarya Kapasitesi Ölçümü
-Şarj Gücü Ölçümü
-Kritik Sıcaklık tespiti ve önlenmesi
-CanBUS sistemi ile silecek-korna vs çalıştırma


Genel olarak(adet olmadan) Malzemeler:

-MCP2515

-LoRa E32

-Arduino Mega 2560

-Arduino Uno R3

-DS18B20 Sıcaklık Sensörü

-CD74HC4067 4 Bit MUX

-Fan

-Buzzer

-Kontaktör

-Nextion Ekran (P043)


Arduino MEGA 2560 LoRa, Nextion, Sıcaklık ve Voltaj okuma, Fan, Buzzer, Kontaktör görevlerinde;

Arduino Uno R3 ise CanBus Sistemi için kullanılmıştır. CanBUS için MCP2515 kullanılmıştır. CanBUS'ta sadece röle kontrolü yapılmaktadır.

Voltaj okuma Opamplarla filtrelenip yapılmaktadır. Bataryamız 17 Seriydi. Arduinoya 17 tane bağlantı yapmak yerine MUX 'a bağlayıp tek bağlantı ile işi çözdük.

Sıcaklık Sensörü de aynı şekilde birden fazla pin kullanmaktansa tek pine indirilmiştir. Fakat bu sefer OneWire.h kütüphanesi kullanılarak yapılmıştır.

Tek işlemci ile çok fazla görev yüklenmesi olduğundan belli gecikmeler meydana gelmişti. Bu da haberleşme Sistemi LORA'nın verileri yakalayamaması ile sonuçlandı. Farklı yerlere delay(lar) eklememe rağmen çözememiştim.
