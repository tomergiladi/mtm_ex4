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
Weapon::Weapon(const Weapon& other)
    : name(new char[strlen(other.name) + 1]),
      target(other.target),
      hitStrength(other.hitStrength) {
    strcpy(this->name, other.name);
}
Weapon& Weapon::operator=(const Weapon& other) {
    if (this == &other) {
        return *this;
    }
    this->target = other.target;
    this->hitStrength = other.hitStrength;
    delete[] this->name;
    this->name = new char[strlen(other.name) + 1];
    strcpy(this->name, other.name);
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
bool Weapon::operator>(const Weapon& other) const {
    return this->getValue() > other.getValue();
}
bool Weapon::operator<(const Weapon& other) const {
    return other > *this;
}
bool Weapon::operator==(const Weapon& other) const {
    return !(*this > other || *this < other);
}
bool Weapon::operator!=(const Weapon& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const Weapon& weapon) {
    return os << "{weapon name: " << weapon.name
              << ", weapon value:" << weapon.getValue() << "}";
}