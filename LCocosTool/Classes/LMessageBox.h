/************************************
功能说明：对话框
************************************/

#ifndef __CSMessageBoxBase_BASE_H__
#define __CSMessageBoxBase_BASE_H__

#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"
#include "ui/CocosGUI.h"


USING_NS_CC;
using namespace cocostudio;
using namespace ui;

// 点击目标
enum EMClicked
{
	EM_CK_OK,
	EM_CK_CANCEL,
	EM_CK_CLOSE,
};

// 消息框风格
enum MBStyle
{
	EM_MB_OK,
	EM_MB_OKCANCEL,
};

typedef void (cocos2d::Ref::*SEL_MESSAGEBOX)(cocos2d::Node *, EMClicked);
#define messagebox_selector(_SELECTOR) static_cast<SEL_MESSAGEBOX>(&_SELECTOR)

// 消息框回调
struct ccMBCallBack
{
	ccMBCallBack()
	: target(nullptr)
	, callback(nullptr)
	{

	}

	ccMBCallBack(cocos2d::Ref *_target, SEL_MESSAGEBOX _func)
		: target(_target)
		, callback(_func)
	{

	}

	~ccMBCallBack()
	{
		target = nullptr;
		callback = nullptr;
	}

	void execute(cocos2d::Node *pSender, EMClicked clicked)
	{
		if (target && callback)
		{
			(target->*callback)(pSender, clicked);
		}
	}

private:
	cocos2d::Ref*  target;
	SEL_MESSAGEBOX callback;
};

// 消息框最大长度
const int MAX_MESSAGEBOX_LEN = 256;

// 消息数据
struct STMessage
{
	MBStyle style;
	ccMBCallBack      callback;
	char              content[MAX_MESSAGEBOX_LEN];

	STMessage(MBStyle _style, const std::string &_content, ccMBCallBack _callback)
		: style(_style)
		, callback(_callback)
	{
		memcpy(content, _content.c_str(), MAX_MESSAGEBOX_LEN);
	}
};


class CSMessageBoxBase : public cocos2d::Node
{
public:
	CSMessageBoxBase(MBStyle style, const std::string &content, ccMBCallBack callback);
	~CSMessageBoxBase();

	// 初始化函数
	virtual bool init() override;

	// 创建函数
	static CSMessageBoxBase* create(MBStyle style, const std::string &content, ccMBCallBack callback);

	virtual void onEnter();

public:

	// 开启触摸
	void setTouchEnabled(bool bRet);


private:
	// 创建菜单
	void createMenuItem();

	void buttonEvent(Ref *pSender, Widget::TouchEventType type);

private:
	std::string					_strContent;
	MBStyle					   m_eStyle;
	ccMBCallBack			   m_callback;
	Node* _rootNode;

};

#endif