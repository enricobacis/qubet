#ifndef MAINQUBET_H
#define MAINQUBET_H

#include <QMainWindow>
#include <QtOpenGL/QGLWidget>

namespace Ui {
    class MainQubet;
}

class MainQubet : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainQubet(QWidget *parent = 0);
    ~MainQubet();

private:
    Ui::MainQubet *ui;
};

#endif // MAINQUBET_H
