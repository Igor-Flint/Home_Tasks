#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int data;
    struct TreeNode* right;
    struct TreeNode* left;
};

struct TreeNode* createTreeNode(int val) {
    struct TreeNode* newNode = NULL;
    newNode = calloc(1, sizeof(struct TreeNode));
    if (newNode == NULL)
    {
        fprintf(stderr, "No enough memory\n");
        return NULL;
    }

    newNode->data = val;
    newNode->right = NULL;
    newNode->left = NULL;
    return newNode;
}

struct TreeNode* insertTreeNode(struct TreeNode* root, int val) {
    if (root == NULL) return createTreeNode(val);

    if (val < root->data) root->left = insertTreeNode(root->left, val);
    else if (val > root->data) root->right = insertTreeNode(root->right, val);
    return root;
}

struct TreeNode* findMinValueNode(struct TreeNode* Node) {
    struct TreeNode* current = Node;
    while ((current != NULL) && (current->left != NULL)) {
        current = current->left;
    }
    return current;
}

struct TreeNode* deleteTreeNodeByValue(struct TreeNode* root, int key) {
    if (root == NULL) return root;

    if (key < root->data) 
		root->left = deleteTreeNodeByValue(root->left, key);
    else if (key > root->data) 
		root->right = deleteTreeNodeByValue(root->right, key);
    else {
        if (root->left == NULL) {
            struct TreeNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct TreeNode* temp = root->left;
            free(root);
            return temp;
        }
        struct TreeNode* temp = findMinValueNode(root->right);
        root->data = temp->data;
        root->right = deleteTreeNodeByValue(root->right, temp->data);
    }
    return root;
}

int findValue(struct TreeNode *root, int val) {
    struct TreeNode* current = root;

    while (current != NULL)
    {
        if (val == current->data)
        {
            return 1;
        }
        else if (val < current->data)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }

    return 0;
}

int treeHeight(struct TreeNode* root) {
    if (root == NULL) {
        return 0;
    }
    
    int leftHeight = treeHeight(root->left);
    int rightHeight = treeHeight(root->right);
    
	if (leftHeight > rightHeight)
		return (leftHeight + 1);
	else return (rightHeight + 1);
}

int main() {
    int el;
    char sym;
    struct TreeNode* root = NULL;
    
    while (1) {
        int read_result = scanf(" %c", &sym);
        if (read_result == EOF) break;
        
        if (sym != '+' && sym != '-' && sym != '?') {
            continue;
        }
        
        if (scanf("%d", &el) != 1) {
            break;
        }
        
        if (sym == '?') {
            if (findValue(root, el) == 1) printf("%d yes\n", el);
            else printf("%d no\n", el);
        }
        else if (sym == '+') {
            root = insertTreeNode(root, el);
			int height = treeHeight(root);
			printf("Элемент %d добавлен. Высота дерева: %d\n", el, height);
		}
        else if (sym == '-') {
            root = deleteTreeNodeByValue(root, el);
			int height = treeHeight(root);
			printf("Элемент %d добавлен. Высота дерева: %d\n", el, height);
        }
    }
    return 0;
}
