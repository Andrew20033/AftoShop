#include <conio.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <vector>

using namespace std;

struct info
{
    char phone[15]; 
    char email[32]; 
};

struct TAvto
{
    char mk[64]; // Marka
    char model[64]; 
    int year; 
    char photo_name[64]; 
    int cost; 
    info inf;
};

typedef char* Name; 
typedef FILE File; 
Name NameFile = new char[32]; 
File* file; 
TAvto Avto;  
int flag = 0; 

void Menu(void) 
{
    system("cls");
    cout << "MENU" << endl
        << "1.Create / open base of cars" << endl
        << "2.Add car to base" << endl
        << "3.Delete car from base" << endl
        << "4.Viewing the entire database" << endl
        << "5.Update an entry with a given number" << endl
        << "6.Search for cars less than 30,000 grn" << endl
        << "7.Exit [ESC]" << endl;
}

void VvodAvto(TAvto& Avto) 
{
    cout << "<Add cars>" << endl;
    cout << "Marka of car: ";
    cin.getline(Avto.mk, 64);
    cin.clear();
    cout << "Model of car: ";
    cin.getline(Avto.model, 64);
    cin.clear();
    cout << "Year of issue: ";
    cin >> Avto.year;
    cin.get();
    cout << "Foto: ";
    cin.getline(Avto.photo_name, 64);
    cin.clear();
    cout << "Cost: ";
    cin >> Avto.cost;
    cin.get();
    cout << "<Information>" << endl;
    cin.clear();
    cout << "Telefon: ";
    cin >> Avto.inf.phone;
    cin.get();
    cout << "E-mail: ";
    cin.getline(Avto.inf.email, 32);
    cin.clear();
}

void Show_Avto(TAvto Avto) 
{
    cout << "Marka of car: " << Avto.mk << endl;
    cout << "Model of car: " << Avto.model << endl;
    cout << "Year of issue: " << Avto.year << endl;
    cout << "Foto: " << Avto.photo_name << endl;
    cout << "Cost: " << Avto.cost << endl;
    cout << "<Information>" << endl;
    cout << "Telefon: " << Avto.inf.phone << endl;
    cout << "E-mail: " << Avto.inf.email << endl;
}

void CreatOpenFile(Name& NameFile, int& flag) // Создание,открытие файла базы данных
{
    char YorN;
    flag = 0;
    cout << "Enter file name: ";
    gets(NameFile);
    file = fopen(NameFile, "r");
    if (file == NULL)
    {
        do
        {
            system("cls");
            cout << "File " << NameFile << " " << "does not exist!" << endl;
            cout << "Create file " << NameFile << " ?" << endl;
            cout << "Click Y / N" << endl;
            YorN = getch();
            if (YorN == 'Y' || YorN == 'y')
            {
                file = fopen(NameFile, "w");
                cout << "File create!" << endl;
                system("pause");
                flag = 1;
                fclose(file);
            }
            if (YorN == 'N' || YorN == 'n')
            {
                cout << "File doesnt create!" << endl;
                system("pause");
                fclose(file);
            }
        } while (!(YorN == 'Y' || YorN == 'y' || YorN == 'N' || YorN == 'n'));
    }
    else
    {
        flag = 1;
        fclose(file);
        cout << "File opened successfully!" << endl;
        system("pause");
    }
}

void RecordAvto(Name NameFile, TAvto& Avto, int flag) 
{
    if (flag)
    {
        file = fopen(NameFile, "a");
        VvodAvto(Avto);
        fwrite(&Avto, sizeof(Avto), 1, file);
        fclose(file);
    }
    else
    {
        cout << endl << "Choose a file to work!" << endl;
        cout << "Select item 1 in the menu!" << endl;
        getch();
    }
}

void Show_File() 
{
    int i = 0;
    if (flag)
    {
        file = fopen(NameFile, "r");
        cout << "Base of cars" << endl << endl;
        while (fread(&Avto, sizeof(TAvto), 1, file))
        {
            cout << "Record number: " << i + 1 << endl << endl;
            Show_Avto(Avto);
            cout << endl << endl;
            i++;

        }
        getch();
        fclose(file);
    }
    else
    {
        cout << "Choose a file to work!" << endl;
        cout << "Choose item 1 from the menu!" << endl;
        getch();
    }
}

long filesize(File* file) 
{
    long curpos, length;

    curpos = ftell(file); 
    fseek(file, 0L, SEEK_END); 
    length = ftell(file); 
    fseek(file, curpos, SEEK_SET); 
    return length;
}

