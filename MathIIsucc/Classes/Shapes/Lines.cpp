
#include "Lines.h"

C_Lines::C_Lines(Scene* parentScene, std::vector<Vec2> points, float LineWidth, Color4F color)
{
	// Set Data
	this->points = points;

	// Create Node
	drawNode = DrawNode::create();

	// Set Lines
	if (points.size() > 1)
	{
		drawNode->setLineWidth(LineWidth);

		unsigned int total_points = points.size();

		for (unsigned int i = 0; i < total_points - 1; i++)
		{
			drawNode->drawLine(points[i], points[i + 1], color);
		}

	}

	// Add self to scene
	parentScene->addChild(drawNode);
}

C_Lines::~C_Lines()
{
	drawNode = nullptr;
}

void C_Lines::setOffset(Vec2 position)
{
	this->offset = position;

	drawNode->setPosition(position);

}

void C_Lines::rotateAll(float degrees)
{
	float PI = 3.1416;
	drawNode->setRotation(degrees * (PI / 180.0f));
}