#include "Weapon.h"
#include "string.h"
int Weapon::getTargetValue() const {
    switch (this->getTarget()) {
        case LEVEL: {
            return 1;
        }
        case STRENGTH: {
            return 2;
        }
        case LIFE: {
            return 3;
        }
        default: { return 0; }
    }
}
Weapon::Weapon(const char* name, Target target, int hit_strength)
    : name(new char[strlen(name) + 1]),
      target(target),
      hitStrength(hit_strength) {
    strcpy(this->name, name);
}
Weapon::Weapon(const Weapon& weapon)
    : name(new char[strlen(weapon.name) + 1]),
      target(weapon.target),
      hitStrength(weapon.hitStrength) {
    strcpy(this->name, weapon.name);
}
Weapon& Weapon::operator=(const Weapon& weapon) {
    // we dont want to change anything if we are assigning to the same weapon
    if (this == &weapon) {
        return *this;
    }
    this->target = weapon.target;
    this->hitStrength = weapon.hitStrength;
    delete[] this->name;
    this->name = new char[strlen(weapon.name) + 1];
    strcpy(this->name, weapon.name);
    return *this;
}
Weapon::~Weapon() {
    delete[] this->name;
}
Target Weapon::getTarget() const {
    return this->target;
}
int Weapon::getHitStrength() const {
    return this->hitStrength;
}
int Weapon::getValue() const {
    return this->getHitStrength() * this->getTargetValue();
}

bool operator>(const Weapon& weapon1, const Weapon& weapon2) {
    return weapon1.getValue() > weapon2.getValue();
}
bool operator<(const Weapon& weapon1, const Weapon& weapon2) {
    return weapon2 > weapon1;
}
bool operator==(const Weapon& weapon1, const Weapon& weapon2) {
    return !(weapon1 > weapon2 || weapon1 < weapon2);
}
bool operator!=(const Weapon& weapon1, const Weapon& weapon2) {
    return !(weapon1 == weapon2);
}

std::ostream& operator<<(std::ostream& os, const Weapon& weapon) {
    return os << "{weapon name: " << weapon.name
              << ", weapon value:" << weapon.getValue() << "}";
}