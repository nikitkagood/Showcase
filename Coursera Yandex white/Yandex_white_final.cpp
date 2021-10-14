//��� ��� ������� ��������� ������ ����� ������ ���������� �� C++: ����� ���� (�� ������ � ����) �� Cousera
//������� �������� �� �������� ������ � ���������, ������� ����� �������� ������������� � ����� ������ ��� � ��� ����� ��������� ������-�� �����������
//�� ����, ��� ����� ���� ������ ��� ������, ��������� ��������� map (������ �� ���������� �����)
//�� � �� ����, ��� ����� ��� �������� ������� ����� ����� ������� �� ���� ����, ��� ���� ��� ����, � � map ��� ����� ������������
//��������� � �� ������� ���� ����, � ������ ��� � ������ �������������: � �� ����� ������������ ������� � �� �������������� �� ����, ��� ������� �� ���� ��������� ����������� ��������

//���� �� �����-�� ������� ������ ������� ������� ���� ������ � ����� ��� � ��������� - �� ����, �� �����������

//��� ������� ���� �������� ��� � ������

#include<iostream>
#include<map>
#include<vector>
#include<algorithm>
#include<iomanip>
#include<string>
#include<sstream>

using namespace std;

//Functionality:
//-���������� ������� : Add ���� �������
//- �������� ������� : Del ���� �������
//- �������� ���� ������� �� ���������� ���� : Del ����
//- ����� ������� �� ���������� ���� : Find ����
//- ������ ���� ������� �� ��� ���� : Print

vector commands
{
    "Add", //AddEvent
    "Del", //DeleteEvent, DeleteDate
    "Find", //Find
    "Print",  //Print
    "Exit" 
};

map<string, int> commands_map
{
    {commands[0], 1}, //AddEvent
    {commands[1], 2}, //DeleteEvent, DeleteDate
    {commands[2], 3}, //Find
    {commands[3], 4}, //Print
    {commands[4], 99}
};

class Date { //����-��-��
public:
    Date()
    {
        year = 0;
        month = 0;
        day = 0;
    }

    Date(int year, int month, int day)
    {
        this->year = year;
        this->month = month;
        this->day = day;
    }

    int GetYear() const
    {
        return year;
    }
    int GetMonth() const
    {
        return month;
    }
    int GetDay() const
    {
        return day;
    }

    friend bool operator == (const Date& lhs, const Date& rhs)
    {
        return lhs.GetYear() == rhs.GetYear() && lhs.GetMonth() == rhs.GetMonth() && lhs.GetDay() == rhs.GetDay();
    }

    friend bool operator < (const Date& lhs, const Date& rhs)
    {
        return lhs.GetYear() < rhs.GetYear() && lhs.GetMonth() < rhs.GetMonth() && lhs.GetDay() < rhs.GetDay();
    }

    friend ostream& operator << (ostream& os, const Date& date)
    {
        os << date.GetYear() << date.GetMonth() << date.GetDay();
        return os;
    }


private:
    int year = 0;
    int month = 0;
    int day = 0;
};

class Database {
public:
    void AddEvent(const Date& date, const string& event) // ������� - ������ ��� ������������
    {
        if (date.GetMonth() > 12 || date.GetMonth() < 0)
        {
            string error = "Month value is incorrect: " + date.GetMonth();
            throw runtime_error(error);
        } 
        if (date.GetDay() > 31 || date.GetDay() < 0)
        {
            string error = "Day value is invalid: " + date.GetDay();
            throw runtime_error(error);
        }

        bool already_exists = false;
        for (auto& item : db)
        {
            if (item.first == date && item.second == event)
            {
                already_exists = true;
            }
        }
        if(!already_exists) db.insert({ date, event });

        

        //���� ����� ������
        //if (db[dates] != event)
        //{
        //    dates.push_back(date);
        //    db.insert({ dates, event });
        //}
        

    }

    bool DeleteEvent(const Date& date, const string& event)
    {
        for (multimap<Date, string>::iterator iter = db.begin(); iter != db.end();++iter)
        {
            if (iter->second == event)
            {
                db.erase(iter);
                cout << "Event was deleted successfully" << endl;
                return true;
            }
        }
        throw runtime_error("There is no such event on this date");
        return false;

    }

