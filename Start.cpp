/* ---------------------- 전처리기 선언 ----------------------- */
# include  < windows.h > // 콘솔 속성을 설정하기 위한 전처리기
# include  < iostream > // 표준 입력/출력을 얻기 위한 전처리기
# include  < conio.h > // 콘솔의 기능을 처리하는 전처리기
# include  < string > // 문자열 입력을 관리하는 전처리기
# include  < fstream > // 파일 처리 방법을 위한 전처리기
# include  < regex > // 정규 표현식을 처리하기 위한 전처리기
# include  < iomanip > // 입력 출력을 조작하는 전처리기
/* ------------------------------ E N D ---------------------------------- */


using namespace std; // 표준 형식 사용

//global variables
char un[20], pw[20];
int lgStat = 0;// 로그인 상태를 저장할 변수
char login[20];// 로그인된 사용자 이름

void Menu();// 함수 프로토타입


/* ---------------------- 정규식 함수 - 입력 유효성 검사 -------------------- --- */
bool validate(string expressions, char tests[]) {
	regex ry(expressions);
	cmatch result;
	//Compare the variables with regular expressions
	if (regex_match(tests, result, ry)) {
		return true;
	}
	else {
		return false;
	}
}
/* ------------------------------ 끝 ---------------------------------- */


#pragma  region structures 
// 데이터를 저장할 Stucture 학생 생성
struct users {
	char username[20], password[20];
};

// 데이터를 저장할 Stucture 학생 생성
struct student {

	unsigned int sid, age;
	char FName[20], SName[30], course[20], address[100], phoneNo[11];

	void clear() {
		// 변수를 다시 초기화하여 데이터 flush
		sid, age;
		FName[20], SName[20], course[20], address[100], phoneNo[11];
	}
};

#pragma endregion structures

student stdobject;// 프로그램이 학생에게 접근하기 위한 전역 변수



#pragma region login

/* ---------------------- 제목 기능 - 제목 표시 --------------------- -- */
void heading() {
	if (lgStat == 2)cout << setw(20) << "\n                다음 아이디로 로그인 되었습니다 >> " << login;
	cout << setw(20) << "\n-------------------------------------------------------------------";
	cout << setw(20) << "\n                        대학생 관리 시스템                         ";
	cout << setw(20) << "\n-------------------------------------------------------------------\n";
}
/* ------------------------------ 끝 ----------------------------------- */


/* ---------------------- 암호 기능 - *로 표시됩니다. -------------------- --- */
void getPassword(string msg) {
	char ch = '0';

	cout << setw(5) << msg + "비밀번호를 입력하세요:  ";
	/* ---------------------- 암호를 텍스트에서 *로 변환 -------------------- --- */
	// 루프에서 증가하는 문자 크기 확인
	for (int x = 0; x <= sizeof(pw); ++x) {

		// 문자 길이 확인
		if (ch != 13 && ch != (int)-52) {
			ch = _getch();
			if (ch == 8) {
				cout << endl;
				if (msg != "Re ") msg = "Re ";
				getPassword(msg);// 함수에 값을 전달
				break;
			}
			if (ch != 13) cout << "*";// 문자 대신 * 표시

			pw[x] = ch;

		}
		else if ((int)ch == 13) {

			pw[x - 1] = (int)0;
			pw[x] = (int)-52;
			ch = (int)-52;
		}
		else {
			pw[x] = (int)-52;
		}
	}

}

/* ---------------------- 로그인 입력 출력 기능 - 자격 증명 가져오기 ------------------- ---- */
void LoginIO(string msg) {
	system("cls"); // 콘솔 지우기
	heading();// 제목 표시
	cout << setw(20) << "\n                                 " << msg << " 로그인                                          ";
	cout << setw(20) << "\n-------------------------------------------------------------------\n";

	cout << setw(5) << "Enter Username: ";
	cin >> un;

	getPassword("");// 암호 얻기 함수 호출

}
/* ------------------------------ 끝 ---------------------------------- */

