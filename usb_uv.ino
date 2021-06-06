#define PIN_HOUT A1
#define PIN_LOUT A2
#define INTERVAL 1000
#define AVE_WINDOW 100 // 1〜100
#define STATUS_OK 0
#define VERSION "1.00"

void setup()
{
  Serial.begin(9600);
  while (!Serial)
    ;
  delay(100);
}

void loop()
{
  uint32_t u32_val_high = 0;
  uint32_t u32_val_low = 0;
  uint32_t u32_val_result = 0;
  static uint32_t su32_val_sum = 0;
  static uint32_t su32_loop = 0;

  if ((AVE_WINDOW) > su32_loop)
  {
    u32_val_high = analogRead(PIN_HOUT);
    u32_val_low = analogRead(PIN_LOUT);
    if (u32_val_high >= u32_val_low)
    {
      su32_val_sum += (u32_val_high - u32_val_low);
      //      Serial.println(su32_val_sum);
      su32_loop++;
    }
  }
  else
  {
    u32_val_result = ((float)su32_val_sum / 1024) * 5 * 1000 / AVE_WINDOW;
    Serial.print("uv=");
    Serial.print(u32_val_result);
    Serial.print(";status=");
    Serial.print(STATUS_OK);
    Serial.print(";version=");
    Serial.print(VERSION);
    Serial.print("\n");
    u32_val_result = 0;
    su32_val_sum = 0;
    su32_loop = 0;
  }

  delay((uint32_t)(INTERVAL / AVE_WINDOW));
}
