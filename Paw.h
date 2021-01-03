#include <Arduino.h>
#include <Servo.h>
#include "InverseKinematic.h"

class Paw {
  public:
    double steps = 10;
    uint8_t init_angle = 90;
    uint16_t delay_time = 100;
    uint16_t last_time;
    bool side;
    
  
    Paw(uint8_t p_coxa, uint8_t p_femur, uint8_t p_tibia, int16_t s_coxa, int16_t s_femur, int16_t s_tibia, bool side);

    void begin();
    void dirset_coxa(int angle);
    void dirset_femur(int angle);
    void dirset_tibia(int angle);

    int dirread_coxa();
    int dirread_femur();
    int dirread_tibia();

    void set_target_coxa(int angle);
    void set_target_femur(int angle);
    void set_target_tibia(int angle);

    bool step2target();

  private:
    uint8_t pin_coxa; //таз
    uint8_t pin_femur; //бедро
    uint8_t pin_tibia; //голень-лапа

    int8_t shift_coxa;
    int8_t shift_femur;
    int8_t shift_tibia;

    Servo scoxa;
    Servo sfemur;
    Servo stibia;

    // target angles for segments
    int16_t target_coxa;
    int16_t target_femur;
    int16_t target_tibia;

    // current angles of segments
    double curr_coxa;
    double curr_femur;
    double curr_tibia;

    // angle steps for segments
    double coxa_move_k=0;
    double femur_move_k=0;
    double tibia_move_k=0;

    // min angles
    int16_t min_coxa = 35;
    int16_t min_femur = 35;
    int16_t min_tibia = 35;

    // max angles
    int16_t max_coxa = 145;
    int16_t max_femur = 145;
    int16_t max_tibia = 145;

    
    int border_angle(int angle, int min_angle, int max_angle);
};
