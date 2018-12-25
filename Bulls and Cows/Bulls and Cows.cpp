// Bulls and Cows.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include <random>
#include <windows.h>
#include <cmath>
#include <fstream>
using namespace std;

#define DATE_CREATE 25

void clear(); // ������� �������
int randNumFunc(const int min, const int max); // ��������� ����� � ���������
string NowDate(); // ������� ������ ����

// ������ ������
enum ConsoleColor;
// ������������� ���� ������ � �������� � �������
void SetColor(int text, int background);
// ������������� ���� ������ � �������� � ������� 
void SetColor(int text, ConsoleColor/*int*/ background);

// ����
int Menu_Item(); 
void Menu_LoadGame();
void Menu_Settings(int& GodMode, int& colorText, int& colorBG);
void Menu_Author();
bool Menu_ExitGame();

// ������ - ����� �� ����� ����, ������� ���� � �����
void SearchCows(int count, int TurnDigit, int countUser);

// ���� - ����� �� ����� ����, ������� ���� � ����� � ����� � ������ �������
void SearchBulls(int count, int TurnDigit, int countUser);

// ��������� ����
void difGame(int VarDifGame, int& pointsUser, int& TurnCount);

// ���������, ������� ���������� �����
class EnemyPC
{
public:
	EnemyPC(int TurnDigit)
	{
		this->TurnDigit = TurnDigit;
	};

	// ������� ������������ ����� � �������� ������� (������:999)
	int MaxNumFromDigit(int TurnDigit)
	{
		int MaxNum = 9;
		for (int i = 1; i < TurnDigit; i++)
		{
			MaxNum = MaxNum * 10 + 9;
		}
		return MaxNum;
	}

	// ���������� ��������� ����� � �������� ����������� ����
	int RandomNumberPCFunc(int TurnDigit)
	{
		int min = pow(10, (TurnDigit - 1));
		int max = MaxNumFromDigit(TurnDigit);
		return randNumFunc(min, max);
	}

private:
	int TurnDigit;
};

// ������� ������������
class UserUser
{
public:
	UserUser(int TurnCount, int TurnDigit, int GodMode)
	{
		userName = "NoName";
		this->TurnCount = TurnCount;
		this->TurnDigit = TurnDigit;
		this->GodMode = GodMode;
	}

	void SetName(string userName)
	{
		this->userName = userName;
	}
	void SetTurnCount(int TurnCount)
	{
		this->TurnCount = TurnCount;
	}
	void SetTurnDigit(int TurnDigit)
	{
		this->TurnDigit = TurnDigit;
	}
	void SetGodMode(int GodMode)
	{
		this->GodMode = GodMode;
	}
	void SetAllPointsUser(int allPointsUser)
	{
		this->allPointsUser = allPointsUser;
	}
	void SetCountGameRound(int countGameRound)
	{
		this->countGameRound = countGameRound;
	}
	void SetTextColor(int textColor)
	{
		this->textColor = textColor;
	}
	void SetBgColor(int bgColor)
	{
		this->bgColor = bgColor;
	}
	void SetVarDifGame(int varDifGame)
	{
		this->varDifGame = varDifGame;
	}


	string GetName()
	{
		return userName;
	}
	int GetTurnCount()
	{
		return TurnCount;
	}
	int GetTurnDigit()
	{
		return TurnDigit;
	}
	int GetGodMode()
	{
		return GodMode;
	}
	int GetAllPointsUser()
	{
		return allPointsUser;
	}
	int GetCountGameRound()
	{
		return countGameRound;
	}
	int GetTextColor()
	{
		return textColor;
	}
	int GetBgColor()
	{
		return bgColor;
	}
	int GetVarDifGame()
	{
		return varDifGame;
	}


private:
	string userName;

	int TurnCount,
		TurnDigit,
		allPointsUser = 0,
		countGameRound,
		textColor,
		bgColor,
		GodMode,
		varDifGame;
};

// ��������� ������ � ���� autosave
void SaveGame(UserUser& myClass, string Date);

