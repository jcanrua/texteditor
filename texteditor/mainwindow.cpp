#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFile File(QString fileName);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionOpenFile_triggered()
{
    QFile fileName = QFileDialog::getOpenFileName(this, tr("Abrir archivo"), "~/", tr("*.txt (*.txt)"));
    fileName.open(QIODevice::ReadWrite);
    QTextStream stream(&fileName);
    QString openText = stream.readAll();
    ui->textEdit->setText(openText);
    fileName.close();
}


void MainWindow::on_actionExitFile_triggered()
{
    //Esto cierra todo y me gustaria que fuese el archivo
    QApplication::quit();
}

//NO FUNCIONA
void MainWindow::on_actionSaveAsFile_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Guardar archivo"), "", "*.txt (*.*)");  //"Text Files (*.txt);;All Files (*)"

    if (fileName.isEmpty())
        return;
    else {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(this, tr("Error al abrir archivo"),
                file.errorString());
            return;
        }
        QDataStream out(&file);
        out.setVersion(QDataStream::Qt_4_5);
        out << contacts;
    }
}



void MainWindow::on_actionSaveFile_triggered()
{

}