    int DeleteDate(const Date& date) //���������� ���-�� ��������� ��������� �������
    {
        auto range = db.equal_range(date);
        int counter = 0;

        for (auto& i = range.first; i != range.second ; ++i)
        {
            ++counter;
        }

        if (counter == 0) return counter;
        else
        db.erase(date);
        return counter;
    }

    void Find(const Date& date) const //����������� ��� ������� � ��������� ����
    {
        auto range = db.equal_range(date);
        if (range.first == range.second)
        {
            throw runtime_error("There is no such date");
        }
        else 
        {
            for (auto& i = range.first; i != range.second; ++i)
            {
                cout << i->second << endl;
            }
        }
        
    }

    void Print() const
    {
        if (db.empty()) cout << "There is nothing to print" << endl;
        else
        {
            for (auto& i : db)
            {
                cout << setw(4) << setfill('0') << i.first.GetYear() << "-" << setw(2) << setfill('0') << i.first.GetMonth() << "-" << setw(2) << setfill('0') << i.first.GetDay() << " " << i.second << endl;
            }
        }
    }

private:
    //map<set<Date>, string> db;

    //vector<Date> dates;
    //map<vector<Date>, string> db;

    multimap<Date, string> db;
};

void CheckNextSymbolAndSkip(stringstream& ss)
{
    if (ss.peek() != '-') throw exception("The date is invalid");
    ss.ignore(1);
}

void CheckCommand(string method)
{
    bool isCommand = false;
    for (int i = 0; i < commands.size(); ++i)
    {
        if (method == commands[i]) isCommand = true;
    }
    string errmsg1 = "There is no such command: " + method;
    if (isCommand == false) throw runtime_error(errmsg1);
}
Date ParseDate(stringstream& ss)
{
    int year;
    int month;
    int day;

    ss >> year;
    CheckNextSymbolAndSkip(ss);
    ss >> month;
    CheckNextSymbolAndSkip(ss);
    ss >> day;

    Date date{ year, month, day };
    return date;
}

string ParseEvent(stringstream& ss)
{
    string event;
    ss >> event;

    return event;
}

int main() {
    //MAIN SECTION
    Database db;
    Date date;
    stringstream ss;
    string command; //��� ������ ���� ���������� � ���������, ������ � ���� ��� ������, �������� �������������
    string db_method; //� �� ������ command, �� ��� �������. ������ � ���� ���� ��������, ������� �������� ������������ 
    string event;
    
    cout << "Input: COMMAND YYYY-MM-DD EVENT" << endl;


    while (getline(cin, command)) { //��� ������ ���� ���������� � ���������, � �� ������ cin << arg1 << arg2 << arg3 � �.�.
        try
        {
            ss << command;
            ss >> db_method;

            CheckCommand(db_method);

            if(ss.peek() == ' ')
            date = ParseDate(ss);
            if (ss.peek() == ' ')
            event = ParseEvent(ss);
        
            switch (commands_map[db_method])
            {
            case(1): //Add
                db.AddEvent(date, event);
                break;

            case(2): //Del
                if (!event.empty())
                db.DeleteEvent(date, event);
                else
                db.DeleteDate(date);
                break;

            case(3):
                db.Find(date);
                break;

            case(4):
                db.Print();
                break;

            case(99):
                exit(0); //����� �� ��������� �� �������� ������������

            default:
                throw runtime_error("Switch statement went wrong");
                break;
            }
        }
        catch (const std::runtime_error& rterr)
        {
            cerr << rterr.what() << endl;
        }
        catch (const std::exception& ex)
        {
            cerr << ex.what() << endl;
            exit(-1);
        }

        ss.clear();
    }

    //TEST SECTION
    //Date a(2020, 7, 8);
    //Date b;

    //a.year = 2021;
    //a.month = 7;
    //a.day = 8;

    //b.year = 2021;
    //b.month = 8;
    //b.day = 8;
    //bool c = a < b;
    //cout << c << endl;

    //db.AddEvent(a, "shit happened");
    //db.AddEvent(a, "shit happened");
    //db.AddEvent(a, "shit happened twice");

    //db.DeleteEvent(a, "shit happened twice");
    //cout << db.DeleteDate(a);

    //db.Find(a);

    //db.Print();

    return 0;
}