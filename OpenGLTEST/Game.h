#pragma once
#include <vector>
#include "GameObject.h"

namespace LGE
{
	class Game
	{
	public:
		int globalCounter = 0;
		std::vector<GameObject*> staticObjects;
		std::vector<GameObject*> dynamicObjects;
		GameObject *playObject;
		std::vector<Shader> shaders;
		float a2 = 0.0f;
		float x_shift = 0.0f;
		float y_shift = 0.0f;

		Game();
		void placing();
		void render();
	};
}
