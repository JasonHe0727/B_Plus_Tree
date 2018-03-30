#ifndef BPLUSTREE_HPP
#define BPLUSTREE_HPP

#include <iostream>
#include <memory>
#include <string>
#include <vector>
using std::cout;
using std::endl;
using std::shared_ptr;
using std::string;
using std::vector;

class Page;
class LeafPage;
class IndexPage;
class BPlusTree;

using Key = int;
using Value = string;
using PagePtr = shared_ptr<Page>;
using LeafPagePtr = shared_ptr<LeafPage>;
using IndexPagePtr = shared_ptr<IndexPage>;

class Page
{
public:
	virtual bool isLeaf() = 0;
};

/*
 * [ k0 | v0 | k1 | v1 | k2 | v2 ]
 *
 * We can always assert that
 * p.keys.size() == p.values.size() for all nodes p.
 */
class LeafPage : public Page
{
public:
	vector<Key> keys;
	vector<Value> values;
	PagePtr nextPage;
	LeafPage();
	virtual bool isLeaf() override;
	void append(Key key, Value value);
};

/*
 * [ * | k0 | * | k1 | * | k2 | * | k3 | * ]
 *     where '*' stands for page pointer
 * We can always assert that p.keys.size() + 1 == p.pointers.size().
 */
class IndexPage : public Page
{
public:
	vector<Key> keys;
	vector<PagePtr> pointers;
	IndexPage();
	virtual bool isLeaf() override;
	PagePtr before(int k);
	PagePtr after(int k);
};

class BPlusTree
{
public:
    PagePtr root;
    LeafPagePtr search(PagePtr page, Key key);
    IndexPagePtr insertIntoTree(
            IndexPagePtr root, Key newKey, Value value);
    IndexPagePtr insertIntoNode(
            PagePtr target, Key newKey, Value value);
};

void DisplayPage(PagePtr& page, int depth);

#endif // BPLUSTREE_HPP