/* ---------------------- 로그인 기능 - 로그인 상태 설정, 시스템에 대한 액세스 권한 부여 ----------------------- */
void loginFunc()
{
	lgStat = 0;// 로그인 상태

	system("cls");// 콘솔 지우기

	users object;

	ifstream file;



	while (true) {
		if (lgStat == 0) {
			system("cls");// 콘솔 지우기

			heading();// 제목 표시
			LoginIO("");// 로그인 입력 출력 함수 호출

			file.open("users.dat", ios::binary);
			while (file.read((char*)&object, sizeof(object))) {

				// 문자 비교
				if ((strcmp(un, object.username) == 0 && strcmp(pw, object.password) == 0)) {

					// 구조체의 변수에 문자 복사
					strncpy_s(login, object.username, sizeof(object.username));
					lgStat = 2;//로그인
					break;
				}
				else {
					lgStat = 1;//로그아웃
				}
			}
			file.close();
			//login
			if (lgStat == 2) break;
		}
		else if (lgStat == 1) {
			system("cls");// 콘솔 지우기
			heading();// 제목 표시
			cout << setw(20) << "\n                                  로그인                              ";
			cout << setw(20) << "\n-------------------------------------------------------------------\n";
			cout << setw(20) << "\n 액세스가 거부되었습니다........ 잘못된 사용자 이름 또는 비밀번호입니다...................\n";
			cout << setw(20) << "\n로그인을 다시 시도하려면 'Y'를 누르거나 메인 메뉴로 이동하려면 다른 키를 누르십시오: ";

			char ch;
			cin >> ch;

			if (ch == 'y' || ch == 'Y') {
				LoginIO("Re ");// 로그인 입력 출력 함수 호출

				file.open("users.dat", ios::binary);
				while (file.read((char*)&object, sizeof(object))) {
					//문자 비교
					if ((strcmp(un, object.username) == 0 && strcmp(pw, object.password) == 0)) {
						lgStat = 2;
						break;
					}
					else {
						lgStat = 1;
					}
				}
				file.close();
				if (lgStat == 2) break;
			}
			else {
				system("cls");//콘솔 지우기
				Menu();//메뉴 함수 호출

				break;
			}
		}
		else if (lgStat == 2) {
			break;

		}
	}



	if (lgStat == 2) {
		system("cls");//콘솔 지우기
		Menu();//메뉴 함수 호출
	}
}
/* ------------------------------ 끝 ---------------------------------- */

/* ---------------------- 사용자 추가 기능 - 시스템에 새 사용자 추가 ----------------------- */
void adduser()
{
	system("cls");//콘솔 지우기

	heading();// 제목 표시
	cout << setw(20) << "\n                      새로운 사용자 추가                            ";
	cout << setw(20) << "\n-------------------------------------------------------------------\n";
	users object;
	ofstream file;
	file.open("users.dat", ios::binary | ios::app);

	while (true) {
		char temp[20];
		cout << left << "Enter username: ";
		cin >> temp;
		if (validate("[\\w]+", temp)) {
			// 객체에 데이터 복사
			strncpy_s(object.username, temp, sizeof(temp));
			break;
		}
		else {
			cout << left << "\t----------- 잘못된 값입니다.. 다시 입력하십시오.\n\n";
		}

	}

	while (true) {
		getPassword("");//비밀번호 얻는 메소드 호출
		// 비밀번호 확인
		if (validate("[\\w]+", pw)) {
			// 객체에 데이터 복사
			strncpy_s(object.password, pw, sizeof(pw));
			break;
		}
		else {
			cout << left << "\t----------- 잘못된 값입니다.. 다시 입력하십시오.\n\n";
		}

	}

	file.write((char*)&object, sizeof(object));
	file.close();
	cout << "\n데이터가 성공적으로 저장되었습니다... 주 메뉴로 이동하려면 아무 키나 누르십시오..";
	_getch();
	system("cls");// 콘솔 지우기
	Menu(); // 메뉴 함수 호출

}
/* ------------------------------ 끝 ---------------------------------- */

/* ------------------------------------- 사용자 삭제 기능 - 시스템에서 사용자 삭제 --------- */
void deleteUser()
{
	char opt = 0;
	users userObject;

	while (true) {
		bool firstTime = false;
		bool result = false;

		while (true) {
			system("cls");//콘솔 지우기

			if (firstTime == true) {
				cout << left << "\n잘못된 옵션이 선택되었습니다 ...... 계속하려면 다시 선택하십시오 ....... .......\n";
			}

			heading();//제목 표시
			cout << setw(20) << "\n                    학생 세부 정보 메뉴 삭제                    ";
			cout << setw(20) << "\n-------------------------------------------------------------------\n";

			cout << left << "1. 사용자 삭제\n";
			cout << left << "\n2. 메인 메뉴로 돌아가기\n";

			cout << setw(20) << "\n------------------------------------\n";

			cout << setw(20) << "\n *계속하려면 옵션을 선택하십시오 : ";
			cin >> opt;

			firstTime = true;
			if (opt != '1' || opt != '2') break;
		}

		system("cls");//콘솔 지우기
		heading();// Displays Heading

		if (opt == '1') {
			cout << setw(20) << "\n                          사용자 삭제";
		}
		else if (opt == '2') {
			system("cls");//콘솔 지우기
			Menu();//메뉴 함수 호출
			break;
		}

		cout << setw(20) << "\n-------------------------------------------------------------------\n";

		char searchChars[20];
		cout << setw(20) << "** 삭제는 대소문자를 구분합니다 **\n";

		cout << setw(20) << "\n삭제할 사용자 이름을 입력하십시오: ";
		cin >> searchChars;


		ifstream file;
		file.open("users.dat", ios::binary);

		ofstream filet;
		filet.open("userst.tmp", ios::binary);

		while (file.read((char*)&userObject, sizeof(userObject))) {
			if (strcmp(searchChars, userObject.username) == 0) {

				cout << left << "Username : " << userObject.username << endl;
				cout << setw(20) << " \n 레코드가 영구적으로 삭제됩니다... \n ";
				cout << setw(20) << " \n 확인하려면 'Y'를 입력하고 취소하려면 다른 것을 입력하십시오: ";
				char ch;
				cin >> ch;//확인 받기
				if (ch == 'y' || ch == 'Y') {
					lgStat = 0;
					result = true;
				}
				else {
					filet.write((char*)&userObject, sizeof(userObject));
				}
			}
			else {
				filet.write((char*)&userObject, sizeof(userObject));
			}
		}

		file.close();
		filet.close();

		remove("users.dat");
		rename("userst.tmp", "users.dat");

		if (result == true) {

			cout << setw(20) << "\n레코드가 삭제되었습니다 .";

			cout << setw(20) << "\n계속하려면 아무 키나 누르십시오.........";
			_getch();
			system("cls");//콘솔 지우기
			Menu();//메뉴 함수 호출
			break;

		}
		else {
			cout << setw(20) << "\n-------------------삭제된 레코드가 없습니다---------------------------\n";

			cout << setw(20) << "\n 계속하려면 아무 키나 누르십시오.........";
			_getch();
		}
	}
}
/* ------------------------------ 끝 ---------------------------------- */
#pragma endregion login

