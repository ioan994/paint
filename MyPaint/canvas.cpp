#include <canvas.h>
#include <geoobj.h>

#include <typeinfo>

#include <QPainter>
#include <QPen>
#include <QMouseEvent>
#include <QPixmap>

Canvas::Canvas(QWidget* parent):
    QWidget(parent), go(0), stepsPm(image_steps_count), currentStep(0), pressed(false){}
Canvas::~Canvas()
{
    delete go;
}

void Canvas::setObj(GeoObj * obj)
{
    delete go;
    go = obj;
}

void Canvas::setWidth(int width)
{
    if(go == 0)
        return;
    go->setPenWidth(width);
}

void Canvas::setColor(QRgb color)
{
    if(go == 0)
        return;
    go->setPenColor(color);
}

void Canvas::undo()
{
    if(currentStep != 0)
    {
        currentStep--;
    }
    disPm = stepsPm[currentStep];
    update();
}

void Canvas::clear()
{
    nextStep();
    stepsPm[currentStep].fill();
    disPm.fill();
    update();
}


void Canvas::nextStep()
{
    if(currentStep == image_steps_count - 1)
    {
        for(int i = 0; i<image_steps_count - 1; i++) // shifting images, prepare last pixmap for new action
        {
            stepsPm[i] = stepsPm[i+1];
        }
    }
    else
    {
        stepsPm[currentStep+1] = stepsPm[currentStep];
        currentStep++;
    }
}

void Canvas::resizeEvent ( QResizeEvent * event )
{
    stepsPm[0] = QPixmap(event->size());
    stepsPm[0].fill();

    disPm = QPixmap(event->size());
    disPm.fill();
}

void Canvas::mousePressEvent ( QMouseEvent * event )
{
    if(go == 0)
        return;
    go->setFirstP(event->pos());
    event->accept();
    pressed = true;
}

void Canvas::mouseMoveEvent ( QMouseEvent * event )
{
    if(go == 0)
        return;
    if(pressed)
    {
        go->setNextP(event->pos());

        if(typeid(*go) != typeid(Fill)) // fill obj will be drawn only on mouseReleaseEvent
        {
            disPm = stepsPm[currentStep];
            go->draw(disPm); // drawing on temp img
            update();
        }
        event->accept();
    }
}


void Canvas::mouseReleaseEvent ( QMouseEvent * event )
{
    if(go == 0)
        return;
    pressed = false;

    nextStep();

    go->draw(stepsPm[currentStep]); // drawing on actual img
    disPm = stepsPm[currentStep];
    go->clear();
    update();
}

void Canvas::paintEvent( QPaintEvent *e )
{
    QPainter pntr;
    pntr.begin(this);

    pntr.drawPixmap(0,0, disPm);
    pntr.end();
}
