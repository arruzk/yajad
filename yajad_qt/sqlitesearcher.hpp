#ifndef SQLITESEARCHER_HPP
#define SQLITESEARCHER_HPP

#include <QObject>

#include <QLineEdit>
#include <QTextBrowser>
#include <QSqlQuery>
#include <QSqlRecord>

#include "databasemanager.hpp"

#include <QDebug>

class sqliteSearcher : public QObject
{
    Q_OBJECT
private:
    QLineEdit *source;
    QTextBrowser *display;
    databaseManager *dbManager;

public:
    explicit sqliteSearcher(QObject *parent = 0);
    void setSourceWidget(QLineEdit *newSource);
    void setDisplayWidget(QTextBrowser *newDisplay);
signals:
    
public slots:
    void search();
};

#endif // SQLITESEARCHER_HPP