void LoadGame(UserUser& myClass);

int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	system("title Bulls and Cows");
	system("mode con cols=82 lines=16");
	
	// ������ ������
	{
		CONSOLE_FONT_INFOEX cfi;
		cfi.cbSize = sizeof cfi;
		cfi.nFont = 0;
		cfi.dwFontSize.X = 0;
		cfi.dwFontSize.Y = 26;
		cfi.FontFamily = FF_DONTCARE;
		cfi.FontWeight = FW_NORMAL;
		wcscpy_s(cfi.FaceName, L"Consolas");
		SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
	}

	// settings
	int TurnCount = 10; // ���������� �����
	const int TurnDigit = 4;
	int GodMode = 0;

	// settings - new game
	string userName;
	int pointsUser = 0, // ���������� �����
		turnUser = 0,
		allPointsUser = 0,
		varDifGame,
		countGameRound = 0;
	int textColor = 7,
		bgColor = 0;

	string Date = NowDate();
	UserUser User(TurnCount, TurnDigit, GodMode);

	string saveName;
	int counterPointSave;
	int answerLoadGame;

	while (true)
	{
		newGame:
		int answer = Menu_Item();

		if (answer == 1)
		{
			{
				ifstream file;
				file.open("autosave.txt");


				if (file)
				{
					clear();
					cout << "� ��� ���� ����������: ";
					file >> saveName;
					cout << saveName;
					file >> counterPointSave;
					cout << " | ����� = " << counterPointSave << endl;
					file.close();

					cout << "��������� ����������? (0 - ���, 1 - ��)\n>>> ";
					cin >> answerLoadGame;
					if (answerLoadGame == 1)
					{
						LoadGame(User);
						countGameRound = User.GetCountGameRound();
						textColor = User.GetTextColor();
						bgColor = User.GetBgColor();
						SetColor(textColor, bgColor);
						goto StartGame;
					}
				}
			}

			clear();
			cout << "����� ����" << endl << endl;
			cout << "1. ������" << endl;
			cout << "����� = 10\n����� �� ������ = 4096" << endl << endl;
			cout << "2. �������" << endl;
			cout << "����� = 5\n����� �� ������ = 8192" << endl << endl;
			cout << "3. �������" << endl;
			cout << "����� = 3\n����� �� ������ = 16384\n\n>>> ";
			cin >> varDifGame;

			User.SetVarDifGame(varDifGame);

			clear();

			User.SetTextColor(textColor);
			User.SetBgColor(bgColor);

			cout << "���� ���: ";
			cin >> userName;
			User.SetName(userName);

			User.SetTurnCount(TurnCount);
			User.SetGodMode(GodMode);

			StartGame:
			bool againGame = true;
			while (againGame == true)
			{
				EnemyPC Enemy(TurnDigit);
				int GameRandNum = Enemy.RandomNumberPCFunc(TurnDigit);

				int answerNumber;
				bool answerTrue = false;
				varDifGame = User.GetVarDifGame();
				difGame(varDifGame, pointsUser, TurnCount);

				clear();
				while (answerTrue == false)
				{
					if (User.GetGodMode() == 1)
						cout << "���������� [" << GameRandNum << "]" << endl;

					cout << "\n���� �����\n>>> ";
					cin >> answerNumber;
					cout << endl;

					if (answerNumber == GameRandNum)
					{
						clear();
						cout << "����������, " << User.GetName() << "! �� ��������! =)" << endl;

						if (User.GetAllPointsUser() >= 0)
						{
							allPointsUser = User.GetAllPointsUser();
						}
						allPointsUser = allPointsUser + pointsUser;
						User.SetAllPointsUser(allPointsUser);
						cout << "����� �����: " << User.GetAllPointsUser() << endl;

						cout << "��� = " << turnUser << " �� " << TurnCount << endl;

						countGameRound++;
						User.SetCountGameRound(countGameRound);
						cout << "����� = " << User.GetCountGameRound() << endl;
					
						SaveGame(User, Date);

						cout << "\n\n���? (0 - ���, 1 - ��)";
						cin >> againGame;
						answerTrue = true;
						turnUser = 0;
					}
					else if (answerNumber != GameRandNum)
					{
						clear();
						cout << "������: ";
						SearchCows(GameRandNum, TurnDigit, answerNumber);
						cout << endl;

						cout << "����: ";
						SearchBulls(GameRandNum, TurnDigit, answerNumber);
						cout << endl;

						turnUser++;
						cout << "��� = " << turnUser << " �� " << TurnCount << endl;
						pointsUser /= 2;
						cout << "���� = " << (pointsUser) << endl;

						if (turnUser == TurnCount)
						{
							clear();
							cout << User.GetName() << "! �� ��������� :(" << endl << endl;
							cout << "����� = " << turnUser << " �� " << TurnCount << endl;
							pointsUser = 0;
							answerTrue = true;

							if (User.GetAllPointsUser() > 0)
							{
								allPointsUser = User.GetAllPointsUser();
							}
							allPointsUser += pointsUser;
							User.SetAllPointsUser(allPointsUser);
							cout << "����� �����: " << User.GetAllPointsUser() << endl;

							countGameRound++;
							User.SetCountGameRound(countGameRound);
							cout << "����� = " << User.GetCountGameRound() << endl;

							SaveGame(User, Date);

							int againGame;
							cout << "���? (0 - ���, 1 - ��)";
							cin >> againGame;
							if (againGame == 0)
							{
								goto newGame;
							}
							turnUser = 0;
						}
					}

				}
			}
		}
		else if (answer == 2)
		{
			Menu_LoadGame();

			ifstream file;
			file.open("autosave.txt");

			if (file)
			{
				clear();
				cout << "� ��� ���� ����������: ";
				file >> saveName;
				cout << saveName;
				file >> counterPointSave;
				cout << " | ����� = " << counterPointSave << endl;
				file.close();

				cout << "��������� ����������? (0 - ���, 1 - ��)\n>>> ";
				cin >> answerLoadGame;
				if (answerLoadGame == 1)
				{
					LoadGame(User);
					countGameRound = User.GetCountGameRound();
					textColor = User.GetTextColor();
					bgColor = User.GetBgColor();
					SetColor(textColor, bgColor);
					goto StartGame;
				}
			}
			else
			{
				cout << "���������� �� �������..." << endl;
				system("pause");
			}
		}
		else if (answer == 3)
		{
			Menu_Settings(GodMode, textColor, bgColor);
		}
		else if (answer == 4)
		{
			Menu_Author();
		}
		else if (answer == 5)
		{
			clear();
			cout << "���� ����: ������� 4-������� ����� �� ������������ ���������� �������." << endl;
			cout << "������ - ����� �������, �� � ������� � ���" << endl;
			cout << "���� - ��������� � �����, � � �������." << endl;
			cout << "��������, ���� �������� ����� �1234�, � �� ��������� �6531�" << endl;
			cout << "�� ����������� ����� 1 ������ (����� �1�) � 1 ��� (����� �3�)." << endl << endl;
			system("pause");
		}
		else if (answer == 6)
		{
			break;
		}
	}

	clear();
	cout << "����..." << endl << endl;
	Menu_ExitGame(); // ������� �������

    return 0;
}

