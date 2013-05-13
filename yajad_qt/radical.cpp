#include "radical.h"
#include "ui_radical.h"

radical::radical(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::radical)
{
    ui->setupUi(this);
//    createDbConnection();
    initRadicalList();
    connect(ui->pushButton_2, SIGNAL(clicked()), SLOT(clearHierogliphList()));
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
    updateHieroglyph();
}

void radical::updateRadical(){
    QSqlQuery my_query;
    QHash<int, QString> hieroglyphs;
    availableRadicals.clear();
    foreach (const int &curRadicalId, inputRadical){
        QString query = QString("SELECT DISTINCT HR2.radical_id AS r22 FROM radical R "
                                "JOIN hieroglyphRadical HR1 ON R.id = HR1.radical_id "
                                "JOIN hieroglyph H ON H.id = HR1.hieroglyph_id "
                                "JOIN hieroglyphRadical HR2 ON HR2.hieroglyph_id = H.id WHERE R.id = %1")
                                  .arg(curRadicalId);
        if(!my_query.exec(query))
            qDebug()<<"error"<< my_query.lastError().databaseText();
        QSqlRecord rec = my_query.record();
        int id;
        QSet<int> temp;
        while(my_query.next()){
            id = my_query.value(rec.indexOf("r22")).toInt();
            temp.insert(id);
        }
        if(availableRadicals.isEmpty())
            availableRadicals = temp;
        else
            availableRadicals.intersect(temp);
    }
    qDebug()<<availableRadicals;
    clearColor();
    foreach(const int &highlight, availableRadicals){
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
    updateRadical();
}

void radical::clearHierogliphList(){
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
