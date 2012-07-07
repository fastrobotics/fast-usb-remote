#include "dashboard.h"

dashboard::dashboard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::dashboard),
    ui2(new Ui::profileDialog),
    popup(new QDialog)
{    
    ui->setupUi(this);
    ui2->setupUi(popup);

    connect(ui->addbutton, SIGNAL(clicked()),this, SLOT(addprofile()));
    connect(ui->delbutton, SIGNAL(clicked()),this, SLOT(delprofile()));
    connect(ui2->buttonBox,SIGNAL(accepted()),this,SLOT(addprofileok()));
}

void dashboard::addprofile ()
{
    ui->textEdit->append( "add profile");

    popup->show();

}

void dashboard::addprofileok ()
{
//    int i;

    ui->textEdit->append( ui2->lineEdit->text());

    ui->proflist->addItem(ui2->lineEdit->text());

}

void dashboard::delprofile ()
{
    ui->textEdit->append( "del profile");

    qDeleteAll(ui->proflist->selectedItems());
}

void dashboard::newprofile ()
{

}

void dashboard::saveprofile ()
{

}

void dashboard::uploadprofile ()
{

}

void dashboard::downloadprofile ()
{

}

dashboard::~dashboard()
{
    delete ui;
    delete ui2;
    delete popup;
}
