#include "SeparationRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"

Vector2 SeparationRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
    //Try to avoid boids too close
    Vector2 separatingForce = Vector2::zero();

    float desiredDistance = desiredMinimalDistance;

    // todo: implement a force that if neighbor(s) enter the radius, moves the boid away from it/them
    if (!neighborhood.empty()) {
        Vector2 position = boid->transform.position;
        int countCloseFlockmates = 0;
        for (int i = 0; i < neighborhood.size(); i++)
        {
            if (sqrt(pow((neighborhood[i]->getPosition().x - position.x), 2) + pow((neighborhood[i]->getPosition().y - position.y), 2)) < desiredMinimalDistance)
            {
                separatingForce += (position - neighborhood[i]->getPosition()) * (1.0 / sqrt(pow((neighborhood[i]->getPosition().x - position.x), 2) + pow((neighborhood[i]->getPosition().y - position.y), 2)));
                countCloseFlockmates++;
            }
        }
        if (countCloseFlockmates != 0)
        {
            separatingForce /= countCloseFlockmates;
        }

    }

    //separatingForce = Vector2::normalized(separatingForce);

    return separatingForce;
}

bool SeparationRule::drawImguiRuleExtra() {
    ImGui::SetCurrentContext(world->engine->imGuiContext);
    bool valusHasChanged = false;

    if (ImGui::DragFloat("Desired Separation", &desiredMinimalDistance, 0.05f)) {
        valusHasChanged = true;
    }

    return valusHasChanged;
}
