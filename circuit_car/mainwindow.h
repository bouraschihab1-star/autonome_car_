#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <circuitwidget.h>
#include <controleur.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(int nbVoitures,QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    CircuitWidget circuit;

private slots:
    void newTimeVoiture(int voiture,int time);
    void newBestTimeVoiture(int voiture,int time);
    void newNbTours(int voiture,int nb);
    void start();
    void stop();


};
#endif // MAINWINDOW_H
