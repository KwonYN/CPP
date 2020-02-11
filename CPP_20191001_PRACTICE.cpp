//<Score.h>

#ifndef _SCORE_H_
#define _SCORE_H_

#define ScoreRng(S) (((S >= 0) && (S <= 100)) ? (S) : (0))

struct Score
{
private:
	char * name; // 동적 할당
	int  kor, eng, mat;
	int tot;
	double ave;
	static int classtot;
	static int num;//
public:
	Score(){ cout << "Score class make" << endl; };
	~Score(){ cout << "Bye bye" << endl; };
	void Init_Score(void);
	void InitScore(const char * irum, int k, int e, int m);
	void Clac_Score(void);
	void PrintScore(void);
	void Delete_Score(void);
	static void Print_TotScore(void);
	static Score * Input_Num(void);//
};

#endif // _SCORE_H_



// <Score.cpp>
#include <iomanip>
#include <iostream>
using namespace std;
#include "Score.h"
#define MAX_NAME	(10)

int Score::classtot = 0;
static int num = 0;

Score * Input_Num(void)
{
	int n;

	cout << "Count : ";
	cin >> num;
	
	return (new Score[num]);
}

void Score::Init_Score(void)	// ★
{
	char temp[10];
	size_t len;

	do{
		cout << "Name : ";
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cin.getline(temp, MAX_NAME);
	} while (cin.fail());

	len = ::strlen(temp);
	name = new char[++len];
	::strcpy_s(name, len, temp);

	do{
		cout << "Score(K, E, M):";
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cin >> kor >> eng >> mat;
	} while (cin.fail() || !ScoreRng(kor) || !ScoreRng(eng) || !ScoreRng(mat));

	Clac_Score();
}

void Score::InitScore(const char * irum, int k, int e, int m)
{
	size_t len;

	len = ::strlen(irum);
	name = new char[len + 1];
	::strcpy_s(name, len + 1, irum);
	kor = ScoreRng(k), eng = ScoreRng(e), mat = ScoreRng(m);

	Clac_Score();
}

void Score::Clac_Score(void)
{
	tot = kor + eng + mat;
	ave = tot / 3.0;
	Score::classtot += tot;
}

void Score::PrintScore(void)
{
	static char *grade = "FFFFFFDCBAA";

	cout << std::setw(10) << std::left << name
		<< setw(5) << grade[kor / 10] << setw(5) << grade[eng / 10] << setw(5) << grade[mat / 10]
		<< setw(5) << tot << setw(8) << std::fixed << std::setprecision(2) << ave << endl;
}

void Score::Print_TotScore(void)
{
	cout << "Total Score : " << Score::classtot << endl;
}

void Score::Delete_Score(void)	// ★
{
	delete [] name;
}



// <Main.cpp>
#include <iostream>
using namespace std;
#include "Score.h"

void main(void)
{
	Score * pstudent = (Score *)0x0;

	pstudent = Score::Input_Num();

	for (n = 0; n < num; n++){
		student[n].Init_Score();
	}

	for (n = 0; n < num; n++){
		student[n].Clac_Score();
	}

	for (n = 0; n < num; n++){
		student[n].PrintScore();
	}

	Score::Print_TotScore();

	for (n = 0; n < num; n++){
		student[n].Delete_Score();
	}

	delete [] student;
}

