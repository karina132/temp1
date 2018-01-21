#include "stdafx.h"  
#include "stdio.h" 
#include "io.h" 
#include <iostream> 
#include <fstream> 
#include <string> 
#include <iomanip> 
using namespace std;

struct StudentInformation
{
	char FIO[20];
	int year;
	char group[7];
	int physics;
	int math;
	int informatics;
	int chemistry;
	double sr_b;
};

StudentInformation* students;
int students_count;

const int VIEW	  = 1;
const int ADD     = 2;
const int SORTING = 3;
const int DELETE  = 4;
const int EDIT	  = 5;
const int EXIT	  = 0;

int getInt(int from, int to);
int getCode();
void checkFile();
int getStringsCount();
void readFileStudents();
void showStudentsArray();
void sortingStudentsArray();
void increaseSizeOfArray();
void writeRezultToFile();
void writeEndFileStudents(); 
void addStudentinArray();
void deleteStudent();
void editInformation();
void rewritingData();
void inputStudentInformation(int);


int main()
{
	checkFile();
	students_count = getStringsCount();
	students = new StudentInformation[students_count]; 
	readFileStudents();
	while (true)
	{
		switch (getCode())
		{
		case VIEW:
			showStudentsArray();
			break;
		case ADD:
			addStudentinArray();
			writeEndFileStudents();
			break;
		case SORTING:
			sortingStudentsArray();
			showStudentsArray();
			writeRezultToFile();
			break;
		case DELETE:
			if (students_count == 0)
			{
				cout << "There are no students" << endl;
				break;
			}
			deleteStudent();
			rewritingData();
			break;
		case EDIT:
			if (students_count == 0)
			{
				cout << "There are no students" << endl;
				break;
			}
			editInformation();
			rewritingData();
			break;
		case EXIT:
			delete[] students;
			system("pause");
			return 0;
		}
	}
}

