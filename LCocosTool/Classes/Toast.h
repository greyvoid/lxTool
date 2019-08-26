#pragma once

#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"
#include "ui/CocosGUI.h"


USING_NS_CC;
using namespace cocostudio;
using namespace ui;

class Toast
{
public:

	static void showText(const char* text, Node* nodeParent);
	static void showText(const char* text, Node* nodeParent, Point startPosition);

	static void showText(const char* text, Node* nodeParent, float dt);

	static void showImg(const char* strFrame, Node* nodeParent);

	static void showTip(Node* nodeParent, const char *tip, Point startPosition);

private:
	ImageView* _img;
	Text* _text;

};

