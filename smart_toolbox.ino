// Smart Toolbox Security Monitor
// Reed Switch + SW-420 Vibration Sensor

const int vibPin = 2;       // SW-420 digital output connected to D2
const int reedPin = 3;      // Reed switch connected to D3
const int buzzerPin = 8;    // Active buzzer connected to D8

void setup() {
  pinMode(vibPin, INPUT);
  pinMode(reedPin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);

  Serial.begin(9600);

  Serial.println("Close the toolbox to arm the security system.");

  // Wait until the toolbox is closed before arming the system.
  while (digitalRead(reedPin) == 1) {
    tone(buzzerPin, 2000);
    delay(100);

    noTone(buzzerPin);
    delay(100);

    Serial.println("Toolbox is OPEN. Please close it using the magnet.");
    delay(500);
  }

  noTone(buzzerPin);
  Serial.println("Toolbox CLOSED. Security system is ARMED.");
  delay(1000);
}

void loop() {
  int vib = digitalRead(vibPin);   // LOW indicates detected vibration
  int reed = digitalRead(reedPin); // HIGH = open, LOW = closed

  if (reed == 1) {
    Serial.println("!!! ALERT: TOOLBOX OPENED !!!");
    alarm();
  }
  else if (vib == 0) {
    Serial.println("!!! ALERT: VIBRATION DETECTED !!!");
    alarm();
  }
  else {
    Serial.println("Toolbox Secure.");
    delay(500);
  }
}

void alarm() {
  // Generate an alternating-tone alarm for approximately 3 seconds.
  for (int i = 0; i < 5; i++) {
    tone(buzzerPin, 1000);
    delay(300);

    tone(buzzerPin, 1800);
    delay(300);
  }

  noTone(buzzerPin);
}
