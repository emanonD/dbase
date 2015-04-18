#include "main_window.h"
#include "dbase/dbase.h"
#include "globals.h"
#include <sstream>
#include <iostream>

using namespace std;
dbase db;


struct ObjN
{
	bool operator()(user u1, user u2)
	{
		string name1;
		string name2;
		vector<string> tempN1 = u1._name;
		string nameInput1 = " ";
		for (unsigned int i=0; i<tempN1.size(); i++)
		{
			nameInput1 = nameInput1+" "+tempN1[i];		
		}
		vector<string> tempN2 = u2._name;
		string nameInput2 = " ";
		for (unsigned int i=0; i<tempN2.size(); i++)
		{
			nameInput2 = nameInput1+" "+tempN2[i];		
		}
		return nameInput1<nameInput2;
	}
};

struct ObjD
{
	bool operator()(user u1, user u2)
	{
		string date1 = u1._date;
		string date2 = u2._date;
		return date1<date2;
	}
};

MainWindow::MainWindow()
{

	
	// Title
	setWindowTitle("Welcome to Autobroker Database!");
	overallLayout = new QHBoxLayout;
	lhsLayout = new QVBoxLayout;
	
	search = new QLabel("Search customer profile:");
	lhsLayout->addWidget(search);
	searchInput = new QLineEdit();
	lhsLayout->addWidget(searchInput);
	viewFile = new QPushButton("Search");
	connect(viewFile, SIGNAL(clicked()), this, SLOT(viewPopup()));
	lhsLayout->addWidget(viewFile);
	overallLayout->addLayout(lhsLayout);
	buttonLayout = new QVBoxLayout;
	inputData = new QPushButton("Select the Database");
	connect(inputData, SIGNAL(clicked()), this, SLOT(selectFile()));
	buttonLayout->addWidget(inputData);
	select = new QLabel("Please select from the following:") ;
	buttonLayout->addWidget(select);
	searchFile = new QRadioButton("Search existing profile");
	inputFile = new QRadioButton("Input new profile");
	exportFile = new QRadioButton("Output to file");
	viewPlan = new QRadioButton("Review Monthly Plan");
	ok1Button = new QPushButton("OK");
	connect(ok1Button, SIGNAL(clicked()), this, SLOT(choice()));

	buttonLayout->addWidget(select);

	buttonLayout->addWidget(searchFile);
	buttonLayout->addWidget(inputFile);
	buttonLayout->addWidget(exportFile);
	buttonLayout->addWidget(viewPlan);
	buttonLayout->addWidget(ok1Button);
	setLayout(buttonLayout);
}

MainWindow::~MainWindow()
{
	
}


void MainWindow::selectFile()
{
	QString fileName = QFileDialog::getOpenFileName(this,tr("Open File"),"Home://","All files (*.*);;Text File(*.txt)");
	QMessageBox::information(this,tr("File name"),fileName);
	std::string name = fileName.QString::toStdString();
	db.parse(name);
}

void MainWindow::choice()
{
	if (searchFile->isChecked())
	{
		searchPopup();
	}
	else if (inputFile->isChecked())
	{
		showPopup();
	}
	else if (exportFile->isChecked())
	{
		exportPopup();
	}
	else if (viewPlan->isChecked())
	{
		planPopup();
	}
}

void MainWindow::planPopup()
{
	QDialog planWindow;
	QVBoxLayout* overallLayout = new QVBoxLayout;
	QCalendarWidget* planC = new QCalendarWidget;
	overallLayout->addWidget(planC);
	planC->setGridVisible(true);
	QDate selectedDate = planC->selectedDate();
	QString selectedDateQS = selectedDate.toString(Qt::TextDate); 
	QPushButton* selectD = new QPushButton("Select date");
	connect(selectD, SIGNAL(clicked()), this, SLOT(viewSpecific()));
	overallLayout->addWidget(selectD);
	planWindow.setLayout(overallLayout);
	planWindow.exec();
}

