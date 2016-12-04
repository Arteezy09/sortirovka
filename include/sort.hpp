#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <functional>
#include <algorithm>
#include <queue>

using namespace std;

struct stud
{
    string surname;
    string name;
    int year;
    unsigned long length() { return surname.size() + name.size() + sizeof(year); }
};


struct T
{
    ifstream *ptr;
    stud data;
};


bool operator > (const stud & st1, const stud & st2) {
    return st1.surname > st2.surname;
}

bool operator < (const stud & st1, const stud & st2) {
    return st1.surname < st2.surname;
}

bool operator < (const T & st1, const T & st2) {
    return st1.data > st2.data;
}

ostream & operator << (ostream & output, stud const & st)
{
    output << st.surname << " " << st.name << " " << st.year;
    return output;
}

istream & operator >> (istream & input, stud & st)
{
    input >> st.surname >> st.name >> st.year;
    return input;
}


class _sort {
public:
    _sort(string, string, int buffer_size);

    _sort(_sort const &) = delete;
    auto operator=(_sort const &) -> _sort & = delete;
    _sort(_sort &&) = delete;
    auto operator=(_sort &&) -> _sort & = delete;

private:
    
    void sort();
    void make_file(string, vector<stud>);
    void remove_create_files();
    void generate();

    vector<string> f;
    string f1;
    string f2;
    long long buffer_size;
};

_sort::_sort(string st1, string st2, int size) : f1(st1), f2(st2),
    buffer_size(size * 1024 * 1024) {
    generate();
    sort();
}

void _sort::make_file(string name_file, vector<stud> arr) 
{
    ofstream file(name_file);
    if (!file) 
    {
        std::logic_error("Error: file not open");
    }
    for (int i = 0; i < arr.size(); ++i)
    {
        file << arr[i] << std::endl;
    }
    file.close();
}

void _sort::generate() 
{
    ifstream file(f1);
    unsigned long size = 0;
    string name_file = "0";
    stud data;
    vector<stud> arr;

    while (file >> data) {
        size += data.length();
        if (buffer_size - data.length() <= size) {
            f.push_back(name_file);
            std::sort(arr.begin(), arr.end());
            make_file(name_file, arr);
            name_file = f.size();
            size = (unsigned long) data.length();
            arr.clear();
        }
        arr.push_back(data);
    }
    if (arr.size() > 0) {
        std::sort(arr.begin(), arr.end());
        f.push_back("end.txt");
        make_file("end.txt", arr);
    }
    file.close();
}


void _sort::sort() 
{
    std::priority_queue<T> other;
    for (int i = 0; i < f.size(); ++i) {
        T tmp = {new std::ifstream(f[i])};
        *tmp.ptr >> tmp.data;
        other.push(tmp);
    }
    std::ofstream tmp(f2);
    std::string word;
    while (!other.empty()) {
        T tmp1 = other.top();
        tmp << tmp1.data << std::endl;
        other.pop();
        if (!tmp1.ptr->eof() && *tmp1.ptr >> tmp1.data) {
            other.push(tmp1);
        } else {
            tmp1.ptr->close();
        }
    }
    remove_create_files();
}

void _sort::remove_create_files()
{
    for (int i = 0; i < f.size(); ++i) 
    {
        auto a = f[i].c_str();
        std::remove(a);
    }
}
