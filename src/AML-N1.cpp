#include <Arduino.h>
#include <Servo.h>

// Tạo đối tượng servo
Servo myServo_1;
Servo myServo_2;
#define servo1 12
#define servo2 13

// các chân cắm tương ứng 6 kênh của FS-IA6B ( FLY SKY )
#define ch1 2 // trái phải
#define ch2 3 // lên xuống
#define ch3 4
#define ch4 5
#define ch5 54 // KÊNH GẠT SERVO ĐỂ LẤY TÍN HIỆU QUAY CUỐN BÓNG
// #define ch6 7

// các chân của động cơ (BTS DRIVER)
#define R_EN_right 22
#define L_EN_right 24
#define R_PWM_right 6
#define L_PWM_right 7

#define R_EN_left 26
#define L_EN_left 28
#define R_PWM_left 8
#define L_PWM_left 9

#define R_EN_top 30
#define L_EN_top 32
#define R_PWM_top 10
#define L_PWM_top 11
// Các tín hiệu thô từ Flysky
int value1;
int value2;
int value3;
int value4;
int value5;
// int value6;

// Các chỉ số sau khi đã map từ các tín hiệu thô
int signal1; // phải - trái phải
int signal2; // phải - lên xuống
int signal3; // lấy bóng thưởng
int signal4; // servo
int signal5;
// int signal6;

// Khởi tạo các biến cần để lọc các giá trị sai bằng tính trung bình
const int so_buoc_tinh = 3;
short trungbinh_signal1[so_buoc_tinh];
short trungbinh_signal2[so_buoc_tinh];
int index = 0;
int total_signal1 = 0;
int total_signal2 = 0;
int trung_binh_signal1; // phải - trái phải
int trung_binh_signal2; // phải - lên xuống
int max_signal1 = 0;
int max_signal2 = 0;
int j = 0; // gia toc cua lay bong
int i = 0; // speed max lay bong
int z = 0; // gia toc cho dkhien
int count = 0;

void pulseIn()
{
    value1 = pulseIn(ch1, HIGH);
    value2 = pulseIn(ch2, HIGH);
    value3 = pulseIn(ch3, HIGH);
    value4 = pulseIn(ch4, HIGH);
    value5 = pulseIn(ch5, HIGH);
    //     value6 = pulseIn(ch6, HIGH);
}

int MAX(int m)
{
    int max = 0;
    if (fabs(m) > max)
        max = fabs(m);
    return max;
}

int average(int signal1)
{
    total_signal1 -= trungbinh_signal1[index];
    trungbinh_signal1[index] = signal1;
    total_signal1 += signal1;
    index = (index + 1) % so_buoc_tinh;
    if (index == 0)
    {
        trung_binh_signal1 = ceil(total_signal1 / so_buoc_tinh);
    }
    return trung_binh_signal1;
}

void loc_gia_tri()
{
    // bỏ giá trị cuối cùng
    total_signal1 -= trungbinh_signal1[index];
    total_signal2 -= trungbinh_signal2[index];
    // thêm giá trị mới nhất
    trungbinh_signal1[index] = signal1;
    trungbinh_signal2[index] = signal2;
    total_signal1 += signal1;
    total_signal2 += signal2;
    //
    index = (index + 1) % so_buoc_tinh;
    // tính trung bình sau so_buoc_tinh lần
    if (index == 0)
    {
        trung_binh_signal1 = total_signal1 / so_buoc_tinh;
        trung_binh_signal2 = total_signal2 / so_buoc_tinh;
    }

    // kiểm tra giá trị sai số cao nhất mốc 0;
    if (max_signal1 < MAX(trung_binh_signal1))
        max_signal1 = MAX(trung_binh_signal1);
    if (max_signal2 < MAX(trung_binh_signal2))
        max_signal2 = MAX(trung_binh_signal2);

    // //
    // Serial.print("TB Signal1: ");
    // Serial.print(trung_binh_signal1);
    // Serial.print("\t");
    // Serial.print("MAX Signal1: ");
    // Serial.print(max_signal1);
    // Serial.print("\t");
    // //
    // Serial.print("TB Signal2: ");
    // Serial.print(trung_binh_signal2);
    // Serial.print("\t");
    // Serial.print("MAX Signal1: ");
    // Serial.print(MAX(max_signal2));
    // Serial.print("\t");
}

