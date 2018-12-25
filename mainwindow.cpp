#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "config.h"
extern "C"{
#include "sensor.h"
}
#include <QStyleFactory>
#include <QString>
#include <QFont>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    /* setup ui */
    ui->setupUi(this);

    /* change design */
    qApp->setStyle(QStyleFactory::create("fusion"));

    QPalette palette;
    palette.setColor(QPalette::Window, QColor(53,53,53));
    palette.setColor(QPalette::WindowText, Qt::white);
    palette.setColor(QPalette::Base, QColor(15,15,15));
    palette.setColor(QPalette::AlternateBase, QColor(53,53,53));
    palette.setColor(QPalette::ToolTipBase, Qt::white);
    palette.setColor(QPalette::ToolTipText, Qt::white);
    palette.setColor(QPalette::Text, Qt::white);
    palette.setColor(QPalette::Button, QColor(53,53,53));
    palette.setColor(QPalette::ButtonText, Qt::white);
    palette.setColor(QPalette::BrightText, Qt::red);
    palette.setColor(QPalette::Highlight, QColor(142,45,197).lighter());
    palette.setColor(QPalette::HighlightedText, Qt::black);
    qApp->setPalette(palette);
}

MainWindow::~MainWindow()
{
    delete ui;
    label->~QLabel();
    stopSensor();
    deinitSensor();
}

void MainWindow::on_pushButton_clicked()
{
    /* change values */
    getData(&red, &green, &blue, &clear);

    /* update display */
    update();
}

void MainWindow::on_pushButton_2_clicked()
{
    this->~MainWindow();
}

/* is called when update() is called */
void MainWindow::paintEvent(QPaintEvent *event)
{
    /* avoid compiler warning */
    (void) event;

    /* print colored rect */
    QPainter *painter = new QPainter(this);
    painter->fillRect(RECT_POS_X, RECT_POS_Y, RECT_SIZE_X, RECT_SIZE_Y, QColor(red,green,blue));
    //painter->drawText(RECT_POS_X, RECT_POS_Y, "Machine " + QString::number(20));
    painter->~QPainter();


    /* print rgb value label */
    label->setText("red: " + QString::number(red)
                   + "\ngreen: " + QString::number(blue)
                   + "\nblue: " + QString::number(green)
                   + "\nclear: " + QString::number(clear));
    label->setGeometry(LABEL_POS_X,LABEL_POS_Y,LABEL_SIZE_X,LABEL_SIZE_Y);
    QFont f( "Ubuntu", LABEL_FONT_SIZE, QFont::Light);
    label->setFont(f);
    label->show();
}


