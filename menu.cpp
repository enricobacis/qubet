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
    glPushName(1);
    glPushMatrix();
        glTranslatef(0.0, 3.5, 0.0);
        drawRectangle(10.0, 4.0);
    glPopMatrix();
    glPopName();

    glPushName(2);
    glPushMatrix();
        glTranslatef(0.0, -3.5, 0.0);
        drawRectangle(10.0, 4.0);
    glPopMatrix();
    glPopName();
}

void Menu::itemClicked(QList<GLuint> listNames)
{
    if (!listNames.isEmpty())
    {
        if (listNames.at(0) == 1)
            qDebug() << "Story";
        else
            qDebug() << "Arcade";
    }
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
