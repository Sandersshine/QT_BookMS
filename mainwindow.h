// mainwindow.h

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <QString>
#include "Book.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initBooks();

private slots:
    void on_pushBtUpdate_clicked();

    void on_pushBtDelete_clicked();

    void on_pushBtAdd_clicked();

    void on_pushBtSearch_clicked();

private:
    Ui::MainWindow *ui;
    std::vector<Book> books; // 添加这一行来声明书籍列表
};

#endif // MAINWINDOW_H
