//#include "ElasticListView.h"
//
////self
////#include "studioUi/commonFun/ComUiFun.h"
//
////using namespace StudioComFunSpce;
//
////-------------ElasticItem---------------------------------------------
//
//bool ElasticItem::IsHaveExtTxt = false;
//
//ElasticItem::ElasticItem()
//{
//	_ElasticItemValue = 0;
//	_itemIndex = 0;
//
//	_pElasticItemBtn = nullptr;
//	_pItemNameTxt = nullptr;
//	_pExtTxt = nullptr;
//}
//
//ElasticItem::~ElasticItem()
//{
//}
//void ElasticItem::Clear()
//{
//
//	_pElasticItemBtn->removeFromParentAndCleanup(0);
//}
//
//
//ElasticItem* ElasticItem::Create(Node *pRoot, Widget::ccWidgetTouchCallback callback, int itemIndex)
//{
//	ElasticItem * pRet = nullptr;
//
//	ElasticItem * pElasticItem = new (std::nothrow) ElasticItem();
//	if (pElasticItem && pElasticItem->Init(pRoot, callback, itemIndex))
//	{
//		pRet = pElasticItem;
//	}
//	else
//	{
//		CC_SAFE_DELETE(pRet);
//	}
//
//	return pRet;
//}
//
//bool ElasticItem::Init(Node *pRoot, Widget::ccWidgetTouchCallback callback, int itemIndex)
//{
//	bool ret = false;
//
//	do
//	{
//		_pElasticItemBtn = static_cast<ui::Button*>(pRoot);
//		CC_BREAK_IF(!_pElasticItemBtn || !callback);
//
//		Node *pNode = nullptr;
//
//
//		//
//		_itemIndex = itemIndex;
//
//		//btnTxt
//		pNode = FindUiChildNode(_pElasticItemBtn, "btnTxt");
//		_pItemNameTxt = static_cast<Text*>(pNode);
//		CC_BREAK_IF(!_pItemNameTxt);
//		//extBtnTxt0
//		if (IsHaveExtTxt)
//		{
//			pNode = FindUiChildNode(_pElasticItemBtn, "extBtnTxt0");
//			_pExtTxt = static_cast<Text*>(pNode);
//			CC_BREAK_IF(!_pExtTxt);
//		}
//
//
//
//		//UserData
//		_pElasticItemBtn->setUserData(this);
//		//event
//		_pElasticItemBtn->addTouchEventListener(callback);
//
//
//		ret = true;
//	} while (0);
//
//
//	return ret;
//}
//
//void ElasticItem::SetItemName(const char *pName)
//{
//	if (_pItemNameTxt)
//	{
//		_pItemNameTxt->setString(pName);
//	}
//}
//
//void ElasticItem::SetItemNameColor(const Color3B& color)
//{
//	if (_pItemNameTxt)
//	{
//		_pItemNameTxt->setColor(color);
//	}
//}
//
//void ElasticItem::SetExtTxt(const char *pName)
//{
//	if (_pExtTxt)
//	{
//		_pExtTxt->setString(pName);
//	}
//}
//
//void ElasticItem::SetExtTextVisible(bool bset)
//{
//	if (_pExtTxt)
//	{
//		_pExtTxt->setVisible(bset);
//	}
//}
//
//void ElasticItem::SetSetExtTxtColor(const Color3B& color)
//{
//	if (_pExtTxt)
//	{
//		_pExtTxt->setColor(color);
//	}
//}
//
//
//void ElasticItem::OnSelect()
//{
//	_pElasticItemBtn->setBright(false);
//	_pElasticItemBtn->setEnabled(false);
//}
//
//void ElasticItem::OnCancleSelect()
//{
//	_pElasticItemBtn->setBright(true);
//	_pElasticItemBtn->setEnabled(true);
//}
//
//void ElasticItem::UpdateItemTxtPos()
//{
//	bool bOnelyNameTxt = true;
//	Size itemSize = _pElasticItemBtn->getContentSize();
//	Size nameTxtSize = _pItemNameTxt->getContentSize();
//	Size extTxtSize;
//	Vec2 naemPos(itemSize.width / 2, itemSize.height / 2);
//	Vec2 extPos = naemPos;
//
//
//	if (_pExtTxt&&_pExtTxt->isVisible())
//	{
//		bOnelyNameTxt = false;
//		extTxtSize = _pExtTxt->getContentSize();
//	}
//
//
//	//只有ItemNameTxt
//	if (bOnelyNameTxt)
//	{
//		naemPos.x = (itemSize.width - nameTxtSize.width) / 2;
//
//		_pItemNameTxt->setPosition(naemPos);
//	}
//	else
//	{
//		naemPos.x = (itemSize.width - nameTxtSize.width - extTxtSize.width) / 2;
//		extPos.x = naemPos.x + nameTxtSize.width + 2;
//
//		_pItemNameTxt->setPosition(naemPos);
//		_pExtTxt->setPosition(extPos);
//	}
//
//
//}
//
////-------------ElasticList---------------------------------------------
//
//float ElasticList::ScaleSteep = 0.04f;
//
//
//ElasticList::ElasticList()
//{
//	_pListPanel = nullptr;
//	_pListName = nullptr;
//	_pElasticListView = nullptr;
//
//	_needUpdateUi = false;
//
//	_listIndex = 0;
//	_elasticListValue = 0;
//
//	_totalHeight = 0;
//
//	_curListState = ListStateOut;
//	_curActionType = ActionNone;
//}
//
//ElasticList::~ElasticList()
//{
//	//释放内存
//	ElasticItemMap::iterator it;
//	ElasticItem* pElasticItem = nullptr;
//	for (it = _itemList.begin(); it != _itemList.end();)
//	{
//		pElasticItem = it->second;
//		pElasticItem->Clear();
//		CC_SAFE_DELETE(pElasticItem);
//		it = _itemList.erase(it);
//	}
//}
//
//void ElasticList::Clear()
//{
//
//	_needUpdateUi = true;
//	_curListState = ListStateOut;
//	_curActionType = ActionNone;
//
//	//更新容器高度
//	_totalHeight = _pListName->getContentSize().height + NameVerticalPanding * 2;
//	Size panelSize = _pListPanel->getContentSize();
//	panelSize.height = _totalHeight;
//	_pListPanel->setContentSize(panelSize);
//
//
//	//释放内存
//	ElasticItemMap::iterator it;
//	ElasticItem* pElasticItem = nullptr;
//	for (it = _itemList.begin(); it != _itemList.end();)
//	{
//		pElasticItem = it->second;
//		pElasticItem->Clear();
//		CC_SAFE_DELETE(pElasticItem);
//		it = _itemList.erase(it);
//	}
//
//	_itemList.clear();
//}
//
//ElasticList* ElasticList::Create(int listIndex, ElasticListView *pElasticListView)
//{
//	ElasticList * pRet = nullptr;
//
//	ElasticList * pElasticList = new (std::nothrow) ElasticList();
//	if (pElasticList && pElasticList->Init(listIndex, pElasticListView))
//	{
//		pRet = pElasticList;
//	}
//	else
//	{
//		CC_SAFE_DELETE(pRet);
//	}
//
//	return pRet;
//}
//
//bool ElasticList::Init(int listIndex, ElasticListView *pElasticListView)
//{
//	bool ret = false;
//
//	do
//	{
//		CC_BREAK_IF(!pElasticListView);
//
//		_listIndex = listIndex;
//		_pElasticListView = pElasticListView;
//
//		//变量
//		char tc[128] = { 0 };
//		Node *pNode = nullptr;
//		Widget *pElasticItemClone = nullptr;
//		int itemHeight = 0;
//
//		//获取克隆控件
//		Widget *pElasticListClone = pElasticListView->GetElasticListClone();
//		CC_BREAK_IF(!pElasticListClone);
//
//		//ElasticList克隆控件
//		Widget *pElasticListTemp = pElasticListClone->clone();
//		CC_BREAK_IF(!pElasticListTemp);
//		pElasticListTemp->setVisible(true);
//
//		//修改控件名
//		sprintf(tc, "elasticList%d", _listIndex);
//		pElasticListTemp->setName(tc);
//
//		//elasticList
//		_pListPanel = static_cast<Layout*>(pElasticListTemp);
//		CC_BREAK_IF(!_pListPanel);
//
//		//elasticListName
//		pNode = FindUiChildNode(pElasticListTemp, "elasticListName");
//		_pListName = static_cast<ui::Button*>(pNode);
//		CC_BREAK_IF(!_pListName);
//		Widget::ccWidgetTouchCallback nameCallback = CC_CALLBACK_2(ElasticList::OnListNameTouch, this);
//		_pListName->addTouchEventListener(nameCallback);
//
//		//更新高度
//		_totalHeight = _totalHeight + _pListName->getContentSize().height + NameVerticalPanding * 2;
//
//		//elasticItem
//		pNode = FindUiChildNode(pElasticListTemp, "elasticItem");
//		pElasticItemClone = static_cast<Widget*>(pNode);
//		CC_BREAK_IF(!pElasticItemClone);
//		//itemHeight = pElasticItemClone->getContentSize().height + ItemVerticalPanding;
//
//		//设置更新标记
//		_needUpdateUi = true;
//
//		//删除item
//		pElasticListTemp->removeChild(pElasticItemClone);
//
//		ret = true;
//	} while (0);
//
//
//	return ret;
//}
//
//ElasticItem *ElasticList::AddItem(int itemIndex)
//{
//	ElasticItem* pElasticItem = nullptr;
//
//	do
//	{
//		//变量
//		char tc[128] = { 0 };
//		Node *pNode = nullptr;
//		Widget *pElasticItemClone = nullptr;
//		int itemHeight = 0;
//
//		//elasticItem克隆控件
//		pElasticItemClone = _pElasticListView->GetElasticItemClone();
//		CC_BREAK_IF(!pElasticItemClone);
//		itemHeight = pElasticItemClone->getContentSize().height + ItemVerticalPanding;
//
//		//更新高度
//		_totalHeight = _totalHeight + itemHeight;
//
//		Widget *pElasticItemTemp = pElasticItemClone->clone();
//		CC_BREAK_IF(!pElasticItemTemp);
//
//		//callback
//		Widget::ccWidgetTouchCallback callback = CC_CALLBACK_2(ElasticList::OnItemTouch, this);
//
//		//创建ElasticItem
//		pElasticItem = ElasticItem::Create(pElasticItemTemp, callback, itemIndex);
//		CC_BREAK_IF(!pElasticItem);
//
//		//修改控件名
//		sprintf(tc, "elasticItem%d", itemIndex);
//		pElasticItemTemp->setName(tc);
//
//		//添加
//		_pListPanel->addChild(pElasticItem->GetRootNode());
//		_itemList[itemIndex] = pElasticItem;
//
//		//设置更新标记
//		_needUpdateUi = true;
//
//
//
//	} while (0);
//
//	return pElasticItem;
//}
//
//void ElasticList::DelItem(int itemIndex)
//{
//	ElasticItemMap::iterator it = _itemList.find(itemIndex);
//	if (it != _itemList.end())
//	{
//		_itemList.erase(it);
//
//		//设置更新标记
//		_needUpdateUi = true;
//	}
//
//}
//
//void ElasticList::SetListName(const char *pName)
//{
//	do
//	{
//		CC_BREAK_IF(!pName);
//
//		Node *pNode = nullptr;
//		Text *pText = nullptr;
//
//		//btnTxt
//		pNode = FindUiChildNode(_pListName, "btnTxt");
//		pText = static_cast<Text*>(pNode);
//		CC_BREAK_IF(!pText);
//
//		pText->setString(pName);
//
//	} while (0);
//}
//
//void ElasticList::UpdateElasticItemTxtPos()
//{
//
//	//更新ElasticItem txt位置
//	ElasticItemMap::iterator it;
//	for (it = _itemList.begin(); it != _itemList.end(); it++)
//	{
//		ElasticItem* pElasticItem = it->second;
//		if (pElasticItem)
//		{
//			pElasticItem->UpdateItemTxtPos();
//		}
//	}
//}
//
//void  ElasticList::UpdateElasticItem()
//{
//	int totalHeight = _totalHeight;
//
//	Size panelSize = _pListPanel->getContentSize();
//	Size nameSizes = _pListName->getContentSize();
//
//	Vec2 pos(panelSize.width / 2, 0);
//
//
//	//更新ListName位置
//	pos.y = totalHeight - NameVerticalPanding;
//	_pListName->setPosition(pos);
//	totalHeight = totalHeight - NameVerticalPanding - nameSizes.height;
//
//	//更新ElasticItem位置
//	ElasticItemMap::iterator it;
//	for (it = _itemList.begin(); it != _itemList.end(); it++)
//	{
//		ElasticItem* pElasticItem = it->second;
//		if (pElasticItem)
//		{
//			Size itemSizes = pElasticItem->GetRootNode()->getContentSize();
//
//			pos.y = totalHeight - ItemVerticalPanding;
//			pElasticItem->SetPos(pos);
//
//			totalHeight = totalHeight - ItemVerticalPanding - itemSizes.height;
//		}
//	}
//
//
//	//更新容器高度
//	panelSize.height = _totalHeight;
//	_pListPanel->setContentSize(panelSize);
//
//	//更新ElasticList
//	_pElasticListView->UpdateElasticList();
//}
//
//void ElasticList::OnListNameTouch(Ref* pSender, Widget::TouchEventType touchuType)
//{
//	do
//	{
//		ui::Button *pBtn = static_cast<ui::Button*>(pSender);
//		CC_BREAK_IF(!pBtn);
//
//		if (touchuType == Widget::TouchEventType::BEGAN)
//		{
//			pBtn->setScale(1.2f);
//		}
//		else if (touchuType == Widget::TouchEventType::CANCELED)
//		{
//			pBtn->setScale(1.0f);
//		}
//		else if (touchuType == Widget::TouchEventType::MOVED)
//		{
//		}
//		else if (touchuType == Widget::TouchEventType::ENDED)
//		{
//			pBtn->setScale(1.0f);
//
//			//
//			if (_itemList.size() > 0)
//			{
//				if (_curActionType == ActionNone&&_pElasticListView->CanElasticList())
//				{
//					if (_curListState == ListStateIn)
//					{
//						ChangeListState(ListStateOut);
//					}
//					else if (_curListState == ListStateOut)
//					{
//						ChangeListState(ListStateIn);
//					}
//				}
//
//			}
//
//
//		}
//
//	} while (0);
//}
//
//void ElasticList::OnItemTouch(Ref* pSender, Widget::TouchEventType touchuType)
//{
//	do
//	{
//		ui::Button *pBtn = static_cast<ui::Button*>(pSender);
//		CC_BREAK_IF(!pBtn);
//
//		if (touchuType == Widget::TouchEventType::BEGAN)
//		{
//		}
//		else if (touchuType == Widget::TouchEventType::CANCELED)
//		{
//		}
//		else if (touchuType == Widget::TouchEventType::MOVED)
//		{
//		}
//		else if (touchuType == Widget::TouchEventType::ENDED)
//		{
//			void *p = pBtn->getUserData();
//			//int *pValue = (int*)p;
//			ElasticItem *pItem = (ElasticItem*)p;;
//			CC_BREAK_IF(!pItem);
//
//			//选中
//			SelectItem(pItem);
//
//		}
//
//	} while (0);
//}
//
//void ElasticList::SelectItem(ElasticItem *pItem)
//{
//	do
//	{
//		CC_BREAK_IF(!pItem);
//		ElasticItem *pLastItem = _pElasticListView->GetCurSelectItem();
//		if (pItem != pLastItem)
//		{
//			//取消选中处理
//			if (pLastItem)
//				pLastItem->OnCancleSelect();
//			//选中处理
//			pItem->OnSelect();
//			//保存指针
//			_pElasticListView->SetCurSelectItem(pItem);
//		}
//
//
//
//	} while (0);
//
//}
//
//bool ElasticList::IsElasticing()
//{
//	bool ret = false;
//
//	if (_curActionType != ActionNone)
//		ret = true;
//
//	return ret;
//}
//
//
//ElasticItem * ElasticList::GetItem(int itemIndex)
//{
//	ElasticItem *pRet = nullptr;
//	do
//	{
//		ElasticItem* pItem = _itemList.at(itemIndex);
//		CC_BREAK_IF(!pItem);
//
//		pRet = pItem;
//	} while (0);
//
//
//	return pRet;
//}
//
//void ElasticList::ChangeListState(ItemListState tarState)
//{
//	if (_curActionType == ActionNone&&_curListState != tarState)
//	{
//		if (tarState == ListStateIn)
//		{
//			_curActionType = ActionIn;
//
//			//设置正在缩放
//			_pElasticListView->SetIsElasticingList(true);
//		}
//		else if (tarState == ListStateOut)
//		{
//			_curActionType = ActionOut;
//
//			//设置正在缩放
//			_pElasticListView->SetIsElasticingList(true);
//
//			//ElasticItem处理
//			ElasticItemMap::iterator it;
//			for (it = _itemList.begin(); it != _itemList.end(); it++)
//			{
//				ElasticItem* pElasticItem = it->second;
//				if (pElasticItem)
//					pElasticItem->Show(true);
//
//			}
//		}
//	}
//}
//
//void ElasticList::Update(float dt)
//{
//	if (_needUpdateUi)
//	{
//		//更新ElasticItem
//		UpdateElasticItem();
//
//		_needUpdateUi = false;
//	}
//
//
//	if (_curActionType != ActionNone)
//	{
//		if (_curActionType == ActionIn)
//			ActionInUpdate(dt);
//		else if (_curActionType == ActionOut)
//			ActionOutUpdate(dt);
//	}
//
//
//
//}
//
//void ElasticList::ActionOutUpdate(float dt)
//{
//	do
//	{
//		int count = _itemList.size();
//		CC_BREAK_IF(count == 0);
//		ElasticItemMap::iterator it = _itemList.begin();
//		ElasticItem* pFirstItem = it->second;
//		CC_BREAK_IF(!pFirstItem);
//
//		//scale
//		static float totalScale = 0.01f;
//		totalScale += ScaleSteep;
//
//		float verticalPanding = ItemVerticalPanding*totalScale;
//		//
//
//
//		Size panelSize = _pListPanel->getContentSize();
//		Size nameSizes = _pListName->getContentSize();
//		Size itemSize = pFirstItem->GetRootNode()->getContentSize();
//		float totalHeight = (itemSize.height + ItemVerticalPanding)*totalScale*count + (nameSizes.height + NameVerticalPanding * 2);
//		Vec2 pos(panelSize.width / 2, 0);
//
//		//更新容器高度
//		panelSize.height = totalHeight;
//		_pListPanel->setContentSize(panelSize);
//
//		//更新ListName位置
//		pos.y = totalHeight - NameVerticalPanding;
//		_pListName->setPosition(pos);
//		totalHeight = totalHeight - NameVerticalPanding - nameSizes.height;
//
//		//更新ElasticItem位置
//		for (it = _itemList.begin(); it != _itemList.end(); it++)
//		{
//			ElasticItem* pElasticItem = it->second;
//			if (pElasticItem)
//			{
//				Node *pItemRoot = pElasticItem->GetRootNode();
//				//scale
//				pItemRoot->setScaleY(totalScale);
//				//size
//				Size itemSizes = pItemRoot->getContentSize();
//
//				pos.y = totalHeight - verticalPanding;
//				pElasticItem->SetPos(pos);
//
//				totalHeight = totalHeight - verticalPanding - itemSizes.height*totalScale;
//			}
//		}
//
//
//		//结束处理
//		if (totalScale >= 0.95f)
//		{
//			//ElasticItem处理
//			for (it = _itemList.begin(); it != _itemList.end(); it++)
//			{
//				ElasticItem* pElasticItem = it->second;
//				if (pElasticItem)
//				{
//					Node *pItemRoot = pElasticItem->GetRootNode();
//					//scale
//					pItemRoot->setScaleY(1.0f);
//				}
//			}
//
//			//更新ElasticItem
//			UpdateElasticItem();
//
//			//更新ElasticListView
//			_pElasticListView->UpdateElasticList();
//			//设置结束缩放
//			_pElasticListView->SetIsElasticingList(false);
//
//
//			//状态设置
//			_curActionType = ActionNone;
//			_curListState = ListStateOut;
//			totalScale = 0.01f;
//		}
//
//	} while (0);
//}
//
//void ElasticList::ActionInUpdate(float dt)
//{
//	do
//	{
//		int count = _itemList.size();
//		CC_BREAK_IF(count == 0);
//		ElasticItemMap::iterator it = _itemList.begin();
//		ElasticItem* pFirstItem = it->second;
//		CC_BREAK_IF(!pFirstItem);
//		//scale
//		static float totalScale = 1.0f;
//		totalScale -= ScaleSteep;
//
//		float verticalPanding = ItemVerticalPanding*totalScale;
//		//
//
//
//		Size panelSize = _pListPanel->getContentSize();
//		Size nameSizes = _pListName->getContentSize();
//		Size itemSize = pFirstItem->GetRootNode()->getContentSize();
//		float totalHeight = (itemSize.height + ItemVerticalPanding)*totalScale*count + (nameSizes.height + NameVerticalPanding * 2);
//		//totalHeight = (_totalHeight - nameSizes.height - VerticalPanding)*totalScale;
//
//		Vec2 pos(panelSize.width / 2, 0);
//
//		//更新容器高度
//		panelSize.height = totalHeight;
//		_pListPanel->setContentSize(panelSize);
//
//		//更新ListName位置
//		pos.y = totalHeight - NameVerticalPanding;
//		_pListName->setPosition(pos);
//		totalHeight = totalHeight - NameVerticalPanding - nameSizes.height;
//
//		//更新ElasticItem位置
//		for (it = _itemList.begin(); it != _itemList.end(); it++)
//		{
//			ElasticItem* pElasticItem = it->second;
//			if (pElasticItem)
//			{
//				Node *pItemRoot = pElasticItem->GetRootNode();
//				//scale
//				pItemRoot->setScaleY(totalScale);
//				//size
//				Size itemSizes = pItemRoot->getContentSize();
//
//				pos.y = totalHeight - verticalPanding;
//				pElasticItem->SetPos(pos);
//
//				totalHeight = totalHeight - verticalPanding - itemSizes.height*totalScale;
//			}
//		}
//
//
//		//结束处理
//		if (totalScale <= 0.01f)
//		{
//			//ElasticItem处理
//			for (it = _itemList.begin(); it != _itemList.end(); it++)
//			{
//				ElasticItem* pElasticItem = it->second;
//				if (pElasticItem)
//					pElasticItem->Show(false);
//
//			}
//
//			//更新容器高度
//			//_totalHeight = nameSizes.height + NameVerticalPanding * 2;
//			panelSize.height = nameSizes.height + NameVerticalPanding * 2;
//			_pListPanel->setContentSize(panelSize);
//
//			//更新ListName位置
//			pos.y = panelSize.height - NameVerticalPanding;
//			_pListName->setPosition(pos);
//
//
//			//更新ElasticListView
//			_pElasticListView->UpdateElasticList();
//
//
//			//设置结束缩放
//			_pElasticListView->SetIsElasticingList(false);
//
//
//			//状态设置
//			_curActionType = ActionNone;
//			_curListState = ListStateIn;
//			totalScale = 1.0f;
//		}
//
//	} while (0);
//}
//
////-------------ElasticListView---------------------------------------------
//
//
//
//ElasticListView::ElasticListView()
//{
//	_totalHeight = 0;
//	_isElasticing = false;
//
//	_pCurSelectItem = nullptr;
//	_pSelItemListener = nullptr;
//	_pElasticListClone = nullptr;
//}
//
//ElasticListView::~ElasticListView()
//{
//
//	//取消更新
//	Director::getInstance()->getScheduler()->unschedule("ElasticListView::Update", this);
//
//	//释放内存
//	ElasticListMap::iterator it;
//	ElasticList* pElasticList = nullptr;
//	for (it = _elasticListMap.begin(); it != _elasticListMap.end();)
//	{
//		pElasticList = it->second;
//		CC_SAFE_DELETE(pElasticList);
//		it = _elasticListMap.erase(it);
//	}
//}
//
//
//
//void ElasticListView::Clear()
//{
//
//
//	_pCurSelectItem = nullptr;
//	_totalHeight = 0;
//	_isElasticing = false;
//
//	int count = _elasticListMap.size();
//
//
//	_totalHeight = 0;
//	for (int i = 0; i < count; i++)
//	{
//		ElasticList* pElasticList = _elasticListMap.at(i);
//		if (pElasticList)
//		{
//			pElasticList->Clear();
//		}
//	}
//
//
//}
//
//bool ElasticListView::Init(Node *pRoot)
//{
//	bool ret = false;
//
//	do
//	{
//
//		CC_BREAK_IF(!pRoot);
//
//		//
//		Node *pNode = nullptr;
//
//		//elasticListView
//		pNode = FindUiChildNode(pRoot, "elasticListView");
//		_pConScrollView = static_cast<ui::ScrollView*>(pNode);
//		_pConScrollView->SetBounceBackDuration(0.5f);
//		//_pConScrollView->setBounceEnabled(false);
//
//
//		//elasticListClone
//		pNode = FindUiChildNode(_pConScrollView, "elasticListClone");
//		_pElasticListClone = static_cast<Widget*>(pNode);
//		CC_BREAK_IF(!_pElasticListClone);
//		_pElasticListClone->setVisible(false);
//
//		//elasticItem
//		pNode = FindUiChildNode(_pElasticListClone, "elasticItem");
//		_pElasticItemClone = static_cast<Widget*>(pNode);
//		CC_BREAK_IF(!_pElasticItemClone);
//
//
//
//		ret = true;
//	} while (0);
//
//
//	return ret;
//}
//
//
//void ElasticListView::RigisterUpdate()
//{
//	//注册更新
//	ccSchedulerFunc updateCall = CC_CALLBACK_1(ElasticListView::Update, this);
//	Director::getInstance()->getScheduler()->schedule(updateCall, this, 0, false, "ElasticListView::Update");
//}
//
//void ElasticListView::AddElasticList(ElasticList *pElasticList)
//{
//
//	do
//	{
//		CC_BREAK_IF(!pElasticList);
//
//		//char tc[128] = { 0 };
//
//		int index = pElasticList->GetListIndex();
//
//		////set list name
//		//sprintf(tc, "ElasticList%d", index);
//		//pElasticList->SetListName(tc);
//
//		//添加
//		_pConScrollView->addChild(pElasticList->GetRootNode());
//
//		_elasticListMap[index] = pElasticList;
//
//	} while (0);
//}
//
//ElasticList* ElasticListView::GetElasticList(int index)
//{
//	ElasticList* pRet = nullptr;
//
//	ElasticListMap::iterator it = _elasticListMap.find(index);
//	if (it != _elasticListMap.end())
//	{
//		pRet = it->second;
//	}
//
//	return pRet;
//}
//
//void ElasticListView::UpdateElasticList()
//{
//
//	int count = _elasticListMap.size();
//	Size panelSize = _pConScrollView->getContentSize();
//	float totalHeight = 0;
//	Vec2 pos(panelSize.width / 2, 0);
//
//	//更新_totalHeight,itemtx pos
//	_totalHeight = 0;
//	for (int i = 0; i < count; i++)
//	{
//		ElasticList* pElasticList = _elasticListMap.at(i);
//		if (pElasticList)
//		{
//			_totalHeight = _totalHeight + pElasticList->GetListSize().height + VerticalPanding;
//
//			//itemtx pos
//			pElasticList->UpdateElasticItemTxtPos();
//		}
//	}
//
//	//高度保护
//	if (_totalHeight < panelSize.height)
//	{
//		_totalHeight = panelSize.height + 10;
//	}
//	totalHeight = _totalHeight;
//
//	//更新ElasticList位置
//	for (int i = 0; i < count; i++)
//	{
//		ElasticList* pElasticList = _elasticListMap.at(i);
//		if (pElasticList)
//		{
//			pos.y = totalHeight - VerticalPanding;
//			pElasticList->SetPos(pos);
//
//			totalHeight = totalHeight - VerticalPanding - pElasticList->GetListSize().height;
//		}
//	}
//
//	//更新容器高度
//	panelSize.height = _totalHeight;
//	_pConScrollView->setInnerContainerSize(panelSize);
//}
//
//void ElasticListView::Update(float dt)
//{
//	bool bUpdateList = false;
//	ElasticListMap::iterator it;
//	for (it = _elasticListMap.begin(); it != _elasticListMap.end(); it++)
//	{
//		it->second->Update(dt);
//		if (it->second->IsElasticing())
//			bUpdateList = true;
//	}
//
//	if (bUpdateList)
//	{
//		UpdateElasticList();
//	}
//}
//
//void ElasticListView::SetIsElasticingList(bool bSet)
//{
//	_isElasticing = bSet;
//	//if (bSet)
//	//{
//	//    SaveScrollViewPercent();
//	//}
//	//else
//	//{
//	//    RecoveryScrollViewPercent();
//	//}
//
//}
//
//void ElasticListView::SaveScrollViewPercent()
//{
//	CCLOG("-----------------SaveScrollViewPercent--------------------");
//
//	Size panelSize = _pConScrollView->getContentSize();
//	Size innerSize = _pConScrollView->getInnerContainerSize();
//	Vec2 innerlPos = _pConScrollView->getInnerContainerPosition();
//
//	float minY = panelSize.height - innerSize.height;
//	float h = -minY;
//
//	float percent = innerlPos.y * 100 / h;
//
//	if (percent < 0)
//		percent = -percent;
//
//	_scrollViewPercent = percent;
//
//	CCLOG("--panelSize:(%f,%f)", panelSize.width, panelSize.height);
//	CCLOG("--innerSize:(%f,%f)", innerSize.width, innerSize.height);
//	CCLOG("--innerlPos:(%f,%f)", innerlPos.x, innerlPos.y);
//	CCLOG("--minY=%f,percent=%f", minY, percent);
//}
//
//void ElasticListView::RecoveryScrollViewPercent()
//{
//	CCLOG("-----------------RecoveryScrollViewPercent--------------------");
//
//	Size panelSize = _pConScrollView->getContentSize();
//	Size innerSize = _pConScrollView->getInnerContainerSize();
//	Vec2 innerlPos = _pConScrollView->getInnerContainerPosition();
//
//	float minY = panelSize.height - innerSize.height;
//	float h = -minY;
//
//	float percent = innerlPos.y * 100 / h;
//
//	if (percent < 0)
//		percent = -percent;
//
//	CCLOG("--panelSize:(%f,%f)", panelSize.width, panelSize.height);
//	CCLOG("--innerSize:(%f,%f)", innerSize.width, innerSize.height);
//	CCLOG("--innerlPos:(%f,%f)", innerlPos.x, innerlPos.y);
//	CCLOG("--minY=%f,percent=%f", minY, percent);
//
//	//_pConScrollView->scrollToPercentVertical(_scrollViewPercent, 0.5f,false);
//}
//
//void ElasticListView::PrepareElastic()
//{
//	Size panelSize = _pConScrollView->getContentSize();
//	Size innerSize = _pConScrollView->getInnerContainerSize();
//	Vec2 innerlPos = _pConScrollView->getInnerContainerPosition();
//
//	float minY = panelSize.height - innerSize.height;
//
//	//if (innerlPos.y>)ISAutoScrolling
//	//{
//	//}
//
//}
//
//bool ElasticListView::CanElasticList()
//{
//	bool ret = false;
//	bool isScrooling = _pConScrollView->ISAutoScrolling();
//	bool isElasticing = IsElasticingList();
//
//	if (!isScrooling)
//	{
//		if (!isElasticing)
//		{
//			ret = true;
//		}
//	}
//
//
//	return ret;
//}
//
//void ElasticListView::SetCurSelectItem(ElasticItem *pItem)
//{
//	do
//	{
//		CC_BREAK_IF(!pItem);
//		_pCurSelectItem = pItem;
//
//		//选中item事件
//		if (_pSelItemListener)
//		{
//			_pSelItemListener(_pCurSelectItem->GetValue());
//		}
//
//	} while (0);
//
//}
//
//void ElasticListView::SetCurSelectItem(int listIndex, int itemIndex)
//{
//	do
//	{
//		ElasticList* pList = _elasticListMap.at(listIndex);
//		CC_BREAK_IF(!pList);
//		ElasticItem *pItem = pList->GetItem(itemIndex);
//		CC_BREAK_IF(!pItem);
//
//		_pCurSelectItem = pItem;
//
//		//选中item事件
//		if (_pSelItemListener)
//		{
//			_pSelItemListener(_pCurSelectItem->GetValue());
//		}
//
//	} while (0);
//
//}