void MainWindow::viewSpecific()
{
	QDialog specific;
	QVBoxLayout* overallLayout = new QVBoxLayout;
	specific.setLayout(overallLayout);
	specific.exec();
}

//view profile, search, call history
void MainWindow::searchPopup()
{
	QDialog viewWindow;
	lhsLayout = new QVBoxLayout;
	search = new QLabel("Search customer profile:");
	lhsLayout->addWidget(search);
	searchInput = new QLineEdit();
	lhsLayout->addWidget(searchInput);
	viewFile = new QPushButton("Search");
	connect(viewFile, SIGNAL(clicked()), this, SLOT(viewPopup()));
	

	listLayout = new QGridLayout;
	
	list = new QComboBox();
	listLabel = new QLabel("Choose list order:");
	listLayout->addWidget(listLabel);
	
	//Choose the way of listing
	list->addItem("alphabetical sort");
	list->addItem("date sort");
	listLayout->addWidget(listLabel, 1, 0, 1, 1);
	listLayout->addWidget(list, 2, 0, 1, 2);
	listLayout->addWidget(viewFile);
	//listLayout->addWidget(list);
	lhsLayout->addLayout(listLayout);
	profileListWidget = new QListWidget();
	//connect(profileWidget,SIGNAL(currentRowChanged(int)), this, SLOT(displayReview(int)));
	lhsLayout->addWidget(profileListWidget);

	searchButtons = new QGridLayout;
	callButton = new QPushButton("Call History");
	connect(callButton, SIGNAL(clicked()), this, SLOT(callHistory()));
	editButton = new QPushButton("Edit User");
	connect(editButton, SIGNAL(clicked()), this, SLOT(editUser()));
	searchButtons->addWidget(callButton, 1, 0, 1, 1);
	searchButtons->addWidget(editButton, 1, 2, 1, 1);

	//TODO
	//add calendar whenever call history || add history
	lhsLayout->addLayout(searchButtons);
	viewWindow.setLayout(lhsLayout);
	viewWindow.exec();
}

void MainWindow::callHistory()
{
	historyWindow = new QDialog;
	QVBoxLayout* overallLayout = new QVBoxLayout;
	listHistory = new QListWidget;
	overallLayout->addWidget(listHistory);
	historyWindow->setWindowTitle("View Call History");
	if (profileListWidget->currentRow()<0)
		return;
	user temp = userR[profileListWidget->currentRow()];
	vector<string> u = temp._name;
	string userName="";
	for (unsigned int i=0; i<u.size();i++)
	{
		userName=userName+" "+u[i];
	
	//QLabel* title = new QLabel(userName);
	}
	QString quser = QString::fromStdString(userName);
	listHistory->addItem(quser);
	
	for (unsigned int i=0; i<temp._callHistory.size(); i++)
	{
		string chDate = temp._callHistory[i]._date;
		QString qchDate = QString::fromStdString(chDate);
		listHistory->addItem(qchDate);
	}
	QHBoxLayout* buttons = new QHBoxLayout;
	QPushButton* addCall = new QPushButton("Add Call");
	
	QPushButton* details = new QPushButton("View Details");
	connect(details, SIGNAL(clicked()), this, SLOT(detailsPopup()));
	QPushButton* cancel = new QPushButton("Cancel");
	connect(cancel, SIGNAL(clicked()), this, SLOT(cancelCHPopup()));
	buttons->addWidget(details);
	buttons->addWidget(addCall);
	buttons->addWidget(cancel);
	overallLayout->addLayout(buttons);
	historyWindow->setLayout(overallLayout);
	historyWindow->exec();
}

void MainWindow::cancelCHPopup()
{
	historyWindow->close();
}