#pragma region students
/* ---------------------- 표시 기능 - 학생 세부 정보 표시 ----------------------- */
void displayStudent()
{
	if (stdobject.age != NULL) {
		cout << endl;
		cout << setw(20) << "---------------------- 학생 세부사항 ----------------------\n";
		cout << left << "학생 ID  : " << stdobject.sid << endl;
		cout << left << "성  : " << stdobject.FName << endl;
		cout << left << "이름 : " << stdobject.SName << endl;
		cout << left << "나이        : " << stdobject.age << endl;
		cout << left << "주소	     : " << stdobject.address << endl;
		cout << left << "전화 번호   : " << stdobject.phoneNo << endl;
		cout << left << "강의      : " << stdobject.course << endl;
		cout << endl;
	}

}
/* ------------------------------ 끝 ---------------------------------- */


/* ----------------- 학생 세부 정보 기능 - 구조에 유효성을 검사한 후 학생 데이터를 푸시합니다---------------- */
void stdDetailsToObject(char x) {
	// 학생 ID를 개체에 저장
	if (x == 'a') {
		while (true) {
			char id[10];
			cout << left << "\n학생 ID를 입력하세요                : ";
			cin >> id;
			// 검증
			if (validate("[\\d]+", id)) {
				int num = 0;
				sscanf_s(id, "%d", &num);
				// 객체에 데이터 복사
				stdobject.sid = num;
				break;
			}
			else {
				cout << left << "\t----------- 잘못된 값입니다.. 다시 입력하십시오\n\n";
			}
		}
	}
	// 학생의 이름을 객체에 저장
	if (x == 'a' || x == '1' || x == '7') {
		while (true) {
			char fntemp[20];
			cout << left << "\n학생의 이름을 입력하십시오   : ";
			cin >> fntemp;
			// 검증
			if (validate("[a-zA-Z]+", fntemp)) {
				// 객체에 데이터 복사
				strncpy_s(stdobject.FName, fntemp, sizeof(fntemp));
				break;
			}
			else {
				cout << left << "\t----------- 잘못된 값입니다.. 다시 입력하십시오\n\n";
			}

		}
	}
	// 학생의 성을 객체에 저장
	if (x == 'a' || x == '2' || x == '7') {
		while (true) {
			char sntemp[30];
			cout << left << "\n학생의 성을 입력하십시오    : ";
			cin >> sntemp;
			// 검증
			if (validate("[a-zA-Z]+", sntemp)) {
				// 객체에 데이터 복사
				strncpy_s(stdobject.SName, sntemp, sizeof(sntemp));
				break;
			}
			else {
				cout << left << "\t----------- 잘못된 값입니다.. 다시 입력하십시오\n\n";
			}

		}
	}
	// 객체에 학생 나이 저장
	if (x == 'a' || x == '3' || x == '7') {
		while (true) {
			char agetemp[10];
			cout << left << "\n학생의 연령(18-40) 입력: ";
			cin >> agetemp;
			// 검증
			if (validate("[\\d]+", agetemp)) {
				int num = 0;
				sscanf_s(agetemp, "%d", &num);
				// 객체에 데이터 복사
				if (num >= 18 && num <= 40) {
					stdobject.age = num;
					break;
				}
				else {
					cout << left << "\t----------- 한도가 잘못되었습니다. 다시 입력하세요.\n\n";
				}
			}
			else {
				cout << left << "\t----------- 값이 잘못되었습니다. 다시 입력하세요\n\n";
			}

		}
	}
	// 객체에 학생 주소 저장
	if (x == 'a' || x == '4' || x == '7') {
		while (true) {
			char adTemp[100];
			cout << left << "\n주소 입력                    : ";
			cin.ignore();
			cin.getline(adTemp, 99);
			//검증
			if (validate("[/:a-zA-Z0-9\\s]+", adTemp)) {
				// 객체에 데이터 복사
				strncpy_s(stdobject.address, adTemp, sizeof(adTemp));
				break;
			}
			else {
				cout << left << "\t----------- 값이 잘못되었습니다. 다시 입력하세요\n\n";
			}
		}
	}

	// 객체에 학생 전화번호 저장
	if (x == 'a' || x == '5' || x == '7') {
		while (true) {

			char phnoTemp[11];
			cout << left << "\nEnter Phone Number                : ";
			cin >> phnoTemp;
			// 검증
			if (validate("[\\d]{10}", phnoTemp)) {
				// 객체에 데이터 복사
				strncpy_s(stdobject.phoneNo, phnoTemp, sizeof(phnoTemp));
				break;
			}
			else {
				cout << left << "\t----------- 값이 잘못되었습니다. 다시 입력하세요\n\n";
			}

		}
	}
	// 학생 과정을 개체에 저장
	if (x == 'a' || x == '6' || x == '7') {
		while (true) {
			char crseTemp[20];
			cout << left << "\n강의 입력                     : ";
			cin >> crseTemp;
			//검증
			if (validate("[\\w\\s]+", crseTemp)) {
				// 객체에 데이터 복사
				strncpy_s(stdobject.course, crseTemp, sizeof(crseTemp));
				break;
			}
			else {
				cout << left << "\t----------- 값이 잘못되었습니다. 다시 입력하세요\n\n";
			}

		}
	}
}
/* ------------------------------ 끝 ---------------------------------- */


