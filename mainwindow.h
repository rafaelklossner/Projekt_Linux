#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QLabel>
#include <QPushButton>
#include <stdint.h>

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
    void paintEvent(QPaintEvent *event);

private slots:
    void button1_clicked();
    void button2_clicked();
    void button3_clicked();

private:
    QLabel *label;
    QPushButton *button1;
    QPushButton *button2;
    QPushButton *button3;
};

#endif // MAINWINDOW_H
