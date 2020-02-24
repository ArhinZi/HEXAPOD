#include <Servo.h>

class Joint{
    public:
        void set(int degree){
            // TODO: use limits
            this->servo.write(degree);
        }
        int get(){
            return this->servo.read();
        }
        void attach(int pin){
            this->servo.attach(pin);
        }
        Servo servo;
};

class Leg{
    public:
        Joint *joints = new Joint[3];
};

class Hexapod{
    public:
        // minimal avaiable, standing and maximum avaiable degrees values
        // [leg][joint][value]
        /*
        int limits[6][3][2] = {
            {}
        };
        */
        
        // from head, left then right, nearest then farest from body
        int pins[3][2][3] = {
            {{27, 26, 25}, {10, 11, 12}},
            {{30, 29, 28}, {7, 8, 9}},
            {{33, 32, 31}, {4, 5, 6}}
        };

        int basicState[3][2][3] = {
            {{130, 90, 90}, {50, 90, 90}},
            {{90, 90, 90}, {90, 90, 90}},
            {{50, 90, 90}, {130, 90, 90}}
        };

        int basicStand[3][2][3] = {
            {{130, 140, 100}, {50, 40, 80}},
            {{90, 140, 100}, {90, 40, 80}},
            {{50, 140, 100}, {130, 40, 80}}
        };

        int legsUp[3][2][3] = {
            {{130, 40, 140}, {50, 140, 40}},
            {{90, 40, 100}, {90, 140, 80}},
            {{50, 40, 100}, {130, 140, 80}}
        };

        void attach(){
            for (int segment = 0; segment < 3; segment++){
                for (int side = 0; side < 2; side++){
                    for (int phalanx = 0; phalanx < 3; phalanx++){
                        this->legs[segment][side].joints[phalanx].attach(this->pins[segment][side][phalanx]);
                    }
                    Serial.println();
                }
            }
        }

        void logState() {
            Serial.println("logState start");
            for (int segment = 0; segment < 3; segment++){
                for (int side = 0; side < 2; side++){
                    for (int phalanx = 0; phalanx < 3; phalanx++){
                        Serial.print(this->legs[segment][side].joints[phalanx].get());
                        Serial.print(" ");
                    }
                    Serial.println();
                }
            }
        }

        void setPosition(int position[3][2][3]){
            this->logState();
            for (int segment = 0; segment < 3; segment++){
                for (int side = 0; side < 2; side++){
                    for (int phalanx = 0; phalanx < 3; phalanx++){
                        this->legs[segment][side].joints[phalanx].set(position[segment][side][phalanx]);
                    }
                }
            }
        }

    private:
        // from head, left then right
        Leg (*legs)[2] = new Leg[3][2];
};


Hexapod hexa;

void setup()
{
    Serial.begin(9600);
    Serial.println("Hello Hexa!");
    hexa.attach();
    delay(2000);

    Serial.println("basicState");
    hexa.setPosition(hexa.basicState);
    delay(2000);
}

void loop()
{
    Serial.println("basicState");
    hexa.setPosition(hexa.basicState);
    delay(2000);

    Serial.println("legsUp");
    hexa.setPosition(hexa.legsUp);
    delay(2000);

    Serial.println("basicStand");
    hexa.setPosition(hexa.basicStand);
    delay(2000);

}
