#include "setupmap.h"
#include "ui_setupmap.h"

setupMap::setupMap(QWidget *parent, parameters* setup, processor* model) :
    QWidget(parent),
    ui(new Ui::setupMap)
{
    fromFile = false;
    villageType.resize(0);
    ui->setupUi(this);
    ui->continue_2->setEnabled(false);
    ready = false;
    this->setup = setup;
    this->model = model;
    editMode = false;
    row = -1;

    QTableWidget *table= ui->table;
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setColumnCount(4);
    table->setRowCount(0);
    //table->setColumnWidth(0);
    QStringList list;
    list<< "Name:" << "Pop:" << "X:" << "Y:";
    table->setHorizontalHeaderLabels(list);
    table->verticalHeader()->setVisible(false);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setStyleSheet("QTableView {selection-background-color: blue;}");
    table->setColumnWidth(0,100);
    table->setColumnWidth(1, 50);
    table->setColumnWidth(2, 50);
    table->setColumnWidth(3, 50);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    //QTableWidgetItem* testItem = new QTableWidgetItem("Testing", 0);
    //table->setItem(0, 0, testItem);

    connect(ui->table, SIGNAL(cellClicked(int,int)), this, SLOT(itemSelected(int,int)));
}

setupMap::~setupMap()
{
    delete ui;
}

void setupMap::itemSelected(int row, int column){
    for(int i = 0; i < ui->table->rowCount(); i++){
        for(int j = 0; j < ui->table->columnCount(); j++){
            std::cout << "At x: " << j << " y: " << i << " data: " << (ui->table->item(i, j)->data(0).toString()).toStdString() << std::endl;
        }
    }
    editMode = true;
    this->row = row;
    std::cout << "row: " << row << std::endl;
    ui->nameValue->setText(ui->table->item(row, 0)->data(0).toString());
    ui->popValue->setText(ui->table->item(row, 1)->data(0).toString());
    ui->xlongValue->setText(ui->table->item(row, 2)->text());
    ui->ylatValue->setText(ui->table->item(row, 3)->text());

    ui->add->setText("Update");
    ui->clear->setDisabled(true);

}

void setupMap::on_back_pressed()
{
    emit indexChange(2);
}

void setupMap::on_continue_2_pressed()
{
    emit indexChange(4);
}

void setupMap::on_relative_toggled(bool checked)
{
    if(checked){
        ui->x_long->setText("X position:");
        ui->y_lat->setText("Y position:");
    }
}

void setupMap::on_geographic_toggled(bool checked)
{
    if(checked){
        ui->x_long->setText("Longitude:");
        ui->y_lat->setText("Latitude:");
    }
}

void setupMap::on_clear_pressed()
{
    ui->nameValue->setText("");
    ui->xlongValue->setText("");
    ui->ylatValue->setText("");
    ui->popValue->setText("");
    if(ui->relative->isChecked()){
        ui->x_long->setText("<font color='black'>X position:</font>");
        ui->y_lat->setText("<font color='black'>Y position:</font>");
    }
    else{
        ui->x_long->setText("<font color='black'>Longitude:</font>");
        ui->y_lat->setText("<font color='black'>Latitude:</font>");
    }
    ui->name->setText("<font color='black'>Name:</font>");
    ui->population->setText("<font color='black'>Population:</font>");
}

