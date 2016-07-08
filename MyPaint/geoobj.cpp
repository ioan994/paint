#include <geoobj.h>
#include <QPainter>
#include <QQueue>

GeoObj::GeoObj()
{
    pen.setColor(Qt::black);
    pen.setWidth(1);
}
void GeoObj::setPenWidth(int w)
{
    pen.setWidth(w);
}
void GeoObj::setPenColor(QRgb color)
{
    pen.setColor(color);
}




void Fill::setFirstP(const QPoint & p)
{
    pnt = p;
}

void Fill::setNextP(const QPoint & p)
{
    pnt = p; // only last point matters
}

void Fill::draw(QPixmap & pm)
{
    QImage im = pm.toImage();

    floodFill(im, pnt, pen.color().rgb());
    pm = QPixmap::fromImage(im);

}

void Fill::clear(){}
void Fill::floodFill(QImage & im, QPoint p, QRgb repColor)
{
    if(p.x()<0 || p.x()>= im.width() || p.y()<0 || p.y()>=im.height()) // if pixel outside of image
        return;

    QPoint tmp, north, south, west, east;
    QRgb pcol = im.pixel(p);

    if(pcol == repColor)
        return;


    QQueue<QPoint> pqueue;
    pqueue.enqueue(p);
    while(!pqueue.isEmpty()) // while all points are not flooded
    {
        tmp = pqueue.dequeue();
        if(im.pixel(tmp) == pcol)
        {
            im.setPixel(tmp, repColor); // setting new color

            // enqueuing all points around
            west = QPoint(tmp.x()-1, tmp.y());
            if(west.x()>= 0 && im.pixel(west) !=repColor)
            {
                pqueue.enqueue(west);
            }

            east = QPoint(tmp.x()+1, tmp.y());
            if(east.x()< im.width() && im.pixel(east) !=repColor)
            {
                pqueue.enqueue(east);
            }

            north = QPoint(tmp.x(), tmp.y()-1);
            if(north.y()>= 0 && im.pixel(north) !=repColor)
            {
                pqueue.enqueue(north);
            }

            south = QPoint(tmp.x(), tmp.y()+1);
            if(south.y()< im.height() && im.pixel(south) !=repColor)
            {
                pqueue.enqueue(south);
            }
        }
    }

}






void CustomLine::setFirstP(const QPoint & p)
{
    path.moveTo(p); // stetting start point
}

void  CustomLine::setNextP(const QPoint & p)
{
    path.lineTo(p); // line to new point
}

void  CustomLine::draw(QPixmap & pm)
{
    QPainter pntr;
    pntr.begin(&pm);
    pntr.setPen(pen);

    for(int i = 0; i<path.elementCount(); i++)
    {
        pntr.drawPoint(path.elementAt(i));
    }
    pntr.drawPath(path);
    pntr.end();
}
void CustomLine::clear()
{
    path = QPainterPath();
}




void TwoPointGeoObj::setFirstP(const QPoint & p)
{
    fPointSet = true;
    startP = p;

}
void TwoPointGeoObj::setNextP(const QPoint &p)
{
    ePointSet = true;
    endP = p;
}
void TwoPointGeoObj::clear()
{
    fPointSet = false;
    ePointSet = false;
}



void Line::draw(QPixmap &pm)
{
    if(fPointSet && ePointSet)
    {
        QPainter pntr;
        pntr.begin(&pm);
        pntr.setPen(pen);

        pntr.drawLine(startP, endP);
        pntr.end();
    }
}



void Rectangle::draw(QPixmap & pm)
{
    if(fPointSet && ePointSet)
    {
        QPainter pntr;
        pntr.begin(&pm);
        pntr.setPen(pen);

        pntr.drawRect(QRectF(startP, endP));
        pntr.end();
    }
}



void Ellipse::draw(QPixmap &pm)
{
    if(fPointSet && ePointSet)
    {
        QPainter pntr;
        pntr.begin(&pm);
        pntr.setPen(pen);

        pntr.drawEllipse(QRectF(startP, endP));
        pntr.end();
    }
}
