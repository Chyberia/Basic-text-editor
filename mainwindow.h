#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

QT_BEGIN_NAMESPACE


namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

extern int currTabIndex;
extern QString currFilePath;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private slots:
    void on_tabWidget_tabCloseRequested(int index);

    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionExit_triggered();

    void on_pTabCornerWidget_triggered();

    void on_tabWidget_tabBarClicked(int index);

    void on_actionSave_triggered();

    void on_saveShortcut_activated();

    void on_newShortcut_activated();

    void on_openFileShortcut_activated();

    void on_actionSave_as_triggered();

    void on_undoChangeShortcut_activated();

    static void addCharToStack();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
