#ifndef QGLQUBETWIDGET_H
#define QGLQUBETWIDGET_H

#include <QGLWidget>

#include <GL/gl.h>

/**
 * @brief
 *
 */
class QGLQubetWidget : public QGLWidget
{
    Q_OBJECT

public:
    /**
     * @brief
     *
     * @param parent
     */
    explicit QGLQubetWidget(QObject *parent = 0);

    /**
     * @brief
     *
     */
    ~QGLQubetWidget();

private:
    /**
     * @brief
     *
     * @param e
     */
    void mousePressEvent(QMouseEvent *e);

    /**
     * @brief
     *
     * @param e
     */
    void keyPressEvent(QKeyEvent *e);

signals:
    /**
     * @brief
     *
     * @param e
     */
    void keyPressed(QKeyEvent *e);

    /**
     * @brief
     *
     * @param id
     */
    void itemClicked(GLint id);

};

#endif // QGLQUBETWIDGET_H
