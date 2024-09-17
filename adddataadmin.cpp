#include "adddataadmin.h"
#include "ui_adddataadmin.h"

addDataAdmin::addDataAdmin(QWidget *parent) : // Конструктор
    QDialog(parent),
    ui(new Ui::addDataAdmin)
{
    ui->setupUi(this);
}

addDataAdmin::~addDataAdmin() // Деструктор
{
    delete ui;
}

void addDataAdmin::loadInterface(int index) // Загрузка интерфейса
{
    currentIndex = index;
    switch (currentIndex) {
    case 0:{addBus();break;}
    case 1:{addDriver();break;}
    case 2:{addDepot();break;}
    case 3:{addRoute();break;}
    case 4:{addStop();break;}
    case 5:{addBusType();break;}}
}

void addDataAdmin::addDriver() // Добавить водителя
{
    setWindowTitle("Добавить водителя");
    createLineEdit("name_driver",10,10,300,50,"Введите ФИО");
}

void addDataAdmin::addDepot() // Добавить депо
{
    setWindowTitle("Добавить депо");
    createLineEdit("name_depot",10,10,300,50,"Введите наименование депо");
}

void addDataAdmin::addBusType() // Добавить тип автобуса
{
    setWindowTitle("Добавить тип автобуса");
    createLineEdit("name_Bus_Type",10,10,300,50,"Введите название типа автобуса");
}

void addDataAdmin::addStop() // Добавить остановку
{
    setWindowTitle("Добавить остановку");
    createLineEdit("name_Stop",10,10,300,50,"Введите название остановки");

    createDoubleSpinBox("lat",10,70,100,50,-90,90);
    createDoubleSpinBox("lon",10,130,100,50,-90,90);

    createLabel("lat",120,70,100,50,"Укажите широту");
    createLabel("lon",120,130,100,50,"Укажите долготу");
}

void addDataAdmin::addBus() // Добавить автобус
{
    setWindowTitle("Добавить автобус");
    createComboBox("driver",10,10,300,50,additionalData[0]);
    createLabel("driver",10,70,300,50,"Водитель");

    createComboBox("route",320,10,300,50,additionalData[1]);
    createLabel("route",320,70,300,50,"Маршрут");

    createComboBox("depot",10,110,300,50,additionalData[2]);
    createLabel("depot",10,170,300,50,"Депо");

    createComboBox("type",320,110,300,50,additionalData[3]);
    createLabel("type",320,170,300,50,"Тип");

    createLineEdit("regnum",700,10,300,50,"Введите регистрационный номер");

    createCheckBox("online",700,70,200,20,"На линии");

    createSpinBox("year",700,100,50,50,1960,2024);
    createLabel("year",760,100,200,50,"Год производства");

    createSpinBox("pos",700,160,50,50,1,100);
    createLabel("pos",760,160,200,50,"Позиция");
}

void addDataAdmin::addRoute() // Добавить маршрут
{
    setWindowTitle("Добавить маршрут");
    createLineEdit("nameRoute",10,10,300,50,"Введите название маршрута");

    createTimeEdit("first",320,10,100,50);
    createLabel("first",320,70,100,50,"Время отправления первого");

    createTimeEdit("last",320,100,100,50);
    createLabel("last",320,180,100,50,"Время отправления последнего");

    createTimeEdit("interval",500,100,100,50);
    createLabel("interval",500,180,100,50,"Интервал");

    createTimeEdit("overall",500,10,100,50);
    createLabel("overall",500,70,100,50,"Общее время");
}

void addDataAdmin::setAdditionalData(QList<QMap<int, QString>> data) // Считывание доп информации
{
    additionalData = data;
}

void addDataAdmin::createLineEdit(QString objectName, int x, int y, int w, int h, QString placeholderText) // Создать LineEdit
{
    QLineEdit* temp = new QLineEdit(this);
    setWidgetParams(temp,objectName,x,y,w,h);
    temp->setPlaceholderText(placeholderText);
}

void addDataAdmin::createDoubleSpinBox(QString objectName, int x, int y, int w, int h, double min, double max) // создать DbouleSPinxBox
{
    QDoubleSpinBox* temp = new QDoubleSpinBox(this);
    setWidgetParams(temp,objectName,x,y,w,h);
    temp->setMinimum(min);
    temp->setMaximum(max);
    temp->setDecimals(5);
    temp->setSingleStep(0.001);
}

void addDataAdmin::createLabel(QString objectName, int x, int y, int w, int h, QString text) // Создать label
{
    QLabel* temp = new QLabel(this);
    setWidgetParams(temp,objectName,x,y,w,h);
    temp->setText(text);
}

void addDataAdmin::createComboBox(QString objectName, int x, int y, int w, int h, QMap<int, QString> data) // Создать comboBox
{
    QComboBox* temp = new QComboBox(this);
    setWidgetParams(temp,objectName,x,y,w,h);
    for (int i = 0; i < data.count(); i++)
        temp->addItem(data[data.keys()[i]]);
}

