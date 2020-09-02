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
    AVLTreeNode<T>* _pLeft; // �ýڵ������
    AVLTreeNode<T>* _pRight; // �ýڵ���Һ���
    AVLTreeNode<T>* _pParent; // �ýڵ��˫��
    T _data;
    int _bf; // �ýڵ��ƽ������
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
        // 1. �Ȱ��ն����������Ĺ��򽫽ڵ���뵽AVL����
        if (nullptr == _pRoot) {
            _pRoot = new Node(data);
            return true;
        }
        // ���ն�����������������data��AVL�еĲ���λ��
        PNode pCur = _pRoot;
        PNode pParent = nullptr;
        while (pCur) {
            pParent = pCur;
            if (data < pCur->_data)
                pCur = pCur->_pLeft;
            else if (data > pCur->_data)
                pCur = pCur->_data;
            else
                return false; // �ýڵ��ڶ����������д���
        }
        // �����½ڵ㣺�½ڵ�һ��������pParent���������Ҳ�
        if (data < pParent->_data)
            pParent->_pLeft = pCur;
        else
            pParent->_pRight = pCur;
        // ����pCur��˫�׽ڵ�
        pCur->_pParent = pParent;

        // 2. �½ڵ�����AVL����ƽ���Կ��ܻ��⵽�ƻ�����ʱ����Ҫ����ƽ�����ӣ�������Ƿ��ƻ���AVL����ƽ����

        /*
        pCur�����pParent��ƽ������һ����Ҫ�������ڲ���֮ǰ��pParent
        ��ƽ�����ӷ�Ϊ���������-1��0, 1, ���������������
        1. ���pCur���뵽pParent����ֻ࣬���pParent��ƽ������-1����
        2. ���pCur���뵽pParent���Ҳֻ࣬���pParent��ƽ������+1����

        ��ʱ��pParent��ƽ�����ӿ��������������0������1�� ����2
        1. ���pParent��ƽ������Ϊ0��˵������֮ǰpParent��ƽ������Ϊ����1������󱻵�����0����ʱ����AVL�������ʣ�����ɹ�
        2. ���pParent��ƽ������Ϊ����1��˵������ǰpParent��ƽ������һ��Ϊ0������󱻸��³�����1����
        ʱ��pParentΪ�������ĸ߶����ӣ���Ҫ�������ϸ���
        3. ���pParent��ƽ������Ϊ����2����pParent��ƽ������Υ��ƽ���������ʣ���Ҫ���������ת����
        */
        while (pParent) {
            // ����˫�׵�ƽ������
            if (pParent->_pLeft == pCur)
                pParent->_bf--;
            else
                pParent->_bf++;
            // ���º���˫�׵�ƽ������
            if (pParent->_bf == 0)
                break;
            else if (pParent->_bf == 1 || pParent->_bf == -1) {
                // ����ǰ˫�׵�ƽ��������0�������˫�׵�ƽ����ΪΪ1 ���� -1 ��˵����˫��Ϊ���Ķ�����
                // �ĸ߶�������һ�㣬�����Ҫ�������ϵ���
                pCur = pParent;
                pParent = pCur->_pParent;
            }
            else if (pParent->_bf == 2 || pParent->_bf == -2) {
                // ˫�׵�ƽ������Ϊ����2��Υ����AVL����ƽ���ԣ���Ҫ����pParent
                // Ϊ������������ת����
                if (pParent->_bf == 2 && pCur->_bf == 1) {
                    //�ұߵ��ұ߸ߣ�����
                    _RotateL(pParent);
                }
                else if (pParent->_bf == -2 && pCur->_bf == -1) {
                    //��ߵ���߸ߣ�����
                    _RotateR(pParent);
                }
                else if (pParent->_bf == 2 && pCur->_bf == -1) {
                    //�ұߵ���߸ߣ�������
                    _RotateRL(pParent);
                }
                else if (pParent->_bf == -2 && pCur->_bf == 1) {
                    //��ߵ��ұ߸ߣ�������
                    _RotateLR(pParent);
                }
            }
            break;
        }
        return true;
    }
    //�ҵ���:�½ڵ����ϸ������������
    void _RotateR(PNode pParent) {
        // pSubL: pParent������
        // pSubLR: pParent���ӵ��Һ���
        PNode pSubL = pParent->_pLeft;
        PNode pSubLR = pSubL->_pRight;

        // ��ת���֮��pParent���ӵ��Һ��� ��Ϊ pParent������
        pParent->_pLeft = pSubLR;
        // ���pSubLR���ڣ�������˫��ΪpParent
        if (pSubLR)
            pSubLR->_pParent = pParent;
        //pParent��ΪpSubL���Һ���
        pSubL->_pRight = pParent;

        // pParent�����ǿ�����������ڸ�����˫��ǰ�����ȱ���˫��
        PNode pPParent = pParent->_pParent;
        // ����˫��
        pParent->_pParent = pSubL;

        // ����pSubL��˫��
        pSubL->_pParent = pPParent;

        // ���pParent�Ǹ��ڵ㣬����ָ����ڵ��ָ��
        if (NULL == pPParent) {
            _pRoot = pSubL;
            pSubL->_pParent = NULL;
        }
        else {
            // ���pParent����������������˫�׵���������Ҳ������������
            if (pPParent->_pLeft == pParent)
                pPParent->_pLeft = pSubL;
            else
                pPParent->_pRight = pSubL;
        }
        // ���ݵ�����Ľṹ���²��ֽڵ��ƽ������
        pParent->_bf = pSubL->_bf = 0;
    }

    //����:�½ڵ����ϸ����������Ҳ�
    void _RotateL(PNode pParent) {
        // pSubR: pParent���Һ���
        // pSubRL: pParent�Һ��ӵ�����
        PNode pSubR = pParent->_pRight;
        PNode pSubRL = SubR->_pLeft;


        // ��ת���֮��pParent�Һ��ӵ����� ��Ϊ pParent���Һ���
        pParent->_pRight = pSubRL;
        // ���pSubRL���ڣ�������˫��ΪpParent
        if (pSubRL)
            pSubRL->_pParent = pParent;
        //pParent��ΪpSubR������
        pSubR->_pLeft = pParent;

        // pParent�����ǿ�����������ڸ�����˫��ǰ�����ȱ���˫��
        PNode pPParent = pParent->_pParent;
        // ����˫��
        pParent->_pParent = pSubR;

        // ����pSubR��˫��
        pSubR->_pParent = pPParent;

        // ���pParent�Ǹ��ڵ㣬����ָ����ڵ��ָ��
        if (NULL == pPParent) {
            _pRoot = pSubR;
            pSubR->_pParent = NULL;
        }
        else {
            // ���pParent����������������˫�׵���������Ҳ������������
            if (pPParent->_pLeft == pParent)
                pPParent->_pLeft = pSubR;
            else
                pPParent->_pRight = pSubR;
        }
        // ���ݵ�����Ľṹ���²��ֽڵ��ƽ������
        pParent->_bf = pSubR->_bf = 0;
    }

    //������: �½ڵ����ϸ����������Ҳ�  ���������ҵ���
    void _RotateLR(PNode pParent) {
        PNode pSubL = pParent->_pLeft;
        PNode pSubLR = pSubL->_pRight;

        // ��ת֮ǰ������pSubLR��ƽ�����ӣ���ת���֮����Ҫ���ݸ�ƽ�����������������ڵ��ƽ������
        int bf = pSubLR->_bf;

        // �Ƚ�������
        _RotateL(pParent->_pLeft);

        // �ٽ����ҵ���
        _RotateR(pParent);
        if (bf == 1)
            pSubL->_bf = -1;
        else if (bf == -1)
            pParent->_bf = 1;
    }

    //������:�½ڵ����ϸ������������  ���ҵ���������
    void _RotateRL(PNode pParent) {
        PNode pSubR = pParent->_pRight;
        PNode pSubRL = pSubR->_pLeft;

        // ��ת֮ǰ������pSubRL��ƽ�����ӣ���ת���֮����Ҫ���ݸ�ƽ�����������������ڵ��ƽ������
        int bf = pSubRL->_bf;

        // �Ƚ����ҵ���
        _RotateR(pParent->_pRight);

        // �ٽ����ҵ���
        _RotateL(pParent);
        if (bf == 1)
            pParent->_bf = -1;
        else if (bf == -1)
            pSubR = 1;
    }

    //����pRoot���������ĸ߶�
    int _Height(PNode pRoot)
    {
        if (nullptr == pRoot)
            return 0;
        // ����pRoot���������ĸ߶�
        int leftHeight = _Height(pRoot->_pLeft);
        int rightHeight = _Height(pRoot->_pRight);
        // �������������нϸߵ������߶�+1
        return (leftHeight > rightHeight) ? (leftHeight + 1) : (rightHeight + 1);
    }

    //�ж��Ƿ�ΪAVL��
    bool _IsBalanceTree(PNode pRoot)
    {
        // ����Ҳ��AVL��
        if (nullptr == pRoot)
            return true;
        // ����pRoot�ڵ��ƽ�����ӣ���pRoot���������ĸ߶Ȳ�
        int leftHeight = _Height(pRoot->_pLeft);
        int rightHeight = _Height(pRoot->_pRight);
        int diff = rightHeight - leftHeight;
        // ����������ƽ��������pRoot��ƽ�����Ӳ���ȣ�����
        // pRootƽ�����ӵľ���ֵ����1����һ������AVL��
        if (diff != pRoot->_bf || (diff > 1 || diff < -1))
            return false;
        // pRoot��������������AVL���������һ����AVL��
        return _IsBalanceTree(pRoot->_pLeft) && _IsBalanceTree(pRoot->_pRight);
    }

    //��������ɵõ�һ����������У���˵��Ϊ����������
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




