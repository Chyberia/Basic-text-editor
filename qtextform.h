#ifndef QTEXTFORM_H
#define QTEXTFORM_H

#include <QWidget>
#include <QPlainTextEdit>
#include <QObject>
#include <QStack>
#include <QList>

namespace Ui {
class qtextform;
}
extern int currentTab;

class qtextform : public QWidget
{
    Q_OBJECT



public:
    explicit qtextform(QWidget *parent = nullptr);
    ~qtextform();
public slots:
    static void loadFromFile(QPlainTextEdit* child, QString fileName);

    static QString saveToFile(QPlainTextEdit* child, QString fileName);

    static void undoChange(QPlainTextEdit* child);

    static void createStack();

    static void undo(QPlainTextEdit* child);

private slots:
    void on_plainTextEdit_textChanged();

private:
    Ui::qtextform *ui;
};

#endif // QTEXTFORM_H
