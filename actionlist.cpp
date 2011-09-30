#include "actionlist.h"

ActionList::ActionList(int _primaryAction) :
    primaryAction(_primaryAction)
{
}

ActionList::ActionList(ActionList *other)
{
    primaryAction = other->getPrimaryAction();
    secondaryActions = other->getSecondaryActions();
}

ActionList::~ActionList()
{
}

void ActionList::setPrimaryAction(int _primaryAction)
{
    primaryAction = _primaryAction;
}

int ActionList::getPrimaryAction()
{
    return primaryAction;
}

void ActionList::appendSecondaryAction(int _secondaryAction)
{
    secondaryActions.append(_secondaryAction);
}

void ActionList::removeSecondaryAction(int _secondaryAction)
{
    secondaryActions.removeOne(_secondaryAction);
}

QList<int> ActionList::getSecondaryActions()
{
    return secondaryActions;
}

QList<int> ActionList::getAllActions()
{
    QList<int> actions;

    actions.append(primaryAction);
    actions += secondaryActions;

    return actions;
}
