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
    //��������
    BSTree(const BSTree<T>& tree) {
        _pRoot = Copy(tree._pRoot);
    }
    //��ֵ���������
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
    void Inorder(PNode root) {//����������������� �����Ǵ�С�����˳��
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
        // �����Ϊ�գ�ֱ�Ӳ���
        if (nullptr == _pRoot) {
            _pRoot = new Node(data);
            return true;
        }
        // ���ն��������������ʲ���data�����еĲ���λ��
        PNode pCur = _pRoot;
        // ��¼pCur��˫�ף���Ϊ��Ԫ�����ղ�����pCur˫�����Һ��ӵ�λ��
        PNode pParent = nullptr;
        while (pCur) {
            pParent = pCur;
            if (data < pCur->_data)
                pCur = pCur->_pLeft;
            else if (data > pCur->_data)
                pCur = pCur->_pRight;
            else
                // Ԫ���Ѿ������д���
                return false;
        }
        // ����Ԫ��
        pCur = new Node(data);
        if (data < pParent->_data)
            pParent->_pLeft = pCur;
        else
            pParent->_pRight = pCur;
        return true;
    }

    bool Erase(const T& data) {
        // �����Ϊ�գ�ɾ��ʧ��
        if (nullptr == _pRoot)
            return false;
        // ������data�����е�λ��
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
        // data���ڶ����������У��޷�ɾ��
        if (nullptr == pCur)
            return false;

        Node* Del = pCur;
        // ��ǰ�ڵ���Ҷ�ӽڵ����ֻ����ڵ�---��ֱ��ɾ��	
        if (nullptr == pCur->_pRight) {
            //Ҫɾ���Ľڵ��Ǹ��ڵ�
            if (pParent == nullptr)
                _pRoot = _pRoot->_pLeft;
            if (pParent->_pLeft == pCur)
                pParent->_pLeft = pCur->_pLeft;
            else
                pParent->_pRight = pCur->_pLeft;
        }

        // ��ǰ�ڵ�ֻ���Һ���---��ֱ��ɾ��
        else if (nullptr == pCur->_pLeft) {
            if (pParent == nullptr)
                _pRoot = _pRoot->_pRight;
            if (pParent->_pLeft == pCur)
                pParent->_pLeft = pCur->_pRight;
            else
                pParent->_pRight = pCur->_pRight;
        }
        // ��ǰ�ڵ����Һ��Ӷ����ڣ�ֱ��ɾ������ɾ��������������������һ�������㣬���磺
        // �����������е����ڵ㣬�������������Ҳ�Ľڵ㣬����������������С�Ľڵ㣬���������������Ľڵ�
        // ����ڵ��ҵ��󣬽�����ڵ��е�ֵ������ɾ���ڵ㣬ת����ɾ������ڵ�
        else {
            PNode Replace = pCur->_pRight;
            PNode Pre = pCur;//����ڵ��˫�׽ڵ�
            if (Replace->_pLeft) {
                //�ýڵ�����������С�ڵ���Ϊ����ڵ�
                Pre = Replace;
                Replace = Replace->_pLeft;
            }
            //������ڵ��е�ֵ������ɾ���ڵ㣬ת����ɾ������ڵ�
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
        cout << "��������û�����ֵ" << endl;
    else
        cout << "�ڶ����������ҵ��˸�ֵ" <<" "<<add->_data << endl;
    tree1.Erase(6);
    cout << "ɾ���������������Ϊ:" << endl;
    tree1.Print_Tree();

    BSTree<int> tree2(tree1);
    cout << "Tree2��";
    tree2.Print_Tree();
    return 0;


}