int getInt(int from, int to)
{
	int number;
	while ((!(cin >> number)) || (number < from || number > to)) //cin >> number возвращает true если успешно записано
	{
		cin.clear(); // сбрасывает все биты потока, тоесть поток становится "хорошим", сбрасывает флаги ошибок, в противном случае повторный cin не сработает
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); //cin.ignore(n, k) извлекает и пропускает n символов 
															 //из потока пока не встретит символ k (т.е. пока не достигнет конца строки)
															 //numeric_limits<streamsize>::max() - наибольшее возможное значение для ввода (для печати)
		//очистка потока (отбрасываем максимальное число смволов, которое может содержать поток, до первого перевода строки включительно)
		cout << "Incorrect input. Please input integer number from " << from << " to " << to << endl;
	}
	return number;
}
int getCode()
{
	int kod;
	cout << "1 - View "								<< endl
		 << "2 - Adding new student "				<< endl
		 << "3 - Sorting (increasing the ranking) " << endl
		 << "4 - Delete student "					<< endl
		 << "5 - Editing of information"			<< endl
		 << "0 - EXIT "								<< endl;
	kod = getInt(EXIT, EDIT);
	return kod;
}
void checkFile()
{
	ifstream read("zapisi.txt", ios::in);
	if (!read.is_open())
	{
		read.close();
		ofstream create("zapisi.txt", ios::out);
		cout << "You have created new file" << endl;
		create.close();
	}
	read.close();
}
int getStringsCount()
{
	char str[1024];
	int str_count = 0;
	ifstream base("zapisi.txt");
	while (!base.eof())
	{
		base.getline(str, 1024, '\n');
		str_count++;
	}  
	base.close();
	return str_count;
}
void readFileStudents()
{
	ifstream fin("zapisi.txt", ios::in);
	if (!fin.is_open()) //связан ли текущий поток с файлом, 1 - открыт успешно, 0 - не открыт
	{
		cout << "The specified file does not exist!" << endl;
	}
	else
	{
		for (int i = 0; i < students_count && !fin.eof(); i++)
		{
			fin >> students[i].FIO
				>> students[i].year
				>> students[i].group
				>> students[i].physics
				>> students[i].math
				>> students[i].informatics
				>> students[i].chemistry;
			students[i].sr_b = (students[i].physics + students[i].math + students[i].informatics + students[i].chemistry) / 4.;
		}
	}
	fin.close();
}
void showStudentsArray()
{
		cout << "                                  INFORMATION ABOUT STUDENTS" << endl;
		cout << "============================================================================================" << endl;
		cout << setw(3) << "#" << setw(19) << "Surname" << setw(14) << "Year of birth" << setw(7) << "Group" << setw(8) << "Physics" << setw(5) << "Math" << setw(12) << "Informatics" << setw(10) << "Chemistry" << setw(14) << "Average score" << endl;
		cout << "============================================================================================" << endl;
	for (int i = 0; i < students_count; i++)
	{
		cout << setw(3)  << i + 1 
			 << setw(19) << students[i].FIO 
			 << setw(14) << students[i].year
			 << setw(7)  << students[i].group
			 << setw(8)  << students[i].physics
			 << setw(5)  << students[i].math 
		  	 << setw(12) << students[i].informatics
			 << setw(10) << students[i].chemistry
			 << setw(14) << students[i].sr_b << endl;
	}
	cout << "--------------------------------------------------------------------------------------------" << endl;
}
void sortingStudentsArray()
{
	cout << endl << "                                  * * * * * SORTING * * * * *" << endl;
	for (int i = 0; i < students_count - 1; i++) 
	{
		for (int j = i + 1; j < students_count; j++)
		{
			if (students[i].sr_b > students[j].sr_b)
			{
				swap(students[i], students[j]);
			}
		}
	}
}
void writeRezultToFile()
{
	ofstream fout_rezult("rezult.txt", ios::out);
	fout_rezult << "                                  INFORMATION ABOUT STUDENTS" << endl;
	fout_rezult << "============================================================================================" << endl;
	fout_rezult << setw(3) << "#" << setw(19) << "Surname" << setw(14) << "Year of birth" << setw(7) << "Group" << setw(8) << "Physics" << setw(5) << "Math" << setw(12) << "Informatics" << setw(10) << "Chemistry" << setw(14) << "Average score" << endl;
	fout_rezult << "============================================================================================" << endl;
	for (int i = 0; i < students_count; i++)
	{
		fout_rezult << setw(3)	<< i + 1
					<< setw(19) << students[i].FIO
					<< setw(14) << students[i].year
					<< setw(7)	<< students[i].group
					<< setw(8)	<< students[i].physics
					<< setw(5)	<< students[i].math
					<< setw(12) << students[i].informatics
					<< setw(10) << students[i].chemistry
					<< setw(14) << students[i].sr_b << endl;
	}
	fout_rezult << "--------------------------------------------------------------------------------------------" << endl;
	fout_rezult.close();
}
void rewritingData()
{
	ofstream fout("zapisi.txt", ios::out);
	for (int i = 0; i < students_count; i++)
	{
		fout << students[i].FIO << " "
			 << students[i].year << " "
			 << students[i].group << " "
			 << students[i].physics << " "
			 << students[i].math << " "
			 << students[i].informatics << " "
			 << students[i].chemistry << " ";
		if (i < students_count - 1)
		{
			fout << endl;
		}
	}
	fout.close();
}
void increaseSizeOfArray()
{
	StudentInformation *new_students_array = new StudentInformation[students_count + 1];
	for (int i = 0; i < students_count; i++)
	{
		new_students_array[i] = students[i];
	}
	delete[] students;
	students = new_students_array;
}
void addStudentinArray()
{
	increaseSizeOfArray();
	students_count++;
	cout << "Input information about new student" << endl;
	cout << "Student #" << students_count << endl;
	inputStudentInformation(students_count - 1);
}
void writeEndFileStudents()
{
	ofstream fadd("zapisi.txt", ios::app);
	fadd << endl;
	fadd << students[students_count-1].FIO		<< " "
		 << students[students_count-1].year		<< " "
		 << students[students_count-1].group		<< " "
		 << students[students_count-1].physics	<< " "
		 << students[students_count-1].math		<< " "
		 << students[students_count-1].informatics<< " "
		 << students[students_count-1].chemistry	<< " ";
	fadd.close();
}
void deleteStudent()
{
	int del_num;
	cout << "Which student do you want to delete? ";
	del_num = getInt(1, students_count);
	del_num--;

	for (int i = del_num; i < students_count-1; i++)
	{
		students[i] = students[i+1];
	}
	students_count--;
}
void editInformation()
{
	int edit_num;
	cout << "Which student do you want to edit? ";
	edit_num = getInt(1, students_count);
	cout << "Input new information about student #" << edit_num << endl;
	edit_num--;
	inputStudentInformation(edit_num);
}
void inputStudentInformation(int input_student_number)
{
	cout << "Surname -         ";
	cin >> students[input_student_number].FIO;

	cout << "Year of birth -   ";
	students[input_student_number].year = getInt(1900, 2017);

	cout << "Group -           ";
	cin >> students[input_student_number].group;

	cout << "Physics -         ";
	students[input_student_number].physics = getInt(0, 10);

	cout << "Math -            ";
	students[input_student_number].math = getInt(0, 10);

	cout << "Informatics -     ";
	students[input_student_number].informatics = getInt(0, 10);

	cout << "Chemistry -       ";
	students[input_student_number].chemistry = getInt(0, 10);

	cout << "Average Score -   ";
	students[input_student_number].sr_b = (students[input_student_number].physics
		+ students[input_student_number].math
		+ students[input_student_number].informatics
		+ students[input_student_number].chemistry) / 4.;
	cout << students[input_student_number].sr_b << endl;
}