void setupMap::on_add_pressed()
{
    bool goodName = true;
    bool goodPop = true;
    bool goodX = true;
    bool goodY = true;
    QString testName = ui->nameValue->text();
    if(testName.length()!= 0){
        for(int i = 0; i < testName.length(); i++){
            if(!(testName.at(i).isLetter() || testName.at(i).isNumber())){
                ui->name->setText("<font color='red'>Name:</font>");
                goodName = false;
                break;
            }
        }
    }
    double population = ui->popValue->text().toDouble(&goodPop);
    if(!goodPop || population < 1){
        ui->population->setText("<font color='red'>Population:</font>");
        goodPop = false;
    }
    double x = ui->xlongValue->text().toDouble(&goodX);
    if(!goodX || x < 0 || x > setup->x){
        if(ui->relative->isChecked()){
            ui->x_long->setText("<font color='red'>X position:</font>");
        }
        else{
            ui->x_long->setText("<font color='red'>Longitude:</font>");
        }

        goodX = false;
    }
    double y = ui->ylatValue->text().toDouble(&goodY);
    if(!goodY || y < 0 || y > setup->y){
        if(ui->relative->isChecked()){
            ui->y_lat->setText("<font color='red'>Y position:</font>");
        }
        else{
            ui->y_lat->setText("<font color='red'>Latitude:</font>");
        }

        goodY = false;
    }

    if(editMode){
        if(goodName && goodPop && goodX && goodY){
            villageType.push_back(false);
            ui->table->item(row, 0)->setText(testName);
            QString temp;
            temp = QString::number(population);
            ui->table->item(row, 1)->setText(temp);
            temp = QString::number(x);
            ui->table->item(row, 2)->setText(temp);
            temp = QString::number(y);
            ui->table->item(row, 3)->setText(temp);

            ui->nameValue->setText("");
            ui->xlongValue->setText("");
            ui->ylatValue->setText("");
            ui->popValue->setText("");
            if(ui->relative->isChecked()){
                ui->x_long->setText("<font color='black'>X position:</font>");
                ui->y_lat->setText("<font color='black'>Y position:</font>");
            }
            else{
                ui->x_long->setText("<font color='black'>Longitude:</font>");
                ui->y_lat->setText("<font color='black'>Latitude:</font>");
            }
            ui->name->setText("<font color='black'>Name:</font>");
            ui->population->setText("<font color='black'>Population:</font>");

            QItemSelectionModel *selection = ui->table->selectionModel();
            selection->clear();
            editMode = false;
            ui->add->setText("Add");
            ui->clear->setDisabled(false);
            ui->continue_2->setEnabled(true);
            ui->nameValue->setFocus();
        }
    }
    else{
        if(goodName && goodPop && goodX && goodY){
            villageType.push_back(false);
            QString temp;
            QTableWidgetItem* tempName = new QTableWidgetItem(testName, 0);
            temp = QString::number(population);
            QTableWidgetItem* tempPop = new QTableWidgetItem(temp, 0);
            temp = QString::number(x);
            QTableWidgetItem* tempX = new QTableWidgetItem(temp, 0);
            temp = QString::number(y);
            QTableWidgetItem* tempY = new QTableWidgetItem(temp, 0);
            int rows = ui->table->rowCount();
            ui->table->setRowCount(rows + 1);
            ui->table->setItem(rows, 0, tempName);
            ui->table->setItem(rows, 1, tempPop);
            ui->table->setItem(rows, 2, tempX);
            ui->table->setItem(rows, 3, tempY);

            ui->nameValue->setText("");
            ui->xlongValue->setText("");
            ui->ylatValue->setText("");
            ui->popValue->setText("");
            if(ui->relative->isChecked()){
                ui->x_long->setText("<font color='black'>X position:</font>");
                ui->y_lat->setText("<font color='black'>Y position:</font>");
            }
            else{
                ui->x_long->setText("<font color='black'>Longitude:</font>");
                ui->y_lat->setText("<font color='black'>Latitude:</font>");
            }
            ui->name->setText("<font color='black'>Name:</font>");
            ui->population->setText("<font color='black'>Population:</font>");

            ui->continue_2->setEnabled(true);
            ui->nameValue->setFocus();
        }
    }
}