void MainWindow::detailsPopup()
{
	window = new QDialog;
	window->setWindowTitle("View Details");
	QVBoxLayout* overallLayout = new QVBoxLayout;
	if (listHistory->currentRow()<0)
		return;
	QListWidget* show = new QListWidget;
	int index = listHistory->currentRow()+1;
	user temp = userR[profileListWidget->currentRow()];
	string output = temp._callHistory[index].displayString();
	QString qoutput = QString::fromStdString(output);
	show->addItem(qoutput);
	QPushButton* cancel = new QPushButton("Cancel");
	connect(cancel, SIGNAL(clicked()), this, SLOT(cancelPopup()));
	overallLayout->addWidget(show);
	overallLayout->addWidget(cancel);
	window->setLayout(overallLayout);
	window->exec();
}

void MainWindow::cancelPopup()
{
	window->close();
}

void MainWindow::editUser()
{
	QDialog popWindow;
	popWindow.setWindowTitle("Edit User");
	QVBoxLayout* overallLayout = new QVBoxLayout();
	QHBoxLayout* inputLayout = new QHBoxLayout();
	QHBoxLayout* labelLayout = new QHBoxLayout();
	QFormLayout* inputlhs = new QFormLayout();
	QVBoxLayout* input1 = new QVBoxLayout();
	QFormLayout* inputrhs = new QFormLayout();
	QVBoxLayout* input2 = new QVBoxLayout();
	if (profileListWidget->currentRow()<0)
		return;
	user temp = userR[profileListWidget->currentRow()];
	car tempC = temp._car;
	saveKey=temp._key;
	vector<string> tempN = temp._name;
	string nameInput1 = "";
	for (unsigned int i=0; i<tempN.size(); i++)
	{
		nameInput1 = nameInput1+" "+tempN[i];
		
	}
	
	nameInput= new QLineEdit(QString::fromStdString(nameInput1));
	dateinput= new QLineEdit(QString::fromStdString(temp._date));
	cout << "set place..."	<< endl;
	cellInput = new QLineEdit(QString::fromStdString(temp._cell));	 
	cellInput2= new QLineEdit(QString::fromStdString(temp._other));	
	email= new QLineEdit(QString::fromStdString(temp._email));
	vector<string> tempA = temp._address;
	string addressInput1 = "";
	for (unsigned int i=0; i<tempA.size(); i++)
	{
		addressInput1 = addressInput1+" "+tempA[i];
		cout << addressInput1;
	}
	cout << endl;

	addressInput= new QLineEdit(QString::fromStdString(addressInput1));
	referralInput= new QLineEdit(QString::fromStdString(temp._Referral));
	brokerInput= new QLineEdit(QString::fromStdString(temp._Broker));
	officeInput= new QLineEdit(QString::fromStdString(temp._Office));
	ssnInput= new QLineEdit(QString::fromStdString(temp._SSN));	
	income= new QLineEdit(QString::fromStdString(temp._MonthlyIncome));	
	dob= new QLineEdit(QString::fromStdString(temp._DOB));
	//ethnicity->setPalceholderText(QString::fromStdString(temp._Ethnicity));
	//gender->setPlaceholderText(QString::fromStdString(temp._Gender));
	occupation= new QLineEdit(QString::fromStdString(temp._Occupation));

	


	title1Label = new QLabel("Customer Profile");
	labelLayout ->addWidget(title1Label);
	title2Label = new QLabel("Current Car Info(Use for trade-in)");
	labelLayout->addWidget(title2Label);
	overallLayout->addLayout(labelLayout);
	//inputlhs->addRow(tr("&Customer Profile"),title1Label);
	
	cout << 1 << endl;

	inputlhs->addRow(tr("&Name:"),nameInput);		
	inputlhs->addRow(tr("&Date:"),dateinput);	
	inputlhs->addRow(tr("&Cell #:"),cellInput);	
	inputlhs->addRow(tr("&Other #:"),cellInput2);		
	inputlhs->addRow(tr("&Email:"),email);
	inputlhs->addRow(tr("&Address:"),addressInput);	
	inputlhs->addRow(tr("&Referral:"),referralInput);	
	inputlhs->addRow(tr("&Broker"),brokerInput);	
	inputlhs->addRow(tr("&Office"),officeInput);	
	inputlhs->addRow(tr("&SSN:"),ssnInput);	
	inputlhs->addRow(tr("&Monthly Income:"),income);
	inputlhs->addRow(tr("&DOB:"),dob);
	QLineEdit* ethnicityQLineEdit = new QLineEdit(QString::fromStdString(temp._Ethnicity));
	inputlhs->addRow(tr("&Ethnicity:"),ethnicityQLineEdit);
	QLineEdit* genderQLineEdit = new QLineEdit(QString::fromStdString(temp._Gender));
	inputlhs->addRow(tr("&Gender:"),genderQLineEdit);
	inputlhs->addRow(tr("&Occupation:"),occupation);
	input1->addLayout(inputlhs);
	inputLayout->addLayout(input1);
	makeInput = new QLineEdit(QString::fromStdString(tempC._make));
	colorInput2 = new QLineEdit(QString::fromStdString(tempC._exterior));	
	colorInput = new QLineEdit(QString::fromStdString(tempC._interior));
	yearInput = new QLineEdit(QString::fromStdString(tempC._year));
	mrsp = new QLineEdit(QString::fromStdString(tempC._MRSP));
	valueInput = new QLineEdit(QString::fromStdString(tempC._value));
	navigation = new QLineEdit(QString::fromStdString(tempC._navigation));
	RCamera = new QLineEdit(QString::fromStdString(tempC._rearCamera));
	featureInput = new QLineEdit(QString::fromStdString(tempC._feature));
	inputrhs->addRow(tr("&Make:"),makeInput);	
	inputrhs->addRow(tr("&Exterior Color:"),colorInput2);	
	inputrhs->addRow(tr("&Interior Color:"),colorInput);	
	inputrhs->addRow(tr("&Year:"),yearInput);	
	inputrhs->addRow(tr("&M.R.S.P:"),mrsp);	
	inputrhs->addRow(tr("&Current Value:"),valueInput);		
	inputrhs->addRow(tr("&Navigation:"),navigation);	
	inputrhs->addRow(tr("&Rear Camera:"),RCamera);	
	inputrhs->addRow(tr("&Additional Features:"),featureInput);
	QCalendarWidget* editC = new QCalendarWidget;
	editC->setGridVisible(true);
	QDate selectedDate = editC->selectedDate();
	QString selectedDateQS = selectedDate.toString(Qt::TextDate); 
	string selectedDateS = selectedDateQS.toStdString();
	//add to data structure
	input2->addLayout(inputrhs);
	QLabel* addCallHistory = new QLabel("Select Call-back Date:");
	input2->addWidget(addCallHistory);
	input2->addWidget(editC);
	inputLayout->addLayout(input2);
	//inputLayout->addLayout(inputlhs);
	/*inputLayout->addLayout(inputmhs);
	inputLayout->addLayout(inputrhs);*/
	
	overallLayout->addLayout(inputLayout);
	QHBoxLayout* button = new QHBoxLayout;
	QPushButton* saveButton = new QPushButton("Save");
	button->addWidget(saveButton);
	QPushButton* viewButton = new QPushButton("View Call History");
	button->addWidget(viewButton);
	QPushButton* addButton = new QPushButton("Add Call History");
	button->addWidget(addButton);
	connect(saveButton, SIGNAL(clicked()), this, SLOT(changeSave()));
	overallLayout->addWidget(saveButton);
	popWindow.setLayout(overallLayout);
	popWindow.exec();

}


