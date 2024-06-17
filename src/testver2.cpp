#include <Arduino.h>
#include <Servo.h>
// #define ch1 16
// #define ch2 15
#define ch1 16
#define ch2 15
#define ch3 54

#define R_EN_right 4
#define L_EN_right 5
#define R_PWM_right 6
#define L_PWM_right 7


#define R_EN_left 8
#define L_EN_left 9
#define R_PWM_left 11 
#define L_PWM_left 10

#define R_EN_cuon_bong 55
#define L_EN_cuon_bong 56
#define R_PWM_cuon_bong 2
#define L_PWM_cuon_bong 3

int value1;
int value2;
int value3;
int signal1;
int signal2;
int signal3;

int z = 0;
int start_pulse = 110;
int rotage = 260;
void pulseIn()
{
    value1 = pulseIn(ch1, HIGH);
    value2 = pulseIn(ch2, HIGH);
    value3 = pulseIn(ch3, HIGH);
}
void map()
{
    pulseIn();
    signal1 = map(value1, 868, 1840, -240, 240); // TRÁI PHẢI
    signal2 = map(value2, 868, 1855, -240, 240); // LÊN XUỐNG
    signal3 = map(value3, 868, 1855, -245, 245); // Cuốn bóng

}
void cuon_bong(int value)
{

    if(value>61)
    {
        Serial.println(value);
        if(value>240)
        {
            value=255;
        }
        analogWrite(R_PWM_cuon_bong, value);
        analogWrite(L_PWM_cuon_bong, 0);
    }
    else
    {
        analogWrite(R_PWM_cuon_bong, 0);
        analogWrite(L_PWM_cuon_bong, 0);
    }

}
void di_chuyen(int value1,int value2)
{
      if ((fabs(value1) <= start_pulse) && (fabs(value2) <= start_pulse))
    {
        analogWrite(R_PWM_right, 0);
        analogWrite(L_PWM_right, 0);
        analogWrite(R_PWM_left, 0);
        analogWrite(L_PWM_left, 0);
        z = rotage;
    }

    else
    {
        if (fabs(value1) <= start_pulse && fabs(value2) > start_pulse)
        {

            if (value2 < 0) // phai
            {

                // tiến
                analogWrite(R_PWM_right, fabs(value2));
                analogWrite(L_PWM_right, 0);
                analogWrite(R_PWM_left, fabs(value2));
                analogWrite(L_PWM_left, 0);
            }
            else // trai
            {
                // Serial.print("lui");
                // Serial.print('\t');
                // Serial.println(value2);
                analogWrite(R_PWM_right, 0);
                analogWrite(L_PWM_right, fabs(value2));
                analogWrite(R_PWM_left, 0);
                analogWrite(L_PWM_left, fabs(value2));
            }
        }
        // trai phai
        if (fabs(value1) > start_pulse && fabs(value2) <= start_pulse)
        {
            if (fabs(value1) < rotage)
            {
                if (value1 > 0) // tien
                {
                    // Serial.print("rephai");
                    // Serial.print('\t');
                    //  Serial.println(value1);
                    analogWrite(R_PWM_right, 0);
                    analogWrite(L_PWM_right, fabs(value1)-5+14);
                    analogWrite(R_PWM_left, fabs(value1)+12+14);
                    analogWrite(L_PWM_left, 0);
                }
                else // lui
                {

                    analogWrite(R_PWM_right, fabs(value1));
                    analogWrite(L_PWM_right, 0);
                    analogWrite(R_PWM_left, 0);
                    analogWrite(L_PWM_left, fabs(value1));
                }
            }
        }
    }
}

void setup()
{
    Serial.begin(9600);
    pinMode(ch1, INPUT);
    pinMode(ch2, INPUT);
    pinMode(R_PWM_left, OUTPUT);
    pinMode(L_PWM_left, OUTPUT);
    pinMode(R_PWM_right, OUTPUT);
    pinMode(L_PWM_right, OUTPUT);
    pinMode(R_PWM_cuon_bong, OUTPUT);
    pinMode(L_PWM_cuon_bong,OUTPUT);


    pinMode(R_EN_left, OUTPUT);
    pinMode(L_EN_left, OUTPUT);
    pinMode(R_EN_right, OUTPUT);
    pinMode(L_EN_right, OUTPUT);
    pinMode(R_EN_cuon_bong, OUTPUT);
    pinMode(L_EN_cuon_bong, OUTPUT);

  
}



void loop()
{
    digitalWrite(R_EN_right, HIGH);
    digitalWrite(L_EN_right, HIGH);
    digitalWrite(R_EN_left, HIGH);
    digitalWrite(L_EN_left, HIGH);
    digitalWrite(L_EN_cuon_bong, HIGH);
    digitalWrite(R_EN_cuon_bong, HIGH);

    map();
    di_chuyen(signal1,signal2);
    cuon_bong(signal3);

    //  analogWrite(R_PWM_cuon_bong, 30);
    // analogWrite(L_PWM_cuon_bong, 0);



Serial.print(value1);
Serial.print('\t');
Serial.print(signal1);
Serial.print('\t');
Serial.print(value2);
Serial.print('\t');
Serial.print(signal2);
Serial.print('\t');
Serial.print(value3);
Serial.print('\t');
Serial.println(signal3);
              

}
