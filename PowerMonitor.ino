// TODO : Add a Fancy Boot Logo
// TODO : Add PushButtons to change settings

// I2C addresses -> use the i2c_scanner demo to get the addresses
// 0x3C ---> OLED
// 0x40 ---> INA219

#include <Wire.h>
#include <INA219.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define BAUD 115200

#define OLED_RESET 4
#define OLED_I2C_ADDR 0x3C



#define SHUNT_MAX_V 0.04  /* Rated max for our shunt is 75mv for 50 A current: 
                             we will mesure only up to 20A so max is about 75mV*20/50 lets put some more*/
#define BUS_MAX_V   16.0  /* for the first trial 16 V seems okay*/
#define MAX_CURRENT 20    /* In our case this is enough even shunt is capable to 50 A*/
#define SHUNT_R   0.1   /* Shunt resistor in ohm, what the resistor show : R100 */

INA219 monitor;
Adafruit_SSD1306 display(OLED_RESET); 
unsigned long power;

void setup() {
  // For Debug only
  Serial.begin(BAUD);
  
  // init global variables
  power = 0;
  
  // init and configure the INA219 sensor
  monitor.begin();
  monitor.configure(INA219::RANGE_16V, INA219::GAIN_2_80MV, INA219::ADC_64SAMP, INA219::ADC_64SAMP, INA219::CONT_SH_BUS);
  monitor.calibrate(SHUNT_R, SHUNT_MAX_V, BUS_MAX_V, MAX_CURRENT);
  
  // init the OLED
  // Please do not forget to modify the Adafruit_SSD1306 library for the proper OLED setup
  display.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDR);
  display.display();
  // erease display 
  display.clearDisplay();
  
}

void loop() {
  // Loop starts
  Serial.print("raw shunt voltage: ");
  Serial.println(monitor.shuntVoltageRaw());
  
  Serial.print("raw bus voltage:   ");
  Serial.println(monitor.busVoltageRaw());
  
  Serial.println("--");
  
  Serial.print("shunt voltage: ");
  Serial.print(monitor.shuntVoltage() * 1000, 4);
  Serial.println(" mV");
  
  Serial.print("shunt current: ");
  Serial.print(monitor.shuntCurrent() * 1000, 4);
  Serial.println(" mA");
  
  Serial.print("bus voltage:   ");
  Serial.print(monitor.busVoltage(), 4);
  Serial.println(" V");
  
  Serial.print("bus power:     ");
  Serial.print(monitor.busPower() * 1000, 4);
  Serial.println(" mW");
  
  Serial.println(" ");
  Serial.println(" ");
  
  delay(1000); 
}
