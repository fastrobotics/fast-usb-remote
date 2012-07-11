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
    connect(ui->newbutton, SIGNAL(clicked()),this, SLOT(newprofile()));
    connect(ui->savebutton, SIGNAL(clicked()),this, SLOT(saveprofile()));
    connect(ui->openbutton, SIGNAL(clicked()),this, SLOT(openprofile()));
    connect(ui->uploadbutton, SIGNAL(clicked()),this, SLOT(uploadprofile()));
    connect(ui->downloadbutton, SIGNAL(clicked()),this, SLOT(downloadprofile()));

    connect(ui2->buttonBox,SIGNAL(accepted()),this,SLOT(addprofileok()));
}

void dashboard::addprofile ()
{
    ui->textEdit->append( "add profile");

    popup->show();

}

void dashboard::addprofileok ()
{
    ui->textEdit->append( "add profile ok");

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
    ui->textEdit->append( "new profile");
}

void dashboard::openprofile ()
{
    ui->textEdit->append( "open profile");

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                     "",
                                                     tr("Re-Mote Profile Bucket (*.rpb)"));
    ui->textEdit->append(fileName);
}

void dashboard::saveprofile ()
{
    ui->textEdit->append( "save profile");

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                     "",
                                                     tr("Remote Profile Bucket (*.rpb)"));
    ui->textEdit->append(fileName);
}

void dashboard::uploadprofile ()
{
    ui->textEdit->append( "upload profile");
}

void dashboard::downloadprofile ()
{
    ui->textEdit->append( "download profile");
}

dashboard::~dashboard()
{
    delete ui;
    delete ui2;
    delete popup;
}