/* ---------------------- 학생 등록 ​​기능 - 학생 등록 ----------------------- */
void stdRegistration()
{
	system("cls");// 콘솔 지우기

	heading();// 제목 표시
	cout << setw(20) << "\n                          학생등록                       ";
	cout << setw(20) << "\n-------------------------------------------------------------------\n";
	stdobject.clear();//객체 지우기
	ofstream file;
	file.open("stdDetails.dat", ios::binary | ios::app);
	stdDetailsToObject('a');// 개체 함수에 대한 학생 세부 정보 호출

	file.write((char*)&stdobject, sizeof(stdobject));

	file.close();
	displayStudent();// 디스플레이 학생 함수 호출

	cout << "데이터가 성공적으로 저장되었습니다... 주 메뉴로 이동하려면 아무 키나 누르십시오..";
	_getch();
	system("cls");// 콘솔 지우기

	Menu();// 메뉴 함수 호출

}
/* ------------------------------ 끝 ---------------------------------- */

/* ---------------------- 검색 기능 - 학생 세부 정보 검색----------------------- */
void stdSearch() {
	char opt = 0;

	while (true) {
		bool firstTime = false;
		bool result = false;

		while (true) {
			system("cls");//Clear Console

			if (firstTime == true) {
				cout << left << " 잘못된 옵션이 선택되었습니다 ...... 계속하려면 다시 선택하십시오 .......\n";
			}
			heading();// Displays Heading
			cout << setw(20) << "\n                          학생 검색 메뉴                         ";
			cout << setw(20) << "\n-------------------------------------------------------------------\n";
			cout << left << " 1. 학생 ID로 검색 \n ";
			cout << left << " 2. 이름으로 학생 검색 \n ";
			cout << left << " 3. 과목별 학생 검색 \n ";
			cout << left << " 4. 메인 메뉴로 돌아가기 \n ";

			cout << setw(20) << "\n------------------------------------\n";

			cout << setw(20) << "\n *계속하려면 옵션을 선택하십시오: ";
			cin >> opt;

			firstTime = true;
			if (opt == '1' || opt == '2' || opt == '3' || opt == '4') break;
		}

		system("cls");//Clear Console
		heading();// Displays Heading
		cout << setw(20) << "\n                           학생 검색                            ";
		cout << setw(20) << "\n-------------------------------------------------------------------\n";

		char searchChars[20];
		cout << setw(20) << "** 검색은 대소문자를 구분합니다 **\n";

		if (opt == '1') {
			cout << setw(20) << "\n학번을 입력하세요 : ";
		}
		else if (opt == '2') {
			cout << setw(20) << "\n학생의 이름을 입력하세요: ";
		}
		else if (opt == '3') {
			cout << setw(20) << "\n학생 과정 입력: ";
		}
		else if (opt == '4') {
			system("cls");//콘솔 지우기
			Menu();// 메뉴 함수 호출
			break;
		}

		cin >> searchChars;
		ifstream file;
		file.open("stdDetails.dat", ios::binary);

		while (file.read((char*)&stdobject, sizeof(stdobject))) {
			// 학생 ID로 검색
			if (opt == '1') {
				int num = 0;
				sscanf_s(searchChars, "%d", &num);

				if ((num == stdobject.sid)) {

					result = true;
					break;
				}
				else {

				}

			}
			// 학생 이름으로 검색
			else if (opt == '2') {
				if (strcmp(searchChars, stdobject.FName) == 0) {

					result = true;
					break;
				}
				else {

				}
			}
			// 학생 강의를 사용하여 검색
			else if (opt == '3') {

				if (strcmp(searchChars, stdobject.course) == 0) {

					result = true;
					break;
				}
				else {

				}
			}

		}

		file.close();

		if (result == true) {
			displayStudent();//call display student function
			cout << setw(20) << "\n계속하려면 아무 키나 누르십시오.........";
			_getch();
		}
		else {
			cout << setw(20) << "\n-------------------검색된 기록을 찾을 수 없습니다 ---------------------------\n";

			cout << setw(20) << "\n계속하려면 아무 키나 누르십시오.........";
			_getch();

		}
	}
}
/* ------------------------------ 끝 ---------------------------------- */

