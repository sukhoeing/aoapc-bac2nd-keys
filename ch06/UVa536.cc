// Tree Recovery, ULM 1997, UVa 536
// 陈锋
#include<cassert>
#include<cstdio>
#include<cmath>
#include<functional>
#include<algorithm>
#include<cstring>
#include<stack>
using namespace std;

const int MAXSIZE = 32;

struct Node {
    Node *left, *right;
    char value;
    
    void init(char v) {
        value = v;
        left = right = NULL;
    }
};

Node nodesBuf[MAXSIZE];
int cur;

Node* newNode(){ return &(nodesBuf[cur++]); }

Node* buildTree(const char *preord, const char *inord, int len) {
    if(len == 0) return NULL;
    char value = preord[0];
    Node *root = newNode();
    root->init(value);
    if(len == 1) {
        assert(value == inord[0]);
        return root;
    }
    
    const char *p = strchr(inord, value);
    int lLen = p-inord;
    int rLen = len - lLen - 1;
    root->left = buildTree(preord+1, inord, lLen);
    root->right = buildTree(preord+1+lLen, p+1, rLen);
    return root;
}

void postPrint(Node* root) {
    if(root == NULL) return;
    postPrint(root->left);
    postPrint(root->right);
    printf("%c", root->value);
}

int main()
{
    char preord[MAXSIZE], inord[MAXSIZE];
    while(scanf("%s %s", preord, inord) == 2) {
        // printf("%s %s\n", preord, inord);
        cur = 0;
        Node* root = buildTree(preord, inord, strlen(inord));
        postPrint(root);
        puts("");
    }
    return 0;
}

// 14804429	536	Tree Recovery	Accepted	C++	0.015	2015-01-15 03:00:50