#include <cmath>

using namespace std;

class Robot: public Fighter {
	protected:
        int bonusDamage, maxEnergy, energy;
    public:
		Robot() {}
        Robot(string newName, int newHitPoints, int newStrength, int newSpeed, int newMagic) {
            name = newName;
            maxHitPoints = newHitPoints;
            hitPoints = newHitPoints;
            strength = newStrength;
            speed = newSpeed;
            magic = newMagic;
            maxEnergy = 2*magic;
            energy = 2*magic;
        }
		~Robot() {}
        int getDamage() {
            int damage = bonusDamage + strength;
            bonusDamage = 0;
            return damage;
        }
		void reset() {
            hitPoints = maxHitPoints;
            energy = maxEnergy;
            bonusDamage = 0;
        }
		bool useAbility() {
            if(energy >= ROBOT_ABILITY_COST) {
                bonusDamage = ((double)strength * pow((double)energy/(double)maxEnergy,4));
                energy -= ROBOT_ABILITY_COST;
                return true;
            }
            return false;
        }
};
