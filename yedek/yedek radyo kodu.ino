///Arduino FM Radio
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <TEA5767Radio.h>

LiquidCrystal_I2C lcd(0x27,16,2);//A4 and A5 Arduino port for SLC adn SLA
TEA5767Radio radio = TEA5767Radio();

double frequency = 87.5;
double frequency_pt = 87.5;

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  lcd.begin ();
  lcd.setCursor(0, 0);
  lcd.print("Arduino FM Radio");
  Serial.println("Arduino FM Radio ");
}

void loop()
{
  
  int value_pot = analogRead(A0); //Potansiyometre bilgisi

  //Frekans hesaplaması
  frequency = ((double)value_pot * (108.0 - 87.5)) / 1024.0 + 87.5;
  frequency = ((int)(frequency * 10)) / 10.0;

  // Frekans değişikliğinin ekranda gösterilmesi
  if (frequency_pt != frequency)
  {
    lcd.setCursor(0, 1);
    lcd.print("Freq: ");
    lcd.setCursor(6, 1);
    lcd.print("     MHz");
    lcd.setCursor(6, 1);
    lcd.print(frequency, 1);
    Serial.print("Frequency: ");
    Serial.println(frequency);
    radio.setFrequency(frequency);
    frequency_pt = frequency;
  }
}
