#include "Paw.h"

Paw::Paw(uint8_t p_coxa, uint8_t p_femur, uint8_t p_tibia, int16_t s_coxa, int16_t s_femur, int16_t s_tibia, bool side):
  pin_coxa(p_coxa), pin_femur(p_femur), pin_tibia(p_tibia), shift_coxa(s_coxa), shift_femur(s_femur), shift_tibia(s_tibia), side(side) {}

void Paw::begin() {
  scoxa.attach(pin_coxa);
  sfemur.attach(pin_femur);
  stibia.attach(pin_tibia);
  scoxa.write(init_angle + shift_coxa);
  sfemur.write(init_angle + shift_femur);
  stibia.write(init_angle + shift_tibia);

  curr_coxa = target_coxa = init_angle + shift_coxa;
  curr_femur = target_femur = init_angle + shift_femur;
  curr_tibia = target_tibia = init_angle + shift_tibia;
}

void Paw::dirset_coxa(int angle) {
  scoxa.write(border_angle(angle, min_coxa, max_coxa));

}
void Paw::dirset_femur(int angle) {
  sfemur.write(border_angle(angle, min_femur, max_femur));
}
void Paw::dirset_tibia(int angle) {
  stibia.write(border_angle(angle, min_tibia, max_tibia));
}

int Paw::dirread_coxa() {
  return scoxa.read();
}
int Paw::dirread_femur() {
  return sfemur.read();
}
int Paw::dirread_tibia() {
  return stibia.read();
}

void Paw::set_target_coxa(int angle) {
  target_coxa = angle + shift_coxa;
  coxa_move_k = (target_coxa - curr_coxa) / steps;
}
void Paw::set_target_femur(int angle) {
  target_femur = angle + shift_femur;
  femur_move_k = (target_femur - curr_femur) / steps;
}
void Paw::set_target_tibia(int angle) {
  target_tibia = angle + shift_tibia;
  tibia_move_k = (target_tibia - curr_tibia) / steps;
}

bool Paw::step2target() {
  bool res = true;
  if ((coxa_move_k > 0 && curr_coxa < target_coxa) || (coxa_move_k < 0 && curr_coxa > target_coxa)) {
    curr_coxa = curr_coxa + coxa_move_k;
    scoxa.write(curr_coxa);
    res = res&&false;
  }
  if ((femur_move_k > 0 && curr_femur < target_femur) || (femur_move_k < 0 && curr_femur > target_femur)) {
    curr_femur = curr_femur + femur_move_k;
    sfemur.write(curr_femur);
    res = res&&false;
  }
  if ((tibia_move_k > 0 && curr_tibia < target_tibia) || (tibia_move_k < 0 && curr_tibia > target_tibia)) {
    curr_tibia = curr_tibia + tibia_move_k;
    stibia.write(curr_tibia);
    res = res&&false;
  }
  return res;
}

int Paw::border_angle(int angle, int min_angle, int max_angle) {
  if (angle < min_angle) {
    return min_angle;
  }
  else if (angle > max_angle) {
    return max_angle;
  }
  return angle;
}
