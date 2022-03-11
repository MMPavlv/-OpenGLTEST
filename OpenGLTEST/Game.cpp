#include "Game.h"

LGE::Game::Game()
{
}

void LGE::Game::placing()
{
	auto userobj = dynamic_cast<LGE::GameObjectPolyhedron*> (playObject);
	userobj->move();
	userobj->updateCollider();

	auto SecondCollider = std::make_pair(userobj->LocalCollider, userobj->velocity);
	for (auto element : staticObjects)
	{
		LGE::GameObjectPolyhedron* lobj = dynamic_cast<LGE::GameObjectPolyhedron*>(element);
		lobj->updateCollider();

		auto FirstCollider = std::make_pair(lobj->LocalCollider, lobj->velocity);
		if (LGE::Collider::Collide(FirstCollider, SecondCollider))
		{
			userobj->move(userobj->prevGlobalCoords);
			return;
		}
	}
}

void LGE::Game::render()
{
	auto userobj = dynamic_cast<LGE::GameObjectPolyhedron*> (playObject);

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // очищаем буфер цвета и буфер глубины

	// Создаем преобразование камеры/вида
	glm::mat4 view = glm::mat4(1.0f); // сначала инициализируем единичную матрицу
	float radius = 10.0f;
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	//view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	//render static objects
	for (auto element : staticObjects)
	{
		view = glm::lookAt(userobj->getCameraFrom(), userobj->getCameraTo(), glm::vec3(0.0f, 1.0f, 0.0f));

		LGE::GameObjectPolyhedron* lobj = dynamic_cast<LGE::GameObjectPolyhedron*>(element);

		shaders[lobj->shaderID].bindTextures();
		shaders[lobj->shaderID].use();
		shaders[lobj->shaderID].setMat4("view", view);
		lobj->bind();
		// Вычисляем матрицу модели для каждого объекта и передаем её в шейдер до отрисовки
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, lobj->GlobalCoords);
		//model = glm::rotate(model, glm::radians(a2), glm::vec3(0.0, 1.0, 0.0));

		shaders[lobj->shaderID].setMat4("model", model);

		lobj->Draw();
	}

	//render user object
	shaders[userobj->shaderID].bindTextures();
	shaders[userobj->shaderID].use();

	userobj->bind();
	glm::mat4 model = glm::mat4(1.0f);
	//TODO NORMALIZE 2D MOVEMENT
	userobj->setLocalVelocity(glm::vec3(x_shift, 0.0f, y_shift));

	model = glm::translate(model, userobj->GlobalCoords);

	userobj->GlobalRotation = a2;

	model = glm::rotate(model, glm::radians(360 * userobj->GlobalRotation), glm::vec3(0.0, 1.0, 0.0));

	shaders[userobj->shaderID].setMat4("model", model);
	shaders[userobj->shaderID].setMat4("view", view);

	userobj->Draw();
}
