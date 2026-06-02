#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <cmath>
#include <poland.h>
const double pi = acos(-1);
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    resize(800,600);
    button = new QPushButton(this);
    button -> setGeometry(690, 10, 100, 30);
    button->setText("BUILD");
    button->setStyleSheet("background-color: #FFC0CB");

    ui->button_clear -> setGeometry(690, 560, 100, 30);
    ui->button_clear -> setText("CLEAR");
    ui->button_clear->setStyleSheet("background-color: #FFC0CB");
    connect(button,SIGNAL(pressed()),this,SLOT(drgr()));

    fun = new QLineEdit(this);
    fun -> setGeometry(40,10,640,30);
    Max = new QLineEdit(this);
    Max -> setGeometry(690,300,100,30);
    Min = new QLineEdit(this);
    Min -> setGeometry(690,240,100,30);
    ui->MIN->setGeometry(725,210,100,30);
    ui->MIN->setText("MIN X");
    ui->MAX->setGeometry(725,270,100,30);
    ui->MAX->setText("MAX X");

    MaxY = new QLineEdit(this);
    MaxY -> setGeometry(690,180,100,30);
    MinY = new QLineEdit(this);
    MinY -> setGeometry(690,120,100,30);
    ui->MINY->setGeometry(725,90,100,30);
    ui->MINY->setText("MIN Y");
    ui->MAXY->setGeometry(725,150,100,30);
    ui->MAXY->setText("MAX Y");

    ui->FUN->setGeometry(10,10,200,30);
    ui->FUN->setText("f(x)");
    ui->centralWidget->setStyleSheet("background-color: #FFF0F5;");
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow :: drgr(){
    QPixmap pm(670,540);//холст для рисования
    pm.fill(QColor("#FFC0CB"));
    ui-> label-> setGeometry(10,50,670,540);
    //ui->label->setStyleSheet("color: ");
    double xmin = -2*pi, ymax =1;
    double xmax = 2*pi, ymin =-1;


    if (Min->text() == ""){
        xmin = -2*pi;
    }else{
        xmin = Min->text().toDouble();
    }
    if (Max->text() == ""){
        xmax = 2*pi;
    }else{
        xmax = Max->text().toDouble();
    }


    double x,y;

    int xgmax = pm.width(), xgmin = 0;
    int ygmax = pm.height(), ygmin = 0;
    QPainter painter;
    painter.begin(&pm);

    double kx =(xgmax - xgmin)/(xmax - xmin);
    double step = 0.1/kx;
    double xg,yg;
    QString func;
    func = fun->text();
    QString func_replace = func;
    double result;
    calculate(func_replace.replace("x","("+QString::number(xmin)+")").toStdString(),result);
    ymin = result; ymax = result;
    if (MinY->text() == ""){
        ymin = -2;
    }else{
        ymin = MinY->text().toDouble();
    }
    if (MaxY->text() == ""){
        ymax = 2;
    }else{
        ymax = MaxY->text().toDouble();
    }
    for(double i = xmin;i < xmax; i+=step){
         calculate(func_replace.replace("x","("+QString::number(i)+")").toStdString(),result);
         if (result < ymin){
             ymin = result;
         }
         if (result >ymax){
             ymax = result;
         }
         func_replace = func;
    }
    if ((ymax-ymin) > 5 * (xmax - xmin)){
        ymax = 5 * (xmax - xmin)/2;
        ymin = -5 * (xmax - xmin)/2;
    }
    double ky =(ygmin - ygmax)/(ymax - ymin) ;
    double x0 = xgmin - kx*xmin, y0 = ygmin - ky*ymax;
    painter.drawLine(xgmin,y0,xgmax,y0);
    painter.drawLine(x0,ygmin,x0,ygmax);
    QPen pen(QColor("#800020"),2);
   // pen.setColor(QColor("#FF1493"));
    pen.setCapStyle(Qt :: RoundCap);
    pen.setJoinStyle(Qt :: RoundJoin);
    painter.setRenderHint(QPainter ::Antialiasing);
    painter.setPen(pen);
    QPainterPath path;

    x = xmin;
    bool first_re = calculate(func_replace.replace("x","("+QString::number(x)+")").toStdString(),y);
    calculate(func_replace.replace("x","("+QString::number(x)+")").toStdString(),y);
    func_replace = func;
    xg = (xgmin);
    yg = ygmin + ky*(y-ymax);
    path.moveTo(xgmin + kx * (x - xmin),ygmin + ky *(y - ymax));//задание нач точки

    while (x < xmax){
       double prev_y = y;
       x+=step;
       bool re = calculate(func_replace.replace("x","("+QString::number(x)+")").toStdString(),y);

       func_replace = func;

       xg = (xgmin + kx * (x - xmin));
       yg = (ygmin + ky *(y - ymax));

       if ((prev_y >0 && y<0 && (prev_y -y)>100) || (prev_y <0 && y>0 && (y-prev_y)>100) || re == false){
           path.moveTo(xg,yg);

       }else{
           path.lineTo(xg,yg);

       }
    }
    painter.drawPath(path);
    painter.end();
    ui->label->setPixmap(pm);
}

void MainWindow::on_button_clear_clicked()
{
    fun->setText("");
    Max->setText("");
    Min->setText("");
}
