/*
 * This file is part of yata -- Yet Another Tail Application
 * Copyright 2010-2012 James Smith
 * 
 * Licensed under the GNU General Public License.  See license.txt for details.
 */

#include <QObject>
#include <QString>
#include <QDir>
#include "YApplication.h"

QString YApplication::displayAppName()
{
    return QObject::tr("Yata");
}

QString YApplication::appVersion()
{
    return APPVERSION;
}

QString YApplication::settingsPath()
{
    const QString settingsDirName = ".yata";
    return QDir::homePath() + "/" + settingsDirName;
}

QString YApplication::sessionFilePath()
{
    const QString sessionFileName = "session.yaml";
    return settingsPath() + "/" + sessionFileName;
}

QString YApplication::preferencesFilePath()
{
    const QString preferencesFileName = "preferences.yaml";
    return settingsPath() + "/" + preferencesFileName;
}
