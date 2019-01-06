/* c header */
extern "C"{
#include "sensor.h"
#include "button.h"
}

/* c++ header */
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "config.h"
#include <QStyleFactory>
#include <QString>
#include <QFont>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    /* set window size*/
    this->setFixedSize(SIZE_X, SIZE_Y);

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

    /* add button1 */
    button1 = new QPushButton("Start messurement", this);
    button1->setGeometry(BUTTON_POS_X, BUTTON_POS_Y, BUTTON_SIZE_X, BUTTON_SIZE_Y);
    connect(button1, SIGNAL (clicked()), this, SLOT (button1_clicked()));

    /* add button2 */
    button2 = new QPushButton("Reset messurement", this);
    button2->setGeometry(BUTTON_POS_X, BUTTON_POS_Y + BUTTON_SIZE_Y + BUTTON_GAP, BUTTON_SIZE_X, BUTTON_SIZE_Y);
    connect(button2, SIGNAL (clicked()), this, SLOT (button2_clicked()));

    /* add button3 */
    button3 = new QPushButton("Quit", this);
    button3->setGeometry(BUTTON_POS_X, BUTTON_POS_Y + 2*(BUTTON_SIZE_Y + BUTTON_GAP), BUTTON_SIZE_X, BUTTON_SIZE_Y);
    connect(button3, SIGNAL (clicked()), this, SLOT (button3_clicked()));

    /* add label */
    label = new QLabel(this);
}

MainWindow::~MainWindow()
{
    label->~QLabel();
    button1->~QPushButton();
    button2->~QPushButton();
    button3->~QPushButton();
}

void MainWindow::button1_clicked()
{
    /* change values */
    getData(&red, &green, &blue, &clear);

    /* update display */
    update();
}
void MainWindow::button2_clicked()
{
    /* reset values */
    red = 0;
    green = 0;
    blue = 0;
    clear = 0;

    /* update display */
    update();
}
void MainWindow::button3_clicked()
{
    //stopSensor();
    //deinitSensor();
    //deinitHardware();
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
    painter->~QPainter();

    /* print rgb value label */
    label->setText("red:        " + QString::number(red)
                   + "\ngreen:   " + QString::number(blue)
                   + "\nblue:      " + QString::number(green)
                   + "\nclear:     " + QString::number(clear));
    label->setGeometry(LABEL_POS_X,LABEL_POS_Y,LABEL_SIZE_X,LABEL_SIZE_Y);
    QFont f( "Ubuntu", LABEL_FONT_SIZE, QFont::Light);
    label->setFont(f);
    label->show();
}




