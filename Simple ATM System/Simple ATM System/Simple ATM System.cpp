#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;
const string ClientsFileName = "Clients.txt";
void Login();
void ShowATMMainMenue();
struct sClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool MarkForDelete = false;
};




sClient CurrentClient;



vector<string> SplitString(string S1, string Delim)
{
	vector<string> vString;
	short pos = 0;
	string sWord; // define a string variable
	// use find() function to get the position of the delimiters
	while ((pos = S1.find(Delim)) != std::string::npos)
	{
		sWord = S1.substr(0, pos); // store the word
		if (sWord != "")
		{
			vString.push_back(sWord);
		}
		S1.erase(0, pos + Delim.length()); /* erase() until
		positon and move to next word. */
	}
	if (S1 != "")
	{
		vString.push_back(S1); // it adds last word of the string.
	}
	return vString;
}

sClient ConvertClientLinetoRecord(string Line, string Seperator = "#//#")
{
	sClient Client;
	vector<string> vClientData;
	vClientData = SplitString(Line, Seperator);
	Client.AccountNumber = vClientData[0];
	Client.PinCode = vClientData[1];
	Client.Name = vClientData[2];
	Client.Phone = vClientData[3];
	Client.AccountBalance = stod(vClientData[4]);

	return Client;
}

string ConvertClientRecordToLine(sClient Client, string Seperator = "#//#")
{
	string stClientRecord = "";
	stClientRecord += Client.AccountNumber + Seperator;
	stClientRecord += Client.PinCode + Seperator;
	stClientRecord += Client.Name + Seperator;
	stClientRecord += Client.Phone + Seperator;
	stClientRecord += to_string(Client.AccountBalance);
	return stClientRecord;

}

vector <sClient> LoadCleintsDataFromFile(string FileName) {
	vector <sClient> vClients;
	fstream MyFile;
	MyFile.open(FileName, ios::in);//read Mode
	if (MyFile.is_open())
	{
		string Line;
		sClient Client;
		while (getline(MyFile, Line))
		{
			Client = ConvertClientLinetoRecord(Line);
			vClients.push_back(Client);
		}
		MyFile.close();
	}
	return vClients;
}


vector <sClient> SaveCleintsDataToFile(string FileName, vector<sClient> vClients)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out);//overwrite
	string DataLine;
	if (MyFile.is_open())
	{
		for (sClient C : vClients)
		{
			if (C.MarkForDelete == false)
			{
				//we only write records that are not marked for delete.
				DataLine = ConvertClientRecordToLine(C);
				MyFile << DataLine << endl;
			}
		}
		MyFile.close();
	}
	return vClients;
}

bool DepositBalanceToClient(double Amount, vector <sClient>& vClients)
{
	char Answer = 'n';
	cout << "\n\nAre you sure you want perfrom this transaction?y / n ? ";
	cin >> Answer;
	if (Answer == 'y' || Answer == 'Y')
	{
		for (sClient& C : vClients)
		{
			if (C.AccountNumber == CurrentClient.AccountNumber)
			{
				C.AccountBalance += Amount;
				CurrentClient.AccountBalance = C.AccountBalance;
				SaveCleintsDataToFile(ClientsFileName, vClients);
				cout << "\n\nDone Successfully. New balance is: "
					<< C.AccountBalance;
				return true;
			}
		}
		return false;
	}
		return false;
}


void ShowDepositScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tDeposit Screen";
	cout << "\n-----------------------------------\n";
	
	double Amount 
		= 0;
	cout << "\nPlease enter deposit amount? ";
	cin >> Amount;
	vector <sClient> vClients =LoadCleintsDataFromFile(ClientsFileName);
	DepositBalanceToClient(Amount,vClients );
}


enum enQuickWithdrawMenueOptions {
	e20 = 1, e50 = 2, e100 = 3,
	e200 = 4, e400= 5,e600= 6,e800= 7,e1000= 8,eExit=9
};
short ReadQuickWithDrawScreenMenueOption(){
	cout << "Choose what to withdraw from[1] to [8] ? ";
	short Choice = 0;
	cin >> Choice;
	return Choice;
}

 void PerfromQuickWithDrawMenueOption(enQuickWithdrawMenueOptions QuickWithdrawMenueOptions, double &Amount) {
	switch (QuickWithdrawMenueOptions) {
		
	case enQuickWithdrawMenueOptions::e20:
	{
		Amount = 20;
		break;
	}
	case enQuickWithdrawMenueOptions::e50:
	{
		Amount = 50;
		break;
	}
	case enQuickWithdrawMenueOptions::e100:
	{
		Amount = 100;
		break;
	}
	case enQuickWithdrawMenueOptions::e200:
	{
		Amount = 200;
		break;
	}
	case enQuickWithdrawMenueOptions::e400:
	{
		Amount = 400;
		break;
	}
	case enQuickWithdrawMenueOptions::e600:
	{
		Amount = 600;
		break;
	}
	case enQuickWithdrawMenueOptions::e800:
	{
		Amount = 800;
		break;
	}
	case enQuickWithdrawMenueOptions::e1000:
	{
		Amount = 1000;
		break;
	}
	case enQuickWithdrawMenueOptions::eExit: {
		ShowATMMainMenue();
	}

	}

}

