#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <string.h>
using namespace std;

class Num{
public:
	Num(int numerator=0, int denominator = 1){
		a = numerator;
		b = denominator;
		int p;
		p = (a + b - abs(a - b)) / 2;
		for (int i = 2; i <= p; ++i){
			if (a%i == 0 && b%i == 0){
				a /= i;
				b /= i;
				i = 2;
			}
		}
	}

	int getNume(){
		return a;
	}

	int getDeno(){
		return b;
	}

	void transFrac(Num &fra){
		int p;
		p = (fra.a + fra.b - abs(fra.a - fra.b)) / 2;
		for (int i = 2; i <= p; ++i){
			if (fra.a%i == 0 && fra.b%i == 0){
				fra.a /= i;
				fra.b /= i;
				i = 2;
			}
		}

	}

	Num operator+(const Num rhs){
		Num result;
		result.b = b*rhs.b;
		result.a = a*rhs.b + rhs.a*b;
		transFrac(result);
		return result;
	}

	Num operator-(const Num rhs){
		Num result;
		result.b = b*rhs.b;
		result.a = a*rhs.b - rhs.a*b;
		transFrac(result);
		return result;
	}

	Num operator*(const Num rhs){
		Num result;
		result.a = a*rhs.a;
		result.b = b*rhs.b;
		transFrac(result);
		return result;
	}

	Num operator/(const Num rhs){
		Num result;
		result.a = a*rhs.b;
		result.b = b*rhs.a;
		transFrac(result);
		return result;
	}

	bool operator==(const Num rhs){
		if (a == rhs.a&&b == rhs.b)
			return true;
		else
			return false;
	}


	Num operator=(const int rhs){
		a = rhs;
		b = 1;
		return *this;
	}
	Num operator=(const Num rhs){
		a = rhs.a;
		b = rhs.b;
		return *this;
	}
private:
	int a;
	int b;

};

void setProbAndAns(int proNum, int proLevel){
	ofstream ofsQues;
	ofstream ofsAnsw;
	ofsQues.open("Questions.txt", ofstream::out);
	ofsAnsw.open("Answer.txt", ofstream::out);
	char Expression[100];
	char Answer[10];
	srand((unsigned)time(NULL));
	int a, b, c, d, e1, e2, e3;
	Num lhs, rhs, res;
	for (int i = 0; i < proNum; ++i){
		vector<Num>A(proNum);
		vector<Num>B(proNum);
		vector<Num>C(proNum);
		vector<Num>D(proNum);  //4 position of number
		vector<Num>R(proNum);  //result
		a = rand() % proLevel;
		b = rand() % proLevel+1;
		c = rand() % proLevel;
		d = rand() % proLevel+1;
		A[i] = a;
		B[i] = b;
		C[i] = c;
		D[i] = d;

		vector<char>E1(proNum);
		vector<char>E2(proNum);
		vector<char>E3(proNum);
		e1 = rand() % 4;
		e2 = rand() % 2;
		e3 = rand() % 4;

		switch (e1){
		case 0:
			E1[i] = '+';
			lhs = A[i] + B[i];
			break;
		case 1:
			E1[i] = '-';
			lhs = A[i] - B[i];
			break;
		case 2:
			E1[i] = '*';
			lhs = A[i] * B[i];
			break;
		case 3:
			E1[i] = '/';
			lhs = A[i] / B[i];
			break;
		}
		switch (e3){
		case 0:
			E3[i] = '+';
			rhs = C[i] + D[i];
			if (e2 == '-')
				rhs = C[i] - D[i];
			break;
		case 1:
			E3[i] = '-';
			rhs = C[i] - D[i];
			if (e2 == '-')
				rhs = C[i] + D[i];
			break;
		case 2:
			E3[i] = '*';
			rhs = C[i] * D[i];
			break;
		case 3:
			E3[i] = '/';
			rhs = C[i] / D[i];
			break;
		}
		switch (e2){
		case 0:
			E2[i] = '+';
			res = lhs + rhs;
			break;
		case 1:
			E2[i] = '-';
			res = lhs - rhs;
			break;
		}
		if (res.getNume() < 0){
			i -= 1;
			continue;
		}
		else{
			R[i] = res;
		}
		//ganrantee no repeat
		int flag = 0;
		for (int j = 0; j < i; ++j){
			if (R[i] == R[j]){
				flag = 1;
				break;
			}
		}
		if (flag == 1){
			i -= 1;
			continue;
		}

		sprintf_s(Expression, "%d %c %d %c %d %c %d = ", A[i].getNume(), E1[i], B[i].getNume(), E2[i], C[i].getNume(), E3[i], D[i].getNume());
		if (R[i].getDeno() == 1||R[i].getNume() == 0)
			sprintf_s(Answer, "%d:%d", i + 1, R[i].getNume());
		else
			sprintf_s(Answer, "%d:%d/%d", i + 1, R[i].getNume(), R[i].getDeno());

		ofsQues << Expression << endl;;
		ofsAnsw << Answer << endl;
	}

	ofsQues.close();
	ofsAnsw.close();

}

