#include "Globals.h"

b2World* world; 
sf::RenderStates* lightRenderStates;
sf::Shader* unshadowShader;
sf::Shader* lightOverShapeShader;
sf::Shader* normalsShader;
tmx::MapLoader* ml;
sf::RenderWindow* window; 