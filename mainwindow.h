#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QLabel>
#include <QPushButton>
#include <QSlider>
#include <stdint.h>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QApplication *qApplication1);
    ~MainWindow();
    uint16_t red = 0;
    uint16_t blue = 0;
    uint16_t green = 0;
    uint16_t clear = 0;
    uint16_t integration = 0;
    uint16_t gain = 0;
    int selectedSlider = 0;
    void paintEvent(QPaintEvent *event);
    void messure();
    void reset();
    void end();

private slots:
    void button1_clicked();
    void button2_clicked();
    void button3_clicked();

private:
    QApplication *qApplication;
    QLabel *label1;
    QLabel *label2;
    QLabel *label3;
    QPushButton *button1;
    QPushButton *button2;
    QPushButton *button3;
    QSlider *slider1;
    QSlider *slider2;
};

#endif // MAINWINDOW_H
