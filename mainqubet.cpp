#include "mainqubet.h"
#include "ui_mainqubet.h"

MainQubet::MainQubet(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainQubet)
{
    ui->setupUi(this);
}

MainQubet::~MainQubet()
{
    delete ui;
}
