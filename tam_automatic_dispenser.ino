#include <Keypad.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const int relayPin = 10;  
const byte ROWS = 4; 
const byte COLS = 4; 

#define OLED_ADDR 0x3C     // I2C address of the OLED display

Adafruit_SSD1306 display(128, 64, &Wire, -1);  // Initialize the OLED display

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

#define btn_on 12
#define btn_off 13

// Layout keypad 
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  pinMode(relayPin, OUTPUT); 
  pinMode(btn_on, INPUT);
  pinMode(btn_off, INPUT);
  Serial.begin(9600); 
  
  // Initialize I2C communication
  Wire.begin();
  
  // Initialize the OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println("Failed to initialize OLED display");
    while (1);
  }

  display.clearDisplay();
}

void loop() {
  char key = keypad.getKey();

  if (key != NO_KEY && (key == '1' || key == '2' || key == '3' || key == '4')) {
    Serial.println(key);  

    if (digitalRead(btn_on) == HIGH) {
      Serial.println("FILLING SOFTENER");
      digitalWrite(relayPin, LOW);  // Activate the relay 
      Serial.println("Relay turned ON");  
      
      // Display shows "Filling" when btn_on is pressed 
      display.setTextSize(2);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(20, 10);
      display.println("Filling");
      display.display();
      delay(3000);
    }
    
    digitalWrite(relayPin, HIGH);  
    display.clearDisplay();
  }
}
