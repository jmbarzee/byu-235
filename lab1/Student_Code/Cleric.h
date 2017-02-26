using namespace std;

class Cleric : public Fighter {
	protected:
        string name;
        int maxMana, mana;
    public:
		Cleric() {}
        Cleric(string newName, int newHitPoints, int newStrength, int newSpeed, int newMagic) {
            name = newName;
            maxHitPoints = newHitPoints;
            hitPoints = newHitPoints;
            strength = newStrength;
            speed = newSpeed;
            magic = newMagic;
            maxMana = 5*magic;
            mana = 5*magic;
        }
		~Cleric() {}
        int getDamage() {
            return magic;
        }
		void reset() {
            hitPoints = maxHitPoints;
            mana = maxMana;
        }
		void regenerate() {
            int hitPointIncrease = strength/6;
            if(hitPointIncrease < 1) {
                hitPointIncrease = 1;
            }
            if(hitPointIncrease + hitPoints >= maxHitPoints) {
                hitPoints = maxHitPoints;
            } else {
                hitPoints += hitPointIncrease;
            }
            int manaIncrease = magic/5;
            if(manaIncrease == 0) {
                manaIncrease = 1;
            }
            if(manaIncrease + mana >= maxMana) {
                mana = maxMana;
            } else {
                mana += manaIncrease;
            }
        }
		bool useAbility() {
            if(mana >= CLERIC_ABILITY_COST) {
               int hitPointIncrease = magic/3;
                if(hitPointIncrease < 2) {
                    hitPointIncrease = 1;
                }
                if(hitPointIncrease + hitPoints >= maxHitPoints) {
                    hitPoints = maxHitPoints;
                } else {
                    hitPoints += hitPointIncrease;
                }
                mana -= CLERIC_ABILITY_COST;
                return true;
            }
            return false;
        }
};
