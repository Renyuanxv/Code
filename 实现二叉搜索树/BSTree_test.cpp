#include <iostream>
using namespace std;
template<class T>
struct BSTNode
{
    BSTNode(const T& data = T())
        : _pLeft(nullptr)
        , _pRight(nullptr)
        , _data(data)
    {}
    BSTNode<T>* _pLeft;
    BSTNode<T>* _pRight;
    T _data;
};

template<class T>
class BSTree
{
    typedef BSTNode<T> Node;
    typedef Node* PNode;
public:
    BSTree()
        : _pRoot(nullptr) {
    }

    ~BSTree() {
        _Destroy(_pRoot);
    }

    void _Destroy(PNode _pRoot) {
        if (_pRoot == nullptr)
            return;
        _Destroy(_pRoot->_pLeft);
        _Destroy(_pRoot->_pRight);
        delete _pRoot;
    }
    //拷贝构造
    BSTree(const BSTree<T>& tree) {
        _pRoot = Copy(tree._pRoot);
    }
    //赋值运算符重载
    BSTree<T>& operator =(const BSTree<T>& tree) {
        if (this != &tree) {
            _Destroy(_pRoot);
            _pRoot = Copy(tree._pRoot);
        }
        return *this;
    }

    PNode Copy(PNode root) {
        if (root == nullptr)
            return root;
        PNode NewRoot = new Node(root->_data);
        NewRoot->_pLeft = Copy(root->_pLeft);
        NewRoot->_pRight = Copy(root->_pRight);
        return NewRoot;
    }

    void Print_Tree() {
        Inorder(_pRoot);
        cout << endl;
    }
    void Inorder(PNode root) {//中序遍历二叉搜索树 是其是从小到大的顺序
        if (root) {
            Inorder(root->_pLeft);
            cout << root->_data << " ";
            Inorder(root->_pRight);
        }
    }

    PNode Find(const T& data) {
        PNode pCur = _pRoot;
        while (pCur)
        {
            if (data == pCur->_data)
                return pCur;
            else if (data < pCur->_data)
                pCur = pCur->_pLeft;
            else
                pCur = pCur->_pRight;
        }
        return nullptr;
    }

    bool Insert(const T& data) {
        // 如果树为空，直接插入
        if (nullptr == _pRoot) {
            _pRoot = new Node(data);
            return true;
        }
        // 按照二叉搜索树的性质查找data在树中的插入位置
        PNode pCur = _pRoot;
        // 记录pCur的双亲，因为新元素最终插入在pCur双亲左右孩子的位置
        PNode pParent = nullptr;
        while (pCur) {
            pParent = pCur;
            if (data < pCur->_data)
                pCur = pCur->_pLeft;
            else if (data > pCur->_data)
                pCur = pCur->_pRight;
            else
                // 元素已经在树中存在
                return false;
        }
        // 插入元素
        pCur = new Node(data);
        if (data < pParent->_data)
            pParent->_pLeft = pCur;
        else
            pParent->_pRight = pCur;
        return true;
    }

    bool Erase(const T& data) {
        // 如果树为空，删除失败
        if (nullptr == _pRoot)
            return false;
        // 查找在data在树中的位置
        PNode pCur = _pRoot;
        PNode pParent = nullptr;
        while (pCur) {
            if (data == pCur->_data)
                break;
            else if (data < pCur->_data) {
                pParent = pCur;
                pCur = pCur->_pLeft;
            }
            else {
                pParent = pCur;
                pCur = pCur->_pRight;
            }
        }
        // data不在二叉搜索树中，无法删除
        if (nullptr == pCur)
            return false;

        Node* Del = pCur;
        // 当前节点是叶子节点或者只有左节点---可直接删除	
        if (nullptr == pCur->_pRight) {
            //要删除的节点是根节点
            if (pParent == nullptr)
                _pRoot = _pRoot->_pLeft;
            if (pParent->_pLeft == pCur)
                pParent->_pLeft = pCur->_pLeft;
            else
                pParent->_pRight = pCur->_pLeft;
        }

        // 当前节点只有右孩子---可直接删除
        else if (nullptr == pCur->_pLeft) {
            if (pParent == nullptr)
                _pRoot = _pRoot->_pRight;
            if (pParent->_pLeft == pCur)
                pParent->_pLeft = pCur->_pRight;
            else
                pParent->_pRight = pCur->_pRight;
        }
        // 当前节点左右孩子都存在，直接删除不好删除，可以在其子树中找一个替代结点，比如：
        // 找其左子树中的最大节点，即左子树中最右侧的节点，或者其右子树中最小的节点，即右子树中最左侧的节点
        // 替代节点找到后，将替代节点中的值交给待删除节点，转换成删除替代节点
        else {
            PNode Replace = pCur->_pRight;
            PNode Pre = pCur;//替代节点的双亲节点
            if (Replace->_pLeft) {
                //用节点右子树的最小节点作为替代节点
                Pre = Replace;
                Replace = Replace->_pLeft;
            }
            //将替代节点中的值交给待删除节点，转换成删除替代节点
            pCur->_data = Replace->_data;
            if (Pre->_pLeft == Replace)
                Pre->_pLeft = Replace->_pRight;
            else
                Pre->_pRight = Replace->_pRight;
            Del = Replace;
        }
        delete Del;
        return true;
    }
 private:
    PNode _pRoot;
};
int main() {
    BSTree<int> tree1;
    tree1.Insert(3);
    tree1.Insert(5);
    tree1.Insert(6);
    tree1.Insert(4);
    tree1.Insert(7);
    tree1.Insert(8);
    tree1.Print_Tree();

    BSTNode<int>* add = tree1.Find(5);
    if (add == nullptr)
        cout << "二叉树中没有这个值" << endl;
    else
        cout << "在二叉搜索树找到了该值" <<" "<<add->_data << endl;
    tree1.Erase(6);
    cout << "删除后的搜索二叉树为:" << endl;
    tree1.Print_Tree();

    BSTree<int> tree2(tree1);
    cout << "Tree2：";
    tree2.Print_Tree();
    return 0;


}