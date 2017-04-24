#include "EnemySmall.hpp"
#include "TextureHandler.hpp"

EnemySmall::EnemySmall(Entity &e)
  : Enemy(e, 10)
{
  e.fixture.radius = 0.03;
  e.fixture.mass = 10;
  e.renderable.texture = TextureHandler::getInstance().getTexture(TextureHandler::TEST);
  e.renderable.destSize = {e.fixture.radius * 2.1, e.fixture.radius * 2.1};
}

void EnemySmall::attack(Player& player)
{
  double                angle = std::rand();
  double                dist = (1 + (double)(std::rand() % 10 + 1) / 10.0);
  Vect<2, double>       enemyPos(dist * cos(angle), dist * sin(angle));

  player.entity.fixture.pos = enemyPos;

}

void    EnemySmall::update(const Player& player)
{
  this->Enemy::update(player);
}
