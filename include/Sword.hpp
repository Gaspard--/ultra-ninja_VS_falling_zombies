#ifndef SWORD_HPP_
# define SWORD_HPP_

# include "Entity.hpp"
# include "Vect.hpp"
# include "Enemy.hpp"

class Sword
{
public:
    Sword(Vect<2, double>, Vect<2, double>, double);
    ~Sword();

public:
    void Hit(Enemy const &) const;

public:
	Entity entity;
    int damage;
};

#endif // !SWORD_HPP_
