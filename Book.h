#ifndef BOOK_H
#define BOOK_H

// Book类定义（可放在单独的book.h中或直接在mainwindow.cpp内定义）
struct Book {
    QString title;      // 图书名称
    QString author;     // 作者
    QString publisher;  // 出版社
};

#endif // BOOK_H
