#include <string>

using namespace std;

class Fighter : public FighterInterface {
	protected:
        string name;
        int maxHitPoints, hitPoints, strength, speed, magic;
		Fighter() {}
        Fighter(string newName, int newHitPoints, int newStrength, int newSpeed, int newMagic) {
            name = newName;
            maxHitPoints = newHitPoints;
            hitPoints = newHitPoints;
            strength = newStrength;
            speed = newSpeed;
            magic = newMagic;
        }
		~Fighter() {}
        string getName() {
            return name;
        }
		int getMaximumHP() {
            return maxHitPoints;
        }
		int getCurrentHP() {
            return hitPoints;
        }
        int getStrength() {
            return strength;
        }
		int getSpeed() {
            return speed;
        }
        int getMagic() {
            return magic;
        }
        virtual int getDamage() = 0;
        void takeDamage(int damage) {
            int damageTaken = damage-speed/4;
            if(damageTaken < 1) {
                damageTaken = 1;
            }
            hitPoints -= damageTaken;
        }
		virtual void reset() = 0;
		virtual void regenerate() {
            int hitPointIncrease = strength/6;
			if(hitPointIncrease < 1) {
				hitPointIncrease = 1;
			}
        	hitPoints += hitPointIncrease;
            if(hitPoints > maxHitPoints) {
                hitPoints = maxHitPoints;
            }
        }
		virtual bool useAbility() = 0;
};
