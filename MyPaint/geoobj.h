#ifndef GEOOBJ_H
#define GEOOBJ_H

#include <QPoint>
#include <QPen>


class GeoObj // shared base class for all geometrical objects
{
public:
    GeoObj();
    virtual ~GeoObj(){}
    virtual void setFirstP(const QPoint &p) = 0;
    virtual void setNextP(const QPoint &p) = 0;
    virtual void draw(QPixmap & pm) = 0 ;
    virtual void clear() = 0; // should make obj undrawable and clear points
    void setPenWidth(int w);
    void setPenColor(QRgb color);
protected:
        QPen pen;

};

class Fill : public GeoObj
{
public:
    Fill(){}
    ~Fill(){}
    void setFirstP(const QPoint & p);
    void setNextP(const QPoint & p);
    void draw(QPixmap & pm);
    void clear();
protected:
    void floodFill(QImage & im, QPoint p, QRgb color);

    QPoint pnt;
};

class CustomLine : public GeoObj // pencil tool
{
public:
    CustomLine(){}
    ~CustomLine(){}
    void setFirstP(const QPoint & p);
    void setNextP(const QPoint & p);
    void draw(QPixmap & pm);
    void clear();
protected:
    QPainterPath path; // saves all points here
};


class TwoPointGeoObj : public GeoObj // shared class for obj that can be drawn with two points
{
public:
    TwoPointGeoObj():  startP(0,0), endP(0,0), fPointSet(false), ePointSet(false) {}
    ~TwoPointGeoObj(){}
    void setFirstP(const QPoint & p);
    void setNextP(const QPoint & p);
    virtual void draw(QPixmap & pm) = 0;
    void clear();
protected:
    QPoint startP;
    QPoint endP;
    bool fPointSet;
    bool ePointSet;
};

class Line : public TwoPointGeoObj
{
public:
    Line(){}
    ~Line(){}
    void draw(QPixmap & pm);
};


class Rectangle : public TwoPointGeoObj
{
public:
    Rectangle(){}
    ~Rectangle(){}
    void draw(QPixmap & pm);
};


class Ellipse : public TwoPointGeoObj
{
public:
    Ellipse(){}
    ~Ellipse(){}
    void draw(QPixmap & pm);
};



#endif // GEOOBJ_H
