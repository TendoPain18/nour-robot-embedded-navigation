// Ultrasonic Sensor Pins
const int trig1 = 7;
const int echo1 = 8;

const int trig2 = 9;
const int echo2 = 10;

const int trig3 = 11;
const int echo3 = 12;

const int outputPin = 4;  // Output pin (5V signal)

long readDistanceCM(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000); // Timeout after 30ms
  long distance = duration * 0.034 / 2; // Convert to cm
  return distance;
}

void setup() {
  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);

  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);

  pinMode(trig3, OUTPUT);
  pinMode(echo3, INPUT);

  pinMode(outputPin, OUTPUT);
  digitalWrite(outputPin, LOW);

  Serial.begin(9600); // Start Serial Monitor
}

void loop() {
  long d1 = readDistanceCM(trig1, echo1);
  delay(50);

  long d2 = readDistanceCM(trig2, echo2);
  delay(50);

  long d3 = readDistanceCM(trig3, echo3);
  delay(50);

  bool triggerOutput = (d1 < 30 || d2 < 30 || d3 < 30);
  digitalWrite(outputPin, triggerOutput ? HIGH : LOW);

  // Print distances and output state in one row
  Serial.print("D1: ");
  Serial.print(d1);
  Serial.print(" cm, D2: ");
  Serial.print(d2);
  Serial.print(" cm, D3: ");
  Serial.print(d3);
  Serial.print(" cm => Output: ");
  Serial.println(triggerOutput ? "HIGH" : "LOW");

  delay(200);
}
