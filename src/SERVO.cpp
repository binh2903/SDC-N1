#include <Arduino.h>
#include <Servo.h>

Servo myServo_1; // Tạo đối tượng servo
Servo myServo_2;

void lay_bong_thuong()
{
    myServo_1.write(0); // Đặt góc quay về 0 độ
    myServo_2.write(180);
    delay(2200); // Đợi 1 giây

    myServo_1.write(180); // Đặt góc quay về 180 độ
    myServo_2.write(0);
    delay(2200); // Đợi 1 giây
}

void setup()
{
    myServo_1.attach(9); // Kết nối servo với chân số 9
    myServo_2.attach(10);
    Serial.begin(115200);
}

void loop()
{
}