#include <Arduino.h>

// // Project 1 ESP32 Inputs Outputs
// // put function declarations here:
// int myFunction(int, int);

// const int buttonPin = 4;
// const int ledPin = 5;
// int buttonState = 0;

// void setup()
// {
//   // put your setup code here, to run once:
//   // int result = myFunction(2, 3);
//   Serial.begin(115200);
//   pinMode(buttonPin, INPUT);
//   pinMode(ledPin, OUTPUT);
// }

// void loop()
// {
//   // put your main code here, to run repeatedly:
//   buttonState = digitalRead(buttonPin);
//   // Serial.println(buttonState);
//   if(buttonState == HIGH){
//     digitalWrite(ledPin, HIGH);
//   }else{
//     digitalWrite(ledPin, LOW);
//   }
// }

// // put function definitions here:
// int myFunction(int x, int y)
// {
//   return x + y;
// }

// // Project 2 ESP32 Analog Inputs
// const int potPin = 4;
// int potValue = 0;

// void setup(){
//     Serial.begin(115200);
//     delay(1000);
// }

// void loop(){
//     potValue = analogRead(potPin);
//     Serial.println(potValue);
//     delay(500);
// }

// // Project 3 ESP32 PWM
// const int ledPin = 5;
// const int freq = 5000; // 5000Hz
// const int ledChannel = 0;
// const int resolution = 8;

// void setup(){
//     ledcSetup(ledChannel, freq, resolution);
//     ledcAttachPin(ledPin, ledChannel);
// }

// void loop(){
//     for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){
//         ledcWrite(ledChannel, dutyCycle);
//         delay(15);
//     }
//     for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--){
//         ledcWrite(ledChannel, dutyCycle);
//         delay(15);
//     }
// }

// // Project 3_1 ESP32 PWM and Analog Inputs
// const int potPin = 4;
// int potValue = 0;
// int dutyCycle = 0;

// const int ledPin = 5;
// const int freq = 5000; // 5000Hz
// const int ledChannel = 0;
// const int resolution = 8;

// void setup(){
//     Serial.begin(115200);
//     ledcSetup(ledChannel, freq, resolution);
//     ledcAttachPin(ledPin, ledChannel);
// }

// void loop(){
//     potValue = analogRead(potPin);
//     dutyCycle = (potValue*1.0/4095)*255;
//     ledcWrite(ledChannel, dutyCycle);
//     // Serial.printf("potValue: %d, ledValue: %d\r\n", potValue, dutyCycle);
//     delay(15);
// }



// // Project 3_2 ESP32 PWM and servo
// // https://blog.csdn.net/yushuir/article/details/126479016
// int freq = 50;      // 1/50秒，50Hz的频率，20ms的周期，这个变量用来存储时钟基准。
// int channel = 8;    // 通道(高速通道（0 ~ 7）由80MHz时钟驱动，低速通道（8 ~ 15）由 1MHz 时钟驱动。)
// int resolution = 8; // 分辨率设置为8，就是2的8次方，用256的数值来映射角度，看下方的占空比函数。
// const int led = 13;

// int calculatePWM(int degree) //定义函数用于输出PWM的占空比
// { //0-180度
//  //20ms周期内，高电平持续时长0.5-2.5ms，对应0-180度舵机角度，参考上面的180度对应图。
//   const float deadZone = 6.4;//对应0.5ms（0.5ms/(20ms/256）)
//   const float max = 32;//对应2.5ms（2.5ms/（20ms/256））
//   if (degree < 0)
//     degree = 0;
//   if (degree > 180)
//     degree = 180;
//   return (int)(((max - deadZone) / 180) * degree + deadZone); //返回度数对应的高电平的数值
// }

// void setup()
// {
//   Serial.begin(115200);
//   ledcSetup(channel, freq, resolution); // 用于设置 LEDC 通道的频率和分辨率。
//   ledcAttachPin(led, channel);          // 将通道与对应的引脚连接
// }

// void loop()
// {
//   for (int d = 0; d <= 180; d += 10)
//   {
//     ledcWrite(channel, calculatePWM(d)); // 输出PWM，设置 LEDC 通道的占空比。
//     Serial.printf("value=%d,calcu=%d\n", d, calculatePWM(d));
//     delay(1000);
//   }
// }

// Project 3_3 ESP32 Analog Input and Servo
int freq = 50;      // 1/50秒，50Hz的频率，20ms的周期，这个变量用来存储时钟基准。
int channel = 8;    // 通道(高速通道（0 ~ 7）由80MHz时钟驱动，低速通道（8 ~ 15）由 1MHz 时钟驱动。)
int resolution = 8; // 分辨率设置为8，就是2的8次方，用256的数值来映射角度，看下方的占空比函数。
const int led = 13;
const int potPin = 4;
int potValue = 0;
int dutyCycle = 0;

int calculatePWM(int degree) // 定义函数用于输出PWM的占空比
{
  // 0-180度
  // 20ms周期内，高电平持续时长0.5-2.5ms，对应0-180度舵机角度，参考上面的180度对应图。
  const float deadZone = 6.4; // 对应0.5ms（0.5ms/(20ms/256）)
  const float max = 32;       // 对应2.5ms（2.5ms/（20ms/256））
  if (degree < 0)
    degree = 0;
  if (degree > 180)
    degree = 180;
  return (int)(((max - deadZone) / 180) * degree + deadZone); // 返回度数对应的高电平的数值
}

void setup()
{
  Serial.begin(115200);
  ledcSetup(channel, freq, resolution); // 用于设置 LEDC 通道的频率和分辨率。
  ledcAttachPin(led, channel);          // 将通道与对应的引脚连接
}

void loop()
{
  potValue = analogRead(potPin);
  dutyCycle = (potValue * 1.0 / 4095) * 180;
  ledcWrite(channel, calculatePWM(dutyCycle));
  // Serial.printf("potValue: %d, ledValue: %d\r\n", potValue, dutyCycle);
  // delay(15);
}