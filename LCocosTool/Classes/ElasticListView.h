//#pragma once
//
////std
//#include <string>
//#include <map>
//
////cocos
//#include "cocos2d.h"
//#include "cocostudio/CocoStudio.h"
//#include "ui/CocosGUI.h"
//
////self
////#include "studioUi/StudioUiBase.h"
//
//
//using namespace std;
//
//USING_NS_CC;
//using namespace cocos2d::ui;
//using namespace cocostudio;
//using namespace cocostudio::timeline;
//
//
////列表项
//class ElasticItem
//{
//public:
//	ElasticItem();
//	virtual ~ElasticItem();
//	//清理
//	void Clear();
//	//创建ElasticList
//	static ElasticItem* Create(Node *pRoot, Widget::ccWidgetTouchCallback callback, int itemIndex);
//	//SetIsHaveExtTxt
//	static void SetIsHaveExtTxt(bool isHave){ IsHaveExtTxt = isHave; }
//
//	//初始化
//	virtual bool Init(Node *pRoot, Widget::ccWidgetTouchCallback callback, int itemIndex);
//
//
//public:
//	//设置列表值
//	void SetValue(int value){ _ElasticItemValue = value; }
//	///获取列表值
//	int GetValue(){ return _ElasticItemValue; }
//	//设置列表名称
//	void SetItemName(const char *pName);
//	//设置列表名称颜色
//	void SetItemNameColor(const Color3B& color);
//	//设置列表扩展文本
//	void SetExtTxt(const char *pName);
//	//设置扩展文本颜色
//	void SetSetExtTxtColor(const Color3B& color);
//	//设置扩展文本是否可见
//	void SetExtTextVisible(bool bset);
//	//获取控件根节点
//	Node *GetRootNode(){ return _pElasticItemBtn; }
//	//设置位置
//	void SetPos(Vec2 &pos){ _pElasticItemBtn->setPosition(pos); }
//	//显示隐藏
//	void Show(bool bShow){ _pElasticItemBtn->setVisible(bShow); }
//	//选中处理
//	void OnSelect();
//	//取消选中处理
//	void OnCancleSelect();
//	//更新item文本位置
//	void UpdateItemTxtPos();
//
//
//
//protected:
//
//	//
//	static bool IsHaveExtTxt;                //是否有扩展Txt
//
//	int _itemIndex;                            //列表项索引
//	int _ElasticItemValue;                    //列表项值
//
//	//ui
//	Text* _pItemNameTxt;                    //ItemNameTxt
//	Text* _pExtTxt;                            //扩展Txt
//	ui::Button* _pElasticItemBtn;            //列表项按钮
//};
//
//
//
//typedef map<int, ElasticItem*> ElasticItemMap;    //列表子项
//
//class ElasticListView;
////弹出式列表
//class ElasticList
//{
//public:
//	//弹出弹入类型
//	enum ActionType
//	{
//		ActionNone = 0,        //没有动作
//		ActionOut,            //弹出
//		ActionIn,            //弹入
//	};
//
//	//item list 状态
//	enum ItemListState
//	{
//		ListStateOut = 0,        //弹出
//		ListStateIn,            //弹入
//	};
//
//public:
//	ElasticList();
//	virtual ~ElasticList();
//	//创建
//	static ElasticList* Create(int listIndex, ElasticListView *pElasticListView);
//	//初始化
//	virtual bool Init(int listIndex, ElasticListView *pElasticListView);
//public:
//	//设置列表值
//	void SetValue(int value){ _elasticListValue = value; }
//	//获取列表值
//	int GetValue(){ return _elasticListValue; }
//	//设置listIndex
//	void SetListIndex(int value){ _listIndex = value; }
//	//获取listIndex
//	int GetListIndex(){ return _listIndex; }
//	//设置列表名称
//	void SetListName(const char *pName);
//	//获取控件根节点
//	Node *GetRootNode(){ return _pListPanel; }
//	//获取ListSize
//	Size GetListSize(){ return _pListPanel->getContentSize(); }
//	//获取List高度
//	float GetListHeight(){ return _totalHeight; }
//	//设置位置
//	void SetPos(Vec2 &pos){ _pListPanel->setPosition(pos); }
//	//更新ElasticItem
//	void UpdateElasticItem();
//	//更新ElasticItem txt pos
//	void UpdateElasticItemTxtPos();
//	//更新
//	void Update(float dt);
//	//item touch callback
//	void OnItemTouch(Ref* pSender, Widget::TouchEventType touchuType);
//	//listname touch callback
//	void OnListNameTouch(Ref* pSender, Widget::TouchEventType touchuType);
//	//改变list state
//	void ChangeListState(ItemListState tarState);
//	//是否正在伸缩list
//	bool IsElasticing();
//	//清理
//	void Clear();
//
//
//	//选中item
//	void SelectItem(ElasticItem *pItem);
//	//获取item
//	ElasticItem *GetItem(int itemIndex);
//	//添加item
//	ElasticItem *AddItem(int itemIndex);
//	//删除item
//	void DelItem(int itemIndex);
//
//protected:
//	//弹出更新
//	void ActionOutUpdate(float dt);
//	//弹入更新
//	void ActionInUpdate(float dt);
//
//protected:
//
//	//data
//	static const int NameVerticalPanding = 10;    //listname上方间距
//	static const int ItemVerticalPanding = 6;    //ElasticItem上方间距
//	static float ScaleSteep;                    //缩放系数
//
//
//	bool _needUpdateUi;                            //需要更新ui
//	int _elasticListValue;                        //列表值
//	int _listIndex;                                //list索引
//	float _totalHeight;                            //总高度
//
//
//	ElasticListView *_pElasticListView;            //ElasticListView指针
//
//	//action
//	ActionType _curActionType;                //当前动作类型
//	ItemListState _curListState;            //当前list状态
//
//	//ui
//	Layout *_pListPanel;                    //列表容器
//	ui::Button *_pListName;                    //列表名
//	ElasticItemMap _itemList;                //子项列表
//};
//
//
//
//typedef map<int, ElasticList*> ElasticListMap;    //列表map
//
//typedef std::function<void(int)> ElasticItemListener;
//
////弹出式列表视图，内含多个ElasticList
//class ElasticListView
//{
//public:
//	ElasticListView();
//	virtual ~ElasticListView();
//	//获取list克隆控件
//	Widget *GetElasticListClone(){ return _pElasticListClone; }
//	//获取item克隆控件
//	Widget *GetElasticItemClone(){ return _pElasticItemClone; }
//
//	//创建ElasticList
//	void AddElasticList(ElasticList *pElasticList);
//	//获取ElasticList
//	ElasticList * GetElasticList(int index);
//
//
//public:
//	//初始化
//	bool Init(Node *pRoot);
//	//注册更新
//	void RigisterUpdate();
//	//更新
//	void Update(float dt);
//	//更新ElasticList
//	void UpdateElasticList();
//	//是否正在缩放list
//	bool IsElasticingList(){ return _isElasticing; }
//	//设置是否正在缩放list
//	void SetIsElasticingList(bool bSet);
//	//保存ScrollView百分比位置
//	void SaveScrollViewPercent();
//	//恢复ScrollView百分比位置
//	void RecoveryScrollViewPercent();
//	//开始伸缩前的准备
//	void PrepareElastic();
//	//是否可以伸缩
//	bool CanElasticList();
//	//设置选中项
//	void SetCurSelectItem(ElasticItem *pItem);
//	//设置选中项
//	void SetCurSelectItem(int listIndex, int itemIndex);
//	//获取选中项
//	ElasticItem *GetCurSelectItem(){ return _pCurSelectItem; }
//	//设置选中监听回调
//	void SetItemListener(const ElasticItemListener &listener){ _pSelItemListener = listener; }
//	//清理
//	void Clear();
//
//
//protected:
//
//	ElasticListMap _elasticListMap;                //列表map
//	static const int VerticalPanding = 10;        //ElasticList垂直间距
//	float _totalHeight;                            //总高度
//	bool _isElasticing;                            //正在缩放list
//	float _scrollViewPercent;                    //ScrollView百分比位置
//
//	ElasticItemListener _pSelItemListener;        //选中item事件
//	ElasticItem *_pCurSelectItem;                //当前选中的item
//
//	//ui
//	Widget *_pElasticListClone;                    //elasticList clone
//	Widget *_pElasticItemClone;                    //elasticItem clone
//	ui::ScrollView *_pConScrollView;            //ScrollView容器
//};