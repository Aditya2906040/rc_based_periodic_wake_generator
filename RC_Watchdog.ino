#define LED 5
#define WAKE_PIN 33 // ext0, single pin wakeup
#define DISCHARGE_PIN 25

void setup()
{
  Serial.begin(115200);

  Serial.println("Booting...");

  pinMode(LED, OUTPUT);
  pinMode(WAKE_PIN, INPUT_PULLUP); // trigger is when pin is LOW
                                   // thus pullup

  // Do work
  for (int i = 0; i < 5; i++)
  {
    digitalWrite(LED, HIGH);
    delay(50);
    digitalWrite(LED, LOW);
    delay(50);
  }

  delay(50);

  Serial.println("Discharging capacitor...");

  // Discharge RC node
  pinMode(DISCHARGE_PIN, OUTPUT); // for discharge
  digitalWrite(DISCHARGE_PIN, LOW);
  delay(1000); // important for completely letting the capacitor discharge.

  // Release node
  pinMode(DISCHARGE_PIN, INPUT);
  delay(200); // allow pin to stabilize HIGH

  Serial.print("WAKE PIN: ");
  Serial.println(digitalRead(WAKE_PIN)); // should be 1 as LOW is wakeup

  Serial.println("Sleeping...");

  digitalWrite(LED, LOW);

  esp_sleep_enable_ext0_wakeup(GPIO_NUM_33, 0); // set pin33 as ext0 i.e. single pin wakeup
  esp_deep_sleep_start();                       // go to sleep.
}

void loop() {}