/*void MainWindow::uploadP()
{
	QString fileName = QFileDialog::getOpenFileName(this,tr("Open File"),"Home://","All files (*.*)");
	QImage* newImage = new QImage();
	//TODO what should go right here?
	newImage->load(fileName);
	Images.push_back(newImage);
	ImageContainer = new QLabel();
	ImageContainer->setPixmap(QPixmap::fromImage(*pokemonImages[pokemonIndex]));

}*/

void MainWindow::sortN(vector<user> r)
{
	ObjN objN;
	mergeSort(r,objN);
}

void MainWindow::sortD(vector<user> r)
{	
	ObjD objD;
	mergeSort(r,objD);

}

void MainWindow::viewPopup()
{
	string search = searchInput->text().toStdString();
	string temp;
	stringstream ss(search);
	vector<string> R;
	while (ss>>temp)
	{
		cout << "search Input " << temp << endl;
		R.push_back(temp);
	}
	userR = db.search(R);
	if (list->currentIndex() == 0)
	{
		sortN(userR);
	}
	//sort by rate
	else if (list->currentIndex() == 1)
	{
		sortD(userR);
	}
		profileListWidget->clear();
	for (unsigned int i=0; i<userR.size(); i++)
	{
		std::string str1= userR[i].displayString();
		cout << "search result " << str1 << endl;
		QString qstr1 = QString::fromStdString(str1);
		profileListWidget->addItem(qstr1);
	}
}