void setupMap::on_delete_2_pressed()
{
    if(editMode){
        ui->table->removeRow(row);

        ui->nameValue->setText("");
        ui->xlongValue->setText("");
        ui->ylatValue->setText("");
        ui->popValue->setText("");
        if(ui->relative->isChecked()){
            ui->x_long->setText("<font color='black'>X position:</font>");
            ui->y_lat->setText("<font color='black'>Y position:</font>");
        }
        else{
            ui->x_long->setText("<font color='black'>Longitude:</font>");
            ui->y_lat->setText("<font color='black'>Latitude:</font>");
        }
        ui->name->setText("<font color='black'>Name:</font>");
        ui->population->setText("<font color='black'>Population:</font>");

        editMode = false;
        ui->add->setText("Add");
        ui->clear->setDisabled(false);
    }
    else{
        if(ui->table->selectionModel()->hasSelection()){
            QModelIndexList selection = ui->table->selectionModel()->selectedRows();
            for(int i = 0; i < selection.count(); i++){
                QModelIndex current = selection.at(i);
                ui->table->removeRow(current.row());
            }
        }
    }

    int rows = ui->table->rowCount();
    ui->table->setRowCount(rows - 1);

    if((rows - 1) == 0){
        ui->continue_2->setDisabled(true);
    }
}

void setupMap::addVillages(processor* simulation){
    if(fromFile){
        cout << "added villages from file" << endl;
        for(int i = 0; i < fileVillages.size(); i++){
            simulation->addVillage(fileVillages.at(i));
        }

        string tName;
        int tX;
        int tY;
        int tPop;

        for(int i = 0; i < ui->table->rowCount(); i++){
            bool test;
            tName = ui->table->item(i, 0)->text().toStdString();
            tPop = ui->table->item(i, 1)->text().toInt(&test, 10);
            tX = ui->table->item(i, 2)->text().toInt(&test, 10);
            tY = ui->table->item(i, 3)->text().toInt(&test, 10);
            std::cout << "i: " << i << " name: " << tName << " pop: " << tPop << " x: " << tX << " y: " << tY << std::endl;
            vector<int> vectorPop(setup->years, tPop);
            simulation->addVillage(new village(tX, setup->y - tY, vectorPop, 0, tName, setup->years));
        }
    }
    else{
        string tName;
        int tX;
        int tY;
        int tPop;

        for(int i = 0; i < ui->table->rowCount(); i++){
            bool test;
            tName = ui->table->item(i, 0)->text().toStdString();
            tPop = ui->table->item(i, 1)->text().toInt(&test, 10);
            tX = ui->table->item(i, 2)->text().toInt(&test, 10);
            tY = ui->table->item(i, 3)->text().toInt(&test, 10);
            std::cout << "i: " << i << " name: " << tName << " pop: " << tPop << " x: " << tX << " y: " << tY << std::endl;
            vector<int> vectorPop(setup->years, tPop);
            simulation->addVillage(new village(tX, setup->y - tY, vectorPop, 0, tName, setup->years));
        }
    }
}

void setupMap::on_nameValue_returnPressed()
{
    on_add_pressed();
}

void setupMap::on_popValue_returnPressed()
{
    on_add_pressed();
}

void setupMap::on_xlongValue_returnPressed()
{
    on_add_pressed();
}

void setupMap::on_ylatValue_returnPressed()
{
    on_add_pressed();
}

