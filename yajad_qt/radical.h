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
    void updateHieroglyph();
    Ui::radical *ui;
    QHash <int, QPushButton* > radicals;
    QSqlDatabase dbase;
    QSet<int> inputRadical;
    QSet<int> availableHieroglyph;
    QSet<int> availableRadicals;
public slots:
    void clearHierogliphList();
    void clearColor();
private slots:
    void radicalSelect();
};

#endif // RADICAL_H
