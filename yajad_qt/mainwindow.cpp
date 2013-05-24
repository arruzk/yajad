#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    sqliteSearch(new sqliteSearcher)
{
    ui->setupUi(this);
    this->sqliteSearch->setSourceWidget(ui->lineEdit);
    this->sqliteSearch->setDisplayWidget(ui->textBrowser);

    connect(ui->searchButton, SIGNAL(clicked()),
            this->sqliteSearch, SLOT(search()));

    connect(ui->radioButton, SIGNAL(toggled(bool)),
            this->sqliteSearch, SLOT(setJapanese(bool)));

    connect(ui->radioButton_2, SIGNAL(toggled(bool)),
            this->sqliteSearch, SLOT(setRussian(bool)));

    connect(ui->radioButton_3, SIGNAL(toggled(bool)),
            this->sqliteSearch, SLOT(setTranslation(bool)));

    connect(ui->lineEdit, SIGNAL(returnPressed()),
            this->sqliteSearch, SLOT(search()));

    //connect(ui->actionOpen, SIGNAL(triggered()), SLOT(openRadicalWindow()));



    openRadicalWindow();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openRadicalWindow(){
    radicalWindow = new radical();
    radicalWindow->show();
}
