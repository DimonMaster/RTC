#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);
#include <microDS3231.h>
MicroDS3231 rtc;
void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
}
void loop() {
  String clock;
  clock += String(rtc.getHours());
  clock += ":";
  clock += String(rtc.getMinutes());
  clock += ":";
  clock += String(rtc.getSeconds());
  lcd.setCursor(0,0);
  lcd.print(clock);

  String date;
  date += String(rtc.getDate());
  date += ".";
  date += String(rtc.getMonth());
  date += ".";
  date += String(rtc.getYear());
  lcd.setCursor(0,1);
  lcd.print(date);
 
}