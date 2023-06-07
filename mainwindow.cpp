#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "poland.h"
#include <string>
#include <QPainter>
#include <QPixmap>
#include <QtMath>
#include <QString>
#include <QLineEdit>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(800, 600);

    QPushButton *button = new QPushButton(this);
    (*button).setGeometry(width() * .856 - 10, 10, width() * .144, height() * 0.05);
    (*button).setText("Calc");

    QLabel *label_1 = new QLabel(this);
    (*label_1).setGeometry(width() * .014, 10, width() * .04, height() * 0.05);
    (*label_1).setText("f(x) = ");

    line = new QLineEdit(this);
    line -> setGeometry(width() * .06, 10, width() * .244, height() * 0.05);

    QLabel *label_xmin = new QLabel(this);
    (*label_xmin).setGeometry(width() * .856 - 10, height() * 0.2, width() * .06, height() * 0.05);
    (*label_xmin).setText("x_min = ");

    QLabel *label_xmax = new QLabel(this);
    (*label_xmax).setGeometry(width() * .856 - 10, height() * 0.3, width() * .07, height() * 0.05);
    (*label_xmax).setText("x_max = ");

    line_xmin = new QLineEdit(this);
    (*line_xmin).setGeometry(width() * .92 - 10, height() * 0.2, width() * .07, height() * 0.05);

    line_xmax = new QLineEdit(this);
    (*line_xmax).setGeometry(width() * .92 - 10, height() * 0.3, width() * .07, height() * 0.05);



    connect(button, SIGNAL(clicked()), this, SLOT(pushButton_clicked()));
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::paintEvent(QPaintEvent *event)
{
    /*QPainter painter;
    painter.begin(this);
    QPen pen;
    //pen.setColor(Qt::red);

    pen.setColor(0xff0000);
    pen.setWidth(100);
    pen.setCapStyle(Qt::RoundCap);
    painter.setPen(pen);

    painter.drawLine(199, 199, 200, 200);
    painter.end();*/
}


int MainWindow::FindK (char q, int gmax, int gmin, double amax, double amin) {
    double ans;
    if (q == 'x') {
        int a = gmax - gmin;
        int b = amax - amin;
        ans = a/b;
    } else {
        int a = gmin - gmax;
        int b = amax - amin;
        ans = a/b;
    }
    return ans;
}




void MainWindow::pushButton_clicked()
{
    QPixmap pm(width() * 0.8125, height() * 0.883);
    QPainter painter;
    painter.begin(&pm);
    QColor col;
    col.setRgb(213, 255, 218);
    pm.fill(col);

    ui->label->setGeometry(10, 50,width() * 0.8125, height() * 0.883);

    QPen pen;

    //double a = 10;
    QString xmn = line_xmin->text();
    QString xmx = line_xmax->text();
    cout << "here" << endl;
    string xmn1 = xmn.toStdString();
    string xmx1 = xmx.toStdString();
    cout << xmn1 << ' ' << xmx1 << endl;
    double xmin = std::stod(xmn1), xmax = std::stod(xmx1);
    double ymin = xmin, ymax = xmax;
    cout << xmin << ' ' << xmax << endl;

    int xgmin = 0, xgmax = pm.width();
    int ygmin = 0, ygmax = pm.height();

    double x, y;
    int xg, yg;

    x = xmin;

    double kx = FindK ('x', xgmax, xgmin, xmax, xmin);
    double ky = FindK ('y', ygmax, ygmin, ymax, ymin);

    double x0 = xgmin - (kx * xmin);
    double y0 = ygmin - (ky * ymax);

    QString fx = line->text();
    QString num;
    double par;
    num = QString::number(x);
    num += ')';
    num = '(' + num;
    fx.replace("x", num);
    string s = fx.toStdString();
    calc(s, y);
    xg = x0 + (kx * x);
    yg = y0 + (ky * y);

    QPainterPath A;
    A.moveTo(xg, yg);
    //cout << "start (" << xg << ", " << yg << ")" << endl;

    double stepx = 1e-2;

    while (x < xmax) {
        if (x >= -1e-10 and x < 0) {
            x = 0;
        }

        if (x <= 1e-4 and x >= -1e-4) {
            x = 0;
        }

         num = QString::number(x);
         num += ')';
         num = '(' + num;
         fx.replace("x", num);
         string s = fx.toStdString();

         calc (s, y);
         cout << " y = " << y << " x = " << x << endl;

         QColor col_1;
         col_1.setRgb(179, 116, 255);
         painter.setPen(pen);
         pen.setColor(col_1);
         pen.setWidth(1);
         pen.setCapStyle(Qt::RoundCap);

         xg = x0 + (kx * x);
         yg = y0 + (ky * y);

         if (y < ymax + 10 and y > ymin - 10) {
            A.lineTo(xg, yg);
            cout << "drawing line to (" << xg << ", " << yg << ")" << endl;
         }
         A.moveTo(xg, yg);

         painter.drawPath(A);

         fx.replace(num, "x");

         x += stepx;
    }

    pen.setColor(Qt::black);
    pen.setWidth(1);
    pen.setCapStyle(Qt::FlatCap);
    painter.setPen(pen);

    //int W = pm.width() / 2;
    //int H = pm.height() / 2;

    painter.drawLine(x0 - pm.width(), y0, x0 + pm.width(), y0);
    painter.drawLine(x0, y0 - pm.width(), x0, y0 + 2 * pm.height());


    ui->label->setPixmap(pm);
    painter.end();
}