void addDataAdmin::createCheckBox(QString objectName, int x, int y, int w, int h, QString text) // Создать checkbox
{
    QCheckBox* temp = new QCheckBox(this);
    setWidgetParams(temp,objectName,x,y,w,h);
    temp->setText(text);
}

void addDataAdmin::createSpinBox(QString objectName, int x, int y, int w, int h, int min, int max) // Создать Spinbox
{
    QSpinBox* temp = new QSpinBox(this);
    setWidgetParams(temp,objectName,x,y,w,h);
    temp->setMinimum(min);
    temp->setMaximum(max);
}

void addDataAdmin::createTimeEdit(QString objectName, int x, int y, int w, int h) // Создать timeEDit
{
    QTimeEdit* temp = new QTimeEdit(this);
    setWidgetParams(temp, objectName,x,y,w,h);
    temp->setDisplayFormat("hh:mm:ss");
}

void addDataAdmin::setWidgetParams(QWidget *widgetToSet, QString objectName, int x, int y, int w, int h) // Задать базовые параметры для объекта
{
    widgetToSet->setObjectName(objectName);
    widgetToSet->setGeometry(x,y,w,h);
    widgetToSet->show();
}

void addDataAdmin::on_pushButton_Ok_clicked() // Кнокп ОК
{
    switch (currentIndex) {
    case 0:{ // автобус
        QComboBox* driver = this->findChild<QComboBox*>("driver");
        if (driver->currentText().length()==0)
        {
            QMessageBox::warning(this,"Ошибка","Не выбран водитель");
            return;
        }
        QComboBox* route = this->findChild<QComboBox*>("route");
        if (route->currentText().length()==0)
        {
            QMessageBox::warning(this,"Ошибка","Не выбран маршрут");
            return;
        }
        QComboBox* depot = this->findChild<QComboBox*>("depot");
        if (depot->currentText().length()==0)
        {
            QMessageBox::warning(this,"Ошибка","Не выбрано депо");
            return;
        }
        QComboBox* type = this->findChild<QComboBox*>("type");
        if (type->currentText().length()==0)
        {
            QMessageBox::warning(this,"Ошибка","Не выбран тип");
            return;
        }
        dataToDb.append({QString::number(additionalData[0].key(driver->currentText())), QString::number(additionalData[1].key(route->currentText())),
                        QString::number(additionalData[2].key(depot->currentText())), QString::number(this->findChild<QCheckBox*>("online")->isChecked()),
                        QString::number(additionalData[3].key(type->currentText())), QString::number(this->findChild<QSpinBox*>("year")->value()),
                        this->findChild<QLineEdit*>("regnum")->text(), QString::number(this->findChild<QSpinBox*>("pos")->value())});
        close();
        break;
    }
    case 1:{ // Водитель
        QLineEdit* line = this->findChild<QLineEdit*>("name_driver");
        if(line->text().trimmed().length() == 0)
        {
            QMessageBox::warning(this,"Ошибка","Заполните имя");
            return;
        }
        dataToDb.append(line->text());
        close();
        break;
    }
    case 2:{ // Депо
        QLineEdit* line = this->findChild<QLineEdit*>("name_depot");
        if(line->text().trimmed().length() == 0)
        {
            QMessageBox::warning(this,"Ошибка","Заполните наименование");
            return;
        }
        dataToDb.append(line->text());
        close();
        break;
    }
    case 3:{ // Маршрут
        QLineEdit* name = this->findChild<QLineEdit*>("nameRoute");
        if(name->text().trimmed().length() == 0)
        {
            QMessageBox::warning(this,"Ошибка","Заполните название маршрута");
            return;
        }
        dataToDb.append({name->text(),this->findChild<QTimeEdit*>("overall")->text(), this->findChild<QTimeEdit*>("first")->text(),
                         this->findChild<QTimeEdit*>("last")->text(), this->findChild<QTimeEdit*>("interval")->text()});
        close();
        break;
    }
    case 4:{ // Остановка
        QLineEdit* line = this->findChild<QLineEdit*>("name_Stop");
        QDoubleSpinBox* lat = this->findChild<QDoubleSpinBox*>("lat");
        QDoubleSpinBox* lon = this->findChild<QDoubleSpinBox*>("lon");
        if(line->text().trimmed().length() == 0)
        {
            QMessageBox::warning(this,"Ошибка","Заполните название станции");
            return;
        }
        dataToDb.append({line->text(), QString::number(lat->value()), QString::number(lon->value())});
        close();
        break;
    }
    case 5:{ // Тип авт
        QLineEdit* line = this->findChild<QLineEdit*>("name_Bus_Type");
        if(line->text().trimmed().length() == 0)
        {
            QMessageBox::warning(this,"Ошибка","Заполните имя типа");
            return;
        }
        dataToDb.append(line->text());
        close();
        break;
    }
    }
}

void addDataAdmin::on_pushButton_cancel_clicked() // Кнопка отмена
{
    close();
}
