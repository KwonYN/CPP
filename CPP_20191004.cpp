/***********************************************************************/
/*							[ 2019.10.04 금 ]						   */
/***********************************************************************/


// 상속 기본
#if 0
#include <iostream>
using namespace std;

class A	// 선배들이 만든 코드
{
	int no;
protected:
	char ch;
public:
	int sum;
	void sub(void);
};

void A::sub(void)
{
	cout << no << ch << endl;
}

class B : public A	// 오늘날 후배들이 만든 코드
{
	//A::sum;	// 이런 경우 가능!
public:
	A::ch;		// protected 권한이었던 것을 public으로 변경 가능!(private 였던 것을 변경하진 못함!)
};

void main(void)
{
	B bb;
	cout << sizeof(bb) << endl;	// A클래스(기반/부모 클래스)의 크기 그대로!(12B)

	//bb.no = 5;					// 부모의 private 멤버에 대한 직접적 접근 불가 (외부에서)
	//bb.ch = 'A';					// 부모의 protected 멤버에 대한 직접적 접근 제한 (외부에서)
	bb.sum = 100;
	// 그렇다면 부모 멤버에 대한 접근 권한 변경 가능한가? 가능!! : public: A::ch; 라고 선언해주면 가능!
	bb.ch = 'A';// 이렇게! 하지만 부모의 private 멤버를 public으로 바꿀 수 없어!!!!
}
#endif

// 파생클래스의 생성자, 소멸자 함수
#if 01
#include <iostream>
using namespace std;

class A	// 선배들이 만든 코드
{
	int no;
protected:
	char ch;
public:
	A(){ cout << "A def. cons..." << endl; };
	A(int n) : no(n) { cout << "A int cons..." << endl; };
	int sum;
	void sub(void);
};

void A::sub(void)
{
	cout << no << ch << endl;
}


class B : public A	// 오늘날 후배들이 만든 코드
{
	char * str;
public:
	B();
	B(char * s);
	B(int n, char c, char * s);	// 자식 클래스의 생성자에는 컴파일러가 자동적으로 :초기화가 들어감! : A()로
};

B::B()	// : A() - 단, A에 기본 생성자가 아닌 다른 생성자만 만들었다면, 이 기본 생성자 함수가 안 만들어지고, 호출되지 않음!!
{
	cout << "B def. cons..." << endl;
}

B::B(char * s)	// : A()
{
	cout << "B char. * cons..." << endl;
}

B::B(int n, char c, char * s)	// : A()
{
	cout << "B int, char., char. * cons..." << endl;
}


void main(void)
{
	B bb("Seoul");	// A(부모/기반) 클래스의 생성자 먼저 호출됨! <-> 소멸자는 생성자 함수의 역순으로(자식/파생 클래스의 소멸자 먼저 호출됨!)
	cout << sizeof(bb) << endl;	// 부모 크기와 char *(4B)를 더한 16B가 나옴!
}
#endif




// string 클래스
#if 0
#include <string>
#include <iostream>
using namespace std;

class mstring : public string
{
// 1) 파생 클래스에서 필요한 멤버 함수/변수 만들기
// 2) 파생 클래스에 맞는 생성자, 소멸자 함수 만들기

	string::c_str;
public:
	mstring();
	mstring(const char * str);
	operator const char *(void) const; // 멤버 데이터를 변경하지 않으므로 const 타입 함수
										// "const char *"이 필요하면 호출됨!!
};

mstring::mstring()
{

}

mstring::mstring(const char * str) : string(str)	// 부모에게 일임 가능하면 일임!
{
}

mstring::operator const char *(void) const
{
	return c_str();		// 파생 클래스 private로 "string::c_str;" (함수 이름만 적으면 됨!).... 함부로 못 씀
}

// 전역함수s
void Gfunc(char * str)
{
	
}

void Gsub(const char * s)
{
	cout << s << endl;
}

void main(void)
{
	string str("Seoul");	// ()내의 문자열로 생성자를 호출하여 초기화(?)하고, 직접 동적할당까지도 하는!
	cout << str << endl;

	Gsub(str.c_str());	// str은 string 타입이고, 인자로는 cahr *가 들어가야 함!
						// string은 형변환 함수가 없다고 함!
						// string 클래스에는 c_str 함수가 있어서 "주소"를 부여 받음!
	cout << ::strlen(str.c_str()) << endl;


	mstring mstr("Seoul");
	cout << mstr << endl;

	Gsub(mstr);
	cout << ::strlen(mstr) << endl;
	Gfunc( (char *)(const char *)mstr ); // char *로 형변환 해주는 함수를 더 만들어주는 방법도 있지만, 
					// const가 없다는 것은 "변경하겠다"라고 명시하는 것이므로 아예 접근을 못하도록 
					// 안 만드는 것이 나은 경우가 많음.
					// 굳이 넘기고 싶으면.. 더블 캐스팅으로 직접 해서 넘기는 것이,,,!

}

