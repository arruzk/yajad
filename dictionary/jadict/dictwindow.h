#ifndef DICTWINDOW_H
#define DICTWINDOW_H

#include <QMainWindow>

namespace Ui {
class dictWindow;
}

class dictWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit dictWindow(QWidget *parent = 0);
    ~dictWindow();
    
private:
    Ui::dictWindow *ui;
};

#endif // DICTWINDOW_H
