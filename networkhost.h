#ifndef NETWORKHOST_H
#define NETWORKHOST_H

#include <QDialog>
#include "QtNetwork"

namespace Ui {
class NetworkHost;
}

class NetworkHost : public QDialog
{
    Q_OBJECT

public:
    explicit NetworkHost(QWidget *parent = nullptr);
    ~NetworkHost();

private:
    Ui::NetworkHost *ui;
    void getRequest(QString *url);

signals:
    void sendData(QString);

private slots:
    void finishedSlot(QNetworkReply *reply);
    void on_pushButton_clicked();
    void on_buttonBox_accepted();
};

#endif // NETWORKHOST_H