void UpdateAvto(Name NameFile, TAvto& Avto, int flag)
{
    long i = 0;
    if (flag)
    {
        file = fopen(NameFile, "r+");
        cout << "Updating an entry with a given number" << endl << endl
            << "Enter the record number to update "
            << "(total records  "
            << (filesize(file) / sizeof(Avto))
            << "): ";
        cin >> i;
        fpos_t t; 
        fseek(file, (i - 1) * sizeof(Avto), SEEK_CUR); 
        fgetpos(file, &t);

        fread(&Avto, sizeof(Avto), 1, file);
        Show_Avto(Avto);
        cout << endl << endl;

        char YorN;
        cout << "Update the data?" << endl;
        cout << "Click Y / N" << endl;
        do
        {
            YorN = getch();
            if (YorN == 'Y' || YorN == 'y')
            {
                system("cls");
                VvodAvto(Avto); 
                fsetpos(file, &t); 
                fwrite(&Avto, sizeof(Avto), 1, file); 
                cout << "Данные обновлены!" << endl;
                fclose(file);
            }
            if (YorN == 'N' || YorN == 'n')
            {
                cout << "Data not updated!" << endl;
                fclose(file);
            }
        } while (!(YorN == 'Y' || YorN == 'y' || YorN == 'N' || YorN == 'n'));
        cout << endl << "Press any key to continue!" << endl;
        getch();
    }
    else
    {
        cout << endl;
        cout << "Choose a file to work" << endl
            << "Select item 1 in the menu";
        getch();
    }
}

void DeleteAvto(Name NameFile, TAvto& Avto, int flag) 
{
    long i = 0, k = 0;
    File* temp;
    if (flag)
    {
        file = fopen(NameFile, "r+");

        cout << "Deleting an entry from the database" << endl << endl
            << "Enter the entry number to delete "
            << "(total records "
            << (filesize(file) / sizeof(Avto))
            << "): ";
        cin >> i;

        fseek(file, (i - 1) * sizeof(Avto), SEEK_CUR); 
        fread(&Avto, sizeof(Avto), 1, file);
        Show_Avto(Avto);
        cout << endl;

        char YorN;
        cout << "Delete data ?" << endl;
        cout << "Y / N" << endl;
        do
        {

            YorN = getch();
            if (YorN == 'Y' || YorN == 'y')
            {
                fseek(file, 0L, SEEK_SET);

                temp = fopen("Temp", "w");
                while (fread(&Avto, sizeof(Avto), 1, file))
                {
                    if (k != (i - 1)) fwrite(&Avto, sizeof(Avto), 1, temp);
                    k++;
                }
                cout << "Entry deleted!" << endl;
                fclose(temp);
                fclose(file);
                remove(NameFile);   
                rename("Temp", NameFile);
            }
            if (YorN == 'N' || YorN == 'n')
            {
                cout << "Entry not deleted!" << endl;
                fclose(file);
            }
        } while (!(YorN == 'Y' || YorN == 'y' || YorN == 'N' || YorN == 'n'));

        cout << endl << "Press any key to continue!" << endl;
        getch();
    }
    else
    {
        cout << endl << "Choose a file to work!" << endl
            << "Select item 1 in the menu!";
        getch();
    }
}

void Poisk_Avto(Name NameFile, TAvto& Avto, int flag)
{
    if (flag)
    {
        vector <TAvto> vec_auto;
        file = fopen(NameFile, "r");
        fread(&Avto, sizeof(TAvto), 1, file);
        int fflag = 0;

        file = fopen(NameFile, "r");
        while (fread(&Avto, sizeof(TAvto), 1, file))
        {
            if (Avto.cost < 300000)
                vec_auto.push_back(Avto);
        }

        for (unsigned int iter = 0; iter < vec_auto.size(); ++iter) {
            cout << "Marka of car: " << vec_auto.at(iter).mk << endl;
            cout << "Model of car: " << vec_auto.at(iter).model << endl;
            cout << "Year of issue: " << vec_auto.at(iter).year << endl;
            cout << "Foto: " << vec_auto.at(iter).photo_name << endl;
            cout << "Cost: " << vec_auto.at(iter).cost << endl;
            cout << "Information" << endl;
            cout << "Telefon: " << vec_auto.at(iter).inf.phone << endl;
            cout << "E-mail: " << vec_auto.at(iter).inf.email << endl;
            cout << "*******" << endl;
        }

        getch();
        fclose(file);
    }
    else
    {
        cout << endl;
        cout << "Choose a file to work!" << endl
            << "Select item 1 in the menu!";
        getch();
    }
}

int main()
{
    SetConsoleCP(1251); 
    SetConsoleOutputCP(1251); 

    char YorN;
    system("cls");
    do
    {
        Menu();
        YorN = getch();
        switch (YorN)
        {
        case '1':   system("cls");
            CreatOpenFile(NameFile, flag);
            break;
        case '2':   system("cls");
            RecordAvto(NameFile, Avto, flag);
            break;
        case '3':   system("cls");
            DeleteAvto(NameFile, Avto, flag);
            break;
        case '4':   system("cls");
            Show_File();
            break;
        case '5':   system("cls");
            UpdateAvto(NameFile, Avto, flag);
            break;
        case '6':   system("cls");
            Poisk_Avto(NameFile, Avto, flag);
            break;
        case '7':
            exit(1);
        }
    } while (YorN != 27);
    return 0;
}