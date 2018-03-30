#include "BPlusTree.hpp"

void DisplayPage(PagePtr& page, int depth)
{
	auto indent = [](int depth) {
		for (int i = 0; i < depth; i++)
		{
			cout << "    ";
		}
	};
	indent(depth);
	if (page->isLeaf())
	{
		auto leaf = std::dynamic_pointer_cast<LeafPage>(page);
		for (int i = 0, n = leaf->keys.size(); i < n; i++)
		{
			cout << "[" << leaf->keys.at(i) << ", ";
			cout << leaf->values.at(i) << "]";
		}
		cout << endl;
	}
	else
	{
		auto indexPage = std::dynamic_pointer_cast<IndexPage>(page);
		for (int i = 0, n = indexPage->keys.size(); i < n; i++)
		{
			cout << "(" << indexPage->keys.at(i) << ")";
		}
		cout << endl;
		for (PagePtr& pointer : indexPage->pointers)
		{
			DisplayPage(pointer, depth + 1);
		}
	}
}

LeafPage::LeafPage()
	: nextPage()
{
}

bool LeafPage::isLeaf()
{
	return true;
}

void LeafPage::append(Key key, Value value)
{
	keys.push_back(key);
	values.push_back(value);
}

IndexPage::IndexPage()
{
}

bool IndexPage::isLeaf()
{
	return false;
}

PagePtr IndexPage::before(int k)
{
	return pointers.at(k);
}

PagePtr IndexPage::after(int k)
{
	return pointers.at(k + 1);
}

LeafPagePtr BPlusTree::search(PagePtr page, Key key)
{
    if(page->isLeaf())
    {
        return std::dynamic_pointer_cast<LeafPage>(root);
    }
    else
    {
        auto ip = std::dynamic_pointer_cast<IndexPage>(page);
        if(key < ip->keys.at(0))
        {
            return search(ip->before(0), key);
        }
        else if(key > ip->keys.at(ip->keys.size() - 1))
        {
            return search(ip->after(ip->keys.size() - 1), key);
        }
        else
        {
            int i=0, n = ip->keys.size();
            bool done = false;
            while(!done && i<n)
            {
                if(key <= ip->keys.at(i))
                {
                    i++;
                }
                else
                {
                    done = true;
                }
            }
            return search(ip->after(i), key);
        }
    }
}

IndexPagePtr BPlusTree::insertIntoTree(IndexPagePtr root, Key newKey, Value value)
{
    LeafPagePtr leaf = search(root, newKey);
    return insertIntoNode(leaf, newKey, value);
}

/*
 * Try to insert the (newKey/value) pair
 * into the node.
 *
 * if 'target' is an interior node,
 * then 'value' must be a page pointer.
 *
 * The tree distinct cases are:
 * 1. The target node has available space for one more key.
 * 2. The target node is full, but its parent has space for one more key.
 * 3. The target node and its parent are both full.
 */
IndexPagePtr BPlusTree::insertIntoNode(
        PagePtr target, Key newKey, Value value)
{
    throw string("not implemented");
}
