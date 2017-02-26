using namespace std;

class Archer : public Fighter {
	protected:
        string name;
        int maxSpeed;
    public:
		Archer() {}
        Archer(string newName, int newHitPoints, int newStrength, int newSpeed, int newMagic) {
            name = newName;
            maxHitPoints = newHitPoints;
            hitPoints = newHitPoints;
            strength = newStrength;
            speed = newSpeed;
			maxSpeed = newSpeed;
            magic = newMagic;
			}
		~Archer() {}
        int getDamage() {
            return speed;
        }
        int getSpeed() {
            return speed;
        }
		void reset() {
            hitPoints = maxHitPoints;
            speed = maxSpeed;
        }
		bool useAbility() {
            speed++;
            return true;
        }
};
