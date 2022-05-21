#include "resultwindow.h"
#include "ui_resultwindow.h"

#include <QFileDialog>
#include <QMessageBox>

ResultWindow::ResultWindow(QWidget *parent) : QDialog(parent), ui(new Ui::ResultWindow) {
    ui->setupUi(this);
    creatTableWidgets();
}

QString directionExport;

void ResultWindow::creatTableWidgets() {
    ui->tableWidgetResult->setColumnCount(1);
    ui->tableWidgetResult->setShowGrid(true);
    ui->tableWidgetResult->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidgetResult->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetResult->setHorizontalHeaderLabels(QStringList() << ("Об'єм реалізації товару (млн. грн)"));
    ui->tableWidgetResult->horizontalHeader()->setStretchLastSection(true);
}
void ResultWindow::getData(QString data) {
    QString s = "";
    for (int i = 0; i < data.size(); i++) {
        if (data[i] == '\n') {
            ui->tableWidgetResult->insertRow(ui->tableWidgetResult->rowCount());
            ui->tableWidgetResult->setItem(ui->tableWidgetResult->rowCount() - 1, 0, new QTableWidgetItem(s));
            s.clear();
        } else {
            s += data[i];
        }
    }
}

ResultWindow::~ResultWindow() {
    delete ui;
}

void ResultWindow::on_pushButtonExport_clicked() {
    QFile file(directionExport);
    if (file.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream data(&file);
        for(int row = 0; row < ui->tableWidgetResult->rowCount(); row++) {
            data << ui->tableWidgetResult->item(row, 0)->text() + "\n";
        }
        file.close();
        QMessageBox::information(this, "Ок", "Файл успішно збережений!");
    } else {
        QMessageBox::warning(this, "Помилка", "Оберіть файл!");
    }
}

void ResultWindow::on_pushButtonBrowse_clicked(){
    QFileDialog directory;
    ui->lineEditFileDirection->setText(directory.getSaveFileName(this, "Оберіть файл", QDir::homePath(), tr("CSV (*.csv);;TXT (*.txt)")));
    directionExport = ui->lineEditFileDirection->text();
}

