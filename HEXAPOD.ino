#include <Servo.h>

class Leg{
  public:
  Servo segm1;
  Servo segm2;
  Servo segm3;


  int current_angle_s1 = 90;
  int current_angle_s2 = 90;
  int current_angle_s3 = 90;

  int target_angle_s1 = 90;
  int target_angle_s2 = 90;
  int target_angle_s3 = 90;

  unsigned long last_millis = 0;

  Leg(){
    // last_millis = millis();
    // Serial.println(last_millis);
  }

  void attach(int pin_s1, int pin_s2, int pin_s3){
    segm1.attach(pin_s1);
    segm2.attach(pin_s2);
    segm3.attach(pin_s3);
    segm1.write(current_angle_s1);
    segm2.write(current_angle_s2);
    segm3.write(current_angle_s3);
  }

  void set_target_angle(int t_s1, int t_s2, int t_s3){
    Serial.println(t_s1);
    this->target_angle_s1 = t_s1;
    this->target_angle_s2 = t_s2;
    this->target_angle_s3 = t_s3;
  }

  void move(int delay_time){
    // int delta_s1 = target_angle_s1 - current_angle_s1;
    // int delta_s2 = target_angle_s2 - current_angle_s2;
    // int delta_s3 = target_angle_s3 - current_angle_s3;

    if(millis() - this->last_millis >= delay_time){
      if(target_angle_s1>current_angle_s1){
        segm1.write(current_angle_s1++);
      }
      else if(target_angle_s1<current_angle_s1){
        segm1.write(current_angle_s1--);
      }

      if(target_angle_s2>current_angle_s2){
        segm2.write(current_angle_s2++);
      }
      else if(target_angle_s2<current_angle_s2){
        segm2.write(current_angle_s2--);
      }

      if(target_angle_s3>current_angle_s3){
        segm3.write(current_angle_s3++);
      }
      else if(target_angle_s3<current_angle_s3){
        segm3.write(current_angle_s3--);
      }

      last_millis = millis();
    }


  }

};


class Hexapod
{
public:
  Leg L1;
  Leg R1;

  Leg L2;
  Leg R2;

  Leg L3;
  Leg R3;

  Hexapod()
  {
  }

  void attach_legs_1(int pinL1, int pinL2, int pinL3, int pinR1, int pinR2, int pinR3)
  {
    L1.attach(pinL1, pinL2, pinL3);
    R1.attach(pinR1, pinR2, pinR3);
  }

  void attach_legs_2(int pinL1, int pinL2, int pinL3, int pinR1, int pinR2, int pinR3)
  {
    L2.attach(pinL1, pinL2, pinL3);
    R2.attach(pinR1, pinR2, pinR3);
  }
  void attach_legs_3(int pinL1, int pinL2, int pinL3, int pinR1, int pinR2, int pinR3)
  {
    L3.attach(pinL1, pinL2, pinL3);
    R3.attach(pinR1, pinR2, pinR3);
  }

  void move_all(int delay_time = 20){
    L1.move(delay_time);
    R1.move(delay_time);
    L2.move(delay_time);
    R2.move(delay_time);
    L3.move(delay_time);
    R3.move(delay_time);
  }

  void to_def_pos()
  {
    //  /\     /\ 
    // /  \___/  \ 
    /**/
    L1.set_target_angle(130,90,90);
    R1.set_target_angle(50,90,90);

    L2.set_target_angle(90,90,90);
    R2.set_target_angle(90,90,90);

    L3.set_target_angle(50,90,90);
    R3.set_target_angle(130,90,90);
    
  }

  void stand_up()
  {
    //  /---___---\ 
    // /           \ 
    /**/

    L1.set_target_angle(130,40,80);
    R1.set_target_angle(50,140,100);

    L2.set_target_angle(90,40,80);
    R2.set_target_angle(90,140,100);

    L3.set_target_angle(50,40,80);
    R3.set_target_angle(130,140,100);
    
  }

  // void lie_down()
  // {
  //   //
  //   //  ------___------
  //   L11.write(130);
  //   L21.write(90);
  //   L31.write(50);
  //   R11.write(50);
  //   R21.write(90);
  //   R31.write(130);
  //   delay(1000);
  //   for (int i = 0; i <= 45; i++)
  //   {
  //     L12.write(90 - i);
  //     L22.write(90 - i);
  //     L32.write(90 - i);
  //     R12.write(90 + i);
  //     R22.write(90 + i);
  //     R32.write(90 + i);
  //     delay(40);
  //   }
  //   delay(1000);
  //   L13.write(0);
  //   L23.write(0);
  //   L33.write(0);
  //   R13.write(180);
  //   R23.write(180);
  //   R33.write(180);
  // }

  void sit_down()
  {
    // ||   ||
    // /|___|\ 
    /**/

    L1.set_target_angle(130,135,90);
    R1.set_target_angle(50,45,90);

    L2.set_target_angle(90,135,90);
    R2.set_target_angle(90,45,90);

    L3.set_target_angle(50,135,90);
    R3.set_target_angle(130,45,90);


    // L11.write(130);
    // L21.write(90);
    // L31.write(50);
    // R11.write(50);
    // R21.write(90);
    // R31.write(130);
    // delay(1000);
    // for (int i = 0; i <= 45; i++)
    // {
    //   L12.write(90 + i);
    //   L22.write(90 + i);
    //   L32.write(90 + i);
    //   R12.write(90 - i);
    //   R22.write(90 - i);
    //   R32.write(90 - i);
    //   delay(40);
    // }
    // // L12.write(135);
    // // L22.write(135);
    // // L32.write(135);
    // // R12.write(45);
    // // R22.write(45);
    // // R32.write(45);
    // delay(1000);
    // for (int i = 45; i >=0 ; i--)
    // {
    //   L13.write(90 + i);
    //   L23.write(90 + i);
    //   L33.write(90 + i);
    //   R13.write(90 - i);
    //   R23.write(90 - i);
    //   R33.write(90 - i);
    //   delay(40);
    // }
    // // L13.write(135);
    // // L23.write(135);
    // // L33.write(135);
    // // R13.write(45);
    // // R23.write(45);
    // // R33.write(45);
  }
};

Hexapod hexa;

void setup()
{
  
  Serial.begin(9600);
  hexa.attach_legs_1(4, 5, 6, 33, 32, 31);
  hexa.attach_legs_2(7, 8, 9, 30, 29, 28);
  hexa.attach_legs_3(10, 11, 12, 27, 26, 25);
  delay(2000);
  hexa.stand_up();
}

void loop()
{
  // hexa.sit_down();

  hexa.move_all(20);
}