#endif





// 3.3 기반클래스의 포인터와 참조 (부모 포인터...??)
#if 0
#include <typeinfo>
#include <iostream>
using namespace std;

class A
{
	int no;
public:
	A(){};
	A(int n) : no(n) {};
	virtual ~A(){ cout << "A Des..." << endl; }
	void sub(void) const { cout << no << endl; };
};


class B : public A
{
	char ch;
public:
	B(){};
	B(char c, int n) : A(n), ch(c) {};
	~B(){ cout << "B Des..." << endl; };
	void func(void);

};

void B::func(void)
{
	cout << ch << " ";
	sub();	// public으로 A로부터 상속을 받았기 때문에 A에서의 public 멤버를 자식이 public으로 접근 가능!
}

// 전역함수
void Gsub(A * p)	// 부모의 포인터는 자식을 가리킬 수 있기 땜누에 A도 B도 가리키게 하기 위해서는 A* 타입으로
{
	p->sub();

	// C++에서는 RTTI(RunTime Type Information)을 제공.. 런타임에도 타입을 확인한다는 것. C에서는 컴파일 타임에만 하던 것을..
	if (typeid(*p) == typeid(B))
	{
		((B *)p)->func();	// B로부터 만들어진 개체만 이 함수를 사용하게 만들고 싶어!
	}
}

void main(void)
{
	/*
	B bb('A', 5);
	bb.func();
	*/

	//A * p = new B;	// B * p = new B;가 기본이겠지만, 형 변환 안 하더라도 A로도 가능!! 상속 받았잖아?
					// 부모가 자식의 포인터로 사용될 수 없는 경우? : void *인 경우(알 수 없는 데이터 타입인 경우!!)
					// 훗날(미래에) 만들어질 B가 어떤 것인지 모르기 때문에!...........
					// 하지만 잘 사용하지는 않는다고.. 위험성이 있때....ㅋㅋ : 자식의 소멸자가 수행되지 않음!
					// A 클래스는 컴파일 타임에 어떤 것인지 알 수 있지만, B는 지정되지 않음(?)
					// 그렇기 때문에 딜리트 할 때도 B는 모르므로 A를 가리키게 되는 것!
					// => virtual ~A();라고 선언해주면, delete 시에 ~A가 가상이므로 컴파일 타임에 이 소멸자와 연결되지 않음!
					//    근데 runtime 때 B로부터 만들어질 것이므로 B의 소멸자를 실행하고, 거기서 부모의 소멸자를 불러 부모의 소멸자도 실행됨...
					//   - 동적 바인딩 개념!! (런타임에 결정되기 때문에 속도는 조금 느려질 수 있겠지만, 이런 경우 효율적!)

	//A * p = new B;
	//delete p;

	A aa(5);
	B bb('A', 10);
	Gsub(&aa);	// 5가 출력될 것
	Gsub(&bb);	// 10이 출력될 것
	cout << typeid(aa).name() << endl;	// 타입의 이름을 알려주는 함수임..ㅋㅋ
	cout << typeid(&aa).name() << endl;
	cout << typeid(bb).name() << endl;
	cout << typeid(&bb).name() << endl;
}

#endif




// 3.4 재정의(overriding)
#if 0
#include <iostream>
using namespace std;

class A
{
public:
	void sub(void);
};

void A::sub(void)
{
	cout << "class " << endl;
}


class B : public A
{
public:
	void sub(void);	// 일반적으로 부모의 함수와 똑같이 사용한다!!
};

void B::sub(void)
{
	A::sub();
	cout << "B" << endl;
}



void main(void)
{
	B aa;	// B타입 개체 aa
	aa.sub();
}

#endif

// 재정의 추가
// 3.6 가상함수(virtual function)
#if 0
#include <iostream>
using namespace std;

class CWnd
{
public:
	void OnLButtonDown(void);
	virtual void OnRButtonUp(void);	// 동적 바인딩 : 컴파일 시간에 호출할 object가 불분명한 경우, 미래를 위해서 가상 함수 설정
	bool OnClose(void);
	void WndProc(void);
};

void CWnd::OnLButtonDown(void)
{
	cout << "left down";
}

void CWnd::OnRButtonUp(void)
{
	cout << "context menu";
}

bool CWnd::OnClose(void)
{
	cout << "close" << endl;
	return true;
}

