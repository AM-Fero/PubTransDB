#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <qDebug>
#include <QSqlRecord>
#include <QPixmap>
#include <QPushButton>
#include <QLineEdit>
#include <QSqlDriver>
#include <QTimer>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <cstdint>
#include <QLine>
#include "adddataadmin.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    bool ConnectToDB();
    void tryAgainToConnect();
    void FillTable(QTableWidget* tableToFill, QString query);
    void FillTableButton(QTableWidget* tableToFill, QString query, QString header, QString text, int propertyColumn, QString propertyName);
    void GuestShowStopInfo();
    void GuestShowRouteInfo();
    void drawStops(double, int, int);
    void stopsParamChange();
    void createNav();
    void pwdcheck(QString);
    void loadAdminInterface();
    void loadTableAdmin(int);
    void createEnterButtons();
    void createExitButton();
    void GuestEnter();
    void AdminEnter();
    void ExitEnter(bool createEnter=true);
    void resetInnerData();
    void addDataToDb();

    QList<QMap<int, QString>> formAdditionalData(int index);
    QTableWidgetItem* GetNewItem(QString name, bool isEditable, bool isHeader = false);
    QPushButton *GetNewButton(QString name, bool isOn, QString propertyName, QString propertyValue);


private:
    Ui::MainWindow *ui;
    QSqlDatabase *db = nullptr;
    QList<QPushButton*> guestNavigation;
    QList<QPushButton*> guestStops;
    QList<QLabel*> guestStopsLabels;
    QList<int> stopsDrawingData;
    QPushButton* pbEnterGuest = nullptr;
    QPushButton* pbEnterAdmin = nullptr;
    QPushButton* pbExitButton = nullptr;
    QTableWidget *table_info = nullptr;
    QComboBox *cb_MainAdmin = nullptr;
    double guestNavParams[3] = {1,0,0};
    QSqlQuery qw;
};

#endif // MAINWINDOW_H
