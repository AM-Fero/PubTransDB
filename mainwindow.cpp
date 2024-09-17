#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : // Конструктор
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("PubTransDB_v1.0.0");
    if (ConnectToDB())createEnterButtons();
    else {
        QPushButton* tryAgain = GetNewButton("Попробовать снова",true,"-","-");
        tryAgain->setParent(this);
        tryAgain->setGeometry(10,10,200,50);
        tryAgain->show();
        connect(tryAgain,SIGNAL(clicked()),this,SLOT(tryAgainToConnect()));
    }
}

MainWindow::~MainWindow() // Деструктор
{
    if (db!=nullptr)
    {        
        delete db;
    }
    ExitEnter(false);
    delete ui;
}

bool MainWindow::ConnectToDB() // Функция подключения к базе данных
{
    db = new QSqlDatabase(QSqlDatabase::addDatabase("QPSQL","newConnection"));
    db->setDatabaseName("Public_Transport_DB");
    db->setHostName("127.0.0.1");
    db->setPort(5432);
    if (!db->open("postgres","user"))
    {
        QMessageBox::warning(this,"Error", db->lastError().text());
        db->removeDatabase("newConnection");
        delete db;
        db = nullptr;
        return false;
    }
    return true;
}

void MainWindow::tryAgainToConnect() // Попробовать покдлючиться снова
{
    if (ConnectToDB())ExitEnter(true);
}

QTableWidgetItem *MainWindow::GetNewItem(QString name, bool isEditable, bool isHeader) // Функция создания новой ячейки в таблице
{
    QTableWidgetItem* temp = new QTableWidgetItem(name);
    temp->setTextAlignment(Qt::AlignCenter);
    if (!isEditable) temp->setFlags(temp->flags() ^ Qt::ItemIsEditable);
    if (isHeader)
    {
        QFont font = temp->font();
        font.setBold(true);
        temp->setFont(font);
    }
    return temp;
}

QPushButton *MainWindow::GetNewButton(QString name, bool isOn, QString propertyName, QString propertyValue) // Функиця создания новой кнопки
{
    QPushButton* temp = new QPushButton();
    temp->setText(name);
    if (!isOn) temp->setEnabled(false);
    temp->setProperty(propertyName.toLocal8Bit().data(),propertyValue);
    return temp;
}

void MainWindow::FillTable(QTableWidget *tableToFill, QString query) // Функция для заполнения таблицы
{
    qw = db->exec(query);
    tableToFill->clear();
    tableToFill->setRowCount(qw.size()+1);
    tableToFill->setColumnCount(qw.record().count());
    tableToFill->verticalHeader()->hide();
    tableToFill->horizontalHeader()->hide();
    for (int i = 0; i < qw.record().count(); i++)
    {
        tableToFill->setItem(0,i,GetNewItem(qw.record().fieldName(i),false, true));
        for (int j = 0; j < qw.size(); j++)
        {
            qw.seek(j);
            tableToFill->setItem(j+1,i,GetNewItem(qw.value(i).toString(),false));
        }
    }
}

void MainWindow::FillTableButton(QTableWidget *tableToFill, QString query, QString header, QString text, int propertyColumn, QString propertyName) // Функция для заполнения таблицы + кнопка
{
    qw = db->exec(query);
    tableToFill->clear();
    tableToFill->setRowCount(qw.size()+1);
    tableToFill->setColumnCount(qw.record().count()+1);
    tableToFill->verticalHeader()->hide();
    tableToFill->horizontalHeader()->hide();
    for (int i = 0; i < qw.record().count(); i++)
    {
        tableToFill->setItem(0,i,GetNewItem(qw.record().fieldName(i),false, true));
        for (int j = 0; j < qw.size(); j++)
        {
            qw.seek(j);
            tableToFill->setItem(j+1,i,GetNewItem(qw.value(i).toString(),false));

        }
    }    for (int j = 0; j < qw.size(); j++)
    {
        qw.seek(j);
        QPushButton* temp = GetNewButton(text, true, propertyName, qw.value(propertyColumn).toString());
        connect(temp, SIGNAL(clicked()), this, SLOT(GuestShowRouteInfo()));
        tableToFill->setCellWidget(j+1, tableToFill->columnCount()-1, temp);
    }
    tableToFill->setItem(0, tableToFill->columnCount()-1, GetNewItem(header,false,true));
}