void ShowQuickWithDrawScreen() {

	 vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
	 double Amount = 0;
	
	do{
	cout << "\n-----------------------------------\n";
	cout << "\t Quick Withdraw";
	cout << "\n-----------------------------------\n";
	cout << "\t[1] 20\t[2] 50\n";
	cout << "\t[3] 100\t[4] 200\n";
	cout << "\t[5] 400\t[6] 600\n";
	cout << "\t[7] 800\t[8] 1000\n";
	cout << "\t[9] Exit\n";
	cout << "\n-----------------------------------\n";
	cout << "Your Balance is " << CurrentClient.AccountBalance<<endl;
	PerfromQuickWithDrawMenueOption((enQuickWithdrawMenueOptions)ReadQuickWithDrawScreenMenueOption(), Amount);
	
		if (Amount > CurrentClient.AccountBalance){
			cout << "\nThe amount exceeds your balance, Make anthor choice.\n";
			cout << "Press anykey to continue...\n";
			system("pause>0");
			system("cls");
	}
	} while (Amount > CurrentClient.AccountBalance);

	DepositBalanceToClient(Amount *-1, vClients);

}



void ShowNormalWithDrawScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tNormal Withdraw Screen";
	cout << "\n-----------------------------------\n";

	vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);


	int Amount = 0;
	do{
		if(Amount > CurrentClient.AccountBalance){
			cout << "\nAmount Exceeds the balance, you can withdraw up to : " << CurrentClient.AccountBalance << endl;
		}
		
		cout << "Enter an amount multiple of 5's ? ";
		cin >> Amount;
	} while (Amount > CurrentClient.AccountBalance || Amount % 5 != 0);

	DepositBalanceToClient(Amount *-1, vClients);
}


void ShowCheckBalance() {
	cout << "\n-----------------------------------\n";
	cout << "\tCheck Balance Screen";
	cout << "\n-----------------------------------\n";
	cout << "Your Balance is "<< CurrentClient.AccountBalance;

}
void GoBackToMainMenue()
{
	cout << "\n\nPress any key to go back to Main Menue...";
	system("pause>0");
	ShowATMMainMenue();
}
short ReadATMMainMenueOption()
{
	cout << "Choose what do you want to do? [1 to 5]? ";
	short Choice = 0;
	cin >> Choice;
	return Choice;
}
enum enTransactionsMenueOptions {
	eQuickWithdraw =1,eNormalWithdraw = 2, eDeposit = 3,
	eCheckBalance = 4, eLogout = 5
};

void PerfromATMMainMenueOption(enTransactionsMenueOptions TransactionMenueOption)
{
	switch (TransactionMenueOption)
	{
	case enTransactionsMenueOptions::eQuickWithdraw:
	{
		system("cls");
		ShowQuickWithDrawScreen();
		GoBackToMainMenue();
		break;
	}
	case enTransactionsMenueOptions::eNormalWithdraw:
	{
		system("cls");
		ShowNormalWithDrawScreen();
		GoBackToMainMenue();
		break;
	}
	case enTransactionsMenueOptions::eDeposit:
	{
		system("cls");
		ShowDepositScreen();
		GoBackToMainMenue();
		break;
	}
	case enTransactionsMenueOptions::eCheckBalance:
	{
		system("cls");
		ShowCheckBalance();
		GoBackToMainMenue();
		break;
	}
	case enTransactionsMenueOptions::eLogout:
	{
		Login();
	}
	}
}
void ShowATMMainMenue()
{
	system("cls");
	cout << "===========================================\n";
	cout << "\t\tTransactions Menue Screen\n";
	cout << "===========================================\n";
	cout << "\t[1] Quick Withdraw.\n";
	cout << "\t[2] Normal Withdraw.\n";
	cout << "\t[3] Deposit.\n";
	cout << "\t[4] Check Balances.\n";
	cout << "\t[5] Logout.\n";
	cout << "===========================================\n";
	PerfromATMMainMenueOption((enTransactionsMenueOptions)ReadATMMainMenueOption());
}




string ReadClientAccountNumber()
{
	string AccountNumber = "";
	cout << "\nPlease enter AccountNumber? ";
	getline(cin>>ws,AccountNumber);
	return AccountNumber;
}
string ReadClientPinCode()
{
	string PinCode = "";
	cout << "\nPlease enter PinCode? ";
	getline(cin >> ws, PinCode);
	return PinCode;
}



bool FindClientByAccountNumberAndPinCode(vector <sClient> vClient, string AccountNumber, string PinCode, sClient& User) {


	for (sClient & u : vClient) {
		if (AccountNumber == u.AccountNumber && PinCode == u.PinCode) {

			User = u;
			return true;

		}

	}
	return false;

}

	



void Login() {

	vector <sClient> vClient = LoadCleintsDataFromFile(ClientsFileName);
	bool LoginFalid = false;
	string AccountNumber, PinCode;

	do {

		system("cls");
		cout << "==================================\n";
		cout << "\tLoginScreen\n";
		cout << "==================================\n";

		if (LoginFalid) {
			cout << "Invalid AccountNumber/PinCode!\n";
		}

		AccountNumber = ReadClientAccountNumber();
		PinCode = ReadClientPinCode();


		LoginFalid = !FindClientByAccountNumberAndPinCode(vClient, AccountNumber, PinCode,CurrentClient);
	} while (LoginFalid);


	
	ShowATMMainMenue();


}


int main()
{
	Login();



	return 0;
}
