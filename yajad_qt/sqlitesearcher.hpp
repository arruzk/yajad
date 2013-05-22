#ifndef SQLITESEARCHER_HPP
#define SQLITESEARCHER_HPP

#include <QObject>

#include <QLineEdit>
#include <QTextBrowser>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QRegExp>

#include "databasemanager.hpp"

#include <QDebug>

class sqliteSearcher : public QObject
{
    Q_OBJECT
private:
    QLineEdit *source;
    QTextBrowser *display;
    databaseManager *dbManager;
    int queryType;

public:
    explicit sqliteSearcher(QObject *parent = 0);
    void setSourceWidget(QLineEdit *newSource);
    void setDisplayWidget(QTextBrowser *newDisplay);
    static QString convertToKana(QString req);
signals:
    
public slots:
    void search();
    void setRussian(bool f);
    void setJapanese(bool f);
    void setTranslation(bool f);
};

#endif // SQLITESEARCHER_HPP
