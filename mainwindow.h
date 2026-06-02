#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QPushButton * button;
    QLineEdit * fun;
    QLineEdit * Min;
    QLineEdit * Max;
    QLineEdit * MinY;
    QLineEdit * MaxY;
    QPushButton * button_clear;


private:
    Ui::MainWindow *ui;
private slots:
    void drgr();
    void on_MAX_linkActivated(const QString &link);
    void on_button_clear_clicked();
};

#endif // MAINWINDOW_H
