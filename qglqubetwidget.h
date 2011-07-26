#ifndef QGLQUBETWIDGET_H
#define QGLQUBETWIDGET_H

#include <QGLWidget>

#include <GL/gl.h>

class QGLQubetWidget : public QGLWidget
{
    Q_OBJECT

public:
    explicit QGLQubetWidget(QObject *parent = 0);
    ~QGLQubetWidget();

private:
    void mousePressEvent(QMouseEvent *e);
    void keyPressEvent(QKeyEvent *e);

signals:
    void keyPressed(QKeyEvent *e);
    void itemClicked(GLint id);

};

#endif // QGLQUBETWIDGET_H