void CWnd::WndProc(void)
{
	int evnt;

	while (1)
	{	
		do
		{
			cout << "Event :";
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cin >> evnt;
		} while (cin.fail() || evnt < 0 || evnt > 2);
		switch (evnt)
		{
		case 1:
			OnLButtonDown();
			break;
		case 2:
			OnRButtonUp();	// this->OnRButtonUp();에서 this가 생략되어 있음. this는 CWnd *타입임..
							// 이 코드는 과거에 만들어져서 호출하고 있고, 아직Mywnd를 모르는 상태잖아? (미래 만들어질 가상의 함수를 호출하고 있는 것!)
							// 
			break;
		case 0:
			if( OnClose() == true ) goto FIN;	// 복합적인 중괄호 다 빠져나갈 때! (break는 하나밖에 못 빠져 나가잖아)
			break;
		}
	}
FIN:;
}


class MyWnd : public CWnd	// 나만의 기능을 만들고 싶어!
{
public:
	void OnRButtonUp(void);
};

void MyWnd::OnRButtonUp(void)
{
	cout << "My ";
	CWnd::OnRButtonUp();
}


void main(void)
{
	MyWnd wndw;
	wndw.WndProc();
}

#endif

// 
#if 0
#include <iostream>
using namespace std;

class A
{
	int no;
public:
	A(){};
	A(int n) : no(n) {};
	virtual ~A(){ cout << "A des..." << endl; };	// 일반적으로 부모의 소멸자 함수를 virtual로 둠. - 자식의 소멸자 함수가 호출되지 않을 우려 피하기 위해!
	void sub(void);
	virtual void func(void);
};

void A::sub(void)
{
	func();	// 미래에 상속되어 재정의되어 호출될 놈을 virtual로 선언
}

void A::func(void)
{
	cout << "A func" << endl;
}


class B : public A
{
	char ch;
public:
	B(){};
	B(char c, int n) : A(n), ch(c) {};
	~B(){ cout << "B des..." << endl; };
	void func(void);						// 오버라이딩(재정의)된 함수
};

void B::func(void)
{
	cout << "B func" << endl;
}


void main(void)
{
	B bb;
	bb.sub();
	cout << sizeof(bb) << endl;	// 왜 12B일까? 8B가 아니라? : 클래스 내 가상 함수를 포함하면 무조건 4B 포함!!
								// 가상 함수가 1500개라도 4B 늘어남!ㅋㅋㅋ
								// => 주소를 저장할 배열이 필요하고, 또 그 배열을 저장할 "더블 포인터"가 필요!!
}
#endif




// 3.7 순수 가상함수(pure virtual function)




// 3.8 클래스 멤버 포인터 : 클래스 안에 있는 멤버 변수를 가리키는 포인터 / static 멤버는 가리킬 수 없다
//						그 포인터가 증가 및 감소할 수 없다. (정수형 ++해주면 4 증가하는데, 그 곳에 정수형이 있대? 없을 수도 있잖아! 그러니 증감 못함!)
#if 0
#include <stdio.h>
#include <iostream>
using namespace std;

int go;

class A
{
public:
	int & ro = go;	// l-value 참조형 변수는 전역변수의 번지도 받을 수 있기 때문에 클래스 멤버 포인터로 접근 불가!
	int no;
	char ch;
	//A(){};
	//~A(){};
};

void main(void)
{
	//int & A::*rp = &A::ro;		// 참조 형식의 멤버 포인터를 사용할 수 없다고 오류 뜸!
	int A::* p = &A::no;		// 없는 공간의 주소를 가지고 있따? 말이 안된다.. 근데 값을 가진다!!
	char A::* cp = &A::ch;		// 무슨 값을 가질까?

	// cout은 멤버 포인터를 지원하지 않으므로 printf로 출력해보자!
	printf("p = %d, cp = %d\n", p, cp);	// 상대주소로 나옴! 나오긴 나오지만 제대로 된 결과값은 아님!
										// class A는 8B임. 먼저 쓰여진 int no는 0번째, char ch는 4번째 주소
										// 그래서 답이 0, 4가 나옴!
	// 공간도 할당 안 되었는데 주소 값을 갖는다? 그럴 이유가 있다는데 과연 무엇일까!?

	A aa;
	A * ap = &aa;
	aa.*p = 10;		// aa라는 개체에 p가 가리키는 내용!
	aa.*cp = 'A';	// aa라는 개체에 cp가 가리키는 내용!

	cout << ap->*p << ap->*cp << endl;
	cout << aa.*p << aa.*cp << endl;   // 둘은 같은 표현!	=> but, ".*"는 이항연산자라 우선순위가 비교적 낮음!!
}
#endif





// 함수 포인터
#if 0
#include <iostream>
using namespace std;