void map()
{
    pulseIn();
    signal1 = map(value1, 998, 1974, -115, 115); // phải - trái phải
    signal2 = map(value2, 987, 1960, -115, 115); // phải - lên xuống
    signal3 = map(value3, 987, 1974, -135, 135);
    signal4 = map(value4, 987, 1968, 987, 1968);
    signal5 = map(value5, 987, 1874, 0, 2);
    // signal6 = map(value6, 987, 1972, 0, 255);

    // /////////////////////////////////////////////////////
    // loc_gia_tri();
    // //
    // Serial.print("TB Signal1: ");
    // Serial.print(trung_binh_signal1);
    // Serial.print("\t");
    // Serial.print("MAX Signal1: ");
    // Serial.print(max_signal1);
    // Serial.print("\t");
    // //
    // Serial.print("TB Signal2: ");
    // Serial.print(trung_binh_signal2);
    // Serial.print("\t");
    // Serial.print("MAX Signal1: ");
    // Serial.print(MAX(max_signal2));
    // Serial.print("\t");
    /////////////////////
    // Serial.print(signal1);
    // Serial.print("\t");
    // Serial.print(signal2);
    // Serial.print("\t");
    // Serial.print(signal3);
    // Serial.print("\t");
    // Serial.print(signal4);
    // Serial.print("\t");
    Serial.print(signal5);
    Serial.print("\t");
    // Serial.print(signal6);
    // Serial.print("\t");
    Serial.print("\n");

    ////////////////////////////////////////////////////
    // Serial.print(value1);
    // Serial.print("\t");
    // Serial.print(value2);
    // Serial.print("\t");
    // Serial.print(value3);
    // Serial.print("\t");
    // Serial.print(value4);
    // Serial.print("\t");
    // Serial.print(value5);
    // Serial.print("\t");
    // Serial.print(value6);
    // Serial.print("\n");

    ////////////////////////////////////////////////////////
    // Serial.print(signal1);
    // Serial.print("\t");
    // Serial.print(value1);
    // Serial.print("\t");
    // Serial.print(signal2);
    // Serial.print("\t");
    // Serial.print(value2);
    // Serial.print("\t");
    // Serial.print(signal3);
    // Serial.print("\t");
    // Serial.print(value3);
    // Serial.print("\t");
    // Serial.print(signal4);
    // Serial.print("\t");
    // Serial.print(value4);
    // Serial.print("\t");
    // Serial.print(signal5);
    // Serial.print("\t");
    // Serial.print(value5);
    // Serial.print("\t");
    // Serial.print(signal6);
    // Serial.print("\t");
    // Serial.print(value6);
    Serial.print("\n");
}

void lay_bong_thuong(int signal)
{

    if (signal < 1500)
    {
        myServo_1.write(0); // Đặt góc quay về 0 độ
        myServo_2.write(180);
    }
    else
    {
        myServo_1.write(180); // Đặt góc quay về 180 độ
        myServo_2.write(0);
    }
}

void lay_bong_ver1(int signal)
{

    int e = 200; // đếm để tăng xung
    long f = millis(), d = 0;
    int start_pulse = 30; // khoảng đứng yên
    int start_pulse2 = 5;
    int jump = 3;     // số bước nhảy xung
    int rotage = 150; // xung tối đa quay không cần chỉnh
    int he_so_lo_xo = 16;
    int he_so_giu = 22;
    // Serial.print(signal5);
    // Serial.print("\t");
    // Serial.print(signal6);
    // Serial.print("\t\n");

    digitalWrite(R_EN_top, HIGH);
    digitalWrite(L_EN_top, HIGH);

    if ((signal >= 0 - start_pulse2) && (signal <= start_pulse))
    {
        analogWrite(R_PWM_top, 0);
        analogWrite(L_PWM_top, 0);
        j = rotage;
        i = 126;
    }
    else
    {
        if (signal > start_pulse) // thu bóng
        {

            //  Serial.println(signal);
            if (signal <= rotage)
            {
                analogWrite(L_PWM_top, signal - he_so_lo_xo);
                // Serial.println(signal-he_so_lo_xo);
            }
            else
            {

                if (f - d >= e)
                {
                    d = f;
                    j = j + 1;
                    analogWrite(L_PWM_top, j - he_so_lo_xo);
                    // Serial.println(j);
                }
            }
        }
        else if (signal < 0 - start_pulse2) // nhat bóng
        {
            Serial.println(signal);

            if (fabs(signal) <= rotage)
            {
                analogWrite(R_PWM_top, fabs(signal));
            }
            else
            {

                if (f - d >= e + 10)
                {

                    d = f;
                    if (i > 109 && i < 130)
                    {
                        i = i - 4;
                    }
                    else
                    {
                        if (i > 30)
                        {
                            i = i - 10;
                        }
                        else
                        {
                            i = 0;
                        }
                    }

                    analogWrite(R_PWM_top, i);

                    // GIU DONG CO TREN KHONG TRUNG
                    if (i == 0)
                    {
                        analogWrite(L_PWM_top, he_so_giu);
                    }
                    Serial.println(i);
                }
            }
        }
    }
}

