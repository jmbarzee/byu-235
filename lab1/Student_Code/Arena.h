#include <map>
#include <sstream>
#include <string>
#include <cstdlib>


using namespace std;

class Arena: public ArenaInterface {
    protected:
        map <string, FighterInterface*> fightersHeld;
    public:
        Arena() {}
        ~Arena() {}
        bool addFighter(string info) {
        	size_t endName = info.find_first_of(" ");
            string name = info.substr(0, endName-0);
            if(fightersHeld.find(name) != fightersHeld.end()) {
				return false;
			}
            size_t startType = info.find_first_not_of(" ", endName);
            size_t endType = info.find_first_of(" ", startType);
            if(endType-startType > 1) {
                return false;
            }
            char type = info[startType];
            size_t startNum1 = info.find_first_not_of(" ", endType);
            size_t endNum1 = info.find_first_of(" ", startNum1);
            if(endNum1-startNum1 < 1) {
                return false;
            }
            double maxHitPoints = strtod(info.substr(startNum1, endNum1-startNum1).c_str(), NULL);
            size_t startNum2 = info.find_first_not_of(" ", endNum1);
            size_t endNum2 = info.find_first_of(" ", startNum2);
            if(endNum2-startNum2 < 1) {
                return false;
            }
            double strength = strtod(info.substr(startNum2, endNum2-startNum2).c_str(), NULL);
            size_t startNum3 = info.find_first_not_of(" ", endNum2);
            size_t endNum3 = info.find_first_of(" ", startNum3);
            if(endNum3-startNum3 < 1) {
                return false;
            }
            double speed = strtod(info.substr(startNum3, endNum3-startNum3).c_str(), NULL);
            size_t startNum4 = info.find_first_not_of(" ", endNum3);
            size_t endNum4 = info.find_first_of(" ", startNum4);
            if(endNum4-startNum4 < 1) {
                return false;
            }
            double magic = strtod(info.substr(startNum4, endNum4-startNum4).c_str(), NULL);
            if(endNum4 != string::npos) {
                return false;
            }
            if(maxHitPoints < 1 || strength < 1 || speed < 1 || magic < 1) {
                return false;
            }
            if(trunc(maxHitPoints) != maxHitPoints || trunc(strength) != strength || trunc(speed) != speed || trunc(magic) != magic ) {
                return false;
            }
            if(type == 'R') {
                fightersHeld.insert(pair<string, FighterInterface*>(name,new Robot(name, (int)maxHitPoints, (int)strength, (int)speed, (int)magic)));
                return true;
            } else if(type == 'C') {
                fightersHeld.insert(pair<string, FighterInterface*>(name,new Cleric(name, (int)maxHitPoints, (int)strength, (int)speed, (int)magic)));
                return true;
            } else if(type == 'A') {
                fightersHeld.insert(pair<string, FighterInterface*>(name,new Archer(name, (int)maxHitPoints, (int)strength, (int)speed, (int)magic)));
                return true;
            }
            return false;
        }
        bool removeFighter(string name) {
             map <string, FighterInterface*>::iterator it = fightersHeld.find(name);
             if (it == fightersHeld.end()) {
                 return false;
             } else {
                 fightersHeld.erase(it);
             }
             return true;
        }
        FighterInterface* getFighter(string name) {
            map <string, FighterInterface*>::iterator it = fightersHeld.find(name);
            if (it == fightersHeld.end()) {
                return NULL;
            }
            return it->second;
        }
		int getSize() {
            return fightersHeld.size();
        }
};
