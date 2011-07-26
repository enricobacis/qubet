#ifndef MENU_H
#define MENU_H

#include <QThread>
#include <QImage>
#include <QKeyEvent>

#include <GL/gl.h>

class Menu : public QThread
{
    Q_OBJECT

public:
    explicit Menu(QMap<QImage, GLint> &_skinsList, QMap<QString, QString> &_levelsList, QObject *parent = 0);
    ~Menu();

    void drawMenu ();

private:
    GLint currentSkin;
    QMap<QImage, GLint> skinsList;
    QMap<QString, QString> levelsList;
    GLint itemSelected;

private slots:
    void keyPressed(QKeyEvent *e);
    void itemClicked(GLint id);

signals:
    void playStory(GLint skinId);
    void playArcade(GLint skinId, QString levelFilename);
    void levelEditor();
    void enableAudio(bool enabled);
    void playAmbientMusic(QString filename);
    void playEffect(GLint effectId);

};

#endif // MENU_H
