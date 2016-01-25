//    Qubet  -  Copyright (C) 2011
//    Enrico Bacis
//    Daniele Ciriello

//    Qubet is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.

//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.

//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.


#include "actionlist.h"

ActionList::ActionList() :
    primaryAction(0)
{ }

ActionList::ActionList(int _primaryAction) :
    primaryAction(_primaryAction)
{ }

ActionList::ActionList(ActionList *other)
{
    primaryAction = other->getPrimaryAction();
    secondaryActions = other->getSecondaryActions();
}

ActionList::~ActionList()
{
    secondaryActions.~QList();
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
