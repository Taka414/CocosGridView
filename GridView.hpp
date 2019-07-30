#pragma once
#pragma execution_character_set("utf-8")

#include "CreateFunc.hpp"

#include "cocos2d.h"
#include "ui/CocosGUI.h"

/**
 * ListView を GridView 風に扱うための簡単な管理機能を定義します。
 */
class GridView : public cocos2d::Ref, CreateFunc<GridView>
{
protected:
    
    // 制御対象のリスト
    cocos2d::ui::ListView* listview = nullptr;
    // 1行の大きさ
    float rowHeight = 0;
    // 1行に入る要素の数
    int rowItemCount = 0;
    // デフォルトのListViewの中身のコンテナサイズ
    cocos2d::Size defaultInnerContainerSize;
    // 行内の要素のマージン
    float itemMarginLeft = 0;
    // 要素のオフセット
    cocos2d::Point itemOffset = cocos2d::Point(0, 0);

public:

    using CreateFunc::create;
    virtual bool init(cocos2d::ui::ListView* listview, float rowHeight, int rowItemCount);

    // 要素を追加するとに加算するオフセット
    void setItemOffset(const cocos2d::Point& offset) { this->itemOffset = offset; }
    cocos2d::Point getImteOffset() { return this->itemOffset; }

    // 行内の要素と要素の間のスペースを設定または取得する
    void setItemMarginLeft(float value) { this->itemMarginLeft = value; }
    float getItemMarginLeft() { return this->itemMarginLeft; }

    // キーを指定して要素を1件追加する
    virtual void add(cocos2d::ui::Widget* item);
    // 名前を指定して要素を1件削除する
    virtual void remove(const std::string& widgetName);
    // 要素をすべて削除する
    virtual void clearAll();
    
    // 表示中の要素をすべて取得する
    std::vector<cocos2d::ui::Widget*> getItems();
    // 指定した名前の要素を取得する、取得できない場合 nullptr
    cocos2d::ui::Widget* findItem(const std::string& widgetName);
    // 全ての要素数を取得する
    int getItemCount();

protected:

    // 1行のデータを格納するパネルを設定する
    cocos2d::ui::Layout* addPanel();
    // 1行のデータを格納するパネルを取得する
    cocos2d::ui::Layout* getPanel(int no);
    // 1行のデータを格納するパネルの現在の行数を取得する
    int getPanelCount();
};
