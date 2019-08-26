#include "Toast.h"
//#include "tool/ToolGlobal.h"


void Toast::showText(const char* text, Node* nodeParent)
{
	//Size laySize = Director::getInstance()->getVisibleSize();
	Size laySize = nodeParent->getBoundingBox().size;
	auto *promptLabel = LabelTTF::create();
	nodeParent->addChild(promptLabel, 99);
	//promptLabel->setString(gb23122utf8(text));
	promptLabel->setString(text);
	promptLabel->setPosition(laySize.width / 2, laySize.height / 2);
	promptLabel->setFontSize(60);
	promptLabel->setFontName("myfonts/QYDK.ttc");
	promptLabel->setFontFillColor(Color3B(30, 144, 255));
	promptLabel->setOpacity(0);
	promptLabel->runAction(Sequence::create(FadeIn::create(0.5), DelayTime::create(1), FadeOut::create(1), RemoveSelf::create(true), NULL));
}

void Toast::showText(const char* text, Node* nodeParent, Point startPosition)
{
	auto *promptLabel = LabelTTF::create();
	nodeParent->addChild(promptLabel, 99);
	//promptLabel->setString(gb23122utf8(text));
	promptLabel->setString(text);
	promptLabel->setPosition(startPosition);
	promptLabel->setFontSize(60);
	promptLabel->setFontName("myfonts/QYDK.ttc");
	promptLabel->setFontFillColor(Color3B(30, 144, 255));
	promptLabel->setOpacity(0);
	promptLabel->runAction(Sequence::create(FadeIn::create(0.5), DelayTime::create(1), FadeOut::create(1), RemoveSelf::create(true), NULL));
}

void Toast::showText(const char* text, Node* nodeParent, float dt)
{
	//Size laySize = Director::getInstance()->getVisibleSize();
	Size laySize = nodeParent->getBoundingBox().size;
	auto *promptLabel = LabelTTF::create();
	nodeParent->addChild(promptLabel);
	//promptLabel->setString(gb23122utf8(text));
	promptLabel->setString(text);
	promptLabel->setPosition(laySize.width / 2, laySize.height / 2);
	promptLabel->setFontSize(60);
	promptLabel->setFontName("myfonts/QYDK.ttc");
	promptLabel->setFontFillColor(Color3B(30, 144, 255));
	promptLabel->setOpacity(0);
	promptLabel->runAction(Sequence::create(FadeIn::create(0.5), DelayTime::create(dt), FadeOut::create(1), RemoveSelf::create(true), NULL));
}

void Toast::showImg(const char* strFrame, Node* nodeParent)
{
	Size laySize = nodeParent->getBoundingBox().size;
	auto *_img = ImageView::create();
	nodeParent->addChild(_img);
	_img->setPosition(Point(laySize.width / 2, laySize.height / 2));
	_img->loadTexture(strFrame);
	_img->setOpacity(0);
	_img->runAction(Sequence::create(FadeIn::create(0.5), DelayTime::create(1), FadeOut::create(1), RemoveSelf::create(true), NULL));
}


void Toast::showTip(Node* nodeParent, const char *tip, Point startPosition)
{
	LabelTTF *tipLabel = LabelTTF::create(tip, "Arial", 20);
	tipLabel->setPosition(startPosition + Point(16, 16));
	nodeParent->addChild(tipLabel);
	tipLabel->runAction(Sequence::create(MoveBy::create(0.5f, Point(0, 32)), DelayTime::create(0.5f), FadeOut::create(0.2f), RemoveSelf::create(true), NULL));
}

