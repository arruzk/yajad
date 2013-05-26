#include "radical.h"
#include "ui_radical.h"

radical::radical(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::radical)
{
    ui->setupUi(this);
    initRadicalList();
    connect(ui->pushButton_2, SIGNAL(clicked()), SLOT(clearRadicalList()));
    connect(ui->sendMainButton, SIGNAL(clicked()), SLOT(sendButtonClick()));
}

radical::~radical()
{
    delete ui;
}

void radical::sendButtonClick(){
    emit sendToMainWondow(ui->lineEdit->text());
    ui->lineEdit->clear();
}

int radical::initRadicalList(){
    QSqlQuery query;
    if(!query.exec("SELECT * FROM radical")){
        qDebug() << "fail";
        return -2;
    }
    QSqlRecord rec = query.record();
    int id;
//    int rgroup;
    QString character;
    int column = 0, row = 0;
    while (query.next()) {
        id = query.value(rec.indexOf("id")).toInt();
        character = query.value(rec.indexOf("character")).toString();
//        rgroup = query.value(rec.indexOf("rgroup")).toInt();
        QPushButton *t = new QPushButton(character);
        t->setMinimumWidth(5);
        radicals.insert(id, t);
        ui->gridLayout_2->addWidget(radicals[id], row, column);
        connect(radicals[id], SIGNAL(clicked()), SLOT(radicalSelect()));
        column++;
        if(column%20 == 0){
            row++;
            column = 0;
        }
    }
    return 0;
}

void radical::radicalSelect(){
    QPushButton *curButton = qobject_cast<QPushButton *>(QObject::sender());
    int radicalId = radicals.key(curButton);
    inputRadical<<radicalId;
    curButton->setDisabled(true);
    updateKanji();
}

void radical::moveChar(){
    QPushButton *curButton = qobject_cast<QPushButton *>(QObject::sender());
    ui->lineEdit->insert(curButton->text());
    clearRadicalList();
}

void radical::updateRadical(){
    QSqlQuery my_query;
    QStringList kanjiInList;
    foreach(const int &curKanjiItem, availableKanji)
        kanjiInList<<QString::number(curKanjiItem);

    QString finalKanjiList = kanjiInList.join(QString(","));
    availableRadicals.clear();
    if(!finalKanjiList.isEmpty()){
        QString query = QString("SELECT DISTINCT KR.radical_id AS myRadical FROM kanji K "
                                "JOIN kanjiRadical KR ON K.id = KR.kanji_id "
                                "WHERE K.id IN(%1)")
                                  .arg(finalKanjiList);
        if(!my_query.exec(query))
            qDebug()<<"error"<< my_query.lastError().databaseText();
        QSqlRecord rec = my_query.record();
        int id;
        while(my_query.next()){
            id = my_query.value(rec.indexOf("myRadical")).toInt();
            availableRadicals.insert(id);
        }
    }
    clearColor();
    foreach(const int &highlight, availableRadicals){
        QPalette myPalette = radicals[highlight]->palette();
        myPalette.setColor( QPalette::Button, QColor(6,127,34) );
        radicals[highlight]->setPalette( myPalette );
        radicals[highlight]->setAutoFillBackground( true );
    }
}

void radical::updateKanji(){
    QSqlQuery my_query;
    QHash<int, QString> kanji;
    availableKanji.clear();
    foreach (const int &curRadicalId, inputRadical){
        QString query = QString("SELECT H.id, H.character FROM radical R "
                                "JOIN kanjiRadical ON R.id = radical_id "
                                "JOIN kanji H ON H.id = kanji_id WHERE R.id = %1")
                                  .arg(curRadicalId);
        if(!my_query.exec(query))
            qDebug()<<"error"<< my_query.lastError().databaseText();
        QSqlRecord rec = my_query.record();
        QSet<int> temp;
        int id;
        while (my_query.next()) {
            id = my_query.value(rec.indexOf("id")).toInt();
            kanji[id] = my_query.value(rec.indexOf("character")).toString();
            temp<<id;
        }
        if(availableKanji.isEmpty())
            availableKanji = temp;
        else
            availableKanji.intersect(temp);
    }
    clearKanjiList();
    int r=0,c=0;
    QPushButton *kanjiButtonTemp;
    foreach(const int &tt, availableKanji){
        kanjiButtonTemp = new QPushButton(kanji[tt]);
        kanjiButtonTemp->setMinimumWidth(5);
        connect(kanjiButtonTemp, SIGNAL(clicked()), SLOT(moveChar()));
        ui->kanjiLayout->addWidget(kanjiButtonTemp,r,c);
        c++;
        if(c%10 == 0){
            c = 0;
            r++;
        }
    }
    //ui->textEdit->setPlainText(zz.join(QString(" ")));
    updateRadical();
}

void radical::clearRadicalList(){
    inputRadical.clear();
    clearKanjiList();
    foreach(QPushButton *curButton, radicals){
        curButton->setDisabled(false);
    }
    clearColor();
}

void radical::clearColor(){
    foreach(QPushButton *curButton, radicals){
        curButton->setAutoFillBackground(false);
    }
}

void radical::clearKanjiList(){
    QLayoutItem *child;
    while ( (child = ui->kanjiLayout->takeAt(0)) != 0) {
        delete child->widget();
        delete child;
    }
}