//save to file window
void MainWindow::exportPopup()
{

	QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "Home//","All files (*.*);;Text File(*.txt)");
	string name = fileName.toStdString();
	ofstream of(name.c_str());
	db.dump(of);
	of.close();
	
	
}


//function of ofile
void MainWindow::ofile()
{
	
	save->close();
}


void MainWindow::showPopup()
{

//TODO

//add call back date QCalendar
	popWindow = new QDialog;
	popWindow->setWindowTitle("Input Data");
	QVBoxLayout* overallLayout = new QVBoxLayout();
	QHBoxLayout* inputLayout = new QHBoxLayout();
	QHBoxLayout* labelLayout = new QHBoxLayout();
	QFormLayout* inputlhs = new QFormLayout();
	QVBoxLayout* input1 = new QVBoxLayout();
	QFormLayout* inputrhs = new QFormLayout();
	QVBoxLayout* input2 = new QVBoxLayout();

	popWindow = new QDialog;
	popWindow->setWindowTitle("Input Data");
	QVBoxLayout* overallLayout = new QVBoxLayout();
	QHBoxLayout* inputLayout = new QHBoxLayout();
	QHBoxLayout* labelLayout = new QHBoxLayout();
	QFormLayout* inputlhs = new QFormLayout();
	QVBoxLayout* input1 = new QVBoxLayout();
	QFormLayout* inputrhs = new QFormLayout();
	QVBoxLayout* input2 = new QVBoxLayout();


	title1Label = new QLabel("Customer Profile");
	labelLayout ->addWidget(title1Label);
	title2Label = new QLabel("Current Car Info(Use for trade-in)");
	labelLayout->addWidget(title2Label);
	overallLayout->addLayout(labelLayout);
	//inputlhs->addRow(tr("&Customer Profile"),title1Label);
	nameInput = new QLineEdit("Name");
	inputlhs->addRow(tr("&Name:"),nameInput);	
	cellInput = new QLineEdit("Cell");
	inputlhs->addRow(tr("&Cell #:"),cellInput);
	cellInput2 = new QLineEdit("cell2");
	inputlhs->addRow(tr("&other #:"),cellInput2);	
	email = new QLineEdit();
	addressInput = new QLineEdit("Address");
	inputlhs->addRow(tr("&Email:"),email);
	inputlhs->addRow(tr("&Address:"),addressInput);
	referralInput = new QLineEdit("Referral");
	inputlhs->addRow(tr("&Referral:"),referralInput);
	brokerInput = new QLineEdit("broker");
	inputlhs->addRow(tr("&Broker"),brokerInput);
	officeInput = new QLineEdit("office");
	inputlhs->addRow(tr("&Office"),officeInput);
	ssnInput = new QLineEdit("SSN");
	inputlhs->addRow(tr("&SSN:"),ssnInput);
	income = new QLineEdit("income");
	inputlhs->addRow(tr("&Monthly Income:"),income);
	dob = new QLineEdit("DOB");
	inputlhs->addRow(tr("&DOB:"),dob);
	
	ethnicity = new QComboBox();
	ethnicityLabel = new QLabel("Ethnicity:");
	inputlhs->addRow(ethnicityLabel);
	ethnicity->addItem("Asian");
	ethnicity->addItem("American Indian or Alaska Native");
	ethnicity->addItem("Black or African American");
	ethnicity->addItem("Native Hawaiian or Other Pacific Islander");
	ethnicity->addItem("White");
	inputlhs->addRow(ethnicity);
	

	gender = new QComboBox();
	genderLabel = new QLabel("Gender:");
	inputlhs->addRow(genderLabel);
	
	//Choose the way of listing
	gender->addItem("Male");
	gender->addItem("Female");
	inputlhs->addRow(gender);
	occupation = new QLineEdit();
	inputlhs->addRow(tr("&Occupation:"),occupation);
	input1->addLayout(inputlhs);
	QPushButton* upload = new QPushButton("Upload pictures");
	connect(upload, SIGNAL(clicked()), this, SLOT(uploadP()));
	input1->addWidget(upload);
	inputLayout->addLayout(input1);

	
makeInput = new QLineEdit("Make");
	inputrhs->addRow(tr("&Make:"),makeInput);
	colorInput2 = new QLineEdit("exteriro");
	inputrhs->addRow(tr("&Exterior Color:"),colorInput2);
	colorInput = new QLineEdit("Interior");
	inputrhs->addRow(tr("&Interior Color:"),colorInput);
	yearInput = new QLineEdit("Year");
	inputrhs->addRow(tr("&Year:"),yearInput);
	mrsp = new QLineEdit("MSRP");
	inputrhs->addRow(tr("&M.R.S.P:"),mrsp);
	valueInput = new QLineEdit("value");
	inputrhs->addRow(tr("&Current Value:"),valueInput);	
	navigation = new QLineEdit("Navigation");
	inputrhs->addRow(tr("&Navigation:"),navigation);
	RCamera = new QLineEdit("RearCamera");
	inputrhs->addRow(tr("&Rear Camera:"),RCamera);
	featureInput = new QLineEdit("Feature");
	inputrhs->addRow(tr("&Additional Features:"),featureInput);
	QLabel* addition = new QLabel("Additional Information:");
	inputrhs->addRow(addition);
	purpose = new QComboBox();
	QLabel* purposeLabel = new QLabel("Purpose of Calling:");
	
	purpose->addItem("Purchasing");
	purpose->addItem("Leasing");
	QLabel* callDate = new QLabel("Select Date:");
	editC = new QCalendarWidget;
	editC->setGridVisible(true);
	
	//add to data structure


	QLabel* Comment = new QLabel("Comments:");
	commentInput = new QTextEdit("Comments");
	input2->addLayout(inputrhs);
	input2->addWidget(purposeLabel);
	input2->addWidget(purpose);
	input2->addWidget(callDate);
	input2->addWidget(editC);
	input2->addWidget(Comment);
	input2->addWidget(commentInput);
	inputLayout->addLayout(input2);
	//inputLayout->addLayout(inputlhs);
	/*inputLayout->addLayout(inputmhs);
	inputLayout->addLayout(inputrhs);*/
	overallLayout->addLayout(inputLayout);
	
	QPushButton* saveButton = new QPushButton("Save");
	connect(saveButton, SIGNAL(clicked()), this, SLOT(saveInput()));
	overallLayout->addWidget(saveButton);
	popWindow->setLayout(overallLayout);
	popWindow->exec();

}

