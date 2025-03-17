#include "notepad.h"
#include "ui_notepad.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QFontDialog>


#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printer)
#if QT_CONFIG(printdialog)
#include <QPrintDialog>
#endif // QT_CONFIG(printdialog)
#include <QPrinter>
#endif // QT_CONFIG(printer)
#endif // QT_PRINTSUPPORT_LIB

Notepad::Notepad(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Notepad)
{
    ui->setupUi(this);
}

Notepad::~Notepad()
{
    delete ui;
}




void Notepad::on_new_file_triggered()
{
    currentFile.clear(); // 清空缓冲区内容
    ui->textEdit->setText(QString());  // 清空输入框内容
}

void Notepad::on_open_file_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "打开文件");
    QFile file(fileName);
    currentFile = fileName;
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "警告", "无法打开此文件: " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

void Notepad::on_save_file_triggered()
{
    QString fileName;
    // If we don't have a filename from before, get one.
    if (currentFile.isEmpty()) {
        fileName = QFileDialog::getSaveFileName(this, "Save");
        if (fileName.isEmpty())
            return;
        currentFile = fileName;
    } else {
        fileName = currentFile;
    }
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "警告", "无法保存此文件: " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}

void Notepad::on_save_as_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save as");
    if (fileName.isEmpty())
        return;
    QFile file(fileName);

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this,  "警告", "无法保存此文件: "  + file.errorString());
        return;
    }
    currentFile = fileName;
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}


void Notepad::on_bolder_triggered(bool bold)
{
    bold ? ui->textEdit->setFontWeight(QFont::Bold) :
           ui->textEdit->setFontWeight(QFont::Normal);
}

void Notepad::on_Italic_triggered(bool italic)
{
    ui->textEdit->setFontItalic(italic);

}

void Notepad::on_underline_triggered(bool underline)
{
    ui->textEdit->setFontUnderline(underline);
}

void Notepad::on_font_triggered()
{
    bool fontSelected;
    QFont font = QFontDialog::getFont(&fontSelected, this);
    if (fontSelected)
        ui->textEdit->setFont(font);
}



void Notepad::on_copy_triggered()
{
    ui->textEdit->copy();
}

void Notepad::on_cut_triggered()
{
    ui->textEdit->cut();
}


void Notepad::on_paste_triggered()
{
    ui->textEdit->paste();
}

void Notepad::on_undo_triggered()
{
    ui->textEdit->undo();
}

void Notepad::on_redo_triggered()
{
    ui->textEdit->redo();
}



void Notepad::on_print_triggered()
{
#if defined(QT_PRINTSUPPORT_LIB) && QT_CONFIG(printer)
    QPrinter printDev;
#if QT_CONFIG(printdialog)
    QPrintDialog dialog(&printDev, this);
    if (dialog.exec() == QDialog::Rejected)
        return;
#endif // QT_CONFIG(printdialog)
    ui->textEdit->print(&printDev);
#endif // QT_CONFIG(printer)
}

void Notepad::on_about_triggered()
{
    QMessageBox::about(this, tr("关于 Notepad"),
                       tr("这是一个Qt Widget实现的记事本。"));
}

void Notepad::on_exit_triggered()
{
    QCoreApplication::exit();
}