void __cdecl sub(int n, char c)	// 함수에는 기본적으로 " __cdecl "와 같은 콜 프로토콜이 생략되어 있음
{

}

void __cdecl func(int n, char c)
{

}

void main(void)
{
	int n;
	void(__cdecl * fp)(int, char);	// 함수의 이름은 함수의 주소!! 함수 이름 앞에도 & 붙여서 주소로! 안 써도 되지만 다른 변수들과 통일시켜주기 위해 써주기로 한다!

	cout << "n : ";
	cin >> n;
	if (n == 0) fp = sub;		// n이 0이면 sub 함수의 주소를 갖고,
	else if (n == 1) fp = func;	// n이 1이면 func 함수의 주소를 갖는다.
	// 마치 동적 바인딩처럼 함수 포인터도 컴파일타임이 아닌 런타임 때 어떤 함수를 사용할 지 결정!

	fp(5, 'A');

}

#endif

// 클래스 멤버 함수 포인터
// 호출 규약이 __cdecl에서 __thiscall로 바뀜
// void(__thiscall A::* fp)(int, char); 로 바뀜
#if 0
#include <iostream>
using namespace std;

class A
{
public:
	void __thiscall sub(int n, char c);
	void func(void);
	void func(void) const;
	void func(int n);
};

void __thiscall A::sub(int n, char c)	// " __thiscall " 가 생략되어 있음
{
	cout << n << " " << c << endl;
}

void A::func(void)
{
	void(__thiscall A::* fp)(int, char) = &A::sub;// 가상함수가 있다면 클래스 크기에 추가되는 4B void ** 변수의 [0] 요소 : 함수 결정(?)
	(this->*fp)(10, 'E');						  // [1] 요소	:	함수 호출
}

void A::func(void) const
{
	cout << "func const" << endl;
}

void A::func(int n)
{
	cout << "func (int n)" << endl;
}


void main(void)
{
	A aa;
	void(__thiscall A::* fp)(int, char) = &A::sub;	// &는 반드시 써야 함!!!!!

	(aa.*fp)(5, 'A');	// object가 반드시 있어야만 호출이 가능!!! 함수 포인터와 달리
					// ".*" 연산자와 "() 함수 호출 연산자" 두개의 연산자가 있고, .*가 우선순위가 낮으므로 ()로 묶어줘야...

	(A().*fp)(6, 'Z');	// 임시 object를 이용하여 call을 하는 것!

	aa.func();

	cout << endl;

	void(__thiscall A::* fp3)(void) const = &A::func;	// void A::func(void) const 호출

	void(__thiscall A::* fp2[3])(void) = 
	{
		&A::func,			// void A::func(void) 호출
		(void(__thiscall A::*)(void)) (void(__thiscall A::*)(void) const) &A::func,	// void A::func(void) const 호출
		(void(__thiscall A::*)(void)) (void(__thiscall A::*)(int)) &A::func
	};
	// => 호출할 때는!?!?
	(A().*fp2[0])();	// void A::func(void) 호출
	(A().*fp2[1])();	// void A::func(void) const 호출
	(A().* (void(__thiscall A::*)(int))fp2[2])(5);
}

#endif





// 마지막 예
// 클래스 내 가상 함수를 두면, 그 가상함수 주소를 초기화 하기 위한 디폴트 생성자가 자동적으로 생성된다!
// (전에 배웠던 것) 멤버 변수를 선언해주고, 디폴트 값을 줬을 때 디폴트 생성자가 자동적으로 생성됨
#if 0
#include <iostream>
using namespace std;

class A;
typedef void(__thiscall A::* VFPTR)(void);

class A
{
	VFPTR m_vfptr;	// 타입 변수 순서
	int no;
public:
	A() : m_vfptr(&A::func) {};
	A(VFPTR vfptr) : m_vfptr(vfptr) {};
	A(int n) : no(n) {};
	virtual ~A(){ cout << "A des..." << endl; };// 일반적으로 부모의 소멸자 함수를 virtual로 둠. - 자식의 소멸자 함수가 호출되지 않을 우려 피하기 위해!
	void sub(void);
	/*virtual*/ void func(void);
};

void A::sub(void)
{
	(this->* this->m_vfptr)();	// 미래에 상속되어 재정의되어 호출될 놈을 virtual로 선언
}

void A::func(void)
{
	cout << "A func" << endl;
}


class B : public A
{
	char ch;
public:
	B() : A((VFPTR)&B::func) {};
	B(char c, int n) : A(n), ch(c) {};
	~B(){ cout << "B des..." << endl; };
	void func(void);						// 오버라이딩(재정의)된 함수
};

void B::func(void)
{
	cout << "B func" << endl;
}


void main(void)
{
	B bb;
	bb.sub();	//


}
#endif
