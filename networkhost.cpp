#include "networkhost.h"
#include "ui_networkhost.h"
#include "QMessageBox"
#include "mainwindow.h"

NetworkHost::NetworkHost(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NetworkHost)
{
    ui->setupUi(this);
}

NetworkHost::~NetworkHost()
{
    delete ui;
}

void NetworkHost::finishedSlot(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray bytes = reply->readAll();
        ui->textBrowser->setText(bytes);
    } else {
        QMessageBox::warning(this,"error",reply->errorString());
    }
    reply->deleteLater();
}

void NetworkHost::on_pushButton_clicked()
{
    QString *url = new QString;
    *url = ui->comboBox->currentText();
    getRequest(url);
}

void NetworkHost::getRequest(QString *url)
{
    QNetworkAccessManager *accessManager = new QNetworkAccessManager(this);
    connect(accessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(finishedSlot(QNetworkReply*)));
    QNetworkRequest request;
    request.setUrl(QUrl(*url));
    accessManager->get(request);
    delete url;
}

void NetworkHost::on_buttonBox_accepted()
{
    emit sendData(ui->textBrowser->toPlainText());
    this->close();
}
