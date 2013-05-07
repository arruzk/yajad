#include "radical.h"
#include "ui_radical.h"

Radical::Radical(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Radical)
{
    ui->setupUi(this);
}

Radical::~Radical()
{
    delete ui;
}
