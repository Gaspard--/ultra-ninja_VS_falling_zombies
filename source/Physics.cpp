# include "Physics.hpp"
# include "Entities.hpp"

bool    Physics::haveCollision(const Fixture& a, const Fixture& b) const
{
  return (sqrt(CAR(a.pos.x() - b.pos.x()) + CAR(a.pos.y() - b.pos.y())) <= a.radius + b.radius);
}

void    Physics::move(Fixture& fixture) const
{
  fixture.pos += fixture.speed;
}

void    Physics::makePhysicesOnEntities(const std::vector<Entities *>& ent) const
{
  for (unsigned int i = 0 ; i < ent.size() ; i++)
    this->move(ent[i]->getFixture());

  for (unsigned int i = 0 ; i < ent.size() ; i++)
    for (unsigned int j = i + 1 ; j < ent.size() ; j++)
      if (haveCollision(ent[i]->getFixture(), ent[j]->getFixture()))
        {
          ent[i]->collision(*ent[j]);
          ent[j]->collision(*ent[i]);
        }
}
