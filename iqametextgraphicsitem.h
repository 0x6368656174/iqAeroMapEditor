#ifndef IQAMETEXTGRAPHICSITEM_H
#define IQAMETEXTGRAPHICSITEM_H

#include <QGraphicsSimpleTextItem>
#include "iqameshapelink.h"

class IqAmeText;
class IqAmeTextGraphicsItem : public QGraphicsSimpleTextItem, public IqAmeShapeLink
{
public:
    explicit IqAmeTextGraphicsItem(QGraphicsItem *parent = Q_NULLPTR);

    void updateCache();

public:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

    virtual QPainterPath shape() const;

public:
    void setText(IqAmeText *text);

private:
    IqAmeText *m_text;
};

#endif // IQAMETEXTGRAPHICSITEM_H
