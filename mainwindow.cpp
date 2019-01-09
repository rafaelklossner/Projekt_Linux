/* c header */
extern "C"{
#include "sensor.h"
#include "button.h"
}

/* c++ header */
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "config.h"
#include "sensor.h"
#include "threadPollButtons.h"
#include <QStyleFactory>
#include <QString>
#include <QFont>
#include <QApplication>
#include <QRect>

MainWindow::MainWindow(QApplication *qApplication1)
{
    qApplication = qApplication1;

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

    /* add label1 */
    label1 = new QLabel(this);

    /* add label2 */
    label2 = new QLabel(this);

    /* add label3 */
    label3 = new QLabel(this);

    /* add slider1 */
    slider1 = new QSlider(this);
    slider1->setGeometry(SLIDER_POS_X, SLIDER_POS_Y, SLIDER_SIZE_X, SLIDER_SIZE_Y);
    slider1->setOrientation(Qt::Horizontal);

    /* add slider1 */
    slider2 = new QSlider(this);
    slider2->setGeometry(SLIDER_POS_X, SLIDER_POS_Y + SLIDER_GAP, SLIDER_SIZE_X, SLIDER_SIZE_Y);
    slider2->setOrientation(Qt::Horizontal);
}

MainWindow::~MainWindow()
{
    label1->hide();
    label1->~QLabel();
    button1->hide();
    button1->~QPushButton();
    button2->hide();
    button2->~QPushButton();
    button3->hide();
    button3->~QPushButton();
    //qApplication->closeAllWindows();
    //qApplication->quit();
    //qApplication->~QApplication();
}

void MainWindow::button1_clicked()
{
    messure();
}
void MainWindow::messure()
{
    /* change values */
    getData(&red, &green, &blue, &clear);

    /* update display */
    update();
}

void MainWindow::button2_clicked()
{
    reset();
}
void MainWindow::reset()
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
    end();
}
void MainWindow::end()
{
    stopSensor();
    deinitSensor();
    deinitHardware();
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
    label1->setText("red:        " + QString::number(red)
                    + "\ngreen:   " + QString::number(blue)
                    + "\nblue:      " + QString::number(green)
                    + "\nclear:     " + QString::number(clear));
    label1->setGeometry(LABEL_POS_X,LABEL_POS_Y,LABEL_SIZE_X,LABEL_SIZE_Y);
    QFont f( "Ubuntu", LABEL_FONT_SIZE, QFont::Light);
    label1->setFont(f);
    label1->show();

    /* change slider1 status */
    tcs34725IntegrationTime_t integrationTime = getIntegationTime();
    int integrationTimeValue = 0;

    switch (integrationTime) {
    case TCS34725_INTEGRATIONTIME_2_4MS:
        integrationTimeValue = 0;
        break;
    case TCS34725_INTEGRATIONTIME_24MS:
        integrationTimeValue = 3;
        break;
    case TCS34725_INTEGRATIONTIME_50MS:
        integrationTimeValue = 7;
        break;
    case TCS34725_INTEGRATIONTIME_101MS:
        integrationTimeValue = 14;
        break;
    case TCS34725_INTEGRATIONTIME_154MS:
        integrationTimeValue = 21;
        break;
    case TCS34725_INTEGRATIONTIME_700MS:
        integrationTimeValue = 100;
        break;
    default:
        break;
    }
    slider1->setSliderPosition(integrationTimeValue);

    /* change slider2 status */
    tcs34725Gain_t gain = getGain();
    int gainValue = 0;

    switch (gain) {
    case TCS34725_GAIN_1X:
        gainValue = 0;
        break;
    case TCS34725_GAIN_4X:
        gainValue = 7;
        break;
    case TCS34725_GAIN_16X:
        gainValue = 26;
        break;
    case TCS34725_GAIN_60X:
        gainValue = 100;
        break;
    default:
        break;
    }
    slider2->setSliderPosition(gainValue);

    /* show slider description */
    QFont font2( "Ubuntu", 10, QFont::Light);
    label2->setText("integration time: " + QString::number(integrationTimeValue));
    label2->setGeometry(SLIDER_POS_X,SLIDER_POS_Y - 20,LABEL_SIZE_X,LABEL_SIZE_Y);
    label2->setFont(font2);
    label2->show();

    label3->setText("gain: " + QString::number(gainValue));
    label3->setGeometry(SLIDER_POS_X,SLIDER_POS_Y - 20 + SLIDER_GAP,LABEL_SIZE_X,LABEL_SIZE_Y);
    label3->setFont(font2);
    label3->show();

    /* show highlighting rect for slider */
    QRect rect;
    if(this->selectedSlider == 0){
        rect.setRect(SLIDER_POS_X, SLIDER_POS_Y, SLIDER_SIZE_X, SLIDER_SIZE_Y);
    }else{
        rect.setRect(SLIDER_POS_X, SLIDER_POS_Y + SLIDER_GAP, SLIDER_SIZE_X, SLIDER_SIZE_Y);
    }
    painter->setPen(QColor(142,45,197));
    painter->drawRect(&rect);
}




