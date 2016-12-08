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

class Sort {
public:
    Sort(string, string, int buffer_size);

    
    Sort(Sort const &) = delete;
    auto operator = (Sort const &) -> Sort & = delete;
    Sort(Sort && ) = delete;
    auto operator = (Sort && ) -> Sort & = delete;

private:
    auto sort() -> void;
    auto make_file(string, vector<S> &) -> void;
    auto remove_create_files() -> void;
    auto generate() -> void;

    vector<string> file_;
    string file1;
    string file2;
    long long buffer_size;
};

Sort::Sort(string str1, string str2, int size)
        : file1(str1),
          file2(str2),
          buffer_size(size * 1024 * 1024)
{
    generate();
    sort();
}

auto Sort::make_file(std::string name_file, std::vector<S> & arr) -> void 
{
    ofstream file(name_file);
    if (!file) 
    {
        std::logic_error("Error: file not open");
    }
    for (int i = 0; i < arr.size(); ++i) {
        file << arr[i] << std::endl;
    }
    file.close();
}

auto Sort::generate() -> void {
    ifstream file(file1);

    unsigned long size = 0;
    string name_file = "0";
    S data;
    vector<S> arr(buffer_size / 24);
    arr.clear();

    while (file >> data) {
        arr.push_back(data);
        ++size;
        if (buffer_size / 24 <= size) {
            file_.push_back(name_file);
            sort(arr.begin(), arr.end());
            make_file(name_file, arr);
            name_file = file_.size();
            size = 0;
            arr.clear();
        }
    }
    if (arr.size() > 0) {
        sort(arr.begin(), arr.end());
        file_.push_back("end.txt");
        make_file("end.txt", arr);
    }
    file.close();
}


auto Sort::sort() -> void {
    std::priority_queue<A> other;
    for (int i = 0; i < file_.size(); ++i) {
        A tmp = {new ifstream(file_[i])};
        *tmp.ptr >> tmp.data;
        other.push(tmp);
    }
    std::ofstream tmp(file2);
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

auto Sort::remove_create_files() -> void {
    for (int i = 0; i < file_.size(); ++i) {
        auto a = file_[i].c_str();
        std::remove(a);
    }
}


bool operator > (const S & s1, const S & s2) 
{ return s1.name > s2.name; }

bool operator < (const S & s1, const S & s2) 
{ return s1.name < s2.name; }

bool operator < (const A & s1, const A & s2) 
{ return s1.data > s2.data; }

ostream & operator << (ostream & output, S const & s) {
    output << s.surname << " " << s.name << " " << s.year;
    return output;
}

istream & operator >> (istream & input, S & s) {
    input >> s.surname >> s.name >> s.year;
    return input;
}
