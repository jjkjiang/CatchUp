#include "../include/mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QDesktopServices>
#include <QMessageBox>
#include <QInputDialog>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setDateToCurrent();
    treeFilterer = TreeFilterer(NULL, qDateToDate(ui->dateEdit->date()),
                                        qDateToDate(ui->dateEdit_2->date()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

Date MainWindow::qDateToDate(QDate qdate) {
    QString qstr = qdate.toString(Qt::ISODate);
    std::string date = qstr.toStdString();
    std::replace(date.begin(), date.end(), '-', '/');
    return Date(date);
}

void MainWindow::setDateToCurrent() {
    QDate date = QDate::currentDate();
    ui->dateEdit_2->setDate(date);
}

void MainWindow::on_pushButton_clicked()
{
    open();
}
void MainWindow::on_actionSave_triggered()
{
    QString filename = QFileDialog::getSaveFileName(
    this,
    tr("Save File"),
    "C://",
    "Text File (*.txt)"
    );

    //call class code here, write
    if (filename == NULL)
        return;

    std::ofstream of;
    of.open(filename.toStdString().c_str());

    of << treeFilterer.getResult();

    of.close();

    QMessageBox::information(this,tr("Status"),"Saved!");
}

void MainWindow::on_actionOpen_File_triggered()
{
    open();
}

void MainWindow::open() {
    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "C://",
                "Text File (*.txt)"
                );

    if (filename == NULL)
        return;
    ui->label->setText(filename);
    treeBuilder.build(filename.toStdString());
    treeFilterer.setRoot(treeBuilder.getRoot());
    filter();

    updateTextBrowser();

    //QMessageBox::information(this,tr("File Name"),filename);
}

void MainWindow::on_dateEdit_editingFinished()
{
    treeFilterer.setStartDate(qDateToDate(ui->dateEdit->date()));

    filter();
}

void MainWindow::on_dateEdit_2_editingFinished()
{
    treeFilterer.setEndDate(qDateToDate(ui->dateEdit_2->date()));

    filter();
}

void MainWindow::filter() {
    //filters based on tree
    treeFilterer.filterDP();

    updateTextBrowser();
}

void MainWindow::updateTextBrowser() {

    ui->textBrowser->setText(QString::fromStdString(treeFilterer.getResult()));
}


void MainWindow::on_actionReport_Bugs_triggered()
{
    QDesktopServices::openUrl(QUrl("https://github.com/jjkjiang/CatchUp/issues"));
}

void MainWindow::on_actionDisplay_Dates_triggered()
{}

void MainWindow::on_actionDisplay_Dates_toggled(bool arg1)
{
    treeFilterer.setShowDate(arg1);
    filter();
}

void MainWindow::on_actionChange_Indent_triggered()
{

    QString text = QInputDialog::getText(this, "Input the indent", "Indent:", QLineEdit::Normal);
    treeFilterer.setIndentStr(text.toStdString());
    filter();
}

void MainWindow::on_actionRestore_Defaults_triggered()
{
    treeFilterer.setShowDate(true);
    QDate date = QDate::currentDate();
    ui->dateEdit_2->setDate(date);
    treeFilterer.setEndDate(qDateToDate(date));
    treeFilterer.setIndentStr("  ");
    filter();
}

void MainWindow::on_actionUsage_triggered()
{
    QMessageBox::information(this,tr("Usage"),"Specify the location of the .txt file that has been parsed, and then choose the date gap you want.");
}
