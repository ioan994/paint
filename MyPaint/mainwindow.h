#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <canvas.h>
#include <geoobj.h>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_horizontalSlider_valueChanged(int value);
    void on_rbPencil_clicked();
    void on_rbRect_clicked();
    void on_rbEllipse_clicked();
    void on_rbLine_clicked();
    void on_rbFill_clicked();
    void on_bClear_clicked();
    void on_bUndo_clicked();
    void on_bColor_clicked();

private:
    void setDefaultPenStyle();
    void setGeoObjInfo(GeoObj * obj); // setting pen styles for geometrical object

    Ui::MainWindow *ui;
    QColor penColor;
    int penWidth;
};

#endif // MAINWINDOW_H
