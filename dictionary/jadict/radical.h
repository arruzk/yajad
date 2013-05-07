#ifndef RADICAL_H
#define RADICAL_H

#include <QWidget>

namespace Ui {
class Radical;
}

class Radical : public QWidget
{
    Q_OBJECT
    
public:
    explicit Radical(QWidget *parent = 0);
    ~Radical();
    
private:
    Ui::Radical *ui;
};

#endif // RADICAL_H
