#ifndef CANVAS_H
#define CANVAS_H

#include <geoobj.h>
#include <QWidget>
#include <QPixmap>
#include <QVector>

const int image_steps_count = 3;

class Canvas : public QWidget // present painting widget
{

    Q_OBJECT

public:
    Canvas(QWidget* parent=0);
    ~Canvas();
    void setObj(GeoObj *obj);  // sets geometrical object to be painted
    void setWidth(int width); // object width
    void setColor(QRgb color); // object color
    void undo();  // undo last action
    void clear(); // clear canvas form pic
protected:
    void nextStep(); //shift currentStep index to the next step
    void resizeEvent ( QResizeEvent * event );
    void paintEvent( QPaintEvent *e );
    void mouseMoveEvent ( QMouseEvent * event );
    void mousePressEvent ( QMouseEvent * event );
    void mouseReleaseEvent ( QMouseEvent * event );

    GeoObj * go;  // painted geometrical object
    QPixmap disPm; // temp. image to display
    QVector<QPixmap> stepsPm;  // steps of image creation
    int currentStep;  // current image displayed
    bool pressed; // if lmb is pressed
};

#endif // CANVAS_H