/* ---------------------- 업데이트 기능 - 학생 세부 정보 업데이트 ----------------------- */
void stdUpdate()
{
	char opt = 0;

	while (true) {
		bool firstTime = false;
		bool result = false;

		while (true) {
			system("cls");//콘솔 지우기

			if (firstTime == true) {
				cout << left << "\n잘못된 옵션이 선택되었습니다 ...... 계속하려면 다시 선택하십시오  .......\n";
			}

			heading();// 제목 표시
			cout << setw(20) << "\n                  학생 정보 메뉴 업데이트                           ";
			cout << setw(20) << "\n-------------------------------------------------------------------\n";

			cout << left << " 1. 학생 이름 업데이트 \n ";
			cout << left << " 2. 학생 성을 업데이트 합니다. \n ";
			cout << left << " 3. 학생 나이 업데이트 \n ";
			cout << left << " 4. 학생 주소 업데이트 \n ";
			cout << left << " 5. 학생 전화번호 업데이트 \n ";
			cout << left << " 6. 학생 course 업데이트 \n ";
			cout << left << " 7. 학생의 모든 세부 정보 업데이트 \n ";
			cout << left << " \n 8. 메인 메뉴로 돌아가기 \n ";

			cout << setw(20) << "\n------------------------------------\n";

			cout << setw(20) << " \n *계속하려면 옵션을 선택하십시오: ";
			cin >> opt;

			firstTime = true;
			if (opt != '1' || opt != '2' || opt != '3' || opt != '4' || opt != '5' || opt != '6' || opt != '7' || opt != '8') break;
		}

		system("cls");// 콘솔 지우기
		heading();// 제목 표시

		if (opt == '1') {
			cout << setw(20) << "\n                          학생 이름 업데이트 ";
		}
		else if (opt == '2') {
			cout << setw(20) << "\n                           학생 성 업데이트 ";
		}
		else if (opt == '3') {
			cout << setw(20) << "\n                          학생 연령 업데이트 ";
		}
		else if (opt == '4') {
			cout << setw(20) << "\n                          학생 주소 업데이트 ";
		}
		else if (opt == '5') {
			cout << setw(20) << "\n                          학생 전화번호 업데이트";
		}
		else if (opt == '6') {
			cout << setw(20) << "\n                          학생 course 업데이트 ";
		}
		else if (opt == '6') {
			cout << setw(20) << "\n                          학생의 모든 세부 정보 업데이트";
		}
		else if (opt == '8') {
			system("cls");//콘솔 지우기
			Menu();//메뉴 함수 호출
			break;
		}

		cout << setw(20) << "\n-------------------------------------------------------------------\n";

		char searchChars[20];
		cout << setw(20) << " ** 검색은 대소문자를 구분합니다 ** \n ";

		cout << setw(20) << " \n 변경하려면 학생 ID를 입력하십시오: ";
		cin >> searchChars;

		int num = 0;

		sscanf_s(searchChars, "%d", &num);

		ifstream file;
		file.open("stdDetails.dat", ios::binary);

		ofstream filet;
		filet.open("stdDetailst.tmp", ios::binary);

		while (file.read((char*)&stdobject, sizeof(stdobject))) {
			if (num == stdobject.sid) {
				result = true;
				stdDetailsToObject(opt);// opt pass 매개변수 및 변경 데이터 기반
				filet.write((char*)&stdobject, sizeof(stdobject));
			}
			else {
				filet.write((char*)&stdobject, sizeof(stdobject));
			}
		}

		file.close();
		filet.close();

		remove("stdDetails.dat");
		rename("stdDetailst.tmp", "stdDetails.dat");// 업데이트된 데이터 복사 및 붙여

		if (result == true) {
			file.open("stdDetails.dat", ios::binary);

			while (file.read((char*)&stdobject, sizeof(stdobject))) {
				if (num == stdobject.sid) {
					cout << setw(20) << "\n선택한 레코드에서 데이터가 업데이트되었습니다 .";
					displayStudent();
					cout << setw(20) << "\n계속하려면 아무 키나 누르십시오........";
					_getch();
				}
			}
			file.close();
		}
		else {
			cout << setw(20) << " \n -------------------검색된 레코드를 찾을 수 없습니다 ---------------------------- -------------- \n ";

			cout << setw(20) << " \n 계속하려면 아무 키나 누르십시오....... ";
			_getch();
		}
	}
}
/* ------------------------------ 끝 ---------------------------------- */

