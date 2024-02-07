#define D10_PIN_INDEX 0 
#define D11_PIN_INDEX 1
#define D12_PIN_INDEX 2

#define NTC_BETA 3950

unsigned int pinMux = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Hello, STM32!");
  pinMode(D10, OUTPUT);
  pinMode(D11, OUTPUT);
  pinMode(D12, OUTPUT);
}

void set(int x, int y){
    unsigned int pin_value = y > 0 ? HIGH : LOW;

    switch(x){
      case D10_PIN_INDEX:
        digitalWrite(D10, pin_value);
      break;

      case D11_PIN_INDEX:
        digitalWrite(D11, pin_value);
      break;

      case D12_PIN_INDEX:
        digitalWrite(D12, pin_value);
      break;

      default:
        break;
    
    }

    if(pin_value == HIGH){
      unsigned int pin_to_set = 1 << (D12_PIN_INDEX - x);
      pinMux = pinMux | pin_to_set;
    }
    else{
      unsigned int pin_to_clear = ~ (1 << (D12_PIN_INDEX - x));
      pinMux = pinMux & pin_to_clear;
    }

    Serial.println("Valor dos pinos: ");
    Serial.println(pinMux, BIN);
}

void loop() {
  // put your main code here, to run repeatedly:
  set(D12_PIN_INDEX, 1);
  delay(250); // this speeds up the simulation
  set(D12_PIN_INDEX, 0);
  delay(2500);

  set(D11_PIN_INDEX, 1);
  delay(250); // this speeds up the simulation
  set(D11_PIN_INDEX, 0);
  delay(250);

  set(D10_PIN_INDEX, 1);
  delay(250); // this speeds up the simulation
  set(D10_PIN_INDEX, 0);
  delay(250);

  int leituraNTC = analogRead(A0);
  float celsius = 1 / (log(1 / (1023. / leituraNTC - 1)) / NTC_BETA + 1.0 / 298.15) - 273.15;

  Serial.print("Temperatura: ");
  Serial.println(celsius, DEC);

  int leituraPOT = analogRead(A1);

  Serial.print("Potenciometro: ");
  Serial.println(leituraPOT, DEC);
}
