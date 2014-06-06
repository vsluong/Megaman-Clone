#include "blast.h"

Bullet::Bullet()
{
	spriteData.width = bulletNS::WIDTH;     // size of 1 image
	spriteData.height = bulletNS::HEIGHT;
	spriteData.rect.bottom = bulletNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = bulletNS::WIDTH;
	columns = bulletNS::TEXTURE_COLS;
	frameDelay = bulletNS::ANIMATION_DELAY;
	startFrame = bulletNS::START_FRAME;       // first frame of bullet animation
	endFrame = bulletNS::END_FRAME;         // last frame of bullet animation
	currentFrame = startFrame;
	radius = bulletNS::COLLISION_RADIUS;  // for circular collision
	active = false;     // bullet starts inactive
	visible = false;	//starts invisible
	fireTimer = bulletNS::FIRE_DELAY;
	enemyFireTimer = bulletNS::ENEMY_FIRE_DELAY;
	spriteData.x = 600;//entity->getCenterX() - spriteData.width / 2;
	spriteData.y = 400;//entity->getCenterY() - spriteData.height / 2;
	collisionType = entityNS::CIRCLE;
	setLoop(false);
}

void Bullet::setID(char ID)
{
	weaponIdentifier_ = ID;
	/////
	if (ID == 'm')
	{
		columns = bulletNS::MEGAMAN_COLS;
		frameDelay = bulletNS::MEGAMAN_ANIMATION_DELAY;
		startFrame = bulletNS::MEGAMAN_START_FRAME;       // first frame of bullet animation
		endFrame = bulletNS::MEGAMAN_END_FRAME;         // last frame of bullet animation
		currentFrame = startFrame;
		radius = bulletNS::COLLISION_RADIUS;  // for circular collision
		active = false;     // bullet starts inactive
		visible = false;	//starts invisible
		fireTimer = bulletNS::FIRE_DELAY;
		enemyFireTimer = bulletNS::ENEMY_FIRE_DELAY;
	}

	if (ID == 'f')
	{
		columns = bulletNS::RUBEN_COLS;
		frameDelay = bulletNS::MEGAMAN_ANIMATION_DELAY;
		startFrame = bulletNS::RUBEN_ATK_START_FRAME;       // first frame of bullet animation
		endFrame = bulletNS::RUBEN_ATK_END_FRAME;         // last frame of bullet animation
		currentFrame = startFrame;
		radius = bulletNS::COLLISION_RADIUS;  // for circular collision
		active = false;     // bullet starts inactive
		visible = false;	//starts invisible
		fireTimer = bulletNS::FIRE_DELAY;
		enemyFireTimer = bulletNS::ENEMY_FIRE_DELAY;
	}
}

void Bullet::update(float frameTime)
{
	fireTimer -= frameTime;                     // time remaining until fire enabled
	enemyFireTimer -= frameTime;

	if (visible == false)
		return;

	//if (fireTimer < 0)                           // if ready to fire
	{
		//visible = false;                        // old torpedo off
		//active = false;
	}

	Entity::update(frameTime);

	spriteData.x += velocity.x*frameTime;     // move along X
	spriteData.y += velocity.y*frameTime;

	// Wrap around screen edge
	if (spriteData.x > GAME_WIDTH)              // if off right screen edge
		active = false;      // position off left screen edge
	else if (spriteData.x < -bulletNS::WIDTH)  // else if off left screen edge
		active = false;              // position off right screen edge
	if (spriteData.y > GAME_HEIGHT)             // if off bottom screen edge
		active = false;      // position off top screen edge
	else if (spriteData.y < -bulletNS::HEIGHT) // else if off top screen edge
		active = false;             // position off bottom screen edge
}

//ernest stamp of approval do not change or famiry dry
void Bullet::fire(Entity* entity)
{
	if (entity->getIdentity() == 'e'){
		if (enemyFireTimer <= 0)                       // if ready to fire
		{
			velocity.x = entity->getKillDirX() * 50;// properly initiliaze
			if (velocity.x < 0)
			{
				faceRight = false;
				flipHorizontal(!faceRight);
			}
			else
			{
				faceRight = true;
				flipHorizontal(!faceRight);
			}
			if (velocity.x < 0)
			{
				//velocity.x *= -1;
				spriteData.x = entity->getCenterX() - entity->getWidth();
			}
			else
				spriteData.x = entity->getCenterX();
			velocity.y = entity->getKillDirY() * 50; //fucking directions
			//spriteData.x = entity->getCenterX();
			spriteData.y = entity->getCenterY() - 50;
			visible = true;                         // make torpedo visible
			active = true;                          // enable collisions
			enemyFireTimer = bulletNS::ENEMY_FIRE_DELAY;      // delay firing
		}
	}
	else{

		if (fireTimer <= 0)                       // if ready to fire
		{
			velocity.x = 200;
			faceRight = entity->getDirection();
			flipHorizontal(!faceRight);
			if (!entity->getDirection())
			{
				velocity.x *= -1;
				spriteData.x = entity->getCenterX() - entity->getWidth();
			}
			else
				spriteData.x = entity->getCenterX();
			velocity.y = 0;
			//spriteData.x = entity->getCenterX();
			spriteData.y = entity->getCenterY() - 50;
			visible = true;                         // make torpedo visible
			active = true;                          // enable collisions
			fireTimer = bulletNS::FIRE_DELAY;      // delay firing
		}
	}
}

void Bullet::damage(WEAPON weapon)
{
	switch (weapon)
	{
	case TORPEDO:
		break;
	case SHIP:
	case PLANET:
		visible = false;
		active = false;
		break;
	}
}