/* ---------------------- 학생 삭제 기능 - 학생 세부 정보 삭제 ----------------------- */
void stdDelete()
{
	char opt = 0;

	while (true) {
		bool firstTime = false;
		bool result = false;

		while (true) {
			system("cls");//콘솔 지우기

			if (firstTime == true) {
				cout << left << "\n잘못된 옵션이 선택되었습니다 ...... 계속하려면 다시 선택하십시오 .......\n";
			}

			heading();// 제목 표시
			cout << setw(20) << "\n                   학생 세부 정보 메뉴 삭제                          ";
			cout << setw(20) << "\n-------------------------------------------------------------------\n";

			cout << left << " 1. 학생 기록 삭제 \n ";
			cout << left << " \n 2. 메인 메뉴로 돌아가기 \n ";

			cout << setw(20) << " \n ------------------------------------ \n ";

			cout << setw(20) << " \n *계속하려면 옵션을 선택하십시오: ";
			cin >> opt;

			firstTime = true;
			if (opt != '1' || opt != '2') break;
		}

		system("cls");// 콘솔 지우기
		heading();// 제목 표시

		if (opt == '1') {
			cout << setw(20) << "\n                          학생 삭제";
		}
		else if (opt == '2') {
			system("cls");//콘솔 지우기
			Menu();// 메뉴 함수 호출
			break;
		}

		cout << setw(20) << "\n-------------------------------------------------------------------\n";

		char searchChars[20];
		cout << setw(20) << " ** 검색은 대소문자를 구분합니다 ** \n ";

		cout << setw(20) << " \n 삭제할 학번을 입력하세요 : ";
		cin >> searchChars;

		int num = 0;

		sscanf_s(searchChars, "%d", &num);

		ifstream file;
		file.open("stdDetails.dat", ios::binary);

		ofstream filet;
		filet.open("stdDetailst.tmp", ios::binary);

		while (file.read((char*)&stdobject, sizeof(stdobject))) {
			if (num == stdobject.sid) {

				cout << setw(20) << " \n 레코드가 영구적으로 삭제됩니다...... ";
				displayStudent();
				cout << setw(20) << " \n 확인하려면 'Y'를 입력하고 취소하려면 다른 것을 입력하십시오: ";
				char ch;
				cin >> ch;
				//확인 유효성 검사 삭제
				if (ch == 'y' || ch == 'Y') {

					result = true;
				}
				else {
					filet.write((char*)&stdobject, sizeof(stdobject));
				}
			}
			else {
				filet.write((char*)&stdobject, sizeof(stdobject));
			}
		}

		file.close();
		filet.close();

		remove("stdDetails.dat");
		rename("stdDetailst.tmp", "stdDetails.dat");// 필요한 데이터 복사 및 붙여넣기

		if (result == true) {

			cout << setw(20) << " \n 레코드가 삭제되었습니다 . ";

			cout << setw(20) << " \n 계속하려면 아무 키나 누르십시오....... ";
			_getch();

		}
		else {
			cout << setw(20) << " \n -------------------삭제 중인 레코드가 없습니다---------------------------- \n ";

			cout << setw(20) << " \n 계속하려면 아무 키나 누르십시오....... ";
			_getch();
		}
	}
}
/* ------------------------------ 끝 ---------------------------------- */
#pragma endregion students

