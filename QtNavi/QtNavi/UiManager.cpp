#include "UiManager.h"
#include "QtNaviView.h"
//#include <QGraphicsItemGroup>
#include "ItemPage.h"
#include "BaseItem.h"
#include "FlickView.h"
#include <QtOpenGL/QGLWidget>
#include "NaviBar.h"


UiManager* UiManager::m_pInstance = 0;

UiManager::UiManager(QObject *parent)
	: QObject(parent), m_pView(NULL)
	,m_pFlickView(NULL)

{

}

UiManager::~UiManager()
{

}

UiManager* UiManager::instance()
{
	if (!m_pInstance) {
		m_pInstance = new UiManager;
	}
	return m_pInstance;
}

// QVector <ItemPage*> * UiManager::GetItemPage()
// {
// 	return &m_pItemPages;
// }


void UiManager::init(QtNaviView *view)
{

	m_pView = view;
	setRenderingSystem();

	m_pNaviBar = new NaviBar();
	m_pNaviBar->setPixmap(QPixmap(":/Resources/bg_topbar.bmp"));
	m_pView->scene()->addItem(m_pNaviBar);

	m_pFlickView = new FlickView();
	m_pView->scene()->addItem(m_pFlickView);
	m_pFlickView->setPos(0, Config::m_nTitleHeight);
	//m_pFlickView->setGeometry(0, 33, 800, 480);
	m_pFlickView->setColCount(Config::m_nItemCols);
	m_pFlickView->setRowCount(Config::m_nItemRows);
	m_pFlickView->setMinMoveDis(Config::m_nMinMoveDis);
	m_pFlickView->setPageDuration(Config::m_nPageDuration);
	m_pFlickView->setPageWidth(Config::m_nScreenWidth);
	m_pFlickView->setPixmap(QPixmap(":/Resources/bg_mainwnd.bmp"));

	for (int i = 0; i < Config::m_nPageCount ; ++i)
	{
		
		
		ItemPageData itemPageData;
		if (Config::LoadPage(i, itemPageData) && itemPageData.m_nItemCount > 0)
		{
			ItemPage * pItemPage = new ItemPage(m_pFlickView);		
			pItemPage->setRowCount(Config::m_nItemRows);
			pItemPage->setColCount(Config::m_nItemCols);
			pItemPage->setPageWidth(Config::m_nScreenWidth);
			pItemPage->setPageHeight(Config::m_nScreenHeight - Config::m_nTitleHeight);
			pItemPage->setItemWidth(Config::m_nItemWidth);
			pItemPage->setItemHeight(Config::m_nItemHeight);
			pItemPage->setContentsMargins(20, 20, 20, 20);
			pItemPage->setPageIndex(i);
			m_pFlickView->addItemPage(pItemPage);
			//pItemPage->setPos(Config::m_nScreenWidth*i, 0);

			for (int j = 0; j < itemPageData.m_nItemCount; ++j)
			{
 				BaseItem *pixmapItem = new BaseItem(pItemPage);  
 				pixmapItem->setPixmap(QPixmap(itemPageData.m_lsItemData.at(j).imagePath));
 				pixmapItem->setRowIndex(itemPageData.m_lsItemData.at(j).row);
 				pixmapItem->setColIndex(itemPageData.m_lsItemData.at(j).col);
 				pItemPage->addBaseItem(pixmapItem);
			}
//			m_pItemPages.append(pItemPage);
		}
	}

}


void UiManager::setRenderingSystem()
{
	QWidget *viewport = 0;

#ifndef QT_NO_OPENGL
	if (1) {
		m_pView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
		QGLWidget *glw = new QGLWidget(QGLFormat(QGL::SampleBuffers));
		//QGLWidget *glw = new QGLWidget();

		//if (0)
		//	glw->format().setSwapInterval(0);
		//glw->setAutoFillBackground(false);
		viewport = glw;
		m_pView->setCacheMode(QGraphicsView::CacheNone);


	} else // software rendering
#endif
	{
		// software rendering
		m_pView->setViewportUpdateMode(QGraphicsView::MinimalViewportUpdate);
		viewport = new QWidget;
		m_pView->setCacheMode(QGraphicsView::CacheBackground);

	}

	m_pView->setViewport(viewport);
}


