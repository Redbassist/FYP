#include "Effect.h" 
 
Effect::Effect(Texture * t, Vector2f pos, int frames, int columns, int rows, int individualWidth, int individualHeight, int speed)
{
	anim.setSpriteSheet(*t);
	anim.addFrames(frames, columns, rows, individualWidth, individualHeight); 
	animSprite = AnimatedSprite(sf::seconds(speed), true, false);
	animSprite.setOrigin(t->getSize().x,t->getSize().y);
	animSprite.setPosition(pos);
	animSprite.setScale(1, 1);
	animSprite.play(anim);
}

void Effect::Draw(sf::Time frameTime)
{
	animSprite.update(frameTime);
	window->draw(animSprite);
}

bool Effect::Complete()
{
	if (!animSprite.isPlaying())
		return true;
	else
		return false;
}
