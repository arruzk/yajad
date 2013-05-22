#include "sqlitesearcher.hpp"

sqliteSearcher::sqliteSearcher(QObject *parent) :
    QObject(parent)
{
    russian = false;
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

void sqliteSearcher::setRussian(bool ru)
{
    this->russian = ru;
}

QString sqliteSearcher::convertToKana(QString req)
{
    QString res = req;
    QRegExp e;

    e = QRegExp("мп");
    qDebug() << "Index in:" << e.indexIn(res);

    e = QRegExp("мм"); res.replace(e,"нм");
    e = QRegExp("мп"); res.replace(e,"нп");
    e = QRegExp("мб"); res.replace(e,"нб");

    e = QRegExp("ка"); res.replace(e,"か");
    e = QRegExp("ки"); res.replace(e,"き");
    e = QRegExp("ку"); res.replace(e,"く");
    e = QRegExp("кэ"); res.replace(e,"け");
    e = QRegExp("ко"); res.replace(e,"こ");

    e = QRegExp("са"); res = res.replace(e,"さ");
    e = QRegExp("си"); res = res.replace(e,"し");
    e = QRegExp("су"); res = res.replace(e,"す");
    e = QRegExp("сэ"); res = res.replace(e,"せ");
    e = QRegExp("со"); res = res.replace(e,"そ");

    e = QRegExp("дза"); res = res.replace(e,"ざ");
    e = QRegExp("дзи"); res = res.replace(e,"じ");
    e = QRegExp("дзу"); res = res.replace(e,"ず");
    e = QRegExp("дзэ"); res = res.replace(e,"ぜ");
    e = QRegExp("дзо"); res = res.replace(e,"ぞ");

    e = QRegExp("та"); res = res.replace(e,"た");
    e = QRegExp("ти"); res = res.replace(e,"ち");
    e = QRegExp("цу"); res = res.replace(e,"つ");
    e = QRegExp("тэ"); res = res.replace(e,"て");
    e = QRegExp("то"); res = res.replace(e,"と");

    e = QRegExp("да"); res = res.replace(e,"だ");
    e = QRegExp("дэ"); res = res.replace(e,"で");
    e = QRegExp("до"); res = res.replace(e,"ど");

    e = QRegExp("на"); res = res.replace(e,"な");
    e = QRegExp("ни"); res = res.replace(e,"に");
    e = QRegExp("ну"); res = res.replace(e,"ぬ");
    e = QRegExp("нэ"); res = res.replace(e,"ね");
    e = QRegExp("но"); res = res.replace(e,"の");

    e = QRegExp("ха"); res = res.replace(e,"は");
    e = QRegExp("хи"); res = res.replace(e,"ひ");
    e = QRegExp("фу"); res = res.replace(e,"ふ");
    e = QRegExp("хэ"); res = res.replace(e,"へ");
    e = QRegExp("хо"); res = res.replace(e,"ほ");

    e = QRegExp("ба"); res = res.replace(e,"ば");
    e = QRegExp("би"); res = res.replace(e,"び");
    e = QRegExp("бу"); res = res.replace(e,"ぶ");
    e = QRegExp("бэ"); res = res.replace(e,"べ");
    e = QRegExp("бо"); res = res.replace(e,"ぼ");

    e = QRegExp("па"); res = res.replace(e,"ぱ");
    e = QRegExp("пи"); res = res.replace(e,"ぴ");
    e = QRegExp("пу"); res = res.replace(e,"ぷ");
    e = QRegExp("пэ"); res = res.replace(e,"ぺ");
    e = QRegExp("по"); res = res.replace(e,"ぽ");

    e = QRegExp("ма"); res = res.replace(e,"ま");
    e = QRegExp("ми"); res = res.replace(e,"み");
    e = QRegExp("му"); res = res.replace(e,"む");
    e = QRegExp("мэ"); res = res.replace(e,"め");
    e = QRegExp("мо"); res = res.replace(e,"も");

    e = QRegExp("ра"); res = res.replace(e,"ら");
    e = QRegExp("ри"); res = res.replace(e,"り");
    e = QRegExp("ру"); res = res.replace(e,"る");
    e = QRegExp("рэ"); res = res.replace(e,"れ");
    e = QRegExp("ро"); res = res.replace(e,"ろ");

    e = QRegExp("кя"); res = res.replace(e,"きゃ");
    e = QRegExp("кю"); res = res.replace(e,"きゅ");
    e = QRegExp("кё"); res = res.replace(e,"きょ");

    e = QRegExp("ся"); res = res.replace(e,"しゃ");
    e = QRegExp("сю"); res = res.replace(e,"しゅ");
    e = QRegExp("сё"); res = res.replace(e,"しょ");

    e = QRegExp("дзя"); res = res.replace(e,"じゃ");
    e = QRegExp("дзю"); res = res.replace(e,"じゅ");
    e = QRegExp("дзё"); res = res.replace(e,"じょ");

    e = QRegExp("тя"); res = res.replace(e,"ちゃ");
    e = QRegExp("тю"); res = res.replace(e,"ちゅ");
    e = QRegExp("тё"); res = res.replace(e,"ちょ");

    e = QRegExp("ня"); res = res.replace(e,"にゃ");
    e = QRegExp("ню"); res = res.replace(e,"にゅ");
    e = QRegExp("нё"); res = res.replace(e,"にょ");

    e = QRegExp("хя"); res = res.replace(e,"ひゃ");
    e = QRegExp("хю"); res = res.replace(e,"ひゅ");
    e = QRegExp("хё"); res = res.replace(e,"ひょ");

    e = QRegExp("бя"); res = res.replace(e,"びゃ");
    e = QRegExp("бю"); res = res.replace(e,"びゅ");
    e = QRegExp("бё"); res = res.replace(e,"びょ");

    e = QRegExp("пя"); res = res.replace(e,"ぴゃ");
    e = QRegExp("пю"); res = res.replace(e,"ぴゅ");
    e = QRegExp("пё"); res = res.replace(e,"ぴょ");

    e = QRegExp("мя"); res = res.replace(e,"みゃ");
    e = QRegExp("мю"); res = res.replace(e,"みゅ");
    e = QRegExp("мё"); res = res.replace(e,"みょ");

    e = QRegExp("ря"); res = res.replace(e,"りゃ");
    e = QRegExp("рю"); res = res.replace(e,"りゅ");
    e = QRegExp("рё"); res = res.replace(e,"りょ");

    e = QRegExp("а"); res = res.replace(e,"あ");
    e = QRegExp("и"); res = res.replace(e,"い");
    e = QRegExp("у"); res = res.replace(e,"う");
    e = QRegExp("э"); res = res.replace(e,"え");
    e = QRegExp("о"); res = res.replace(e,"お");

    e = QRegExp("нъ"); res = res.replace(e,"ん");
    e = QRegExp("н"); res = res.replace(e,"ん");


    return res;
}

void sqliteSearcher::search()
{
    QString request = this->source->text();

    if (russian) request = convertToKana(request);

    qDebug() << "Got request: " << request;

    QString query = "SELECT a.aText FROM article a JOIN "
            "jaWordArticle jwa ON a.id = jwa.articleId "
            "JOIN jaWord j ON jwa.jaWordId = j.id "
            "WHERE j.kana=\"%1\"";
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