void MainWindow::GuestEnter() // Кнопка для входя гостя
{
    pbEnterAdmin->hide();
    pbEnterGuest->hide();
    createExitButton();

    table_info = new QTableWidget(this);
    table_info->setGeometry(0,500,849,150);

    QTableWidget* table_routes = new QTableWidget(this);
    table_routes->setGeometry(849,-1,202,this->height());

    QString query_routes = "SELECT name as \"Название маршрута\" FROM \"Routes\"";
    FillTableButton(table_routes,query_routes, "Действие", "Выбрать", 0, "name");
    table_routes->show();
    table_routes->resizeRowsToContents();
    qw = db->exec("select * from \"Stops\" order by \"id_stop\" ");
    for (int i = 0; i < qw.size(); i++)
    {
        qw.seek(i);
        QStringList coords = qw.value("location").toString().split("{")[1].split("}")[0].split(",");
        guestStops.append(GetNewButton("+",true,"ID",qw.value("id_stop").toString()));
        guestStops[i]->setParent(this);
        guestStopsLabels.append(new QLabel(this));
        guestStopsLabels[i]->setText(qw.value("name").toString());
        connect(guestStops[i], SIGNAL(clicked()),this, SLOT(GuestShowStopInfo()));
        stopsDrawingData.append(int(coords[0].toDouble()*80.));
        stopsDrawingData.append(int(coords[1].toDouble()*80.));
    }
    createNav();
    drawStops(guestNavParams[0], int(guestNavParams[1]), int(guestNavParams[2]));
}

void MainWindow::GuestShowStopInfo() // Показать данные о станции для гостя
{
    QString new_query = "SELECT id_route as \"Номер маршрута\", public.\"Routes-Stops\".position as \"Номер в очереди\", time_to_next as \"Cлед. станция\" "
                        "FROM public.\"Routes-Stops\" WHERE id_stop = "+sender()->property("ID").toString();
    FillTable(table_info,new_query);
    table_info->resizeColumnsToContents();
    table_info->resizeRowsToContents();
    table_info->show();
}

void MainWindow::GuestShowRouteInfo() // Показать данные о маршруте для гостя
{
    QString new_query = "SELECT overall_time as \"Продолжительность\", time_first as \"Первый автобус на линии\", time_last as \"Последний автобус на линии\", "
                        "interval as \"Интервал\", STRING_AGG(public.\"Buses\".registration_number,', ') as \"Автобусы на маршруте\"FROM public.\"Routes\" JOIN"
                        " public.\"Buses\" ON public.\"Routes\".id_route = public.\"Buses\".id_route WHERE public.\"Routes\".name = '" +sender()->property("name").toString() +
            "' GROUP BY public.\"Routes\".id_route";
    FillTable(table_info,new_query);
    table_info->resizeColumnsToContents();
    table_info->resizeRowsToContents();
    table_info->show();
}

void MainWindow::drawStops(double scale, int x, int y) // Отрисовка станицй
{
    for (int i = 0; i<guestStops.count(); i++)
    {
        int newx = int((stopsDrawingData[i*2]+x)*scale);
        int newy = int((stopsDrawingData[(i*2)+1]+y)*scale);
        if (newx>=800 || newy>=500 || newx<=0 || newy<=0)
        {
            guestStops[i]->hide();
            guestStopsLabels[i]->hide();
        }
        else
        {
            guestStops[i]->setGeometry(newx, newy, 20, 20);
            guestStops[i]->show();
            guestStopsLabels[i]->setGeometry(newx, newy-30, 150,20);
            guestStopsLabels[i]->show();
        }
    }
}

void MainWindow::stopsParamChange() // Изменение параметров отрисовки станций
{
    switch (sender()->property("change").toInt()) {
    case 1:{guestNavParams[0] = guestNavParams[0] * 1.15;break;}
    case 2:{guestNavParams[0] = guestNavParams[0] / 1.15;break;}
    case 3:{guestNavParams[2] = guestNavParams[2] - 15;break;}
    case 4:{guestNavParams[1] = guestNavParams[1] - 15;break;}
    case 5:{guestNavParams[2] = guestNavParams[2] + 15;break;}
    case 6:{guestNavParams[1] = guestNavParams[1] + 15;break;}}
    drawStops(guestNavParams[0], int(guestNavParams[1]), int(guestNavParams[2]));
}

void MainWindow::createNav() // Создание элементов управления картой остановок
{
    QStringList buttonNames = {"+", "—", "↑", "←", "↓", "→"};
    QList<QList<int>> buttonGeoms = {{140,10,30,30}, {200,10,30,30}, {170,10,30,30}, {140,40,30,30},
                                     {170,40,30,30}, {200,40,30,30}};
    for (int i = 0; i<6; i++)
    {
        guestNavigation.append(GetNewButton(buttonNames[i], true, "change", QString::number(i+1)));
        guestNavigation[i]->setParent(this);
        guestNavigation[i]->setGeometry(buttonGeoms[i][0], buttonGeoms[i][1], buttonGeoms[i][2],buttonGeoms[i][3]);
        connect(guestNavigation[i],SIGNAL(clicked()),this, SLOT(stopsParamChange()));
        guestNavigation[i]->show();
    }
}

