#include "radical.h"
#include "ui_radical.h"

radical::radical(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::radical)
{
    ui->setupUi(this);
    createDbConnection();
    initRadicalList();
    connect(ui->pushButton_2, SIGNAL(clicked()), SLOT(clearHierogliphList()));
}

radical::~radical()
{
    delete ui;
}

int radical::createDbConnection(){
    dbase = QSqlDatabase::addDatabase("QSQLITE");
    dbase.setDatabaseName("../parser/dict.sqlite");
    if (!dbase.open()) {
        qDebug() << "db connection fail";
        return -1;
    }
    return 0;
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
        radicals.insert(id, t);
        ui->gridLayout_2->addWidget(radicals[id], row, column);
        connect(radicals[id], SIGNAL(clicked()), SLOT(radicalSelect()));
        column++;
        if(column%12 == 0){
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
    updateHieroglyph();
}

void radical::updateRadical(){
    QSqlQuery my_query;
    QHash<int, QString> hieroglyphs;
    availableRadicals.clear();
    foreach (const int &curHierogliphId, availableHieroglyph){
//        qDebug()<<curHierogliphId;
//        int curHierogliphId = 12580;
        QString query = QString("SELECT R.id FROM hieroglyph H JOIN hieroglyphRadical ON H.id = hieroglyph_id "
                            "JOIN radical R ON R.id = radical_id WHERE H.id = %1")
                                  .arg(curHierogliphId);
        if(!my_query.exec(query))
            qDebug()<<"error"<< my_query.lastError().databaseText();
        QSqlRecord rec = my_query.record();
//        QSet<int> temp;
        int id;
        while(my_query.next()){
            id = my_query.value(rec.indexOf("id")).toInt();
            availableRadicals.insert(id);
//            temp<<id;
        }
    }
    foreach(const int &highlight, availableRadicals){
//        qDebug()<<highlight;
//        radicals[highlight]->setText("!");

        QPalette myPalette = radicals[highlight]->palette();
        myPalette.setColor( QPalette::Button, QColor(6,127,34) );
        radicals[highlight]->setPalette( myPalette );
        radicals[highlight]->setAutoFillBackground( true );
    }
}

void radical::updateHieroglyph(){
    QSqlQuery my_query;
    QHash<int, QString> hieroglyphs;
    availableHieroglyph.clear();
    foreach (const int &curRadicalId, inputRadical){
        QString query = QString("SELECT H.id, H.character FROM radical R JOIN hieroglyphRadical ON R.id = radical_id "
                            "JOIN hieroglyph H ON H.id = hieroglyph_id WHERE R.id = %1")
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
        if(availableHieroglyph.isEmpty())
            availableHieroglyph = temp;
        else
            availableHieroglyph.intersect(temp);
    }
    QStringList zz;
    foreach(const int &tt, availableHieroglyph){
        zz<<hieroglyphs[tt];
    }
    ui->textEdit->setPlainText(zz.join(QString(" ")));
//    updateRadical();
}

void radical::clearHierogliphList(){
    inputRadical.clear();
    qDebug()<<"clear";
    foreach(QPushButton *curButton, radicals){
        curButton->setDisabled(false);
    }
}
