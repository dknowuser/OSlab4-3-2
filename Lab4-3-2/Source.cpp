//����������-��������
#include <Windows.h>
#include <iostream>
#include <conio.h>
#define STR_SIZE 512

void main(void)
{
	setlocale(LC_ALL, "Russian");

	//�������� ���������� ���� ����������� ����������
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD CursorPos;
	CursorPos.X = 0;
	CursorPos.Y = 7;

	//�������� ������������� �����
	HANDLE hdl = CreateFile(TEXT("E:\\Temp\\new.txt"), GENERIC_READ, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING, NULL, NULL);
	if (hdl == INVALID_HANDLE_VALUE)
	{
		std::cout << "������ ��� �������� ������������� �����." << std::endl;
		std::cin.clear();
		std::cin.sync();
		getch();
		return;
	};
	std::cout << "�������� ����������: " << hdl << std::endl << std::endl;

	HANDLE hdlmap = CreateFileMapping(hdl, NULL, PAGE_READONLY, NULL, NULL, TEXT("My_mapping_object"));
	if (hdlmap == NULL)
	{
		std::cout << "������ ��� �������� ������������� �����." << std::endl;
		std::cin.clear();
		std::cin.sync();
		getch();
		return;
	};
	std::cout << "���������� ������� �������� �����: " << hdlmap << std::endl << std::endl;

	//������������� ��������� ����� � ������
	LPVOID MapViewAddr;
	if ((MapViewAddr = MapViewOfFile(hdlmap, FILE_MAP_READ, NULL, NULL, NULL)) == NULL)
	{
		std::cout << "������ ��� ������������� ��������� ����� � ������." << std::endl;
		std::cin.clear();
		std::cin.sync();
		getch();
		return;
	};
	std::cout << "������� ����� ������� �������������: " << MapViewAddr << std::endl << std::endl;

	std::cout << "����������� ������:" << std::endl;

	while (true)
	{
		unsigned int Temp = 0;
		char* MapPointer = (char*)MapViewAddr;

		while (Temp < STR_SIZE)
		{
			std::cout << *MapPointer;

			MapPointer++;
			Temp++;
		};

		//���������� ������ � �������� �������
		SetConsoleCursorPosition(hConsole, CursorPos);
	};

	getch();
};