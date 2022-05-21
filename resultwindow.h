#ifndef RESULTWINDOW_H
#define RESULTWINDOW_H

#include <QDialog>

namespace Ui {
class ResultWindow;
}

class ResultWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ResultWindow(QWidget *parent = nullptr);
    ~ResultWindow();
    void creatTableWidgets();

private slots:
    void getData(QString data);

    void on_pushButtonExport_clicked();

    void on_pushButtonBrowse_clicked();

private:
    Ui::ResultWindow *ui;
};

#endif // RESULTWINDOW_H
