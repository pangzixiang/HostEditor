#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<qfiledialog.h>
#include<qstring.h>
#include<QMessageBox>
#include<QCloseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);
    setFixedSize(this->width(), this->height());
}

MainWindow::~MainWindow()
{
    delete ui;
}

//open
void MainWindow::on_pushButton_3_clicked()
{
    QString basePath = "C:\\Windows\\System32\\drivers\\etc\\";
    QString path = QFileDialog::getOpenFileName(this, tr("打开文件"),basePath);
    ui->lineEdit->setText(path);
    openFile(path);
}

void MainWindow::openFile(QString path)
{
    if (!path.isEmpty()) {
        QFile *file = new QFile;
        file->setFileName(path);
        bool isOpen = file->open(QIODevice::ReadOnly);
        if (isOpen) {
            QTextStream in(file);
            QString *content = new QString;
            *content = in.readAll();
            ui->textBrowser->setText(*content);
            ui->textEdit->setText(*content);
            file->close();
            delete file;
            delete content;
        } else {
            QMessageBox::warning(this,"错误","打开文件:" + file->errorString());
            return;
        }
    }
}

//save
void MainWindow::on_pushButton_2_clicked()
{
    QString *path = new QString;
    *path = ui->lineEdit->text();
    saveFile(*path);
    delete path;
}

void MainWindow::saveFile(QString path)
{
    if(!path.isEmpty()) {
        QFile *file = new QFile;
        file->setFileName(path);
        bool isOpen = file->open(QFile::WriteOnly|QFile::Text);
        if (isOpen){
            QTextStream out(file);
            out << ui->textEdit->toPlainText();
            file->close();
            delete file;
        } else {
            QMessageBox::warning(this,"错误信息","打开文件:" + file->errorString());
            return;
        }
        openFile(path);
        QMessageBox::information(this,"info","保存成功!");
    } else {
        QMessageBox::warning(this,"error","请先选择文件!");
    }
}

//reset
void MainWindow::on_pushButton_clicked()
{
    QString *content = new QString;
    *content = ui->textBrowser->toPlainText();
    ui->textEdit->setText(*content);
    delete content;
}

//open(menu)
void MainWindow::on_actionOpen_triggered()
{
    on_pushButton_3_clicked();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    int *button = new int;
    *button = QMessageBox::question(this, tr("Exit"),
                                   QString(tr("Are you sure?")),
                                   QMessageBox::Yes | QMessageBox::No);
    if (*button == QMessageBox::No) {
          event->ignore();
    }
    else if (*button == QMessageBox::Yes) {
          event->accept();
    }
    delete button;
}

void MainWindow::on_actionHelp_triggered()
{
    About *about = new About;
    about->show();
}
