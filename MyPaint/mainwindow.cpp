#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <geoobj.h>

#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    penColor(0,0,0),
    penWidth(1)
{

    ui->setupUi(this);
    setDefaultPenStyle();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setDefaultPenStyle()
{
    CustomLine * ln = new CustomLine;
    setGeoObjInfo(ln);
    ui->widget->setObj(ln);

    QPalette palette = ui->label->palette();
    palette.setColor(ui->label->backgroundRole(), penColor);
    ui->label->setAutoFillBackground(true);
    ui->label->setPalette(palette);
}

void MainWindow::setGeoObjInfo(GeoObj * obj)
{
    obj->setPenColor(penColor.rgb());
    obj->setPenWidth(penWidth);
}

void MainWindow::on_rbPencil_clicked()
{
    CustomLine * cl = new CustomLine;
    setGeoObjInfo(cl);
    ui->widget->setObj(cl);
}

void MainWindow::on_rbRect_clicked()
{
    Rectangle * rec = new Rectangle;
    setGeoObjInfo(rec);
    ui->widget->setObj(rec);
}

void MainWindow::on_rbEllipse_clicked()
{
    Ellipse * el = new Ellipse;
    setGeoObjInfo(el);
    ui->widget->setObj(el);
}
void MainWindow::on_rbLine_clicked()
{
    Line * ln = new Line;
    setGeoObjInfo(ln);
    ui->widget->setObj(ln);
}

void MainWindow::on_rbFill_clicked()
{
    Fill * f = new Fill;
    setGeoObjInfo(f);
    ui->widget->setObj(f);
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    ui->lWidth->setText(QString("Width = ")+QString::number(value));
    penWidth = value;
    ui->widget->setWidth(value);
}



void MainWindow::on_bClear_clicked()
{
    ui->widget->clear();
}

void MainWindow::on_bUndo_clicked()
{
    ui->widget->undo();
}

void MainWindow::on_bColor_clicked()
{
    QColor color = QColorDialog::getColor();
    penColor = color;
    QPalette palette = ui->label->palette();
    palette.setColor(ui->label->backgroundRole(), penColor);
    ui->label->setPalette(palette);

    ui->widget->setColor(penColor.rgb());
}
