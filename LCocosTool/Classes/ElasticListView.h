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
////�б���
//class ElasticItem
//{
//public:
//	ElasticItem();
//	virtual ~ElasticItem();
//	//����
//	void Clear();
//	//����ElasticList
//	static ElasticItem* Create(Node *pRoot, Widget::ccWidgetTouchCallback callback, int itemIndex);
//	//SetIsHaveExtTxt
//	static void SetIsHaveExtTxt(bool isHave){ IsHaveExtTxt = isHave; }
//
//	//��ʼ��
//	virtual bool Init(Node *pRoot, Widget::ccWidgetTouchCallback callback, int itemIndex);
//
//
//public:
//	//�����б�ֵ
//	void SetValue(int value){ _ElasticItemValue = value; }
//	///��ȡ�б�ֵ
//	int GetValue(){ return _ElasticItemValue; }
//	//�����б�����
//	void SetItemName(const char *pName);
//	//�����б�������ɫ
//	void SetItemNameColor(const Color3B& color);
//	//�����б���չ�ı�
//	void SetExtTxt(const char *pName);
//	//������չ�ı���ɫ
//	void SetSetExtTxtColor(const Color3B& color);
//	//������չ�ı��Ƿ�ɼ�
//	void SetExtTextVisible(bool bset);
//	//��ȡ�ؼ����ڵ�
//	Node *GetRootNode(){ return _pElasticItemBtn; }
//	//����λ��
//	void SetPos(Vec2 &pos){ _pElasticItemBtn->setPosition(pos); }
//	//��ʾ����
//	void Show(bool bShow){ _pElasticItemBtn->setVisible(bShow); }
//	//ѡ�д���
//	void OnSelect();
//	//ȡ��ѡ�д���
//	void OnCancleSelect();
//	//����item�ı�λ��
//	void UpdateItemTxtPos();
//
//
//
//protected:
//
//	//
//	static bool IsHaveExtTxt;                //�Ƿ�����չTxt
//
//	int _itemIndex;                            //�б�������
//	int _ElasticItemValue;                    //�б���ֵ
//
//	//ui
//	Text* _pItemNameTxt;                    //ItemNameTxt
//	Text* _pExtTxt;                            //��չTxt
//	ui::Button* _pElasticItemBtn;            //�б��ť
//};
//
//
//
//typedef map<int, ElasticItem*> ElasticItemMap;    //�б�����
//
//class ElasticListView;
////����ʽ�б�
//class ElasticList
//{
//public:
//	//������������
//	enum ActionType
//	{
//		ActionNone = 0,        //û�ж���
//		ActionOut,            //����
//		ActionIn,            //����
//	};
//
//	//item list ״̬
//	enum ItemListState
//	{
//		ListStateOut = 0,        //����
//		ListStateIn,            //����
//	};
//
//public:
//	ElasticList();
//	virtual ~ElasticList();
//	//����
//	static ElasticList* Create(int listIndex, ElasticListView *pElasticListView);
//	//��ʼ��
//	virtual bool Init(int listIndex, ElasticListView *pElasticListView);
//public:
//	//�����б�ֵ
//	void SetValue(int value){ _elasticListValue = value; }
//	//��ȡ�б�ֵ
//	int GetValue(){ return _elasticListValue; }
//	//����listIndex
//	void SetListIndex(int value){ _listIndex = value; }
//	//��ȡlistIndex
//	int GetListIndex(){ return _listIndex; }
//	//�����б�����
//	void SetListName(const char *pName);
//	//��ȡ�ؼ����ڵ�
//	Node *GetRootNode(){ return _pListPanel; }
//	//��ȡListSize
//	Size GetListSize(){ return _pListPanel->getContentSize(); }
//	//��ȡList�߶�
//	float GetListHeight(){ return _totalHeight; }
//	//����λ��
//	void SetPos(Vec2 &pos){ _pListPanel->setPosition(pos); }
//	//����ElasticItem
//	void UpdateElasticItem();
//	//����ElasticItem txt pos
//	void UpdateElasticItemTxtPos();
//	//����
//	void Update(float dt);
//	//item touch callback
//	void OnItemTouch(Ref* pSender, Widget::TouchEventType touchuType);
//	//listname touch callback
//	void OnListNameTouch(Ref* pSender, Widget::TouchEventType touchuType);
//	//�ı�list state
//	void ChangeListState(ItemListState tarState);
//	//�Ƿ���������list
//	bool IsElasticing();
//	//����
//	void Clear();
//
//
//	//ѡ��item
//	void SelectItem(ElasticItem *pItem);
//	//��ȡitem
//	ElasticItem *GetItem(int itemIndex);
//	//���item
//	ElasticItem *AddItem(int itemIndex);
//	//ɾ��item
//	void DelItem(int itemIndex);
//
//protected:
//	//��������
//	void ActionOutUpdate(float dt);
//	//�������
//	void ActionInUpdate(float dt);
//
//protected:
//
//	//data
//	static const int NameVerticalPanding = 10;    //listname�Ϸ����
//	static const int ItemVerticalPanding = 6;    //ElasticItem�Ϸ����
//	static float ScaleSteep;                    //����ϵ��
//
//
//	bool _needUpdateUi;                            //��Ҫ����ui
//	int _elasticListValue;                        //�б�ֵ
//	int _listIndex;                                //list����
//	float _totalHeight;                            //�ܸ߶�
//
//
//	ElasticListView *_pElasticListView;            //ElasticListViewָ��
//
//	//action
//	ActionType _curActionType;                //��ǰ��������
//	ItemListState _curListState;            //��ǰlist״̬
//
//	//ui
//	Layout *_pListPanel;                    //�б�����
//	ui::Button *_pListName;                    //�б���
//	ElasticItemMap _itemList;                //�����б�
//};
//
//
//
//typedef map<int, ElasticList*> ElasticListMap;    //�б�map
//
//typedef std::function<void(int)> ElasticItemListener;
//
////����ʽ�б���ͼ���ں����ElasticList
//class ElasticListView
//{
//public:
//	ElasticListView();
//	virtual ~ElasticListView();
//	//��ȡlist��¡�ؼ�
//	Widget *GetElasticListClone(){ return _pElasticListClone; }
//	//��ȡitem��¡�ؼ�
//	Widget *GetElasticItemClone(){ return _pElasticItemClone; }
//
//	//����ElasticList
//	void AddElasticList(ElasticList *pElasticList);
//	//��ȡElasticList
//	ElasticList * GetElasticList(int index);
//
//
//public:
//	//��ʼ��
//	bool Init(Node *pRoot);
//	//ע�����
//	void RigisterUpdate();
//	//����
//	void Update(float dt);
//	//����ElasticList
//	void UpdateElasticList();
//	//�Ƿ���������list
//	bool IsElasticingList(){ return _isElasticing; }
//	//�����Ƿ���������list
//	void SetIsElasticingList(bool bSet);
//	//����ScrollView�ٷֱ�λ��
//	void SaveScrollViewPercent();
//	//�ָ�ScrollView�ٷֱ�λ��
//	void RecoveryScrollViewPercent();
//	//��ʼ����ǰ��׼��
//	void PrepareElastic();
//	//�Ƿ��������
//	bool CanElasticList();
//	//����ѡ����
//	void SetCurSelectItem(ElasticItem *pItem);
//	//����ѡ����
//	void SetCurSelectItem(int listIndex, int itemIndex);
//	//��ȡѡ����
//	ElasticItem *GetCurSelectItem(){ return _pCurSelectItem; }
//	//����ѡ�м����ص�
//	void SetItemListener(const ElasticItemListener &listener){ _pSelItemListener = listener; }
//	//����
//	void Clear();
//
//
//protected:
//
//	ElasticListMap _elasticListMap;                //�б�map
//	static const int VerticalPanding = 10;        //ElasticList��ֱ���
//	float _totalHeight;                            //�ܸ߶�
//	bool _isElasticing;                            //��������list
//	float _scrollViewPercent;                    //ScrollView�ٷֱ�λ��
//
//	ElasticItemListener _pSelItemListener;        //ѡ��item�¼�
//	ElasticItem *_pCurSelectItem;                //��ǰѡ�е�item
//
//	//ui
//	Widget *_pElasticListClone;                    //elasticList clone
//	Widget *_pElasticItemClone;                    //elasticItem clone
//	ui::ScrollView *_pConScrollView;            //ScrollView����
//};