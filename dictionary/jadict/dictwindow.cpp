#include "dictwindow.h"
#include "ui_dictwindow.h"
#include "radical.h"

dictWindow::dictWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::dictWindow)
{
    ui->setupUi(this);
    Radical *t = new Radical;
    t->open();
}

dictWindow::~dictWindow()
{
    delete ui;
}
