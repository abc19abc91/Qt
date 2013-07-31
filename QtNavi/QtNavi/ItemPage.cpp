#include "ItemPage.h"
#include "BaseItem.h"

ItemPage::ItemPage(QGraphicsItem *parent)
	: QGraphicsItemGroup(parent)
	,m_nPageIndex(0)
	,m_nRowCount(0)
	,m_nColCount(0)
	,m_nItemWidth(0)
	,m_nItemHeight(0)
	,m_nMarginsLeft(0)
	,m_nMarginsTop(0)
	,m_nMarginsRight(0)
	,m_nMarginsBottom(0)
	,m_nPageWidth(0)
	,m_nPageHeight(0)
{

}

ItemPage::~ItemPage()
{

}

// QRectF ItemPage::boundingRect() const
// {
// 	return QRectF(0, 0, 0, 0);
// }



void ItemPage::setPageIndex(const int& nIndex)
{
	m_nPageIndex = nIndex;
}

bool ItemPage::addBaseItem(BaseItem * pItem)
{
	if (pItem->rowIndex() > m_nRowCount - 1 || pItem->colIndex() > m_nColCount - 1)
	{
		return false;
	}
	this->addToGroup(pItem);
	//计算坐标
	//X
	int xSpace =  0;
	int xStart = 0;
	if (m_nColCount > 1)
	{
		xSpace = (m_nPageWidth - m_nMarginsLeft - m_nMarginsRight - m_nColCount*m_nItemWidth)/(m_nColCount - 1);
		xStart = m_nMarginsLeft + (m_nItemWidth + xSpace) * pItem->colIndex();
	}
	else
	{
		xStart = m_nPageWidth - m_nMarginsLeft - m_nMarginsRight - m_nItemWidth /2;
	}
	//Y
	int ySpace =  0;
	int yStart = 0;
	if (m_nRowCount > 1)
	{
		ySpace = (m_nPageHeight - m_nMarginsTop - m_nMarginsBottom - m_nRowCount*m_nItemHeight)/(m_nRowCount - 1);
		yStart = m_nMarginsTop + (m_nItemHeight + ySpace)* pItem->rowIndex();
	}
	else
	{
		yStart = m_nPageHeight - m_nMarginsTop - m_nMarginsBottom - m_nItemHeight /2;
	}
	pItem->setPos(xStart, yStart);
	return true;
}

int ItemPage::rowCount() const
{
	return m_nRowCount;
}

void ItemPage::setRowCount(const int& nRowCount)
{
	m_nRowCount = nRowCount;
}

int ItemPage::colCount() const
{
	return m_nColCount;
}

void ItemPage::setColCount(const int& nColCount)
{
	m_nColCount = nColCount;
}

bool ItemPage::resetItemGrid()
{
	return true;
}

void ItemPage::setItemWidth(int nWidth)
{
	m_nItemWidth = nWidth;
}

void ItemPage::setItemHeight(int nHeight)
{
	m_nItemHeight = nHeight;
}

void ItemPage::setContentsMargins ( qreal left, qreal top, qreal right, qreal bottom )
{
	m_nMarginsLeft = left;
	m_nMarginsTop = top;
	m_nMarginsRight = right;
	m_nMarginsBottom = bottom;
}

void ItemPage::setPageWidth(int nWidth)
{
	m_nPageWidth = nWidth;
}

void ItemPage::setPageHeight(int nHeight)
{
	m_nPageHeight = nHeight;
}
