#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "resultwindow.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

signals:
    void sendData(QString data);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void creatTableWidgets();
private slots:
    void on_pushButtonAdd_clicked();

    void on_pushButtonDelete_clicked();

    void on_tableWidgetFactors_clicked(const QModelIndex &index);

    void on_pushButtonCalculate_clicked();

    void on_pushButtonSelectFile_clicked();

    void on_pushButtonImport_clicked();

    void on_pushButtonEdit_clicked();

private:
    Ui::MainWindow *ui;
    ResultWindow *resultWindow;
};
#endif // MAINWINDOW_H
