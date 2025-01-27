#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>


class FileSystem {
public:
    virtual ~FileSystem() = default;
    virtual void showDetails(int) const = 0;
};


class File : public FileSystem {
private:
    std::string fname_;
public:
    File(const std::string &file) : fname_(file) {}
    void showDetails(int depth = 0) const override {
        std::cout << std::string(depth * 2 , ' ') << " -File: " << fname_ << std::endl;
    }
};

class Directory : public FileSystem {
private:
    std::string dname_;
    std::vector<std::shared_ptr<FileSystem>> vec;
public:
    Directory(const std::string &director) : dname_(director) {}
    void showDetails(int depth = 0) const override {
        std::cout << std::string(depth * 2, ' ') << " + Directory: " << dname_ << std::endl; 
        for(const auto& ptr : vec) {
            ptr->showDetails(depth + 1);
        }
    }
    void remove(std::shared_ptr<FileSystem> component) {
        auto it = std::find(vec.begin(), vec.end(),component);
        if(it != vec.end()) {
            vec.erase(it);
        }else {
            std::cout << "Component Not Found" << std::endl;
        }
    }
    void addElement(const std::shared_ptr<FileSystem> obj) {
        vec.push_back(obj);
    }
};
int main () {
    auto file1 = std::make_shared<File>("file1");
    auto file2 = std::make_shared<File>("file2");
    auto file3 = std::make_shared<File>("file3");

    auto root = std::make_shared<Directory>("Root");
    auto subdir = std::make_shared<Directory>("Dir1");
    auto subdir1 = std::make_shared<Directory>("Dir2");

    root->addElement(file1);
    root->addElement(subdir);
    subdir1->addElement(file2);
    root->addElement(subdir);
    subdir->addElement(file3);

    std::cout << "Show Catalogs" << std::endl;
    root->showDetails();

}