#pragma region menus
/* ---------------------- 도움말 기능 - 시스템에 대한 도움말 ----------------------- */
void help() {

	system("cls");//콘솔 지우기
	heading();// 메뉴 함수 호출

	cout << " \n\n ";
	cout << left << " -------------------------------------------------- " << endl;
	cout << left << " 도움말 - 응용 프로그램 사용 방법 " << endl;
	cout << left << " ----------------------------------- " << " \n\n \n ";

	cout << " 참고 - 모든 필드는 필수이므로 생략할 수 없습니다. \n ";
	cout << " 참고 - 텍스트가 필요한 모든 필드는 텍스트만 인식합니다. \n ";
	cout << " 참고 - 숫자 입력이 필요한 모든 필드는 숫자 입력만 인식합니다 \n ";
	cout << " 참고 - 모든 입력은 파일에 기록된 형식으로 정확하게 검색되므로 모든 작업은 대소문자를 구분합니다. \n ";
	cout << " 참고 - 응용 프로그램에서 최상의 성능을 얻으려면 표준 형식과 규칙을 사용하십시오. " << " \n\n ";

	cout << left << " -------------------------------------------------- " << endl;
	cout << left << "                로그인                " << endl;
	cout << left << " -------------------------------------------------- " << endl;
	cout << " 메인 메뉴에서 1번을 눌러 시스템에 로그인 합니다. " << endl;
	cout << " 그러면 자격 증명을 요청할 것입니다. " << endl;
	cout << " 그리고 모든 세부 정보를 올바르게 입력하면 시스템에 로그인할 수 있습니다. " << endl;
	cout << " 참고 - 시스템에 로그인하려면 필요한 모든 세부 정보를 입력해야 합니다. " << " \n\n ";
	cout << " -------------------------------- ------------------------------------------- \n\n ";

	cout << left << " -------------------------------------------------- " << endl;
	cout << left << "            새 사용자 추가            " << endl;
	cout << left << " -------------------------------------------------- " << endl;
	cout << " 참고 - 이렇게 하려면 시스템에 로그온해야 합니다. " << " \n\n ";
	cout << " 새로운 사용자를 시스템에 추가하려면 메인 메뉴에서 2번을 누르십시오. " << endl;
	cout << " 그리고 모든 세부 정보를 올바르게 입력하면 시스템에 새 사용자를 추가할 수 있습니다. " << " \n\n ";
	cout << " 참고 - 나중에 시스템에 로그인하려면 필요한 모든 세부 정보를 입력해야 합니다. " << " \n\n ";
	cout << " -------------------------------- ------------------------------------------- \n\n ";

	cout << left << " -------------------------------------------------- " << endl;
	cout << left << "           사용자 삭제              " << endl;
	cout << left << " -------------------------------------------------- " << endl;
	cout << " 참고 - 이렇게 하려면 시스템에 로그온해야 합니다. " << " \n\n ";
	cout << " 메인 메뉴에서 3번을 누르면 시스템에서 사용자를 삭제할 수 있습니다. " << endl;
	cout << " 그리고 모든 세부 정보를 올바르게 입력하면 시스템에서 사용자를 삭제할 수 있습니다. " << " \n\n ";
	cout << " 참고 - 시스템에서 사용자를 제거하려면 필요한 모든 세부 정보를 입력해야 합니다. " << " \n\n ";
	cout << " -------------------------------- ------------------------------------------- \n\n ";

	cout << left << " -------------------------------------------------- " << endl;
	cout << left << "           학생 등록          ​​" << endl;
	cout << left << " -------------------------------------------------- " << endl;
	cout << " 참고 - 이렇게 하려면 시스템에 로그온해야 합니다. " << " \n\n ";
	cout << " 새 학생을 시스템에 추가하려면 메인 메뉴에서 4를 누르십시오. " << endl;
	cout << " 그러면 학생 정보를 요구하게 됩니다. " << endl;
	cout << " 그리고 모든 세부 정보를 올바르게 입력하면 시스템에 학생을 추가할 수 있습니다. " << " \n\n ";
	cout << " 참고 - 학생을 시스템에 추가하려면 필요한 모든 세부 정보를 입력해야 합니다. " << " \n\n ";
	cout << " 참고 - 전화번호는 10자만 허용됩니다. " << " \n\n ";
	cout << " 참고 - 주소는 아래 형식이 됩니다. " << " \n\n ";
	cout << " 1600 Amphitheatre Parkway Mountain View CA ";
	cout << " -------------------------------- ------------------------------------------- \n\n ";


	cout << left << " -------------------------------------------------- " << endl;
	cout << left << "        학생 정보 검색       " << endl;
	cout << left << " -------------------------------------------------- " << endl;
	cout << " 참고 - 이렇게 하려면 시스템에 로그온해야 합니다. " << " \n\n ";
	cout << " 시스템에서 학생을 검색하려면 메인 메뉴에서 5번을 누르세요. " << endl;
	cout << " 검색 옵션을 제공하는 하위 메뉴로 이동합니다. " << " \n\n ";
	cout << " 이 메뉴에서는 다양한 옵션에 따라 검색할 수 있습니다: " << " \n\n ";
	cout << " 1번을 누르면 id로 학생을 검색할 수 있습니다. " << " \n\n ";
	cout << " 2번을 누르면 이름으로 학생을 검색할 수 있습니다. " << " \n\n ";
	cout << " 3번을 누르면 수강생을 해당 과목으로 검색할 수 있습니다. " << " \n\n ";
	cout << " 4번을 누르면 메인 메뉴로 이동합니다. " << " \n\n ";
	cout << " 참고 - 검색은 매우 대소문자를 구분합니다. " << " \n\n ";

	cout << left << " -------------------------------------------------- " << endl;
	cout << left << "      학생 정보 업데이트         " << endl;
	cout << " 참고 - 이렇게 하려면 시스템에 로그온해야 합니다. " << " \n\n ";
	cout << " 메인 메뉴에서 6번을 누르면 시스템에서 학생 정보를 업데이트 합니다. " << endl;
	cout << " 업데이트 옵션을 제공하는 하위 메뉴로 이동합니다. " << " \n\n ";
	cout << " 이 메뉴에서 다양한 옵션에 따라 업데이트할 수 있습니다: " << endl;
	cout << " 1번을 누르면 학번을 업데이트 할 수 있습니다. " << endl;
	cout << " 2번을 누르면 학생의 이름을 변경할 수 있습니다. " << endl;
	cout << " 3번을 누르면 학생의 성을 업데이트할 수 있습니다. " << endl;
	cout << " 4번을 누르면 학생 나이를 업데이트 할 수 있습니다. " << endl;
	cout << " 5번을 누르면 학생의 주소를 업데이트 할 수 있습니다. " << endl;
	cout << " 6번을 누르면 수강생의 강의를 업데이트 할 수 있습니다. " << endl;
	cout << " 7번을 누르면 학생의 모든 정보를 업데이트 할 수 있습니다. " << endl;
	cout << " 8번을 누르면 메인 메뉴로 이동합니다. " << endl;
	cout << " 참고 - 업데이트는 학생 ID를 사용하여 검색하라는 메시지를 표시하므로 입력은 대소문자를 엄격하게 구분합니다. " << " \n\n ";

	cout << left << " -------------------------------------------------- " << endl;
	cout << left << "      학생 정보 삭제         " << endl;
	cout << left << " -------------------------------------------------- " << endl;
	cout << " 참고 - 이렇게 하려면 시스템에 로그온해야 합니다. " << " \n\n ";
	cout << " 시스템에서 학생 정보를 삭제하려면 메인 메뉴에서 6번을 누르십시오. " << endl;
	cout << " 삭제 옵션을 제공하는 하위 메뉴로 이동합니다. " << " \n\n ";
	cout << " 이 메뉴에서는 다양한 옵션에 따라 삭제할 수 있습니다: " << endl;
	cout << " 1번을 누르면 학생정보를 삭제할 수 있습니다. " << endl;
	cout << " 2번을 누르면 메인 메뉴로 이동합니다. " << endl;
	cout << " 참고 - 삭제하면 학생 ID를 사용하여 검색하라는 메시지가 표시되므로 입력은 대소문자를 구분해야 합니다. " << endl;


	cout << left << " -------------------------------------------------- " << endl;
	cout << left << "                 도움말                " << endl;
	cout << left << " -------------------------------------------------- " << endl;
	cout << " 참고 - 이렇게 하려면 시스템에 로그온해야 합니다. " << endl;
	cout << " 도움말은 시스템을 사용할 때 따라야 할 기본 규칙을 제공합니다. " << endl;

	cout << left << " -------------------------------------------------- " << endl;
	cout << left << "         기타 기능             " << endl;
	cout << left << " -------------------------------------------------- " << endl;
	cout << " 메인 메뉴에서 9번을 누르면 시스템에서 로그아웃 됩니다. " << endl;
	cout << " 메인 메뉴에서 10번을 눌러 시스템을 종료합니다. " << endl;


	cout << " 메인 메뉴로 가려면 아무 키나 누르세요.. ";
	_getch();

	system("cls");//콘솔 지우기
	Menu();//메뉴 함수 호출



}
/* ------------------------------ 끝 ---------------------------------- */