void di_chuyen_ver1(int value1, int value2)
{
    int b = 800;
    long c = millis(), a = 0;
    int dong_toc = -1;
    // value1 lên xuống
    // value2 trái phải
    digitalWrite(R_EN_right, HIGH);
    digitalWrite(L_EN_right, HIGH);
    digitalWrite(R_EN_left, HIGH);
    digitalWrite(L_EN_left, HIGH);

    int rotage = 150;
    int start_pulse = 25;
    if ((fabs(value1) <= start_pulse) && (fabs(value2) <= start_pulse))
    {
        analogWrite(R_PWM_right, 0);
        analogWrite(L_PWM_right, 0);
        analogWrite(R_PWM_left, 0);
        analogWrite(L_PWM_left, 0);
        z = rotage;
    }
    // tien lui
    else
    {

        if (fabs(value1) <= start_pulse && fabs(value2) > start_pulse)
        {

            if (fabs(value2) < rotage)
            {
                // Serial.print("aaaaaaaaaaa");
                if (value2 > 0) // tien
                {
                    analogWrite(R_PWM_right, fabs(value2) + 20);
                    analogWrite(L_PWM_right, 0);
                    analogWrite(R_PWM_left, fabs(value2) - dong_toc + 20);
                    analogWrite(L_PWM_left, 0);
                }
                else // lui
                {
                    analogWrite(R_PWM_right, 0);
                    analogWrite(L_PWM_right, fabs(value2) + 20);
                    analogWrite(R_PWM_left, 0);
                    analogWrite(L_PWM_left, fabs(value2) - dong_toc - 2 + 20);
                }
            }
            // gia tốc cho tiến và lùi
            else
            {
                if (value2 > 0) // gia toc tien
                {
                    // Serial.println("#12412312");
                    if (c - a >= b && z < fabs(value2) + 10)
                    {
                        if (z >= fabs(value2))
                            z = fabs(value2);
                        else
                            z = z + 5;
                        // Serial.println(z);
                        a = c;
                        analogWrite(R_PWM_right, z);
                        analogWrite(L_PWM_right, 0);
                        analogWrite(R_PWM_left, z - dong_toc);
                        analogWrite(L_PWM_left, 0);
                    }
                }
                else // gia toc lui
                {
                    // Serial.println("#12412312");
                    if (c - a >= b && z < fabs(value2) + 10)
                    {
                        if (z >= fabs(value2))
                            z = fabs(value2);
                        else
                            z = z + 5;
                        // Serial.println(z);
                        a = c;
                        analogWrite(R_PWM_right, 0);
                        analogWrite(L_PWM_right, z);
                        analogWrite(R_PWM_left, 0);
                        analogWrite(L_PWM_left, z - dong_toc);
                    }
                }
            }
        }

        // trai phai
        if (fabs(value1) > start_pulse && fabs(value2) <= start_pulse)
        {
            /////////////////////////////////////////////////////////////////////
            if (fabs(value1) < rotage)
            {
                // Serial.print("aaaaaaaaaaa");
                if (value1 > 0) // re phai 100%
                {
                    analogWrite(R_PWM_right, 0);
                    analogWrite(L_PWM_right, fabs(value1) - fabs(value1) / 3);
                    analogWrite(R_PWM_left, fabs(value1) - fabs(value1) / 3);
                    analogWrite(L_PWM_left, 0);
                }
                else // re trai 100%
                {

                    analogWrite(R_PWM_right, fabs(value1) - fabs(value1) / 3);
                    analogWrite(L_PWM_right, 0);
                    analogWrite(R_PWM_left, 0);
                    analogWrite(L_PWM_left, fabs(value1) - fabs(value1) / 3);
                }
            }
            // gia tốc cho re trai va re phai
            else
            {
                if (value1 > 0) // gia toc trai
                {
                    // Serial.println("#12412312");
                    if (c - a >= b && z < fabs(value1) + 10)
                    {
                        if (z >= fabs(value1))
                            z = fabs(value1);
                        else
                            z = z + 5;
                        Serial.println(z);
                        a = c;
                        analogWrite(R_PWM_right, z);
                        analogWrite(L_PWM_right, 0);
                        analogWrite(R_PWM_left, 0);
                        analogWrite(L_PWM_left, z);
                    }
                }
                else // gia toc phai
                {
                    // Serial.println("#12412312");
                    if (c - a >= b && z < fabs(value1) + 10)
                    {
                        if (z >= fabs(value1))
                            z = fabs(value1);
                        else
                            z = z + 5;
                        Serial.println(z);
                        a = c;
                        analogWrite(R_PWM_right, 0);
                        analogWrite(L_PWM_right, z);
                        analogWrite(R_PWM_left, z - dong_toc);
                        analogWrite(L_PWM_left, 0);
                    }
                }
            }
        }
    }
    // tien re
    if ((fabs(value1) > start_pulse) && (fabs(value2) > start_pulse))
    {

        if (value2 > 0)
        {
            // Serial.print("aaaaaaaaaaa");
            if (value1 > 0) // tien va re phai
            {
                if (fabs(value2) < 50)
                {
                    analogWrite(R_PWM_right, ceil(fabs(value2) / 1) + ceil((fabs(value1)) / 2.7));
                    analogWrite(L_PWM_right, 0);
                    analogWrite(R_PWM_left, fabs(value2));
                    analogWrite(L_PWM_left, 0);
                }
                else
                {
                    analogWrite(R_PWM_right, ceil((fabs(value2) / 2) + ceil((fabs(value1)) / 3.1)));
                    analogWrite(L_PWM_right, 0);
                    analogWrite(R_PWM_left, fabs(value2));
                    analogWrite(L_PWM_left, 0);
                }

                // Serial.print("aaaaaaaaaaa");
                // Serial.print("TIEN VA RE phai ( PHAI TRAI )   ");
                // Serial.print((fabs(value1) / 2) + ceil(fabs(value1) / 4));
                // Serial.print('\t');
                // Serial.print(fabs(value2));
                // Serial.print('\t');
                // Serial.print('\n');
            }
            else // tien va re trai
            {
                int speed = 0;
                if (fabs(value2) < 25)
                {

                    analogWrite(R_PWM_right, fabs(value2));
                    analogWrite(L_PWM_right, 0);
                    if (ceil((fabs(value2)) / 1.1) + ceil((fabs(value1) / 0.8)) > value2)
                    {
                        analogWrite(R_PWM_left, ceil(value2) - 6);
                    }
                    else
                        analogWrite(R_PWM_left, ceil((fabs(value2)) / 2) + ceil((fabs(value1) / 3)));
                    analogWrite(L_PWM_left, 0);
                }
                else if (fabs(value2) < 45 && fabs(value2) >= 25)
                {
                    analogWrite(R_PWM_right, fabs(value2));
                    analogWrite(L_PWM_right, 0);
                    if (ceil((fabs(value2)) / 1.1) + ceil((fabs(value1) / 0.8)) > value2)
                    {
                        analogWrite(R_PWM_left, ceil(value2 - 10));
                    }
                    else
                        // analogWrite(R_PWM_left, ceil((fabs(value2)) / 2.3) + ceil((fabs(value1) / 4)));
                        analogWrite(R_PWM_left, ceil((fabs(value2)) / 2.3) + ceil((fabs(value1) / 4)));
                    analogWrite(L_PWM_left, 0);
                }
                else if (fabs(value2) < 60 && fabs(value2) >= 35)
                {
                    analogWrite(R_PWM_right, fabs(value2));
                    analogWrite(L_PWM_right, 0);
                    if (ceil((fabs(value2)) / 2.5) + ceil((fabs(value1) / 0.8)) > value2)
                    {
                        analogWrite(R_PWM_left, ceil(value2) - 15);
                    }
                    else
                        // analogWrite(R_PWM_left, ceil((fabs(value2)) / 2.5) + ceil((fabs(value1) / 0.8)));
                        analogWrite(R_PWM_left, ceil(value2) - 15);
                    analogWrite(L_PWM_left, 0);
                }
                else if (fabs(value2) < 90 && fabs(value2) >= 60)
                {
                    analogWrite(R_PWM_right, fabs(value2));
                    analogWrite(L_PWM_right, 0);
                    if (ceil((fabs(value2)) / 3) + ceil((fabs(value1) / 1)) > value2)
                    {
                        analogWrite(R_PWM_left, fabs(value2) - 19);
                    }
                    else
                        // analogWrite(R_PWM_left, ceil((fabs(value2)) / 3) + ceil((fabs(value1) / 1)));
                        analogWrite(R_PWM_left, fabs(value2) - 19);
                    analogWrite(L_PWM_left, 0);
                }
                else if (fabs(value2) > 90)
                {
                    analogWrite(R_PWM_right, fabs(value2));
                    analogWrite(L_PWM_right, 0);
                    if (ceil((fabs(value2)) / 4.3) + ceil((fabs(value1) / 1) > value2))
                    {
                        analogWrite(R_PWM_left, ceil(value2) - 22);
                    }
                    else
                        // analogWrite(R_PWM_left, ceil((fabs(value2)) / 3.3) + ceil((fabs(value1) / 1.5)));
                        analogWrite(R_PWM_left, ceil(value2) - 22);
                    analogWrite(L_PWM_left, 0);
                }

                // Serial.print("TIEN VA RE TRAI ( PHAI TRAI )   ");
                // Serial.print(fabs(value2));
                // Serial.print('\t');
                // Serial.print(ceil((fabs(value1)) / 2) + ceil((fabs(value1)) / 4));
                // Serial.print('\t');
                // Serial.print('\n');
            }
        }
        // lui va rẽ
        else
        {
            if (value1 > 0) // lui va re phai
            {
                // if (fabs(value2) < 80)
                // {
                //     analogWrite(R_PWM_right, 0);
                //     analogWrite(L_PWM_right, ceil((fabs(value2)) / 1.4) + ceil((fabs(value1)) / 4.5));
                //     analogWrite(R_PWM_left, 0);
                //     analogWrite(L_PWM_left, fabs(value2));
                // }
                // else
                // {
                //     analogWrite(R_PWM_right, 0);
                //     analogWrite(L_PWM_right, ceil((fabs(value2)) / 2.15) + ceil((fabs(value1)) / 4.7));
                //     analogWrite(R_PWM_left, 0);
                //     analogWrite(L_PWM_left, fabs(value2));
                // }

                // Serial.print("aaaaaaaaaaa");
                // Serial.print("TIEN VA RE phai ( PHAI TRAI )   ");
                // Serial.print(((fabs(value1) ) / 2) + ceil((fabs(value1) ) / 4));
                // Serial.print('\t');
                // Serial.print(fabs(value2));
                // Serial.print('\t');
                // Serial.print('\n');
                /////////////////////////////////////////////////////////////////////////////////////////////////
                // đảo lái
                if (fabs(value2) < 80)
                {
                    analogWrite(R_PWM_right, 0);
                    analogWrite(L_PWM_right, fabs(value2));
                    analogWrite(R_PWM_left, 0);
                    analogWrite(L_PWM_left, ceil((fabs(value2)) / 5.65) + ceil((fabs(value1) / 4)));
                }
                else
                {
                    analogWrite(R_PWM_right, 0);
                    analogWrite(L_PWM_right, fabs(value2));
                    analogWrite(R_PWM_left, 0);
                    analogWrite(L_PWM_left, ceil((fabs(value2)) / 5.95) + ceil((fabs(value1) / 4.5)));
                }
            }
            else // lui va re trai
            {
                // if (fabs(value2) < 80)
                // {
                //     analogWrite(R_PWM_right,0);
                //     analogWrite(L_PWM_right, fabs(value2));
                //     analogWrite(R_PWM_left, 0);
                //     analogWrite(L_PWM_left, ceil((fabs(value2)) / 5.65) + ceil((fabs(value1)/ 4)));
                // }
                // else
                // {
                //     analogWrite(R_PWM_right,0);
                //     analogWrite(L_PWM_right, fabs(value2 ));
                //     analogWrite(R_PWM_left, 0);
                //     analogWrite(L_PWM_left, ceil((fabs(value2)) / 5.95) + ceil((fabs(value1)/ 4.5)));
                // }
                // Serial.print("TIEN VA RE TRAI ( PHAI TRAI )   ");
                // Serial.print(fabs(value2));
                // Serial.print('\t');
                // Serial.print(ceil((fabs(value1)) / 2) + ceil((fabs(value1)) / 4));
                // Serial.print('\t');
                // Serial.print('\n');

                /////////////////////////////////////////////////////////////////////////////////////////////////
                // Đảo lái
                if (fabs(value2) < 80)
                {
                    analogWrite(R_PWM_right, 0);
                    analogWrite(L_PWM_right, ceil((fabs(value2)) / 1.4) + ceil((fabs(value1)) / 4.5));
                    analogWrite(R_PWM_left, 0);
                    analogWrite(L_PWM_left, fabs(value2));
                }
                else
                {
                    analogWrite(R_PWM_right, 0);
                    analogWrite(L_PWM_right, ceil((fabs(value2)) / 2.15) + ceil((fabs(value1)) / 4.7));
                    analogWrite(R_PWM_left, 0);
                    analogWrite(L_PWM_left, fabs(value2));
                }
            }
        }
    }
}
void setup()
{
    myServo_1.attach(servo1); // Kết nối servo với chân số 9
    myServo_2.attach(servo2);
    Serial.begin(9600);
    pinMode(ch1, INPUT);
    pinMode(ch2, INPUT);
    pinMode(ch3, INPUT);
    pinMode(ch4, INPUT);
    // pinMode(7, INPUT);
    // pinMode(8, INPUT);
    pinMode(R_PWM_top, OUTPUT);
    pinMode(L_PWM_top, OUTPUT);
    pinMode(R_PWM_left, OUTPUT);
    pinMode(L_PWM_left, OUTPUT);
    pinMode(R_PWM_right, OUTPUT);
    pinMode(L_PWM_right, OUTPUT);
    pinMode(R_EN_left, OUTPUT);
    pinMode(L_EN_left, OUTPUT);
    pinMode(L_EN_top, OUTPUT);
    pinMode(R_EN_top, OUTPUT);
    pinMode(R_EN_right, OUTPUT);
    pinMode(L_EN_right, OUTPUT);
    digitalWrite(L_EN_left, LOW);
    digitalWrite(R_EN_left, LOW);
    digitalWrite(R_EN_left, HIGH);
    digitalWrite(L_EN_left, HIGH);
    pinMode(31, OUTPUT);
    pinMode(33, OUTPUT);
}
void cuon_bong(int signal5)
{
    if (signal5 == 1)
    {
        if (count == 3)
        {
            digitalWrite(31, LOW);
            digitalWrite(33, LOW);
        }
        else
        {
            digitalWrite(31, HIGH);
            digitalWrite(33, LOW);
        }
    }
    else if (signal5 == 0)
    {
        count = 2;
        digitalWrite(31, LOW);
        digitalWrite(33, LOW);
    }
    else if (signal5 == 2)
    {
        digitalWrite(31, LOW);
        digitalWrite(33, LOW);
        count = 3;
    }
}

void loop()
{
    map();
    lay_bong_thuong(signal4);
    lay_bong_ver1(signal3);
    di_chuyen_ver1(signal1, signal2);
    cuon_bong(signal5);
    // di_chuyen_ver2(value1,value2);

    // Serial.print(value2);
    // Serial.print('\t');
    // Serial.println(value1);
    // Serial.print(signal2);
    // Serial.print('\t');
    // Serial.println(signal1);

    //  Serial.print(value3);
    // Serial.print('\t');
    // Serial.println(signal3);
}
