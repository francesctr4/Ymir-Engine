#include "Random.h"
#include "Application.h"
#include "ModuleScene.h"
#include <limits>

int RandomNumber::generate() {

    std::uniform_int_distribution<int> distribution(1, std::numeric_limits<int>::max());

    for (auto it = External->scene->gameObjects.begin(); it != External->scene->gameObjects.end(); ++it) {

    }

        return distribution(m_randomEngine);
}