/* ---------------------- 메뉴 기능 - 시스템에서 시스템 탐색 ----------------------- */
void Menu()
{
	while (true) {
		heading();// 제목 표시
		cout << left << " 1. 로그인 \n";
		cout << left << " 2. 새 사용자 추가 \n";
		cout << left << " 3. 사용자 삭제 \n";
		cout << left << " 4. 학생 등록\n";
		cout << left << " 5. 학생 검색 \n";
		cout << left << " 6. 학생 정보 업데이트 \n";
		cout << left << " 7. 학생 정보 삭제 \n";
		cout << left << " 8. 도움말 \n";
		cout << left << " 9. 로그아웃 \n";
		cout << left << " 10. 종료 \n ";

		cout << setw(20) << "\n------------------------------------\n";
		cout << setw(20) << " \n *계속하려면 옵션을 선택하십시오: ";

		unsigned short int opt;
		cin >> opt;

		if (opt == 1) {
			loginFunc();// 로그인 함수 호출
			break;
		}
		else if (opt == 2) {
			if (lgStat == 2) {
				adduser();// 사용자 추가 함수 호출
				break;
			}
			else {
				system("cls");// 콘솔 지우기
				cout << left << "\n먼저 로그인을 해주세요......\n";
			}
		}
		else if (opt == 3) {
			if (lgStat == 2) {
				deleteUser();// 사용자 삭제 함수 호출
				break;
			}
			else {
				system("cls");// 콘솔 지우기
				cout << left << "\n먼저 로그인을 해주세요......\n";
			}
		}
		else if (opt == 4) {
			if (lgStat == 2) {
				stdRegistration();// 학생등록 함수 호출
				break;
			}
			else {
				system("cls");// 콘솔 지우기
				cout << left << "\n먼저 로그인을 해주세요......\n";
			}
		}
		else if (opt == 5) {
			stdSearch();// 학생 검색 기능 호출
			break;
		}
		else if (opt == 6) {
			if (lgStat == 2) {
				stdUpdate();// 학생 업데이트 호출
				break;
			}
			else {
				system("cls");// 콘솔 지우기
				cout << left << "\n먼저 로그인을 해주세요......\n";
			}
		}
		else if (opt == 7) {
			if (lgStat == 2) {
				stdDelete();// 학생 삭제 함수 호출
				break;
			}
			else {
				system("cls");// 콘솔 지우기
				cout << left << "\n먼저 로그인을 해주세요......\n";
			}
		}
		else if (opt == 8) {
			if (lgStat == 2) {
				help();// 도움말 함수 호출
				break;
			}
			else {
				system("cls");// 콘솔 지우기
				cout << left << "\n먼저 로그인을 해주세요......\n";
			}
		}
		else if (opt == 9) {
			lgStat = 0;
			system("cls");// 콘솔 지우기
		}
		else if (opt == 10) {
			exit(0);// 애플리케이션 종료
		}
		else {
			system("cls");// 콘솔 지우기
			cout << left << "\n잘못된 옵션을 선택했습니다 ...... 계속하려면 다시 선택하십시오 .......\n";
		}
	}

}
/* ------------------------------ 끝 ---------------------------------- */
#pragma endregion menus

/* ---------------------- 메인 함수 ----------------------- */
int main() {
	system("mode 650");// 콘솔 크기 설정
	SetConsoleTitle(TEXT("대학생 관리 시스템"));// 콘솔 창의 제목 설정
	system("COLOR F0");// 배경 및 텍스트 색상 설정
	Menu();// 메뉴 함수 호출

	system("pause");// 콘솔창 일시정지
}
/* ------------------------------ 끝 ---------------------------------- */
