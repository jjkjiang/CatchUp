#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextStream>
#include "TreeBuilder.h"
#include "TreeFilterer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_actionSave_triggered();
    void on_actionOpen_File_triggered();
    void on_dateEdit_editingFinished();
    void on_dateEdit_2_editingFinished();

    void on_actionChange_Indent_triggered();

    void on_actionReport_Bugs_triggered();

    void on_actionDisplay_Dates_triggered();

    void on_actionDisplay_Dates_toggled(bool arg1);

    void on_actionRestore_Defaults_triggered();

    void on_actionUsage_triggered();

private:
    Date qDateToDate(QDate qdate);

    void createMenus();
    void open();
    void filter();
    void updateTextBrowser();

    void setDateToCurrent();
    Ui::MainWindow *ui;
    TreeBuilder treeBuilder;
    TreeFilterer treeFilterer;
};

#endif // MAINWINDOW_H
