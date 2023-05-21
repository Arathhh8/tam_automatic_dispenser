#include <Keypad.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


const int relePin = 10;  // Pin digital al que está conectado el relé
const byte FILAS = 4;        // Número de filas del teclado
const byte COLUMNAS = 4;     // Número de columnas del teclado

#define OLED_ADDR 0x3C  // Dirección I2C de la pantalla OLED

Adafruit_SSD1306 display(128, 64, &Wire, -1);  // Inicializar la pantalla OLED

byte filasPines[FILAS] = {9, 8, 7, 6};
byte columnasPines[COLUMNAS] = {5, 4, 3, 2};

#define btn_on 12
#define btn_off 13

// Define la disposición de las teclas en el teclado
char teclas[FILAS][COLUMNAS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

Keypad teclado = Keypad(makeKeymap(teclas), filasPines, columnasPines, FILAS, COLUMNAS);

void setup() {
  pinMode(relePin, OUTPUT);  // Configurar el pin del relé como salida
  pinMode(btn_on, INPUT);
  pinMode(btn_off, INPUT);
  Serial.begin(9600);        // Iniciar la comunicación serial a 9600 baudios

    // Iniciar la comunicación I2C
  Wire.begin();
  
  // Iniciar la pantalla OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println("No se pudo iniciar la pantalla OLED");
    while (1);
  }

  // Borrar la pantalla
  display.clearDisplay();
  

}

void loop() {

  char tecla = teclado.getKey();

  if (tecla != NO_KEY && (tecla == '1' || tecla == '2' || tecla == '3' || tecla == '4')) {
    Serial.println(tecla);  // Imprimir la tecla presionada en el monitor serial

    if(digitalRead(btn_on) == HIGH){
      Serial.println("LLENANDO SUAVITEL");
      digitalWrite(relePin, LOW);  // Activar el relé (conexión del circuito)
      Serial.println("Relé encendido");  // Imprimir mensaje cuando se enciende el relé
        // Mostrar un mensaje de bienvenida en la pantalla
      display.setTextSize(2);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(20, 10);
      display.println("Llenando");
      display.display();
      delay(3000); 
  }
    digitalWrite(relePin, HIGH);   // Desactivar el relé (desconexión del circuito)
    display.clearDisplay();
  }
}
