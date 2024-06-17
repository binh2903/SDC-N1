// #include <Arduino.h>
// #define lay_bong_A 32
// #define lay_bong_B 33
// #define lay_bong_r_pwm 8
// #define lay_bong_l_pwm 9
// #define ch5 6
// #define ch6 7

// int value5;
// int value6;

// int signal5;
// int signal6;
// void pulseIn()
// {
//     value5 = pulseIn(ch5, HIGH);
//     value6 = pulseIn(ch6, HIGH);
// }
// void map()
// {
//     signal5 = map(value5, 987, 1874, 0, 1);
//     signal6 = map(value6, 987, 1972, 0, 255);
// }

// void setup()
// {
//     Serial.begin(9600);
//     pinMode(7, INPUT);
//     pinMode(8, INPUT);
//     pinMode(lay_bong_r_pwm, OUTPUT);
//     pinMode(lay_bong_l_pwm, OUTPUT);
//     pinMode(lay_bong_A, OUTPUT);
//     pinMode(lay_bong_B, OUTPUT);
// }
// void loop()
// {
//     pulseIn();
//     map();

//     // Serial.print(signal5);
//     // Serial.print("\t");
//     // Serial.print(signal6);
//     // Serial.print("\t\n");

//     digitalWrite(lay_bong_B, HIGH);
//     digitalWrite(lay_bong_A, HIGH);

//     if (value6 <= 4 || (value6 >= 128 && value6 <= 132))
//     {
//         analogWrite(lay_bong_r_pwm, 0);
//         analogWrite(lay_bong_l_pwm, 0);
//     }
//     else
//     {

//         if (signal6 <= 124 && signal6 >= 4)
//         {

//             analogWrite(lay_bong_r_pwm, signal6);
//         }
//         else if (signal6 >= 132)
//         {

//             analogWrite(lay_bong_l_pwm, signal6 - 128);
//         }
//     }
// }
