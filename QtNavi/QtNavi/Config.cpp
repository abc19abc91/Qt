#include "Config.h"

#include <QApplication>
#include <QDesktopWidget>

QSettings * Config::m_pSettings = NULL;
//QPoint Config::m_nPagePos = QPoint(0, 100);
int Config::m_nItemMarginL = 30;
int Config::m_nItemMarginT = 30;
int Config::m_nItemRows = 2;
int Config::m_nItemCols = 3;
int Config::m_nItemSpacingH = 50;
int Config::m_nItemSpacingV = 10;
int Config::m_nItemWidth = 227;
int Config::m_nItemHeight = 185;
int Config::m_nItemCount = 13;
int Config::m_nPageCount = 13;
QString Config::m_strIniName = "config.ini";
int Config::m_nScreenWidth = 800;
int Config::m_nScreenHeight = 480;
int Config::m_nMinPageDis = 100;
int Config::m_nMinMoveDis = 10;
int Config::m_nPageDuration = 750;
bool Config::m_bIsDraging = false;
int Config::m_nTitleHeight = 33;


Config::Config(void)
{
	
}

Config::~Config(void)
{
	if (m_pSettings)
	{
		delete m_pSettings;
		m_pSettings = NULL;
	}
}


void Config::LoadConfig()
{
	
	m_strIniName  = QCoreApplication::applicationDirPath()+"/"+ m_strIniName;
	m_pSettings = new QSettings(m_strIniName,QSettings::IniFormat);

	m_pSettings->setIniCodec("UTF-8");


	//m_nScreenWidth = QApplication::desktop()->width();
	//m_nScreenHeight = QApplication::desktop()->height();

	
	

 	m_pSettings->beginGroup("Common");
 	m_nPageCount = m_pSettings->value("PageCount").toInt();
 	m_pSettings->endGroup();


	m_pSettings->beginGroup("PageLayout");
	//m_pSettings->setValue("RowCount", QVariant::fromValue(2));
	m_nItemRows = m_pSettings->value("RowCount").toInt();
	m_nItemCols = m_pSettings->value("ColCount").toInt();
	
	m_pSettings->endGroup();

	//for (int i = 0; i < m_nPageCount; ++i)
	//{
		//LoadPage(i);
	//}
}

bool Config::LoadPage(int nPage, ItemPageData & pageDataIn)
{
	if (nPage > m_nPageCount - 1)
	{
		return false;
	}
	m_pSettings->beginGroup(QString("Page%1").arg(nPage));
	pageDataIn.m_nItemCount = m_pSettings->value("IconsCount").toInt();
	ItemPageData::ItemData itemData;
	QString strKey;
	for (int i = 0; i < pageDataIn.m_nItemCount; ++i)
	{
		strKey = QString("Icon%1%2").arg(i).arg("_Name");
		itemData.itemName = m_pSettings->value(strKey).toString();
		strKey = QString("Icon%1%2").arg(i).arg("_Icon");
		itemData.imagePath = m_pSettings->value(strKey).toString();
		strKey = QString("Icon%1%2").arg(i).arg("_Row");
		itemData.row = m_pSettings->value(strKey).toInt();
		strKey = QString("Icon%1%2").arg(i).arg("_Col");
		itemData.col = m_pSettings->value(strKey).toInt();

		pageDataIn.m_lsItemData.append(itemData);
	}
	m_pSettings->endGroup();
	return true;
}
