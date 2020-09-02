template<class T>
struct AVLTreeNode
{
    AVLTreeNode(const T& data)
        : _pLeft(nullptr)
        , _pRight(nullptr)
        , _pParent(nullptr)
        , _data(data)
        , _bf(0)
    {}
    AVLTreeNode<T>* _pLeft; // 该节点的左孩子
    AVLTreeNode<T>* _pRight; // 该节点的右孩子
    AVLTreeNode<T>* _pParent; // 该节点的双亲
    T _data;
    int _bf; // 该节点的平衡因子
};

template<class T>
class AVLTree {
public:
    typedef AVLTreeNode<T> Node;
    typedef Node* PNode;
    AVLTree()
        :_pRoot(nullptr)
    {}

    bool Insert(const T& data) {
        // 1. 先按照二叉搜索树的规则将节点插入到AVL树中
        if (nullptr == _pRoot) {
            _pRoot = new Node(data);
            return true;
        }
        // 按照二叉搜索树的性质找data在AVL中的插入位置
        PNode pCur = _pRoot;
        PNode pParent = nullptr;
        while (pCur) {
            pParent = pCur;
            if (data < pCur->_data)
                pCur = pCur->_pLeft;
            else if (data > pCur->_data)
                pCur = pCur->_data;
            else
                return false; // 该节点在二叉搜索树中存在
        }
        // 插入新节点：新节点一定插入在pParent的左侧或者右侧
        if (data < pParent->_data)
            pParent->_pLeft = pCur;
        else
            pParent->_pRight = pCur;
        // 更新pCur的双亲节点
        pCur->_pParent = pParent;

        // 2. 新节点插入后，AVL树的平衡性可能会遭到破坏，此时就需要更新平衡因子，并检测是否破坏了AVL树的平衡性

        /*
        pCur插入后，pParent的平衡因子一定需要调整，在插入之前，pParent
        的平衡因子分为三种情况：-1，0, 1, 分以下两种情况：
        1. 如果pCur插入到pParent的左侧，只需给pParent的平衡因子-1即可
        2. 如果pCur插入到pParent的右侧，只需给pParent的平衡因子+1即可

        此时：pParent的平衡因子可能有三种情况：0，正负1， 正负2
        1. 如果pParent的平衡因子为0，说明插入之前pParent的平衡因子为正负1，插入后被调整成0，此时满足AVL树的性质，插入成功
        2. 如果pParent的平衡因子为正负1，说明插入前pParent的平衡因子一定为0，插入后被更新成正负1，此
        时以pParent为根的树的高度增加，需要继续向上更新
        3. 如果pParent的平衡因子为正负2，则pParent的平衡因子违反平衡树的性质，需要对其进行旋转处理
        */
        while (pParent) {
            // 更新双亲的平衡因子
            if (pParent->_pLeft == pCur)
                pParent->_bf--;
            else
                pParent->_bf++;
            // 更新后检测双亲的平衡因子
            if (pParent->_bf == 0)
                break;
            else if (pParent->_bf == 1 || pParent->_bf == -1) {
                // 插入前双亲的平衡因子是0，插入后双亲的平衡因为为1 或者 -1 ，说明以双亲为根的二叉树
                // 的高度增加了一层，因此需要继续向上调整
                pCur = pParent;
                pParent = pCur->_pParent;
            }
            else if (pParent->_bf == 2 || pParent->_bf == -2) {
                // 双亲的平衡因子为正负2，违反了AVL树的平衡性，需要对以pParent
                // 为根的树进行旋转处理
                if (pParent->_bf == 2 && pCur->_bf == 1) {
                    //右边的右边高，左旋
                    _RotateL(pParent);
                }
                else if (pParent->_bf == -2 && pCur->_bf == -1) {
                    //左边的左边高，右旋
                    _RotateR(pParent);
                }
                else if (pParent->_bf == 2 && pCur->_bf == -1) {
                    //右边的左边高，右左旋
                    _RotateRL(pParent);
                }
                else if (pParent->_bf == -2 && pCur->_bf == 1) {
                    //左边的右边高，左右旋
                    _RotateLR(pParent);
                }
            }
            break;
        }
        return true;
    }
    //右单旋:新节点插入较高左子树的左侧
    void _RotateR(PNode pParent) {
        // pSubL: pParent的左孩子
        // pSubLR: pParent左孩子的右孩子
        PNode pSubL = pParent->_pLeft;
        PNode pSubLR = pSubL->_pRight;

        // 旋转完成之后，pParent左孩子的右孩子 作为 pParent的左孩子
        pParent->_pLeft = pSubLR;
        // 如果pSubLR存在，更新其双亲为pParent
        if (pSubLR)
            pSubLR->_pParent = pParent;
        //pParent作为pSubL的右孩子
        pSubL->_pRight = pParent;

        // pParent可能是棵子树，因此在更新其双亲前必须先保存双亲
        PNode pPParent = pParent->_pParent;
        // 更新双亲
        pParent->_pParent = pSubL;

        // 更新pSubL的双亲
        pSubL->_pParent = pPParent;

        // 如果pParent是根节点，根新指向根节点的指针
        if (NULL == pPParent) {
            _pRoot = pSubL;
            pSubL->_pParent = NULL;
        }
        else {
            // 如果pParent是子树，可能是其双亲的左子树，也可能是右子树
            if (pPParent->_pLeft == pParent)
                pPParent->_pLeft = pSubL;
            else
                pPParent->_pRight = pSubL;
        }
        // 根据调整后的结构更新部分节点的平衡因子
        pParent->_bf = pSubL->_bf = 0;
    }

