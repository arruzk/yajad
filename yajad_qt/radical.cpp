#include "radical.h"
#include "ui_radical.h"

radical::radical(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::radical)
{
    ui->setupUi(this);
    initRadicalList();
    connect(ui->pushButton_2, SIGNAL(clicked()), SLOT(clearKanjiList()));
}

radical::~radical()
{
    delete ui;
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
}

void radical::radicalSelect(){
    QPushButton *curButton = qobject_cast<QPushButton *>(QObject::sender());
    int radicalId = radicals.key(curButton);
    inputRadical<<radicalId;
    curButton->setDisabled(true);
    updateKanji();
}

void radical::updateRadical(){
    QSqlQuery my_query;
    availableRadicals.clear();
    foreach (const int &curRadicalId, inputRadical){
        QString query = QString("SELECT DISTINCT HR2.radical_id AS myRadical FROM radical R "
                                "JOIN kanjiRadical HR1 ON R.id = HR1.radical_id "
                                "JOIN kanji H ON H.id = HR1.kanji_id "
                                "JOIN kanjiRadical HR2 ON HR2.kanji_id = H.id WHERE R.id = %1")
                                  .arg(curRadicalId);
        if(!my_query.exec(query))
            qDebug()<<"error"<< my_query.lastError().databaseText();
        QSqlRecord rec = my_query.record();
        int id;
        QSet<int> temp;
        while(my_query.next()){
            id = my_query.value(rec.indexOf("myRadical")).toInt();
            temp.insert(id);
        }
        qDebug()<<temp;
        if(availableRadicals.isEmpty())
            availableRadicals = temp;
        else
            availableRadicals.intersect(temp);
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
    QHash<int, QString> hieroglyphs;
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
            hieroglyphs[id] = my_query.value(rec.indexOf("character")).toString();
            temp<<id;
        }
        if(availableKanji.isEmpty())
            availableKanji = temp;
        else
            availableKanji.intersect(temp);
    }
    QStringList zz;
    foreach(const int &tt, availableKanji){
        zz<<hieroglyphs[tt];
    }
    ui->textEdit->setPlainText(zz.join(QString(" ")));
    updateRadical();
}

void radical::clearKanjiList(){
    inputRadical.clear();
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
