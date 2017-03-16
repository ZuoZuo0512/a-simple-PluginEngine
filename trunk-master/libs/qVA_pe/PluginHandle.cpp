#include "PluginHandle.h"
#include <QtCore/QtCore>
#include "MainApplication.h"
#include "IAppPlugin.h"

PluginHandle *gPluginHandle;


PluginHandle::PluginHandle(void)
{
	m_MainApplication = NULL;
}

PluginHandle::~PluginHandle(void)
{
}


void PluginHandle::AddPlugins(  )
{
	// ���ؾ�̬���
	foreach (QObject *plugin, QPluginLoader::staticInstances())
	{		
		AddPlugins(plugin, m_AppPlugins);
	}

	// ����pluginsĿ¼������dll�еĲ��
	QDir pluginsDir = QDir(qApp->applicationDirPath());
	pluginsDir.cd("plugins");

	// ѭ��ÿ�����
	foreach (QString fileName, pluginsDir.entryList(QDir::Files))
	{
		const QString &sFile = pluginsDir.absoluteFilePath(fileName);
		AddPlugins(sFile, m_AppPlugins);
	}
}

// ����dll�ļ��еĲ��
void PluginHandle::AddPlugins( const QString & sFile, QMap<QString, IAppPlugin*> &plugins )
{
	QPluginLoader loader(sFile);
	QObject *plugin = loader.instance();
	AddPlugins(plugin, plugins);
}


void PluginHandle::AddPlugins( QObject* plugin, QMap<QString, IAppPlugin*> &plugins )
{
	if (plugin) 
	{
		IAppPlugin *appPlugin = qobject_cast<IAppPlugin *>(plugin);
		if (appPlugin)
		{
			const QString &sName = appPlugin->Name();
			if (!plugins.contains(sName))
			{
				plugins.insert(sName, appPlugin);
			}
		}
	}
}

// �������ƻ�ȡ���
IAppPlugin* PluginHandle::GetPlugin( const QString &sPluginName )
{
	if (m_AppPluginInstances.contains(sPluginName))
	{
		return m_AppPlugins[sPluginName];
	}
	return NULL;
}

PluginHandle * PluginHandle::StaticInstances()
{
	if (!gPluginHandle)
	{
		gPluginHandle = new PluginHandle();
	}
	return gPluginHandle;
}

void PluginHandle::ReleaseInstances()
{
	if (gPluginHandle)
	{
		delete gPluginHandle;
		gPluginHandle = NULL;
	}
}