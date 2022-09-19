
#define LOG_OUT 1 // use the log output function
#define FHT_N 256  // set to 256 point fht
#include <FHT.h>
#define MIC_PIN 0
#define LOW_PASS 20        // нижний порог чувствительности шумов (нет скачков при отсутствии звука)
#define VOL_THR 25        // порог тишины (ниже него отображения на матрице не будет)

#include <GyverOLED.h>

GyverOLED<SSD1306_128x64, OLED_BUFFER> oled;

#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))

byte gain = 80;   // усиление по умолчанию
unsigned long gainTimer;
byte maxValue=100, maxValue_f;
float k = 0.3;

void setup() {
  oled.init();
  sbi(ADCSRA, ADPS2);
  cbi(ADCSRA, ADPS1);
  sbi(ADCSRA, ADPS0);
  oled.clear();
  analogReference(EXTERNAL);
}

void loop() {
  for (int i = 0 ; i < FHT_N ; i++) {
    int sample = analogRead(MIC_PIN);
    fht_input[i] = sample; // put real data into bins
  }
  fht_window();  // window the data for better frequency response
  fht_reorder(); // reorder the data before doing the fht
  fht_run();     // process the data in the fht
  fht_mag_log(); // take the output of the fht


  oled.clear();
  int steps = 0 , sum = 0;
  for (int curBin = 0; curBin < FHT_N / 2; ++curBin) {
    if (steps < 4){
      sum += fht_log_out[curBin];
      steps += 1;
    }else{
      int middleValue = sum/4;
      oled.rect(curBin-2, 64, curBin+2, 64-map(middleValue, LOW_PASS, gain, 0, 60));
      //oled.line(curBin-2, 64, curBin-2, 64-map(middleValue, LOW_PASS, gain, 0, 120));
      if (middleValue > maxValue) maxValue = middleValue;
      steps = 0;
      sum = 0;
    }
  }
  oled.home();
  oled.print(maxValue);
  oled.update();

  maxValue_f = maxValue * k + maxValue_f * (1 - k);
  if (millis() - gainTimer > 1500) {      // каждые 1500 мс
    
    if (maxValue_f > VOL_THR) gain = maxValue_f; // если максимальное значение больше порога, взять его как максимум для отображения
    else gain = 100;  // если нет, то взять порог побольше, чтобы шумы вообще не проходили
    gainTimer = millis();
  }
}
