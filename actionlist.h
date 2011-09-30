#ifndef ACTIONLIST_H
#define ACTIONLIST_H

#include <QList>

/**
 * @brief
 *
 * @version 1.0
 * @author \#34
 */
class ActionList
{

public:

    /**
     * @brief
     *
     * @param _primaryAction
     */
    explicit ActionList(int _primaryAction);

    /**
     * @brief
     *
     * @param other
     */
    explicit ActionList(ActionList *other);

    /**
     * @brief
     *
     */
    ~ActionList();

    /**
     * @brief
     *
     * @param _primaryAction
     */
    void setPrimaryAction(int _primaryAction);

    /**
     * @brief
     *
     */
    int getPrimaryAction();

    /**
     * @brief
     *
     * @param _secondaryAction
     */
    void appendSecondaryAction(int _secondaryAction);

    /**
     * @brief
     *
     * @param _secondaryAction
     */
    void removeSecondaryAction(int _secondaryAction);

    /**
     * @brief
     *
     */
    QList<int> getSecondaryActions();

    /**
     * @brief
     *
     */
    QList<int> getAllActions();

private:

    int primaryAction; /**< TODO */
    QList<int> secondaryActions; /**< TODO */
};

#endif // ACTIONLIST_H
