#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

int muestreo = 0;
int IRED = 2;

int retardo_1 = 280;
int retardo_2 = 40;
int retardo_3 = 9680;

int valor = 0;
float ppm = 0;
float voltaje = 0;
float densidad_polvo = 0;
float ppm_real = 0;
int i=0;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("  DETECTOR  DE  ");
  lcd.setCursor(0,1);
  lcd.print("PARTICULAS POLVO");
  delay(3000);
}
void loop() {
   i=i+1;
    digitalWrite(IRED,LOW);
    delayMicroseconds(retardo_1);
    valor = analogRead(muestreo);
    ppm = ppm + valor;
    delayMicroseconds(retardo_2);
    digitalWrite(IRED,HIGH);
    delayMicroseconds(retardo_3);
    voltaje = ppm/i*0.0049;
    densidad_polvo = (0.17*voltaje)-0.1;
    Serial.println(densidad_polvo);
    ppm_real = (voltaje-0.0356)*120000;
    if (ppm_real < 0)
      ppm_real = 0;
    if (densidad_polvo < 0 )
      densidad_polvo = 0;
    if (densidad_polvo > 0.5)
      densidad_polvo = 0.5;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("-> VOLTAJE");
    lcd.setCursor(0,1);
    lcd.print(voltaje,3);
    lcd.print(" V");
    delay(2000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("-> CONCENTRACION");
    lcd.setCursor(0,1);
    lcd.print(ppm_real,3);
    lcd.print(" ppm");
    delay(2000);

    String calitat;
    if(ppm_real < 75000) {
      calitat = "Excelente";
    } else if(ppm_real < 150000) {
      calitat = "Muy buena";
    } else if(ppm_real < 300000) {
      calitat = "Buena";
    } else if(ppm_real < 1050000) {
      calitat = "Aceptable";
    } else if(ppm_real < 3000000) {
      calitat = "Pobre";
    } else {
      calitat = "Muy pobre";
    }
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("-> CALIDAD AIRE");
    lcd.setCursor(0,1);
    lcd.print(calitat);
    delay(2000);
}
