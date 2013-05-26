#ifndef RADICAL_H
#define RADICAL_H

#include <QWidget>
#include <QPushButton>
#include <QHash>
#include <QSet>
#include <QtSql>

namespace Ui {
class radical;
}

class radical : public QWidget
{
    Q_OBJECT
    
public:
    explicit radical(QWidget *parent = 0);
    ~radical();
    
private:
    int initRadicalList();
    void updateRadical();
    void updateKanji();
    Ui::radical *ui;
    QHash <int, QPushButton* > radicals;
    QSqlDatabase dbase;
    QSet<int> inputRadical;
    QSet<int> availableKanji;
    QSet<int> availableRadicals;
public slots:
    void clearKanjiList();
    void clearColor();
    void clearRadicalList();
    void moveChar();
    void sendButtonClick();
private slots:
    void radicalSelect();
signals:
    void sendToMainWondow(QString word);
};

#endif // RADICAL_H
