#ifndef IQAMELINE_H
#define IQAMELINE_H

#include "iqamenamedshapeobject.h"
#include "iqamesubline.h"
#include <QGraphicsItemGroup>

class IqAmeLine : public IqAmeNamedShapeObject
{
    Q_OBJECT
public:
    explicit IqAmeLine(QObject *parent = 0);

    ~IqAmeLine();

    virtual QList<QGraphicsItem *> graphicsItems() Q_DECL_OVERRIDE;

    virtual void updateGraphicsItems() Q_DECL_OVERRIDE;

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
};

#endif // IQAMELINE_H
