#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QInputDialog>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableWidget->setColumnWidth(0, 250);

    initBooks();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initBooks()
{
    books = {
        {"《三体》", "刘慈欣", "重庆出版社"},
        {"《百年孤独》", "加西亚·马尔克斯", "南海出版公司"},
        {"《围城》", "钱钟书", "人民文学出版社"},
        {"《哈利·波特与魔法石》", "J.K.罗琳", "布卢姆斯伯里出版社"},
        {"《解忧杂货店》", "东野圭吾", "现代出版社"},
        {"《乌合之众》", "古斯塔夫·勒庞", "中央编译出版社"},
        {"《追风筝的人》", "卡勒德·胡赛尼", "上海人民出版社"},
        {"《小王子》", "安托万·德·圣埃克苏佩里", "人民文学出版社"},
        {"《梦里花落知多少》", "三毛", "北京十月文艺出版社"},
        {"《沉默的大多数》", "王小波", "北方文艺出版社"}
    };

    // 设置行数，等于books的大小
    ui->tableWidget->setRowCount(books.size());
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // 填充数据
    for(int i = 0; i < books.size(); ++i)
    {
        const Book &book = books[i];

        // 创建表格项并设置文本
        QTableWidgetItem *itemTitle = new QTableWidgetItem(book.title);
        QTableWidgetItem *itemAuthor = new QTableWidgetItem(book.author);
        QTableWidgetItem *itemPublisher = new QTableWidgetItem(book.publisher);

        // 将项插入到对应的行和列
        ui->tableWidget->setItem(i, 0, itemTitle);      // 图书名称
        ui->tableWidget->setItem(i, 1, itemAuthor);     // 作者
        ui->tableWidget->setItem(i, 2, itemPublisher);   // 出版社
    }
}


void MainWindow::on_pushBtUpdate_clicked()
{
    int selectedRow = ui->tableWidget->currentRow();
    if (selectedRow < 0)
    {
        QMessageBox::information(this, "提示", "请先选择一行进行更新");
        return;
    }

    // 获取当前行的图书名称、作者、出版社
    QString bookName = ui->tableWidget->item(selectedRow, 0)->text();
    QString author = ui->tableWidget->item(selectedRow, 1)->text();
    QString press = ui->tableWidget->item(selectedRow, 2)->text();

    QString newName = ui->lineEditBookName->text();
    if (newName == "")
    {
        newName = bookName;
    }
    QString newAuthor = ui->lineEditAuthor->text();
    if (newAuthor == "")
    {
        newAuthor = author;
    }
    QString newPress = ui->lineEditPress->text();
    if (newPress == "")
    {
        newPress = press;
    }

    // 如果未输入任何信息
    if (newName == bookName && newAuthor == author && newPress == press)
    {
        QMessageBox noChangeDialog;
        noChangeDialog.setText(tr("无更改\n\n未检测到任何更改，请修改至少一个字段。"));
        noChangeDialog.setWindowTitle(tr("无更改"));
        noChangeDialog.setStandardButtons(QMessageBox::Ok);
        noChangeDialog.setDefaultButton(QMessageBox::Ok);

        noChangeDialog.exec(); // 显示对话框

        return;
    }

    QString dialogContent = tr("确认更新图书信息：\n\n") +
                            tr("旧信息：\n") +
                            tr("名称：%1\n").arg(bookName) +
                            tr("作者：%1\n").arg(author) +
                            tr("出版社：%1\n\n").arg(press) +
                            tr("新信息：\n") +
                            tr("名称：%1\n").arg(newName) +
                            tr("作者：%1\n").arg(newAuthor) +
                            tr("出版社：%1").arg(newPress);

    QMessageBox confirmDialog;
    confirmDialog.setText(dialogContent);
    confirmDialog.setWindowTitle(tr("确认更新"));
    confirmDialog.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    confirmDialog.setDefaultButton(QMessageBox::Ok);

    if (confirmDialog.exec() == QMessageBox::Ok) {
        // 用户点击了确认，执行更新操作
        // 更新表格项
        ui->tableWidget->item(selectedRow, 0)->setText(newName);
        ui->tableWidget->item(selectedRow, 1)->setText(newAuthor);
        ui->tableWidget->item(selectedRow, 2)->setText(newPress);
    }
}


