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
    void creatTableWidgets(); //створює таблицю
private slots:
    void on_pushButtonAdd_clicked(); //кнопка додати

    void on_pushButtonDelete_clicked(); //кнопка видалити

    void on_tableWidgetFactors_clicked(const QModelIndex &index); //коли оберається рядок у таблиці

    void on_pushButtonCalculate_clicked(); //кнопка розрахувати

    void on_pushButtonSelectFile_clicked(); //кнопка обрати файл

    void on_pushButtonImport_clicked(); //кнопка імпортувати

private:
    Ui::MainWindow *ui;
    ResultWindow *resultWindow;
};
#endif // MAINWINDOW_H
