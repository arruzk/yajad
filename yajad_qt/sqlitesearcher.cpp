#include "sqlitesearcher.hpp"

sqliteSearcher::sqliteSearcher(QObject *parent) :
    QObject(parent)
{
    queryType = 0;
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

void sqliteSearcher::setRussian(bool f)
{
    if(f) this->queryType = 1;
}

void sqliteSearcher::setJapanese(bool f)
{
    if(f) this->queryType = 0;
}

void sqliteSearcher::setTranslation(bool f)
{
    if(f) this->queryType = 2;
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

    e = QRegExp("га"); res.replace(e,"が");
    e = QRegExp("ги"); res.replace(e,"ぎ");
    e = QRegExp("гу"); res.replace(e,"ぐ");
    e = QRegExp("гэ"); res.replace(e,"げ");
    e = QRegExp("го"); res.replace(e,"ご");

    e = QRegExp("са"); res.replace(e,"さ");
    e = QRegExp("си"); res.replace(e,"し");
    e = QRegExp("су"); res.replace(e,"す");
    e = QRegExp("сэ"); res.replace(e,"せ");
    e = QRegExp("со"); res.replace(e,"そ");

    e = QRegExp("дза"); res.replace(e,"ざ");
    e = QRegExp("дзи"); res.replace(e,"じ");
    e = QRegExp("дзу"); res.replace(e,"ず");
    e = QRegExp("дзэ"); res.replace(e,"ぜ");
    e = QRegExp("дзо"); res.replace(e,"ぞ");

    e = QRegExp("та"); res.replace(e,"た");
    e = QRegExp("ти"); res.replace(e,"ち");
    e = QRegExp("цу"); res.replace(e,"つ");
    e = QRegExp("тэ"); res.replace(e,"て");
    e = QRegExp("то"); res.replace(e,"と");

    e = QRegExp("да"); res.replace(e,"だ");
    e = QRegExp("дэ"); res.replace(e,"で");
    e = QRegExp("до"); res.replace(e,"ど");

    e = QRegExp("на"); res.replace(e,"な");
    e = QRegExp("ни"); res.replace(e,"に");
    e = QRegExp("ну"); res.replace(e,"ぬ");
    e = QRegExp("нэ"); res.replace(e,"ね");
    e = QRegExp("но"); res.replace(e,"の");

    e = QRegExp("ха"); res.replace(e,"は");
    e = QRegExp("хи"); res.replace(e,"ひ");
    e = QRegExp("фу"); res.replace(e,"ふ");
    e = QRegExp("хэ"); res.replace(e,"へ");
    e = QRegExp("хо"); res.replace(e,"ほ");

    e = QRegExp("ба"); res.replace(e,"ば");
    e = QRegExp("би"); res.replace(e,"び");
    e = QRegExp("бу"); res.replace(e,"ぶ");
    e = QRegExp("бэ"); res.replace(e,"べ");
    e = QRegExp("бо"); res.replace(e,"ぼ");

    e = QRegExp("па"); res.replace(e,"ぱ");
    e = QRegExp("пи"); res.replace(e,"ぴ");
    e = QRegExp("пу"); res.replace(e,"ぷ");
    e = QRegExp("пэ"); res.replace(e,"ぺ");
    e = QRegExp("по"); res.replace(e,"ぽ");

    e = QRegExp("ма"); res.replace(e,"ま");
    e = QRegExp("ми"); res.replace(e,"み");
    e = QRegExp("му"); res.replace(e,"む");
    e = QRegExp("мэ"); res.replace(e,"め");
    e = QRegExp("мо"); res.replace(e,"も");

    e = QRegExp("ра"); res.replace(e,"ら");
    e = QRegExp("ри"); res.replace(e,"り");
    e = QRegExp("ру"); res.replace(e,"る");
    e = QRegExp("рэ"); res.replace(e,"れ");
    e = QRegExp("ро"); res.replace(e,"ろ");

    e = QRegExp("кя"); res.replace(e,"きゃ");
    e = QRegExp("кю"); res.replace(e,"きゅ");
    e = QRegExp("кё"); res.replace(e,"きょ");

    e = QRegExp("ся"); res.replace(e,"しゃ");
    e = QRegExp("сю"); res.replace(e,"しゅ");
    e = QRegExp("сё"); res.replace(e,"しょ");

    e = QRegExp("дзя"); res.replace(e,"じゃ");
    e = QRegExp("дзю"); res.replace(e,"じゅ");
    e = QRegExp("дзё"); res.replace(e,"じょ");

    e = QRegExp("тя"); res.replace(e,"ちゃ");
    e = QRegExp("тю"); res.replace(e,"ちゅ");
    e = QRegExp("тё"); res.replace(e,"ちょ");

    e = QRegExp("ня"); res.replace(e,"にゃ");
    e = QRegExp("ню"); res.replace(e,"にゅ");
    e = QRegExp("нё"); res.replace(e,"にょ");

    e = QRegExp("хя"); res.replace(e,"ひゃ");
    e = QRegExp("хю"); res.replace(e,"ひゅ");
    e = QRegExp("хё"); res.replace(e,"ひょ");

    e = QRegExp("бя"); res.replace(e,"びゃ");
    e = QRegExp("бю"); res.replace(e,"びゅ");
    e = QRegExp("бё"); res.replace(e,"びょ");

    e = QRegExp("пя"); res.replace(e,"ぴゃ");
    e = QRegExp("пю"); res.replace(e,"ぴゅ");
    e = QRegExp("пё"); res.replace(e,"ぴょ");

    e = QRegExp("мя"); res.replace(e,"みゃ");
    e = QRegExp("мю"); res.replace(e,"みゅ");
    e = QRegExp("мё"); res.replace(e,"みょ");

    e = QRegExp("ря"); res.replace(e,"りゃ");
    e = QRegExp("рю"); res.replace(e,"りゅ");
    e = QRegExp("рё"); res.replace(e,"りょ");

    e = QRegExp("а"); res.replace(e,"あ");
    e = QRegExp("и"); res.replace(e,"い");
    e = QRegExp("у"); res.replace(e,"う");
    e = QRegExp("э"); res.replace(e,"え");
    e = QRegExp("о"); res.replace(e,"お");

    e = QRegExp("нъ"); res.replace(e,"ん");
    e = QRegExp("н"); res.replace(e,"ん");


    return res;
}

void sqliteSearcher::search()
{
    QString request = this->source->text();
    QString query = "";
    if (queryType == 2) {
        query = "SELECT kanji, kana, transcription, a.aText "
                "FROM article a JOIN "
                "jaWordArticle jwa ON a.id = jwa.articleId "
                "JOIN jaWord j ON jwa.jaWordId = j.id "
                "WHERE a.aText LIKE \"%%1%\"";
        query = query.arg(request);
    } else {
        if (queryType == 1) request = convertToKana(request);

        query = "SELECT kanji, kana, transcription, a.aText "
                "FROM article a JOIN "
                "jaWordArticle jwa ON a.id = jwa.articleId "
                "JOIN jaWord j ON jwa.jaWordId = j.id "
                "WHERE j.kana LIKE \"%%1%\"";
        query = query.arg(request);
    }

    QSqlQuery sqlQuery;
    if (!sqlQuery.exec(query)) {
        qDebug() << "Cannot execute query for some reason" << dbManager->lastError();
    }

    QSqlRecord sqlRecord = sqlQuery.record();
    QString text, kana, kanji, transcription, accum = "";

    while (sqlQuery.next()) {
        kanji = sqlQuery.value(sqlRecord.indexOf("kanji")).toString();
        kana = sqlQuery.value(sqlRecord.indexOf("kana")).toString();
        transcription = sqlQuery.value(sqlRecord.indexOf("transcription")).toString();
        text = sqlQuery.value(sqlRecord.indexOf("aText")).toString();
        QRegExp e(";"); text.replace(e, "<br />");

        QString disp = "%1 [%2] "
                "<font color=\"grey\" size=\"3\">"
                "<i>%3</i></font>: %4";
        disp = disp.arg(kanji, kana, transcription, text);
        accum = accum + disp + "<br /><br />";
    }
    display->setHtml(accum);
}
