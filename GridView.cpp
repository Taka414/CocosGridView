#include "GridView.hpp"

using namespace std;
using namespace cocos2d;
using namespace cocos2d::ui;

bool GridView::init(cocos2d::ui::ListView* listview, float rowHeight, int rowItemCount)
{
    this->listview = listview;
    this->rowHeight = rowHeight;
    this->rowItemCount = rowItemCount;
    this->defaultInnerContainerSize = listview->getInnerContainerSize();
    
    return true;
}

void GridView::add(cocos2d::ui::Widget* item)
{
    // 要素を追加するパネル
    cocos2d::ui::Layout* panel = nullptr;

    // 最後行のパネルを取得・1行も無ければ新規追加
    if (this->getPanelCount() == 0)
    {
        panel = this->addPanel();
    }
    else
    {
        panel = this->getPanel(this->getPanelCount() - 1); // 最後列の末尾に追加
    }

    // 1列にN個までしか入らないのでそれ以上なら新しいパネルを作成する
    if (panel->getChildrenCount() >= this->rowItemCount)
    {
        panel = this->addPanel();
    }

    // 新しい要素の左からの位置の決定
    float xpos = 0;
    if (panel->getChildrenCount() != 0)
    {
        auto item = panel->getChildren().at(panel->getChildrenCount() - 1);
        xpos = item->getPositionX() + item->getContentSize().width + this->itemMarginLeft;
    }

    item->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
    item->setPosition({ xpos + this->itemOffset.x, this->itemOffset.y });
    panel->addChild(item);
}

void GridView::remove(const std::string& widgetName)
{
    Widget* item = this->findItem(widgetName);
    if (item == nullptr)
    {
        CCLOG("%s, 指定した要素は見つからなかった。widgetName = %s", __FUNCTION__, widgetName.c_str());
        return;
    }

    auto list = this->getItems();
    for (auto&& c : list)
    {
        c->retain();
    }

    this->clearAll();
    
    for (const auto& item : list)
    {
        if (item->getName() == widgetName)
        {
            continue;
        }

        this->add(item);
    }

    for (auto&& c : list)
    {
        c->release();
    }
}

void GridView::clearAll()
{
    this->listview->stopAutoScroll();
    this->listview->removeAllItems();
    this->listview->setInnerContainerSize(this->defaultInnerContainerSize);
    this->listview->scrollToTop(0.2f, true);
}

std::vector<cocos2d::ui::Widget*> GridView::getItems()
{
    vector<Widget*> list;

    for (const auto& panel : this->listview->getItems())
    {
        for (const auto& item : panel->getChildren())
        {
            list.push_back(static_cast<Widget*>(item));
        }
    }

    return list;
}

cocos2d::ui::Widget* GridView::findItem(const std::string& widgetName)
{
    for (const auto& panel : this->listview->getItems())
    {
        for (const auto& item : panel->getChildren())
        {
            if (item->getName() == widgetName)
            {
                return static_cast<Widget*>(item);
            }
        }
    }

    return nullptr;
}

int GridView::getItemCount()
{
    int cnt = 0;
    for (int i = 0; i < this->getPanelCount(); i++)
    {
        cnt += this->getPanel(i)->getChildrenCount();
    }
    return cnt;
}

cocos2d::ui::Layout* GridView::addPanel()
{
    Layout* panel = Layout::create();
    panel->setContentSize({ this->defaultInnerContainerSize.width, this->rowHeight });
    this->listview->addChild(panel);
    return panel;
}

cocos2d::ui::Layout* GridView::getPanel(int no)
{
    return static_cast<Layout*>(this->listview->getItem(no));
}

int GridView::getPanelCount()
{
    return (int)this->listview->getItems().size();
}

