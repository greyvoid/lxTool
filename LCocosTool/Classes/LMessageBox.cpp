#include "LMessageBox.h"
using namespace cocos2d;



CSMessageBoxBase::CSMessageBoxBase(MBStyle style, const std::string &content, ccMBCallBack callback)
	: m_eStyle(style)
	, _strContent(content)
	, m_callback(callback)
{

}

CSMessageBoxBase::~CSMessageBoxBase()
{

}

// 创建函数
CSMessageBoxBase* CSMessageBoxBase::create(MBStyle style, const std::string &content, ccMBCallBack callback)
{
	auto pRet = new CSMessageBoxBase(style, content, callback);
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	delete pRet;
	pRet = nullptr;
	return nullptr;
}

// 初始化函数
bool CSMessageBoxBase::init()
{
	if (!Node::init())
	{
		return false;
	}
	_rootNode = CSLoader::createNode("LayerMessageBox.csb");
	addChild(_rootNode);

	((Text*)_rootNode->getChildByName("txt_content"))->setString(_strContent.c_str());

	// 创建菜单
	createMenuItem();

	auto touchListener = EventListenerTouchOneByOne::create();
	if (nullptr == touchListener) {
		log("null");
	}
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = [&](Touch* touch, Event* event){
		return true;
	};
	
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	//_eventDispatcher->addEventListenerWithFixedPriority(touchListener, -3);

	return true;
}

// 创建菜单
void CSMessageBoxBase::createMenuItem()
{
	if (EM_MB_OK == m_eStyle)
	{
		_rootNode->getChildByName("btn_ok")->setVisible(false);
		_rootNode->getChildByName("btn_cancel")->setVisible(false);
		_rootNode->getChildByName("btn_singlesure")->setVisible(true);

		auto pBtn = (Button*)_rootNode->getChildByName("btn_singlesure");
		pBtn->addTouchEventListener(CC_CALLBACK_2(CSMessageBoxBase::buttonEvent, this));
		pBtn->setTag(EM_CK_OK);
	}
	else
	{
		_rootNode->getChildByName("btn_ok")->setVisible(true);
		_rootNode->getChildByName("btn_cancel")->setVisible(true);
		_rootNode->getChildByName("btn_singlesure")->setVisible(false);

		auto pBtn = (Button*)_rootNode->getChildByName("btn_ok");
		pBtn->addTouchEventListener(CC_CALLBACK_2(CSMessageBoxBase::buttonEvent, this));
		pBtn->setTag(EM_CK_OK);

		pBtn = (Button*)_rootNode->getChildByName("btn_cancel");
		pBtn->addTouchEventListener(CC_CALLBACK_2(CSMessageBoxBase::buttonEvent, this));
		pBtn->setTag(EM_CK_CANCEL);
	}
}


void CSMessageBoxBase::buttonEvent(Ref *pSender, Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED)
	{
		return;
	}
	
	auto pNode = static_cast<Node *>(pSender);
	EMClicked clicked = (EMClicked)pNode->getTag();
	m_callback.execute(this, clicked);
	
}

void CSMessageBoxBase::onEnter()
{
	// 弹出效果
	Action* popupLayer = Sequence::create(ScaleTo::create(0.0, 0.0),
		ScaleTo::create(0.06, 1.05),
		ScaleTo::create(0.08, 0.95),
		ScaleTo::create(0.08, 1.0), NULL);
	this->runAction(popupLayer);
}