bool isCorrect(int a,int b,char *str1,char *str2){
	cout << str1 << " " << str2 << endl;
	for (; str1[a] != '\0'&&str2[b] != '\0';a++,b++){
		cout << str1[a] << " " << str2[b] << endl;
		if (str1[a] != str2[b])
			return false;
	}
	if (str1[a] == '\0'&&str2[b] == '\0')
		return true;
	else
		return false;
}

void setGrade(int proNum){
	ifstream ifsQus;
	ifstream ifsAns;
	ofstream ofsGra;
	ifsQus.open("Questions.txt",ifstream::in);
	ifsAns.open("Answer.txt",ifstream::in);
	ofsGra.open("Grade.txt",ofstream::app);
	char ques[100];
	char answ[10];
	char grade[500];
	int gra;
	vector<int>right(proNum);
	int i,j;
	int a, b;
	for (i = 0; i < proNum; ++i)
		right[i] = 0;
	for (i = 0,j=0; i < proNum;++i){
		ifsQus.getline(ques, 100);
		ifsAns.getline(answ, 10);
		for (a = 0; ques[a] != '='; ++a)
			;
		for (b = a; ques[b] != ' '; ++b)
			;
		for (a = 0; answ[a] != ':'; ++a)
			;


		if (isCorrect(b+1,a+1,ques,answ)){
			j++;
			right[i] = 1;
		}
	}
	vector<int>rightPos(j);
	for (i = 0,j=0; i < proNum; ++i){
		if (right[i] == 1){
			rightPos[j] = i;
			++j;
		}
	}
	char num[10];
	sprintf_s(grade,"Correct:%d( ",j);
	for (i = 0; i < j; ++i){
		sprintf_s(num,"%d ",rightPos[i]+1);
		strcat_s(grade,num);
	}
	strcat_s(grade, ")");

	ofsGra << grade << endl;
	ifsQus.close();
	ifsAns.close();
	ofsGra.close();
}


int main()
{
	int option;
	int proNum;
	int proLevel;

	cout << "Please choose the number of the problem:" << endl;
	cout << "1.10                               2.100" << endl;
	cout << "3.200                              4.500" << endl;
	cin >> option;
	switch (option){
	case 1:
		proNum = 10;
		break;
	case 2:
		proNum = 100;
		break;
	case 3:
		proNum = 200;
		break;
	case 4:
		proNum = 500;
		break;
	default:
		proNum = 50;
		break;
	}
	cout << "Please choose the level of the problem:" << endl;
	cout << "1.10                               2.50" << endl;
	cout << "3.100                                  " << endl;
	cin >> option;
	switch (option){
	case 1:
		proLevel = 10;
		break;
	case 2:
		proLevel = 50;
		break;
	case 3:
		proLevel = 100;
		break;
	default:
		proLevel = 30;
		break;
	}

	setProbAndAns(proNum, proLevel);
	cout << "Please write the  answers in the Questions.txt and save." << endl;
	cout << "Enter 1 to get the Grade" << endl;
	cin >> option;
	while (option != 1){
		cout << "Please enter again:" << endl;
		cin >> option;
	}
	setGrade(proNum);
	cout << "Open the Grade.txt to check your grade!" << endl;
	Sleep(10000);

	return 0;
}

