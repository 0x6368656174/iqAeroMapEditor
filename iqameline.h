#ifndef IQAMELINE_H
#define IQAMELINE_H

#include "iqamenamedshapeobject.h"
#include "iqamesubline.h"
#include <QGraphicsItemGroup>
#include "iqamelinegraphicsitem.h"

class IqAmeLine : public IqAmeNamedShapeObject
{
    Q_OBJECT
public:
    explicit IqAmeLine(QObject *parent = 0);

    ~IqAmeLine();

    virtual IqAmeLineGraphicsItem *graphicsItem() Q_DECL_OVERRIDE;

    virtual void updateGraphicsItem() Q_DECL_OVERRIDE;

    virtual bool loadFromString(const QString &string) Q_DECL_OVERRIDE;

    virtual IqAmeShapesAttributes *outputAttributes() const Q_DECL_OVERRIDE;

    void appendSubLine(IqAmeSubLine *subLine);

    void insertSubLine(const int position, IqAmeSubLine *subLine);

    void removeSubLine(IqAmeSubLine *subLine);

    QList<IqAmeSubLine *> subLines() const;

private:
    void setOutputAttributes(IqAmeShapesAttributes * outputAttributes);

private:
    QList<IqAmeSubLine *> m_subLines;
    IqAmeShapesAttributes * m_outputAttributes;
    IqAmeLineGraphicsItem *m_graphicsItem;
};

#endif // IQAMELINE_H