    //左单旋:新节点插入较高右子树的右侧
    void _RotateL(PNode pParent) {
        // pSubR: pParent的右孩子
        // pSubRL: pParent右孩子的左孩子
        PNode pSubR = pParent->_pRight;
        PNode pSubRL = SubR->_pLeft;


        // 旋转完成之后，pParent右孩子的左孩子 作为 pParent的右孩子
        pParent->_pRight = pSubRL;
        // 如果pSubRL存在，更新其双亲为pParent
        if (pSubRL)
            pSubRL->_pParent = pParent;
        //pParent作为pSubR的左孩子
        pSubR->_pLeft = pParent;

        // pParent可能是棵子树，因此在更新其双亲前必须先保存双亲
        PNode pPParent = pParent->_pParent;
        // 更新双亲
        pParent->_pParent = pSubR;

        // 更新pSubR的双亲
        pSubR->_pParent = pPParent;

        // 如果pParent是根节点，根新指向根节点的指针
        if (NULL == pPParent) {
            _pRoot = pSubR;
            pSubR->_pParent = NULL;
        }
        else {
            // 如果pParent是子树，可能是其双亲的左子树，也可能是右子树
            if (pPParent->_pLeft == pParent)
                pPParent->_pLeft = pSubR;
            else
                pPParent->_pRight = pSubR;
        }
        // 根据调整后的结构更新部分节点的平衡因子
        pParent->_bf = pSubR->_bf = 0;
    }

    //左右旋: 新节点插入较高左子树的右侧  先左单旋再右单旋
    void _RotateLR(PNode pParent) {
        PNode pSubL = pParent->_pLeft;
        PNode pSubLR = pSubL->_pRight;

        // 旋转之前，保存pSubLR的平衡因子，旋转完成之后，需要根据该平衡因子来调整其他节点的平衡因子
        int bf = pSubLR->_bf;

        // 先进行左单旋
        _RotateL(pParent->_pLeft);

        // 再进行右单旋
        _RotateR(pParent);
        if (bf == 1)
            pSubL->_bf = -1;
        else if (bf == -1)
            pParent->_bf = 1;
    }

    //右左旋:新节点插入较高右子树的左侧  先右单旋再左单旋
    void _RotateRL(PNode pParent) {
        PNode pSubR = pParent->_pRight;
        PNode pSubRL = pSubR->_pLeft;

        // 旋转之前，保存pSubRL的平衡因子，旋转完成之后，需要根据该平衡因子来调整其他节点的平衡因子
        int bf = pSubRL->_bf;

        // 先进行右单旋
        _RotateR(pParent->_pRight);

        // 再进行右单旋
        _RotateL(pParent);
        if (bf == 1)
            pParent->_bf = -1;
        else if (bf == -1)
            pSubR = 1;
    }

    //计算pRoot左右子树的高度
    int _Height(PNode pRoot)
    {
        if (nullptr == pRoot)
            return 0;
        // 计算pRoot左右子树的高度
        int leftHeight = _Height(pRoot->_pLeft);
        int rightHeight = _Height(pRoot->_pRight);
        // 返回左右子树中较高的子树高度+1
        return (leftHeight > rightHeight) ? (leftHeight + 1) : (rightHeight + 1);
    }

    //判断是否为AVL树
    bool _IsBalanceTree(PNode pRoot)
    {
        // 空树也是AVL树
        if (nullptr == pRoot)
            return true;
        // 计算pRoot节点的平衡因子：即pRoot左右子树的高度差
        int leftHeight = _Height(pRoot->_pLeft);
        int rightHeight = _Height(pRoot->_pRight);
        int diff = rightHeight - leftHeight;
        // 如果计算出的平衡因子与pRoot的平衡因子不相等，或者
        // pRoot平衡因子的绝对值超过1，则一定不是AVL树
        if (diff != pRoot->_bf || (diff > 1 || diff < -1))
            return false;
        // pRoot的左和右如果都是AVL树，则该树一定是AVL树
        return _IsBalanceTree(pRoot->_pLeft) && _IsBalanceTree(pRoot->_pRight);
    }

    //中序遍历可得到一个有序的序列，就说明为二叉搜索树
    void _inorder(PNode root) {
        if (root) {
            _inorder(root->_left);
            cout << root->_value << " ";
            _inorder(root->_right);
        }
    }

 private:
        PNode _pRoot;
};