void setupMap::on_pushButton_pressed()
{
    QMessageBox infoMessage;
    infoMessage.setText("Currently editing loaded populations isn't supported. They won't show up in the table even when successfully loaded.\n"
                         "The file must include data for at least as many years as were set in simulation duration.");
    infoMessage.setWindowTitle("File Warning");
    infoMessage.exec();

    QString filename = QFileDialog::getOpenFileName(this, tr("Select Population CSV File"), "/home", tr("CSV (*.csv)"));
    string name = filename.toStdString();
    if(name.length() != 0 && name.find(".csv") != string::npos){
        ifstream inputFile(name);
        if(inputFile.is_open()){
            vector<string> names;
            vector<int> xPositions;
            vector<int> yPositions;
            cout << "opened the file" << endl;
            bool done = false;
            int counter = 0;
            string type, input, temp;
            std::getline(inputFile, type, ',');
            std::getline(inputFile, input);
            while(counter < input.size()){
                temp.clear();
                while(counter != input.size()){
                    if(input.at(counter) == ','){
                        break;
                    }
                    else{
                        temp += input.at(counter);
                        counter++;
                    }
                }
                cout << "name: " << temp << " pos: " <<counter << endl;
                names.push_back(temp);
                counter++;

            }
            cout << "input after heade read: " << input << " type: " << type << endl;
            cout << "names: ";
            for(int i = 0; i < names.size(); i++){
                cout << names.at(i) << " ";
            }
            cout << endl;

            std::getline(inputFile, type, ',');
            cout << "type: " << type;
            std::getline(inputFile, input);
            counter = 0;
            while(counter < input.size()){
                temp.clear();
                while(counter != input.size()){
                    if(input.at(counter) == ','){
                        break;
                    }
                    else{
                        temp += input.at(counter);
                        counter++;
                    }
                }
                cout << "x: " << temp << " pos: " <<counter << endl;
                xPositions.push_back(stoi(temp));
                counter++;
            }
            std::getline(inputFile, type, ',');
            cout << "type: " << type;
            std::getline(inputFile, input);
            counter = 0;
            while(counter < input.size()){
                temp.clear();
                while(counter != input.size()){
                    if(input.at(counter) == ','){
                        break;
                    }
                    else{
                        temp += input.at(counter);
                        counter++;
                    }
                }
                cout << "x: " << temp << " pos: " <<counter << endl;
                yPositions.push_back(stoi(temp));
                counter++;
            }

            vector<vector<int>> data(names.size());

            int pos;
            int line = 0;
            bool first;

            while(std::getline(inputFile, input)){
                temp.clear();
                pos = 0;
                first = true;
                line = 0;

                cout << "line: " << line << " input: " << input << " length: " << input.size() << endl;
                while(pos < input.size()){
                    while(pos != input.size()){
                        if(input.at(pos) == ','){
                            break;
                        }
                        else{
                            if(!first){
                                temp += input.at(pos);
                            }
                            else{
                                temp += input.at(pos);
                            }
                            pos++;
                        }
                    }
                    if(first){
                        cout << "first: " << temp << " pos: " << pos << endl;
                        first = false;
                    }
                    else{
                        cout << "after first: " << temp << " pos: " << pos << endl;
                        data.at(line).push_back(stoi(temp));
                        line++;
                    }
                    temp.clear();
                    pos++;
                }

                /*
                if(counter % names.size() != 0){
                    cout << "inside if reader case: ";
                    data.at((counter % names.size()) - 1).push_back(stoi(input));
                }
                else if(counter == 0){
                    cout << " inside else reader case: ";
                    setup->startYear = stoi(input);
                }
                counter++;
                cout << " end of while read loop" << endl;
                */
            }

            bool good = true;

            for(int i =  0; i < names.size(); i++){
                cout << names.at(i) << " ";
                cout << "size: " << data.at(i).size() << " ";
                if(data.at(i).size() < setup->years){
                    good = false;
                }
                for(int j = 0; j < data.at(0).size(); j++){
                    cout << data.at(i).at(j) << " ";
                }
                cout << endl;
            }

            if(!good){
                QMessageBox errorMessage;
                errorMessage.setText("There was a problem reading the selected file.");
                errorMessage.setWindowTitle("Read Error");
                errorMessage.exec();
            }

            inputFile.close();
            if(good && data.at(0).size() >= setup->years){
                fromFile = true;
                //new village(tX, setup->y - tY, vectorPop, 0, tName, setup->years)
                for(int i = 0; i < names.size(); i++){
                    fileVillages.push_back(new village(xPositions.at(i), setup->y - yPositions.at(i), data.at(i),
                                                       0, names.at(i), setup->years));
                }
                emit indexChange(4);
            }
            else{
                QMessageBox errorMessage;
                errorMessage.setText("Please adjust the simulation duration to be no longer than the number of years of population data");
                errorMessage.setWindowTitle("File Error");
                errorMessage.exec();
            }
        }
        else{
            QMessageBox errorMessage;
            errorMessage.setText("There was a problem opening the selected file.");
            errorMessage.setWindowTitle("File Error");
            errorMessage.exec();
        }
    }
}
