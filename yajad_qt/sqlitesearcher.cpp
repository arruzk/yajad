#include "sqlitesearcher.hpp"

sqliteSearcher::sqliteSearcher(QObject *parent) :
    QObject(parent)
{
    dbManager = new databaseManager();
    if(!dbManager->openDB(QString("../parser/dict.sqlite"))) {
        qDebug() << "Cannot open database: " << dbManager->lastError();
    }
}

void sqliteSearcher::setSourceWidget(QLineEdit *newSource)
{
    this->source = newSource;
}

void sqliteSearcher::setDisplayWidget(QTextBrowser *newDisplay)
{
    this->display = newDisplay;
}

void sqliteSearcher::search()
{
    QString request = this->source->text();

    qDebug() << "Got request: " << request;
    QString query = "SELECT a.aText FROM article a JOIN "
            "jaWordArticle jwa ON a.id = jwa.articleId "
            "JOIN jaWord j ON jwa.jaWordId = j.id "
            "WHERE j.syllabary=\"%1\"";
    query = query.arg(request);
    qDebug() << "Query: " << query;

    QSqlQuery sqlQuery;
    if (!sqlQuery.exec(query)) {
        qDebug() << "Cannot execute query for some reason" << dbManager->lastError();
    }

    QSqlRecord sqlRecord = sqlQuery.record();
    QString text;

    while (sqlQuery.next()) {
        text = sqlQuery.value(sqlRecord.indexOf("aText")).toString();
        qDebug() << text;
        display->setText(text);
    }

}
