#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QLabel>
#include <stdint.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    uint16_t red = 0;
    uint16_t blue = 0;
    uint16_t green = 0;
    uint16_t clear = 0;

private slots:
    void on_pushButton_clicked();
    void paintEvent(QPaintEvent *event);

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    QLabel *label = new QLabel(this);
};

#endif // MAINWINDOW_H
