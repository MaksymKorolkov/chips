#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <string>

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    creatTableWidgets();
}

double tetta[4] = {-1541.41, 9.00699, 8.63664, 16.3359}; // Θ - матриця коефіцієнтів
double error = 123.2286699348031; //середній регресійний залишок
QString direction; //шлях до .csv файлу
int selectedRow = -1; //обраний рядок (-1 якщо ще не обранний)

void MainWindow::creatTableWidgets() {
    ui->tableWidgetFactors->setColumnCount(4);
    ui->tableWidgetFactors->setShowGrid(true);
    ui->tableWidgetFactors->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidgetFactors->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetFactors->setHorizontalHeaderLabels(QStringList() << ("Реклама")
                                                    << ("Ціна")
                                                    << ("Ціна у конкурентів")
                                                    << ("Індекс"));
    ui->tableWidgetFactors->horizontalHeader()->setStretchLastSection(true);
}

MainWindow::~MainWindow() {
    delete ui;
}

/* Метод перевіряє формат вхідних данних */
bool isNumber(QString s) {
    if (s.toStdString() == "") return false;
    for (auto x : s.toStdString()) {
        if (!((x - 48) >= 0 && (x - 48) <= 9) && x != '.') {
            return false;
        }
    }
    return true;
}

void MainWindow::on_pushButtonAdd_clicked() {
    QString ad = ui->lineEditAd->text();
    QString price = ui->lineEditPrice->text();
    QString priceCompetitor = ui->lineEditPriceCompetitor->text();
    QString index = ui->lineEditIndex->text();
    if (isNumber(ad) && isNumber(price) && isNumber(priceCompetitor) && isNumber(index)) {
        ui->tableWidgetFactors->insertRow(ui->tableWidgetFactors->rowCount());
        ui->tableWidgetFactors->setItem(ui->tableWidgetFactors->rowCount() - 1, 0, new QTableWidgetItem(ad));
        ui->tableWidgetFactors->setItem(ui->tableWidgetFactors->rowCount() - 1, 1, new QTableWidgetItem(price));
        ui->tableWidgetFactors->setItem(ui->tableWidgetFactors->rowCount() - 1, 2, new QTableWidgetItem(priceCompetitor));
        ui->tableWidgetFactors->setItem(ui->tableWidgetFactors->rowCount() - 1, 3, new QTableWidgetItem(index));
    } else {
        QMessageBox::warning(this, "Помилка", "Невірний формат вхідних даних!");
    }
}

void MainWindow::on_pushButtonDelete_clicked() {
    if (selectedRow != -1) {
        ui->tableWidgetFactors->removeRow(selectedRow);
    } else {
        QMessageBox::warning(this, "Помилка", "Ви не обрали рядок!");
    }
}

void MainWindow::on_tableWidgetFactors_clicked(const QModelIndex &index) {
    selectedRow = index.row();
}

void MainWindow::on_pushButtonCalculate_clicked() {
    std::string result;
    for (int row = 0; row < ui->tableWidgetFactors->rowCount(); row++){
        double ad = ui->tableWidgetFactors->model()->index(row, 0).data().toDouble();
        double price = ui->tableWidgetFactors->model()->index(row, 1).data().toDouble() - ui->tableWidgetFactors->model()->index(row, 2).data().toDouble();
        double index = ui->tableWidgetFactors->model()->index(row, 3).data().toDouble();
        result += std::to_string(row + 1) + " - " + std::to_string(tetta[0] + tetta[1] * ad + tetta[2] * price + tetta[3] * index) + " млн. грн\n";
    }
    QMessageBox::information(this, "Результат", QString::fromStdString(result));
}

void MainWindow::on_pushButtonSelectFile_clicked() {
    QFileDialog directory;
    ui->lineEditFileDirection->setText(directory.getOpenFileName(this, "Оберіть файл", QDir::homePath(), tr("CSV (*.csv)")));
    direction = ui->lineEditFileDirection->text();
}


void MainWindow::on_pushButtonImport_clicked() {
    QString data;
    QFile importedCSV(direction);
    QStringList rowOfData;
    QStringList rowData;
    data.clear();
    rowOfData.clear();
    rowData.clear();
    if (importedCSV.open(QFile::ReadOnly)) {
        data = importedCSV.readAll();
        QString k = "";
        for (int i = 0; i < data.size()-1; ++i) {if (data[i] != '\"' && data[i] != ' ') k+= data[i];}
        if (data[data.size()-1] != '\n') k+=data[data.size()-1];
        data = k;
        rowOfData = data.split("\n");
        importedCSV.close();
    }
    //qInfo("%s", data.toStdString().c_str());
    for (int x = 0; x < rowOfData.size(); x++) {
        rowData = rowOfData.at(x).split(",");
        ui->tableWidgetFactors->insertRow(ui->tableWidgetFactors->rowCount());
        for (int y = 0; y < rowData.size(); y++) {
            if (y == rowData.size()-1) rowData[y].resize(rowData[y].size()-1);
            ui->tableWidgetFactors->setItem(x, y, new QTableWidgetItem(rowData[y]));
        }
    }
}

