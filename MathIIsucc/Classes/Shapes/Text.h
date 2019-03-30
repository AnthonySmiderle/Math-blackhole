#pragma once

#include "cocos2d.h"
using namespace cocos2d;

#include <string>

class BasecodeText
{
public:
	BasecodeText(
		Scene* parentScene,
		const std::string& text,
		const std::string& font_directory,
		float fontsize,
		Vec2 position,
		Color3B color = Color3B::BLACK,
		Vec2 anchor = Vec2(0,0)
	)
	{
		// Create label
		label = Label::createWithTTF(text, font_directory, fontsize);
		setPosition(position);
		setColor(color);
		setAnchor(anchor);

		parentScene->addChild(label);
	}
	void setPosition(Vec2 p)
	{
		label->setPosition(p);
	}
	void setAnchor(Vec2 A)
	{
		label->setAnchorPoint(A.getNormalized());
	}
	void setColor(Color3B c)
	{
		label->setColor(c);
	}
	void setText(const std::string& text)
	{
		label->setString(text);
	}

private:
	Label* label;


};