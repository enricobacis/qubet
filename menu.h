#ifndef MENU_H
#define MENU_H

#include <QThread>
#include <QImage>
#include <QKeyEvent>

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
     * @param QMap<QImage
     * @param _skinsList
     * @param QMap<QString
     * @param _levelsList
     * @param parent
     */
    explicit Menu(QMap<QImage, GLint> &_skinsList, QMap<QString, QString> &_levelsList, QObject *parent = 0);
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
    QMap<QImage, GLint> skinsList; /**< TODO */
    QMap<QString, QString> levelsList; /**< TODO */
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
    void levelEditor();
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
