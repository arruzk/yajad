#ifndef DATABASEMANAGER_HPP
#define DATABASEMANAGER_HPP

#include <QObject>

#include <QString>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDir>

class databaseManager : public QObject
{
    Q_OBJECT
public:
    explicit databaseManager(QObject *parent = 0);
    
public:
    bool openDB(QString path);
    void closeDB();
    QSqlError lastError();

private:
    QSqlDatabase db;
    
};

#endif // DATABASEMANAGER_HPP