// �������

int Menu_Item()
{
	clear();

	cout << " _____ _____ _ _ _ _____    _____ _____ ____     _____ _____ __    __    _____ " << endl;
	cout << "|     |     | | | |   __|  |  _  |   | |    \\   | __  |  |  |  |  |  |  |   __|" << endl;
	cout << "|   --|  |  | | | |__   |  |     | | | |  |  |  | __ -|  |  |  |__|  |__|__   |" << endl;
	cout << "|_____|_____|_____|_____|  |__|__|_|___|____/   |_____|_____|_____|_____|_____|" << endl;
	cout << "                                                                               " << endl;

	// ��������� ������� ����
	int variant;
	cout << setw(30) << "����\n" << endl;
	cout << setw(34) << "1. ����� ����\n"
		<< setw(38) << "2. ��������� ����\n"
		<< setw(33) << "3. ���������\n"
		<< setw(30) << "4. ������\n"
		<< setw(31) << "5. �������\n"
		<< setw(29) << "6. �����\n" << endl;
	cout << ">>> ";
	cin >> variant;
	return variant;
}

// 2
void Menu_LoadGame()
{
	clear();
	cout << "�������� ����������\n" << endl;
}

// 3
void Menu_Settings(int& GodMode, int& colorText, int& colorBG)
{
	clear();
	cout << "��������� ����\n" << endl;
	cout << "������ ������:" << endl;
	cout << "0 - ������\n1 - �������\n2 - �������\n3 - �����\n4 - �������\n7 - �����\n15 - �����\n\n";
	cout << "1. ���� ������: ";
	cin >> colorText;
	cout << "2. ��� ��� �������: ";
	cin >> colorBG;
	cout << "3. ����� ���� (0 - ���, 1 - ��): ";
	cin >> GodMode;
	cout << endl;
	SetColor(colorText, colorBG);
}

