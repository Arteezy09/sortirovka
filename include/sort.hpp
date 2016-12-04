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


struct A
{
    ifstream *ptr;
    stud data;
};

auto operator>(const stud & tmp1, const stud & tmp2)->bool {
    return tmp1.surname > tmp2.surname;
}

auto operator<(const stud & tmp1, const stud & tmp2)->bool {
    return tmp1.surname < tmp2.surname;
}

bool operator<(const A &s1, const A &s2) {
    return s1.data > s2.data;
}

ostream & operator<<(ostream & output, stud const & str)
{
    output << str.surname << " " << str.name << " " << str.year;
    return output;
}

istream & operator>>(istream & input, stud & str)
{
    input >> str.surname >> str.name >> str.year;
    return input;
}

class File_sort {
public:
    File_sort(std::string, std::string, int buffer_size);

    File_sort(File_sort const &) = delete;

    auto operator=(File_sort const &) -> File_sort & = delete;

    File_sort(File_sort &&) = delete;

    auto operator=(File_sort &&) -> File_sort & = delete;



private:
    auto sort() -> void;

    auto make_file(std::string, std::vector<stud>) -> void;

    auto remove_create_files() -> void;

    auto generate() -> void;

    std::vector<std::string> arr_name_file;
    std::string name_input_file;
    std::string name_output_file;
    long long buffer_size;
};

File_sort::File_sort(std::string str1, std::string str2, int size)
        : name_input_file(str1),
          name_output_file(str2),
          buffer_size(size * 1024 * 1024) {
    generate();
    sort();
}

auto File_sort::make_file(std::string name_file, std::vector<stud> arr) -> void {
    std::ofstream file(name_file);
    if (!file) {
        std::logic_error("Error: file not open");
    }
    for (int i = 0; i < arr.size(); ++i) {
        file << arr[i] << std::endl;
    }
    file.close();
}

auto File_sort::generate() -> void {
    std::ifstream file(name_input_file);

    unsigned long size = 0;
    std::string name_file = "0";
    stud data;
    std::vector<stud> arr;

    while (file >> data) {
        size += data.length();
        if (buffer_size - data.length() <= size) {
            arr_name_file.push_back(name_file);
            std::sort(arr.begin(), arr.end());
            make_file(name_file, arr);
            name_file = arr_name_file.size();
            size = (unsigned long) data.length();
            arr.clear();
        }
        arr.push_back(data);
    }
    if (arr.size() > 0) {
        std::sort(arr.begin(), arr.end());
        arr_name_file.push_back("end.txt");
        make_file("end.txt", arr);
    }
    file.close();
}


auto File_sort::sort() -> void {
    std::priority_queue<A> other;
    for (int i = 0; i < arr_name_file.size(); ++i) {
        A tmp = {new std::ifstream(arr_name_file[i])};
        *tmp.ptr >> tmp.data;
        other.push(tmp);
    }
    std::ofstream tmp(name_output_file);
    std::string word;
    while (!other.empty()) {
        A tmp1 = other.top();
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

auto File_sort::remove_create_files() -> void {
    for (int i = 0; i < arr_name_file.size(); ++i) {
        auto a = arr_name_file[i].c_str();
        std::remove(a);
    }
}
