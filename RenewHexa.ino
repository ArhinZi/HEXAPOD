#include <Servo.h>

class Joint{
    public:
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
        int limits[6][3][3] = {
            {}
        };
        */
        
        // from head, left then right, nearest then farest from body
        int pins[3][2][3] = {
            {{27, 26, 25}, {10, 11, 12}},
            {{30, 29, 28}, {7, 8, 9}},
            {{33, 32, 31}, {4, 5, 6}}
        };

        void attach(){
            for (int segment = 0; segment < 3; segment++){
                for (int side = 0; side < 2; side++){
                    for (int phalanx = 0; phalanx < 3; phalanx++){
                        this->legs[segment][side].joints[phalanx].servo.attach(this->pins[segment][side][phalanx]);
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
                        Serial.print(this->legs[segment][side].joints[phalanx].servo.read());
                        Serial.print(" ");
                    }
                    Serial.println();
                }
            }
        }

        void stand() {
            for (int segment = 0; segment < 3; segment++){
                for (int side = 0; side < 2; side++){
                    for (int phalanx = 0; phalanx < 3; phalanx++){
                        this->legs[segment][side].joints[phalanx].servo.write(90);
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
    hexa.logState();
    hexa.stand();

}

void loop()
{
    hexa.logState();
    delay(2000);
}