void MainWindow::changeSave()
{
	string nameS = nameInput->text().toStdString();
	for(int i=0;i<(int)nameS.size();i++)
		if (nameS[i]==' ') nameS[i]='*';
	string cellS = cellInput->text().toStdString();
	string cell2S = cellInput2->text().toStdString();
	string emailS = email->text().toStdString();
	string addressInputS = addressInput->text().toStdString();
	for(int i=0;i<(int)addressInputS.size();i++)
		if (addressInputS[i]==' ') addressInputS[i]='*';
	string referralS = referralInput->text().toStdString();
	string brokerS = brokerInput->text().toStdString();
	string ssnS = ssnInput->text().toStdString();
	string incomeS = income->text().toStdString();
	string dobS = dob->text().toStdString();
	string officeS = officeInput->text().toStdString();
	//ethnicity = new QComboBox();
	//string ethnicityS=ethnicityQLineEdit->text().toStdString();
	/*if (ethnicity->currentIndex() == 0)
	{
		ethnicityS = "Asian";
	}
	else if (ethnicity->currentIndex() == 1)
	{
		ethnicityS = "AmericanIndianorAlaskaNative";
	}
	else if (ethnicity->currentIndex() == 2)
	{
		ethnicityS = "BlackorAfricanAmerican";
	}
	else if (ethnicity->currentIndex() == 3)
	{
		ethnicityS = "NativeHawaiianorOtherPacificIslander";
	}
	else if (ethnicity->currentIndex() == 4)
	{
		ethnicityS = "White";
	}*/
	//string genderS=genderQLineEdit->text().toStdString();
	/*if (gender->currentIndex() == 0)
	{
		genderS = "Male";
	}
	else if (gender->currentIndex() == 1)
	{
		genderS = "Female";
	}*/
	cout << "ohhh lala" << endl;
	string occupationS = occupation->text().toStdString();	
	string makeS = makeInput->text().toStdString();
	string color1S = colorInput2->text().toStdString();
	string color2S = colorInput->text().toStdString();
	string yearS = yearInput->text().toStdString();
	string mrspS = mrsp->text().toStdString();
	string valueInputS = valueInput->text().toStdString();
	string navigationS = navigation->text().toStdString();
	string CameraS = RCamera->text().toStdString();
	string featureS = featureInput->text().toStdString();
	
	user temp =db.users[saveKey];
	cout<<temp.displayString()<<endl;
	
	temp._cell = cellS;
	temp._other = cell2S;
	int lastloc=0;
	temp._address.clear();
	for(int i=0;i<(int)addressInputS.size();i++)
	{
		if (addressInputS[i]=='*')
		{
			temp._address.push_back(addressInputS.substr(lastloc,i-lastloc));		
			
			lastloc=i+1;

		}		
	}
	temp._address.push_back(addressInputS.substr(lastloc,addressInputS.size()-lastloc));
	cout << "after address " << endl;
	QDate selectedDate = editC->selectedDate();
	QString selectedDateQS = selectedDate.toString("yyyy.MM.dd"); 
	string selectedDateS = selectedDateQS.toStdString();
	temp._date=selectedDateS;
	
	temp._email=emailS;
	temp._Referral=referralS;
	temp._Broker=brokerS;
	temp._Office=officeS;
	temp._SSN=ssnS;
	temp._MonthlyIncome=incomeS;
	temp._DOB=dobS;
	//temp._Ethnicity=ethnicityS;
	//temp._Gender=genderS;
	temp._Occupation=occupationS;
	db.users[saveKey]=temp;
	//db.replaceUser(temp);
}

