#include "databasemanager.hpp"

databaseManager::databaseManager(QObject *parent) :
    QObject(parent)
{
}

bool databaseManager::openDB(QString path)
{
    // Find QSLite driver
    db = QSqlDatabase::addDatabase("QSQLITE");

#ifdef Q_OS_LINUX
    path = QDir::toNativeSeparators(path);
    db.setDatabaseName(path);
#else
    // NOTE: File exists in the application private folder, in Symbian Qt implementation
    db.setDatabaseName("my.db.sqlite");
#endif

    return db.open();
}

QSqlError databaseManager::lastError()
{
    // If opening database has failed user can ask
    // error description by QSqlError::text()
    return db.lastError().text();
}

bool databaseManager::closeDB()
{
    // Close database
    db.close();
}
