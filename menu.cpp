#include "menu.h"

Menu::Menu(QMap<GLint,QImage*> &_skinsList, QMap<GLint,QString> &_levelsList, QObject *_parent) :
    parent(_parent),
    skinsList(_skinsList),
    levelsList(_levelsList)
{
}

Menu::~Menu()
{
    parent->disconnect(this);
}

GLvoid Menu::draw(GLboolean simplifyForPicking)
{
    drawSquare(3, 3);
}

void Menu::itemClicked(QList<GLuint> listNames)
{

}

void Menu::mouseReleased(QMouseEvent *event)
{

}

void Menu::mouseMoved(QMouseEvent *event)
{

}

void Menu::keyPressed(QKeyEvent *event)
{

}
