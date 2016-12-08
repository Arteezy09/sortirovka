#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <functional>
#include <algorithm>
#include <queue>
#include <string>


using namespace std;


struct S
{
    string surname;
    string name;
    int year;
    unsigned long length() { return surname.size() + name.size() + sizeof(year); }
};


struct A
{
    ifstream *ptr;
    S data;
};


bool operator > (const S & s1, const S & s2){
    return s1.surname > s2.surname;
}

bool operator < (const S & s1, const S & s2){
    return s1.surname < s2.surname;
}

bool operator < (const A & s1, const A & s2){
    return s1.data > s2.data;
}

ostream & operator << (ostream & output, S const & s)
{
    output << s.surname << " " << s.name << " " << s.year;
    return output;
}

istream & operator >> (istream & input, S & s)
{
    input >> s.surname >> s.name >> s.year;
    return input;
}


class Sort {
public:
    Sort(string, string, int buffer_size);

    Sort(Sort const &) = delete;
    auto operator=(Sort const &) -> Sort & = delete;
    Sort(Sort &&) = delete;
    auto operator=(Sort &&) -> Sort & = delete;

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

_sort::_sort(string s1, string s2, int size) : f1(s1), f2(s2),
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
        file << arr[i] << endl;
    }
    file.close();
}

void _sort::generate() 
{
    ifstream file(f1);

    unsigned long size = 0;
    string name_file = "0";
    S data;
    std::vector<S> arr(buffer_size / 24);
    arr.clear();

    while (file >> data) {
        arr.push_back(data);
        ++size;
        if (buffer_size / 24 <= size) {
            f.push_back(name_file);
            sort(arr.begin(), arr.end());
            make_file(name_file, arr);
            name_file = f.size();
            size = 0;
            arr.clear();
        }
    }
    if (arr.size() > 0) {
        sort(arr.begin(), arr.end());
        f.push_back("end.txt");
        make_file("end.txt", arr);
    }
    file.close();

}


void _sort::sort() 
{
    std::priority_queue<T> other;
    for (int i = 0; i < f.size(); ++i) {
        A tmp = {new std::ifstream(f[i])};
        *tmp.ptr >> tmp.data;
        other.push(tmp);
    }
    std::ofstream tmp(f2);
    std::string word;
    while (!other.empty()) {
        A tmp1 = other.top();
        tmp << tmp1.data << endl;
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
