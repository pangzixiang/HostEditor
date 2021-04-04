#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <about.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_actionOpen_triggered();

    void on_actionHelp_triggered();

private:
    Ui::MainWindow *ui;
    void openFile(QString path);
    void saveFile(QString path);
    void closeEvent(QCloseEvent *event);
};
#endif // MAINWINDOW_H