// 4
void Menu_Author()
{
	clear();
	cout << "����� ���� - ������ ����\n���� ��������: " << DATE_CREATE << " ������ 2018 ����\n" << endl;
	system("pause");
}

// 5
bool Menu_ExitGame()
{
	return EXIT_SUCCESS;
}

// �������
void SearchCows(int count, int TurnDigit, int countUser)
{
	int delitel = 1,
		countNum,
		procNum;

	int delitelUser = 1,
		countNumUser,
		procNumUser;

	int counterMas = 0;

	int *arrNum = new int[TurnDigit]; // ��������� ������ ��� �������
	int k = 0;
	for (int i = 0; i < TurnDigit; i++)
	{
		arrNum[i] = -1;
	}


	for (int i = 1; i < TurnDigit + 1; i++)
	{
		procNum = pow(10, i);
		if (i > 1)
			delitel = pow(10, i - 1);
		countNum = (count % procNum / delitel);

		for (int j = 1; j < TurnDigit + 1; j++)
		{
			procNumUser = pow(10, j);
			if (j > 1)
				delitelUser = pow(10, j - 1);
			countNumUser = (countUser % procNumUser / delitelUser);

			int haveCount = 0;
			if (countNumUser == countNum)
			{
				// ��������, ���������� �� ��������� ����� � �������
				for (int k = 0; k < TurnDigit; k++)
				{

					if (arrNum[k] == countNum)
					{
						break;
					}
					// ���������, ���� �� ����� � �������
					if (arrNum[k] != countNum)
					{
						for (int kk = 0; kk < TurnDigit; kk++)
						{
							if (arrNum[kk] == countNum)
							{
								haveCount = 1;
							}
						}
						if (haveCount == 0)
						{
							arrNum[counterMas] = countNum;
							counterMas++;
							break;
						}
					}
					haveCount = 0;
				}
				// cout << countNum << " ";
			}
		}
		delitelUser = 1;
	}

	// ����� ������� � ��������
	for (int i = 0; i < TurnDigit; i++)
	{
		if (arrNum[i] > -1)
		{
			cout << arrNum[i] << " ";
		}
	}

	delete[] arrNum; // ������� ������
}
void SearchBulls(int count, int TurnDigit, int countUser)
{
	// ������ ��� ����� ������������
	int *arrNumUser = new int[TurnDigit];
	for (int i = 0; i < TurnDigit; i++)// ���������� ����� � �����
	{
		arrNumUser[i] = countUser % 10;
		countUser /= 10;
	}

	// ������ ��� ����� ��
	int *arrNumPC = new int[TurnDigit];
	for (int i = 0; i < TurnDigit; i++)// ���������� ����� � �����
	{
		arrNumPC[i] = count % 10;
		count /= 10;
	}

	// �������� �� ���������� �� �������
	for (int i = TurnDigit - 1; i >= 0; i--)
	{
		if (arrNumUser[i] == arrNumPC[i])
		{
			cout << arrNumUser[i];
		}
		else
		{
			cout << '*';
		}
	}

	// ������� ������
	delete[] arrNumUser;
	delete[] arrNumPC;
}
void difGame(int VarDifGame, int& pointsUser, int& TurnCount)
{
	if (VarDifGame == 1)// ������
	{
		pointsUser = 4096;
		TurnCount = 10;
	}
	else if (VarDifGame == 2) // �������
	{
		pointsUser = 8192;
		TurnCount = 5;
	}
	else if (VarDifGame == 3) // �������
	{
		pointsUser = 16384;
		TurnCount = 3;
	}
	else
	{
		cout << "������! ����������� ������� ���������!" << endl;
	}
}


