#include "Paw.h"
#include "InverseKinematic.h"

#define FEMUR_LEN 55
#define TIBIA_LEN 89

Paw paws[6] {
  Paw(4, 14, 22, 0, -5, 10, true),//left1
  Paw(5, 15, 23, 0, -10, 0, true),//left2
  Paw(6, 16, 24, 10, 5, -5, true),//left3

  Paw(8, 18, 26, 0, 10, -5, false),//right1
  Paw(9, 19, 27, -5, 0, -15, false),//right2
  Paw(10, 20, 28, -5, 0, -10, false)//right3
};

int64_t prev_step_time;
void setup()
{
  Serial.begin(9600);
  for (int i = 0; i < 6; i++) {
    paws[i].begin();
  }

  prev_step_time = millis();

}

// state dim - 32(two (x and y) for each paw)
void calcNset_targets4paws(int16_t *state)
{
  int n = 32;
  double x, y;
  int femur, tibia;
  for (int i = 0; i < 6; i++) {
    if (circle_circle_intersection(0, 0, 55,
                                   state[(i * 3 + 0)], state[(i * 3 + 1)], 89,
                                   &x, &y) &&
        find_angles(0, 0, 55,
                    x, y, 89,
                    state[(i * 3 + 0)], state[(i * 3 + 1)],
                    &femur,
                    &tibia)) {
      //      Serial.println(x);
      //      Serial.println(y);
      //      Serial.println(femur);
      //      Serial.println(tibia);
      if (!paws[i].side) {
        paws[i].set_target_coxa(90);
        paws[i].set_target_femur(90 + 35 - femur);
        paws[i].set_target_tibia(tibia - 30);
      }
      else {
        paws[i].set_target_coxa(90);
        paws[i].set_target_femur(90 - 35 + femur);
        paws[i].set_target_tibia(tibia + 30);
      }

    }
  }
}

bool steps2target() {
  return (
           paws[0].step2target() &
           paws[1].step2target() &
           paws[2].step2target() &

           paws[3].step2target() &
           paws[4].step2target() &
           paws[5].step2target()
         );
}


int move_step = 0;
int16_t move_map[1][32] {
  {
    90, -5, 0,
    90, -5, 0,
    90, -5, 0,
    90, -5, 0,
    90, -5, 0,
    90, -5, 0,
  }
};

void loop()
{
  if (millis() - prev_step_time >= 100) {
    if (steps2target() && move_step<1) {
      calcNset_targets4paws(move_map[move_step++]);
    }
    prev_step_time = millis();
  }

}
