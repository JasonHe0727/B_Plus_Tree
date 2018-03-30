#include "Test.hpp"
#include "BPlusTree.hpp"
#include <vector>
#include <string>
#include <iostream>
using std::make_shared;
using std::vector;
using std::string;
using std::cout;
using std::endl;

void CreateTree()
{
    cout << "This is a test for B+ tree!" << endl;
    auto page1 = make_shared<LeafPage>();
    for(int item: vector<int>{1,2,3,4})
    {
        page1->append(item, string(""));
    }
    auto page2 = make_shared<IndexPage>();
    page2->pointers.push_back(page1);
    page2->keys.push_back(5);
    auto page3 = make_shared<LeafPage>();
    for(int item: vector<int>{5,6,7,8})
    {
        page3->append(item, string(""));
    }
    page2->pointers.push_back(page3);
    page2->keys.push_back(10);
    auto page4 = make_shared<LeafPage>();
    page4->append(10, string(""));
    page2->pointers.push_back(page4);
    PagePtr startPage = std::dynamic_pointer_cast<Page>(page2);
    DisplayPage(startPage, 0);
}
