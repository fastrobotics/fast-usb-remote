#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QMainWindow>
#include "ui_dashboard.h"
#include "ui_addprofile.h"

namespace Ui {
class dashboard;
}

class dashboard : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit dashboard(QWidget *parent = 0);
    ~dashboard();

public slots:
    void addprofile ();
    void addprofileok ();
    void delprofile ();
    void newprofile ();
    void saveprofile ();
    void uploadprofile ();
    void downloadprofile ();

private:
    Ui::dashboard *ui;
    Ui::profileDialog *ui2;
    QDialog *popup;
};

#endif // DASHBOARD_H