void MainWindow::saveInput()
{
	string nameS = nameInput->text().toStdString();
	for(int i=0;i<(int)nameS.size();i++)
		if (nameS[i]==' ') nameS[i]='*';
	
	string cellS = cellInput->text().toStdString();
	string cell2S = cellInput2->text().toStdString();
	string emailS = email->text().toStdString();
	string addressInputS = addressInput->text().toStdString();
	for(int i=0;i<(int)addressInputS.size();i++)
		if (addressInputS[i]==' ') addressInputS[i]='*';
	string referralS = referralInput->text().toStdString();
	string brokerS = brokerInput->text().toStdString();
	string ssnS = ssnInput->text().toStdString();
	string incomeS = income->text().toStdString();
	string dobS = dob->text().toStdString();
	string officeS = officeInput->text().toStdString();
	//ethnicity = new QComboBox();
	string ethnicityS;
	if (ethnicity->currentIndex() == 0)
	{
		ethnicityS = "Asian";
	}
	else if (ethnicity->currentIndex() == 1)
	{
		ethnicityS = "AmericanIndianorAlaskaNative";
	}
	else if (ethnicity->currentIndex() == 2)
	{
		ethnicityS = "BlackorAfricanAmerican";
	}
	else if (ethnicity->currentIndex() == 3)
	{
		ethnicityS = "NativeHawaiianorOtherPacificIslander";
	}
	else if (ethnicity->currentIndex() == 4)
	{
		ethnicityS = "White";
	}
	string genderS;
	if (gender->currentIndex() == 0)
	{
		genderS = "Male";
	}
	else if (gender->currentIndex() == 1)
	{
		genderS = "Female";
	}

	string occupationS = occupation->text().toStdString();	
	string makeS = makeInput->text().toStdString();
	string color1S = colorInput2->text().toStdString();
	string color2S = colorInput->text().toStdString();
	string yearS = yearInput->text().toStdString();
	string mrspS = mrsp->text().toStdString();
	string valueInputS = valueInput->text().toStdString();
	string navigationS = navigation->text().toStdString();
	string CameraS = RCamera->text().toStdString();
	string featureS = featureInput->text().toStdString();
	string purposeS;
	if (purpose->currentIndex() == 0)
	{
		purposeS = "Purchasing";
	}
	else if (purpose->currentIndex() == 1)
	{
		purposeS = "Leasing";
	}
	string commentS = commentInput->toPlainText().toStdString();
	QDate presentDate=QDate::currentDate();
	QString presentDateQS=presentDate.toString("yyyy.MM.dd");
	string presentDateS=presentDateQS.toStdString();
	QDate selectedDate = editC->selectedDate();
	QString selectedDateQS = selectedDate.toString("yyyy.MM.dd"); 
	string selectedDateS = selectedDateQS.toStdString();
	user newUser(nameS,presentDateS,cellS,cell2S,addressInputS);
	cout << "what's wrong " << endl;
	newUser._email=emailS;
	newUser._Referral=referralS;
	newUser._Broker=brokerS;
	newUser._Office=officeS;
	newUser._SSN=ssnS;
	newUser._MonthlyIncome=incomeS;
	newUser._DOB=dobS;
	newUser._Ethnicity=ethnicityS;
	newUser._Gender=genderS;
	newUser._Occupation=occupationS;
	newUser._callBackDate=selectedDateS;
	newUser.haveCar=true;

	//initialize car
	car addCar(makeS,color1S,color2S,yearS);
	addCar._MRSP=mrspS;
	addCar._value=valueInputS;
	addCar._navigation=navigationS;
	addCar._rearCamera=CameraS;
	addCar._feature=featureS;
	//add call history
	newUser._car=addCar;
	for (int i=0;i<(int)commentS.size();i++)
		if (commentS[i]==' ')
			commentS[i]='*';
	
	newUser.generateCallHistory(selectedDateS,addCar,purposeS,commentS);
	//newUser._callHistory.push_back(callH);
	//newUser._callHistoryNum=newUser._callHistory.size();
	newUser.check();
	db.addUser(newUser);
	saveSuccess();
}

void MainWindow::saveSuccess()
{
	popWindow->close();
	QMessageBox* msgBox = new QMessageBox;
	msgBox->setWindowTitle("Success");
	msgBox->setText("Your input has been successfully saved!");
	msgBox->setStandardButtons(QMessageBox::Cancel);
	msgBox->exec();	
}

