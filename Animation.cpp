#include "Animation.h"

Animation::Animation() : m_texture(NULL)
{

}

void Animation::addFrame(sf::IntRect rect)
{
	m_frames.push_back(rect);
}

void Animation::addFrames(int frames, int columns, int rows, int individualWidth, int individualHeight)
//add all frames for the animation using number of frames and the arrangment of the images in the spritesheet
{
	int currentCol = 1;
	int currentRow = 1;
	for (int i = 0; i < frames; i++) {
		addFrame(sf::IntRect(individualWidth * (currentCol - 1), individualHeight * (currentRow - 1), individualWidth, individualHeight));
		currentCol++;
		if (currentCol > columns) {
			currentCol = 1;
			currentRow++;
		}
		if (currentRow > rows) { currentRow = 1; }
	}
}

void Animation::setSpriteSheet(const sf::Texture& texture)
{
	m_texture = &texture;
}

const sf::Texture* Animation::getSpriteSheet() const
{
	return m_texture;
}

std::size_t Animation::getSize() const
{
	return m_frames.size();
}

const sf::IntRect& Animation::getFrame(std::size_t n) const
{
	return m_frames[n];
}