void SaveGame(UserUser& myClass, string Date)
{
	// ���, ����� �����, ���������� �����, ���������� ����, ����� ����, ���������� �������
	// ���� ������, ���� ����, ������� ���������
	ofstream inFile("autosave.txt");
	if (!inFile) cout << "����! �� ������� ������� ���� ����������!";
	// inFile << Date << endl;
	inFile << myClass.GetName() << endl;
	inFile << myClass.GetAllPointsUser() << endl;
	inFile << myClass.GetTurnCount() << endl;
	inFile << myClass.GetTurnDigit() << endl;
	inFile << myClass.GetGodMode() << endl;
	inFile << myClass.GetCountGameRound() << endl;
	inFile << myClass.GetTextColor() << endl;
	inFile << myClass.GetBgColor() << endl;
	inFile << myClass.GetVarDifGame() << endl;
	inFile.close();
}
void LoadGame(UserUser& myClass)
{
	string name;

	ifstream outFile("autosave.txt");
	int i = 0;
	while (i == 0)
	{
		outFile >> name;
		cout << name << endl;
		i++;
	}

	myClass.SetName(name);

	int num;

	while (i <= 9)
	{
		outFile >> num;

		if (i == 1)
		{
			i++;
		}

		if(i == 2)
		{
			cout << num << endl;
			myClass.SetAllPointsUser(num);
			i++;
		}
		else if (i == 3)
		{
			cout << num << endl;
			myClass.SetTurnCount(num);
			i++;
		}
		else if (i == 4)
		{
			cout << num << endl;
			myClass.SetTurnDigit(num);
			i++;
		}
		else if (i == 5)
		{
			cout << num << endl;
			myClass.SetGodMode(num);
			i++;
		}
		else if (i == 6)
		{
			cout << num << endl;
			myClass.SetCountGameRound(num);
			i++;
		}
		else if (i == 7)
		{
			cout << num << endl;
			myClass.SetTextColor(num);
			i++;
		}
		else if (i == 8)
		{
			cout << num << endl;
			myClass.SetBgColor(num);
			i++;
		}
		else if (i == 9)
		{
			cout << num << endl;
			myClass.SetVarDifGame(num);
			i++;
		}
	}

	outFile.close();
}


// ���������������
int randNumFunc(const int min, const int max)
{
	random_device rd;
	mt19937 randomAllTime(rd());
	uniform_int_distribution<int> randomNumPointsMinMax(min, max);
	int randomNumPoints = randomNumPointsMinMax(randomAllTime);

	return randomNumPoints;
}
void clear() {
	COORD topLeft = { 0, 0 };
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;

	GetConsoleScreenBufferInfo(console, &screen);
	FillConsoleOutputCharacterA(
		console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	FillConsoleOutputAttribute(
		console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	SetConsoleCursorPosition(console, topLeft);
};
enum ConsoleColor
{
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};
void SetColor(int text, int background)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
};
void SetColor(int text, ConsoleColor/*int*/ background)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}
string NowDate()
{
	char buffer[80];
	time_t seconds = time(NULL);
	tm* timeinfo = localtime(&seconds);
	char* format = "%d %B | %Y | %I:%M:%S";
	strftime(buffer, 80, format, timeinfo);
	return buffer;
}
