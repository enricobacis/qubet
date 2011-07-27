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

void MainQubet::loadingStepCompleted()
{

}

void MainQubet::loadingCompleted()
{

}

void MainQubet::drawAll()
{

}

void MainQubet::skinsLoaded()
{

}

void MainQubet::levelsLoaded()
{

}

void MainQubet::obstacleModelsLoaded()
{

}

void MainQubet::playStory(GLint skinId)
{

}

void MainQubet::playArcade(GLint skinId, QString levelFilename)
{

}

void MainQubet::levelEditor()
{

}

void MainQubet::showMenu()
{

}
