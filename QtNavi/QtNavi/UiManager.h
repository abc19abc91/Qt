#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <QObject>
#include <QVector>
#include "Config.h"


class QtNaviView;
class FlickView;
class NaviBar;




class UiManager : public QObject
{
	Q_OBJECT

public:

	static UiManager* instance();
	//初始化界面
	void init(QtNaviView *view);
//	QVector <ItemPage*> * GetItemPage();

	QtNaviView *m_pView;


	FlickView * m_pFlickView;

	NaviBar * m_pNaviBar;


	~UiManager();

private:
	explicit UiManager(QObject *parent = 0);
	

	static UiManager *m_pInstance;
	

	void setRenderingSystem();
};

#endif // UIMANAGER_H
