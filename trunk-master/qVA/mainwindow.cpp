#include "mainwindow.h"
#include <QMenu>
#include <QToolBar>
#include <QtCore/QMap>
#include "ui_mainwindow.h"
#include "PluginHandle.h"
#include "IAppPlugin.h"
#include "MainApplication.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	Init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::Init()
{
	if (!m_pApp)
	{
		m_pApp = new MainApplication(this);
	}

	// �������
	PluginHandle * pluginHandle = PluginHandle::StaticInstances();
	if (!pluginHandle)
	{
		return false;
	}

	pluginHandle->m_MainApplication = m_pApp;

	// ������в��
	pluginHandle->AddPlugins();

	QMap<QString, IAppPlugin*> &AppPlugins = pluginHandle->m_AppPlugins;

	if (AppPlugins.count() == 0)
	{
		return false;
	}

	// ���ԣ����ڿɸ���xml��������
	QMenuBar * menuBar = this->menuBar();
	QMenu * menu = new QMenu("Plugin", menuBar);
	menuBar->addMenu(menu);
	for (QMap<QString, IAppPlugin*>::iterator it = AppPlugins.begin(); it != AppPlugins.end(); ++it)
	{
		QAction *action = menu->addAction(it.value()->Caption());
		action->setObjectName(it.value()->Name());
		action->setEnabled(true);
		it.value()->Tool = action;
		// ��������Ҫ����
		it.value()->Connect();
	}
	return true;
}