void MainWindow::pwdcheck(QString pwd) // Проверка пароля админа
{
    if (pwd == "1")
    {
        qobject_cast<QLineEdit*>(sender())->hide();
        loadAdminInterface();
    }
}

void MainWindow::loadAdminInterface() // Загрузка интерфейса админа
{
    table_info = new QTableWidget(this);
    table_info->setGeometry(150,10,this->width()-170,this->height()-120);
    table_info->show();
    cb_MainAdmin = new QComboBox(this);
    cb_MainAdmin->setGeometry(10,80,121,35);
    cb_MainAdmin->addItems({"Автобусы","Водители","Депо","Маршруты","Остановки","Типы Автобусов"});
    cb_MainAdmin->show();
    connect(cb_MainAdmin,SIGNAL(currentIndexChanged(int)),this,SLOT(loadTableAdmin(int)));
    loadTableAdmin(0);
    QPushButton * pb_add = GetNewButton("Добавить данные", true,"-","-");
    pb_add->setParent(this);
    pb_add->setGeometry(10,125,121,40);
    pb_add->show();
    connect(pb_add, SIGNAL(clicked()),this,SLOT(addDataToDb()));
}

void MainWindow::loadTableAdmin(int index) // Загрузка конкретной таблицы для админа
{
    QString query;
    switch (index)
    {
    case 0: {query = R"(SELECT "Buses".on_line as "На линии ли?", "Buses".year_create as "Год производства", "Buses".registration_number  as "Регистрационный номер",
                     "Buses".bus_position + 1 as "Очередь на маршруте", "Drivers".name as "ФИО водителя",  "Routes".name as "Маршрут","Depots".name as "Депо", "Type_Bus".type_name as
                     "Тип автобуса" FROM public."Buses" JOIN public."Drivers" ON public."Buses".id_driver = public."Drivers".id_driver JOIN public."Depots" ON public."Buses".id_depot
                     = public."Depots".id_depot JOIN public."Type_Bus" ON public."Buses".id_type = public."Type_Bus".id_type JOIN public."Routes" ON public."Buses".id_route =
                     public."Routes".id_route)";break;}
    case 1: {query = R"(SELECT "Drivers".name as "ФИО водителя", "Buses".registration_number as "Номер автобуса" FROM public."Drivers"LEFT JOIN public."Buses" ON public."Drivers".id_driver =
                     public."Buses".id_driver)";break;}
    case 2: {query = R"(SELECT name as "Имя депо" FROM public."Depots")";break;}
    case 3: {query = R"(SELECT "Routes".name as "Название", STRING_AGG("Stops".name,', ') as "Станции", "Routes".overall_time as "Время на весь маршрут",  "Routes".time_first as
                     "Первый автобус", "Routes".time_last as "Последний автобус", "Routes".interval as "Интервал" FROM public."Routes-Stops" JOIN public."Routes" ON
                     public."Routes-Stops".id_route = public."Routes".id_route JOIN public."Stops" ON public."Routes-Stops".id_stop = public."Stops".id_stop GROUP BY "Routes".name,
                     "Routes".overall_time, "Routes".time_first, "Routes".time_last, "Routes".interval)";break;}
    case 4: {query = R"(SELECT public."Stops".name as "Название станции", public."Stops".location as "Местоположение", STRING_AGG("Routes".name, ', ') as "Маршруты" FROM public."Routes-Stops" JOIN public."Routes" ON public."Routes-Stops".id_route = public."Routes".id_route JOIN public."Stops" ON public."Routes-Stops".id_stop = public."Stops".id_stop GROUP BY public."Stops".name, public."Stops".location)";break;}
    case 5: {query = R"(SELECT type_name as "Типы автобусов" FROM public."Type_Bus")";break;}
    }
    FillTable(table_info,query);
    table_info->resizeRowsToContents();
}

void MainWindow::createEnterButtons() // Создание кнопок входа
{
    pbEnterGuest = GetNewButton("Я гость",true,"-","-");
    pbEnterGuest->setParent(this);
    pbEnterGuest->setGeometry(10,10,121,61);
    connect(pbEnterGuest, SIGNAL(clicked()), this, SLOT(GuestEnter()));
    pbEnterGuest->show();

    pbEnterAdmin = GetNewButton("Я админ",true,"-","-");
    pbEnterAdmin->setParent(this);
    pbEnterAdmin->setGeometry(140,10,121,61);
    connect(pbEnterAdmin, SIGNAL(clicked()), this, SLOT(AdminEnter()));
    pbEnterAdmin->show();
}

