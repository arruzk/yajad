#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include "sqlitesearcher.hpp"
#include "radical.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void openRadicalWindow();
private:
    Ui::MainWindow *ui;
    sqliteSearcher *sqliteSearch;
    radical *radicalWindow;
};

#endif // MAINWINDOW_HPP
