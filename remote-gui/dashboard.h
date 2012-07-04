#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QMainWindow>

namespace Ui {
class dashboard;
}

class dashboard : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit dashboard(QWidget *parent = 0);
    ~dashboard();
    
private:
    Ui::dashboard *ui;
};

#endif // DASHBOARD_H