void MainWindow::createExitButton() // Создание кнопки выхода
{
    pbExitButton = GetNewButton("Назад",true,"-","-");
    pbExitButton->setParent(this);
    pbExitButton->setGeometry(10,10,121,61);
    pbExitButton->show();
    connect(pbExitButton, SIGNAL(clicked()), this, SLOT(ExitEnter()));
}

void MainWindow::AdminEnter() // Загрузка аутентификации для админа
{
    pbEnterAdmin->hide();
    pbEnterGuest->hide();
    createExitButton();

    QLineEdit *adminKey = new QLineEdit(this);
    adminKey->setPlaceholderText("Введите пароль");
    adminKey->setGeometry(141,10,750,60);
    QFont font = adminKey->font();
    font.setPixelSize(16);
    adminKey->setFont(font);
    adminKey->setEchoMode(QLineEdit::EchoMode::Password);
    adminKey->show();
    connect(adminKey, SIGNAL(textChanged(QString)), this, SLOT(pwdcheck(QString)));
}

void MainWindow::ExitEnter(bool createEnter) // Выход на начало
{
    qDeleteAll(this->findChildren<QWidget*>("",Qt::FindDirectChildrenOnly));
    resetInnerData();
    if (createEnter)createEnterButtons();
}

void MainWindow::resetInnerData() // Очистить глобальные переменные
{
    guestStops.clear();
    stopsDrawingData.clear();
    guestStopsLabels.clear();
    guestNavigation.clear();
    guestNavParams[0]=1;
    guestNavParams[1]=0;
    guestNavParams[2]=0;
}

void MainWindow::addDataToDb() // Вызов диалога добавления данных в БД
{
    QList<QMap<int, QString>> additionalData = formAdditionalData(cb_MainAdmin->currentIndex());
    addDataAdmin* dialog = new addDataAdmin(nullptr);
    if (additionalData.length()!=0) dialog->setAdditionalData(additionalData);
    dialog->loadInterface(cb_MainAdmin->currentIndex());
    dialog->exec();
    if (dialog->dataToDb.length()==0)return;

    switch (cb_MainAdmin->currentIndex())
    {case 0: {db->exec(R"(INSERT INTO public."Buses" VALUES(')" +dialog->dataToDb[0]+"', '"+dialog->dataToDb[1]+"', '"+dialog->dataToDb[2]+"', '"+dialog->dataToDb[3]+"', '"+dialog->dataToDb[4]+"', '"
                +dialog->dataToDb[5]+"', '"+dialog->dataToDb[6]+"', '"+dialog->dataToDb[7]+"')");break;}
    case 1: {db->exec(R"(INSERT INTO public."Drivers" VALUES (')" +dialog->dataToDb[0]+"')");break;}
    case 2: {db->exec(R"(INSERT INTO public."Depots" VALUES (')" +dialog->dataToDb[0]+"')");break;}
    case 3: {db->exec(R"(INSERT INTO public."Routes" VALUES(')" +dialog->dataToDb[0]+"', '"+dialog->dataToDb[1]+"', '"+dialog->dataToDb[2]+"', '"+dialog->dataToDb[3]+"', '"+dialog->dataToDb[4]+"')");break;}
    case 4: {db->exec(R"(INSERT INTO public."Stops" VALUES(')" +dialog->dataToDb[0]+ "', '{"+dialog->dataToDb[1]+","+dialog->dataToDb[2]+"}')");break;}
    case 5: {db->exec(R"(INSERT INTO public."Type_Bus" VALUES (')" +dialog->dataToDb[0]+"')");break;}}

    QMessageBox::information(this,"Уведомление","Данные успешно добавлены");
    loadTableAdmin(cb_MainAdmin->currentIndex());
}

QList<QMap<int, QString>> MainWindow::formAdditionalData(int index) // Формирование доп данных для добавления
{
    QList<QMap<int, QString>> data = {};
    switch (index) {
    case 0:{ // автобусы
        QStringList queries = {R"(SELECT id_driver, public."Drivers".name FROM   public."Drivers" WHERE  id_driver NOT IN (SELECT id_driver FROM public."Buses"))",
                               R"(SELECT id_route, public."Routes".name FROM   public."Routes" )",
                               R"(SELECT id_depot, public."Depots".name FROM   public."Depots" )",
                               R"(SELECT id_type, public."Type_Bus".type_name FROM   public."Type_Bus" )"};
        for (int i = 0; i < queries.count(); i++)
        {
            QMap<int, QString> temp;
            qw = db->exec(queries[i]);
            for (int j = 0; j < qw.size(); j++)
            {
                qw.seek(j);
                temp.insert(qw.value(0).toInt(), qw.value(1).toString());
            }
            data.append(temp);
        }
    }}
    return data;
}