void MainWindow::on_pushBtDelete_clicked()
{
    int selectedRow = ui->tableWidget->currentRow();
    if (selectedRow < 0)
    {
        QMessageBox noSelectionDialog;
        noSelectionDialog.setText(tr("删除失败\n\n请选择要删除的图书。"));
        noSelectionDialog.setWindowTitle(tr("删除失败"));
        noSelectionDialog.setIcon(QMessageBox::Critical); // 设置图标为警告或错误类型
        noSelectionDialog.setStandardButtons(QMessageBox::Ok);
        noSelectionDialog.setDefaultButton(QMessageBox::Ok);
        noSelectionDialog.exec(); // 显示对话框

        return;
    }

    // 获取当前行的图书名称、作者、出版社
    QString name = ui->tableWidget->item(selectedRow, 0)->text();
    QString author = ui->tableWidget->item(selectedRow, 1)->text();
    QString press = ui->tableWidget->item(selectedRow, 2)->text();

    // 构建删除确认对话框的内容
    QString dialogContent = tr("是否要删除这本书？\n\n")
                            + tr("书名: %1\n").arg(name)
                            + tr("作者: %1\n").arg(author)
                            + tr("出版社: %1").arg(press);

    // 使用QMessageBox创建对话框
    QMessageBox deleteConfirmation;
    deleteConfirmation.setText(dialogContent);
    deleteConfirmation.setWindowTitle(tr("删除确认"));
    deleteConfirmation.setIcon(QMessageBox::Question); // 设置图标为问号，表示询问
    deleteConfirmation.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    deleteConfirmation.setDefaultButton(QMessageBox::Yes); // 设置默认按钮为"是"

    // 判断用户的选择
    if (deleteConfirmation.exec() == QMessageBox::Yes)
    {
        // 用户选择了"是"，执行删除操作
        ui->tableWidget->removeRow(selectedRow);
    }
}


void MainWindow::on_pushBtAdd_clicked()
{
    // 获取当前行的图书名称、作者、出版社
    QString name = ui->lineEditBookName->text();
    QString author = ui->lineEditAuthor->text();
    QString press = ui->lineEditPress->text();

    // 检查是否有字段为空
    if (name.isEmpty() || author.isEmpty() || press.isEmpty())
    {
        QMessageBox emptyFieldDialog;
        emptyFieldDialog.setText(tr("输入错误\n\n所有字段均为必填项。"));
        emptyFieldDialog.setWindowTitle(tr("输入错误"));
        emptyFieldDialog.setIcon(QMessageBox::Warning); // 设置警告图标
        emptyFieldDialog.setStandardButtons(QMessageBox::Ok);
        emptyFieldDialog.exec(); // 显示对话框并等待用户关闭
        return;
    }

    // 构建添加确认的对话框内容
    QString addDialogContent =
        tr("是否要添加这本书\n\n") +
        tr("书名: %1\n作者: %2\n出版社: %3").arg(name).arg(author).arg(press);

    QMessageBox::StandardButton result =
        QMessageBox::question(
            this,
            tr("添加确认"),
            addDialogContent,
            QMessageBox::Yes | QMessageBox::No,
            QMessageBox::Yes
        );

    if (result == QMessageBox::No)
    {
        return;
    }

    ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);

    // 创建表格项并设置文本
    QTableWidgetItem *itemTitle = new QTableWidgetItem(name);
    QTableWidgetItem *itemAuthor = new QTableWidgetItem(author);
    QTableWidgetItem *itemPress = new QTableWidgetItem(press);

    // 将项插入到对应的行和列
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, itemTitle);      // 图书名称
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, itemAuthor);     // 作者
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 2, itemPress);   // 出版社

    // 显示添加成功的对话框
    QMessageBox successDialog;
    successDialog.setText(tr("添加成功"));
    successDialog.setWindowTitle(tr("成功"));
    successDialog.setIcon(QMessageBox::Information); // 设置信息图标
    successDialog.setStandardButtons(QMessageBox::Ok);
    successDialog.exec(); // 显示对话框并等待用户关闭
}


void MainWindow::on_pushBtSearch_clicked()
{
    QString searchText = ui->lineEditSearchText->text();
    // 遍历表格的所有行
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        bool shouldShow = false; // 是否应该显示当前行

        // 假设你的tableWidget有三列，分别是书名、作者、出版社
        for (int col = 0; col < 3; ++col)
        {
            QTableWidgetItem *item = ui->tableWidget->item(row, col);
            if (item && item->text().contains(searchText, Qt::CaseInsensitive))
            {
                // 如果任何一列包含关键字，则应该显示此行
                shouldShow = true;
                break;
            }
        }

        // 根据是否匹配来显示或隐藏行
        ui->tableWidget->setRowHidden(row, !shouldShow);
    }
}

