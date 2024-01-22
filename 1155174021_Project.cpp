#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <chrono>
#include <stdio.h>

#pragma warning (disable : 4996)
using namespace std;

class OneNode {
//Every node has its value, the pointer to its left child, and another one to right child
public:
    int value;
    OneNode* left;
    OneNode* right;

    OneNode(int n) {
        value = n;
        left;
        right;
    }
};

OneNode* bst(vector<int>& D, int l, int r) {
//Construct a balanced BST by merge sort
    if (l > r) {
        return 0;
    }

//find the median
    int mid = (l + r) / 2;

//The tree should be balanced, which means the root point have to be the median of all values
    OneNode* root = new OneNode(D[mid]);

//divide S into the first half and the second half and so on until the left boundry is greater than the right
    root->left = bst(D, l, mid - 1);
    root->right = bst(D, mid + 1, r);

    return root;
}

int BST(OneNode* root, int p, int q) {
//Finds the predecessor of a target value target in the tree. p is the current predecessor
//Reach the leaf level and equalment dound
//if node = q, p = root and return
//if node < q, p = root and check the right subtree
//if node > q, check the right subtree

    while (root != 0) {
        if (root->value == q) {
            p = root->value;
            break;
        }
        else if (root->value < q) {
            p = root->value;
            root = root->right;
        }
        else {
            root = root->left;
        }
    }
    return p;
}

int Minimum(OneNode* root) {
//Find the minimum value of the tree to output "no" effectively
    while (root != 0) {
        if (root->left == 0)
            return root->value;
        else
            root = root->left;
    }
    return 0;
}

vector <int> readInteger(const string& filename)
{
    vector <int> tp;
    FILE* file = fopen(filename.c_str(), "r");
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file))
    {
        int len = strlen(buffer);
        tp.push_back(atoi(buffer));
    }
    return tp;
}


int main() {
//ds read
    const vector <int>& dst = readInteger("ds.txt"); //ds - half
    vector <int> v(dst);
    sort(v.begin(), v.end());
    OneNode* root = bst(v, 0, v.size() - 1);

//qs read
    vector<int> q;
    ifstream fon("qry.txt"); //qs - half



    string qry;

//console write
    FILE* fpn = fopen("output.txt", "w");
    int min = Minimum(root);

    while (getline(fon, qry)) {

        qry = qry.substr(4);
        int v = stoi(qry);
        if (v < min)
            fprintf(fpn, "no\n");
        else {
            int Predecessor = BST(root, -1, v);
            fprintf(fpn, "%d\n", Predecessor);
        }
    }
}