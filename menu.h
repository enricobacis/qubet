#ifndef MENU_H
#define MENU_H

#include <QThread>
#include <QImage>
#include <QKeyEvent>
#include <QMap>

#include <GL/gl.h>

/**
 * @brief
 *
 */
class Menu : public QThread
{
    Q_OBJECT

public:
    /**
     * @brief
     *
     * @param _skinsList
     * @param _levelsList
     * @param parent
     */
    explicit Menu(QMap<GLint,QImage*> &_skinsList, QMap<GLint,QString> &_levelsList, QObject *parent = 0);
    /**
     * @brief
     *
     */
    ~Menu();

    /**
     * @brief
     *
     */
    void draw();

private:
    GLint currentSkin; /**< TODO */
    QMap<GLint,QImage*> skinsList; /**< TODO */
    QMap<GLint,QString> levelsList; /**< TODO */
    GLint itemSelected; /**< TODO */

    /**
     * @brief
     *
     */
    void run();

private slots:
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

signals:
    /**
     * @brief
     *
     * @param skinId
     */
    void playStory(GLint skinId);

    /**
     * @brief
     *
     * @param skinId
     * @param levelFilename
     */
    void playArcade(GLint skinId, QString levelFilename);

    /**
     * @brief
     *
     */
    void showLevelEditor();

    /**
     * @brief
     *
     * @param enabled
     */
    void enableAudio(bool enabled);

    /**
     * @brief
     *
     * @param filename
     */
    void playAmbientMusic(QString filename);

    /**
     * @brief
     *
     * @param effectId
     */
    void playEffect(GLint effectId);

};

#endif // MENU_H
