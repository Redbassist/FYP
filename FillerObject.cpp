#include "FillerObject.h"

FillerObject::~FillerObject()
{
}

FillerObject::FillerObject(Vector2f p, float r, std::string t, bool physical, bool light) : m_pos(p), rotation(r), type(t)
{
	LoadAssets();
	if (physical)
		createBox2dBody();
	if (light)
		CreateLight();
}

void FillerObject::LoadAssets()
{
	m_texture.loadFromFile("Sprites/" + type + ".png");
	m_texture.setSmooth(false);
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect(0, 0, m_texture.getSize().x, m_texture.getSize().y));
	//m_sprite.setScale(size.x, size.y); 
	m_sprite.setOrigin(m_texture.getSize().x / 2, m_texture.getSize().y / 2);
	m_sprite.setPosition(m_pos);
	m_sprite.setRotation(rotation);
}

void FillerObject::Draw()
{
	window->draw(m_sprite);
}

void FillerObject::CreateLight()
{
	pointLightTexture.loadFromFile("assets/pointLightTexture.png");
	pointLightTexture.setSmooth(true);

	light = std::make_shared<ltbl::LightPointEmission>();
	light->_emissionSprite.setOrigin(pointLightTexture.getSize().x * 0.5f, pointLightTexture.getSize().y * 0.5f);
	light->_emissionSprite.setTexture(pointLightTexture);
	lightSize = 9;
	light->_emissionSprite.setScale(lightSize, lightSize);
	light->_emissionSprite.setColor({ 203u, 236u, 247u });
	light->_emissionSprite.setPosition(m_pos);
	ltbl::LightSystem::GetInstance()->addLight(light);
}

void FillerObject::createBox2dBody()
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set((m_pos.x) / SCALE, (m_pos.y) / SCALE);
	bodyDef.userData = this;
	bodyDef.gravityScale = 1;
	body = world->CreateBody(&bodyDef);
	b2PolygonShape staticBox;
	staticBox.SetAsBox((m_sprite.getTexture()->getSize().x / 2.0f) / SCALE, (m_sprite.getTexture()->getSize().y / 2.0f) / SCALE);
	fixtureDef.shape = &staticBox;

	fixtureDef.density = 1;
	fixtureDef.friction = 0.3f;
	fixtureDef.userData = "Filler";
	fixtureDef.restitution = b2MixRestitution(0, 0);

	fixtureDef.filter.categoryBits = FILLER;
	fixtureDef.filter.maskBits = PLAYER | MELEE | PUNCH | ENEMY;

	body->CreateFixture(&fixtureDef);
	body->SetTransform(body->GetPosition(), rotation * DEGTORAD);
}
