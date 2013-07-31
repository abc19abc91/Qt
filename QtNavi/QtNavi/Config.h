#ifndef NAVI_CONFIG_H
#define NAVI_CONFIG_H

#include <QPoint>
#include <QString>
#include <QSettings>


typedef struct tagItemPageData
{
	typedef struct tagItemData
	{
		QString itemName;
		QString	imagePath;
		int		row;
		int		col;
	}ItemData, *PItemData;

	int m_nItemCount;
	QList <ItemData> m_lsItemData;
	
}ItemPageData;

class Config
{
public:

	static void LoadConfig();
	static bool LoadPage(int nPage, ItemPageData & pageDataIn);
	
	~Config(void);

	static QSettings	*m_pSettings;

	//static QPoint		m_nPagePos;			//页面相对屏幕位置
	static int			m_nItemMarginL;		//第一个ITEM相对PAGE左边的空白
	static int			m_nItemMarginT;		//第一个ITEM相对PAGE上边的空白
	static int			m_nItemRows;		//每页显示的ITEM的行数
	static int			m_nItemCols;		//每页显示的ITEM的列数
	static int			m_nItemSpacingH;	//ITEM之间的水平间隔
	static int			m_nItemSpacingV;	//ITEM之间的垂直间隔
	static int			m_nItemWidth;		//ITEM的宽度
	static int			m_nItemHeight;		//ITEM的高度
	static int			m_nItemCount;		//ITEM的数量
	static int			m_nPageCount;		//PAGE的数量

	static QString		m_strIniName;		//配置文件名字

	static int			m_nScreenWidth;		//屏幕宽度
	static int			m_nScreenHeight;	//屏幕高度
	static int			m_nMinPageDis;		//移动换页的最小距离
	static int			m_nMinMoveDis;		//移动开始移动最小距离
	static int			m_nPageDuration;	//移动持续时间
	static bool			m_bIsDraging;		//移动持续时间
	static int			m_nTitleHeight;		//标题栏高度

private:
	Config(void);
};

#endif
