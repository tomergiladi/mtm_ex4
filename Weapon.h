#ifndef WEAPON_H_
#define WEAPON_H_
#include <iostream>
enum Target {
    LEVEL,
    STRENGTH,
    LIFE,
};
class Weapon {
   private:
    char* name;
    Target target;
    int hitStrength;
    int getTargetValue() const;

   public:
    explicit Weapon(const char* name, Target target, int hit_strength);
    Weapon(const Weapon& other);
    Weapon& operator=(const Weapon& other);
    ~Weapon();
    Target getTarget() const;
    int getHitStrength() const;
    int getValue() const;
    bool operator>(const Weapon& other) const;
    bool operator<(const Weapon& other) const;
    bool operator==(const Weapon& other) const;
    bool operator!=(const Weapon& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Weapon& weapon);
};
#endif