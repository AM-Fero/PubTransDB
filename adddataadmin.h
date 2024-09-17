#ifndef ADDDATAADMIN_H
#define ADDDATAADMIN_H

#include <QDialog>
#include <QLineEdit>
#include <QMessageBox>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QDebug>
#include <QComboBox>
#include <QCheckBox>
#include <QTimeEdit>

namespace Ui {
class addDataAdmin;
}

class addDataAdmin : public QDialog
{
    Q_OBJECT

public:
    explicit addDataAdmin(QWidget *parent = nullptr);
    ~addDataAdmin();
    void loadInterface(int index);
    QStringList dataToDb;
    void setAdditionalData(QList<QMap<int, QString>> data);

private slots:
    void on_pushButton_Ok_clicked();
    void on_pushButton_cancel_clicked();
    void addDriver();
    void addDepot();
    void addBusType();
    void addStop();
    void addBus();
    void addRoute();
    void createLineEdit(QString objectName, int x, int y, int w, int h, QString placeholderText);
    void createDoubleSpinBox(QString objectName, int x, int y, int w, int h, double min, double max);
    void createLabel(QString objectName, int x, int y, int w, int h, QString text);
    void createComboBox(QString objectName, int x, int y, int w, int h, QMap<int, QString> data);
    void createCheckBox(QString objectName, int x, int y, int w, int h, QString text);
    void createSpinBox(QString objectName, int x, int y, int w, int h, int min, int max);
    void createTimeEdit(QString objectName, int x, int y, int w, int h);
    void setWidgetParams(QWidget* widgetToSet, QString objectName, int x, int y, int w, int h);

private:
    Ui::addDataAdmin *ui;

    int currentIndex;

    QList<QMap<int, QString>> additionalData = {};
};

#endif // ADDDATAADMIN_H
