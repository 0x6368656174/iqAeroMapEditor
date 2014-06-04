#include "iqameapplication.h"

IqAmeMapModel * IqAmeApplication::_aeroMapModel = NULL;

IqAmeApplication::IqAmeApplication(QObject *parent) :
    QObject(parent)
{
}

IqAmeMapModel * IqAmeApplication::aeroMapModel()
{
    if (IqAmeApplication::_aeroMapModel)
    {
        return IqAmeApplication::_aeroMapModel;
    }
    else
    {
        IqAmeApplication::_aeroMapModel = new IqAmeMapModel();
    }

    return IqAmeApplication::_aeroMapModel;
}
