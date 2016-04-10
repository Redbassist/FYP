#include "Effect.h" 
 
Effect::Effect()
{
}

Effect::Effect(Texture * t, Vector2f pos, int frames, int columns, int rows, int individualWidth, int individualHeight, float speed, float scale)
{
	animation.setSpriteSheet(*t);
	animation.addFrames(frames, columns, rows, individualWidth, individualHeight);
	animatedSprite = AnimatedSprite(sf::seconds(speed), true, true);
	animatedSprite.setOrigin(t->getSize().x / 2 / columns,t->getSize().y / 2 / rows);
	animatedSprite.setPosition(pos);
	animatedSprite.setScale(scale, scale);
	int rot = rand() % 360 + 0;
	animatedSprite.setRotation(rot);
	animatedSprite.play(animation);
}

void Effect::DrawEffect(sf::Time frameTime)
{
	animatedSprite.update(frameTime);
	window->draw(animatedSprite);
}

bool Effect::IsComplete()
{
	if (!animatedSprite.isPlaying())
		return true;
	else
		return false;
} 
