#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    int height;
    Node *left, *right;
};

int getHeight(Node* curr){
	if(!curr){
		return 0;
	}
	return curr->height;
}

//int max(int a, int b) {
//    return (a > b) ? a : b;
//}

int max(int a, int b){
	if(a > b){
		return a;
	}else{
		return b;
	}
}

Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

Node* rightRotate(Node* curr){
	Node* child = curr->left;
	Node* subChild = child->right;
	
	child->right = curr;
	curr->left = subChild;
	
	curr->height =  max(getHeight(curr->left), getHeight(curr->right))+1;
	
	child->height = max(getHeight(child->left), getHeight(child->right))+1;
					
	return child;
}

Node *leftRotate(Node * curr){
	Node* child = curr->right;
	Node* subChild = child->left;
	
	child->left = curr;
	curr->right = subChild;
	
	curr->height =  max(getHeight(curr->left), getHeight(curr->right))+1;
	child->height = max(getHeight(child->left), getHeight(child->right))+1;
	return child;
}

int getBalance(Node* curr) {
    if (!curr)
        return 0;
    return getHeight(curr->left) - getHeight(curr->right);
}

Node* insert(Node* curr, int data) {
    if (curr == NULL)
        return newNode(data);

    if (data < curr->data)
        curr->left = insert(curr->left, data);
    else if (data > curr->data)
        curr->right = insert(curr->right, data);
    else 
        return curr;

    curr->height = 1 + max(getHeight(curr->left), getHeight(curr->right));

    int balance = getBalance(curr);

    // Left Left 
    if (balance > 1 && data < curr->left->data)
        return rightRotate(curr);

    // Right Right 
    if (balance < -1 && data > curr->right->data)
        return leftRotate(curr);

    // Left Right 
    if (balance > 1 && data > curr->left->data) {
        curr->left = leftRotate(curr->left);
        return rightRotate(curr);
    }
    
    // Right Left 
    if (balance < -1 && data < curr->right->data) {
        curr->right = rightRotate(curr->right);
        return leftRotate(curr);
    }

    return curr;
}

Node* min(Node* curr) {
    Node* temp = curr;

    while (temp->left == NULL)
        temp = temp->left;

    return temp;
}

Node* deleteNode(Node* root, int data) {
    if (!root)
        return root;
    else if (data < root->data)
        root->left = deleteNode(root->left, data);
    else if (data > root->data)
        root->right = deleteNode(root->right, data);
    else { // one or no child
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            // No child
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } 
			else // One child
                *root = *temp;
            free(temp);
        } 
		else { // two child
            Node* temp = min(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }

    if (!root)
        return root;

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    int balance = getBalance(root);

    // Left Left 
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right 
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right 
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left 
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void preorder(Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

// Function to perform inorder traversal of the AVL tree
void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Function to perform postorder traversal of the AVL tree
void postorder(Node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

int main() {
    Node* root = NULL;

    int choice, data;
    do {
        printf("1. Insertion\n");
        printf("2. Deletion\n");
        printf("3. Traversal\n");
        printf("4. Exit\n");
        printf("Choose: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Insert: ");
                scanf("%d", &data);
                root = insert(root, data);
                printf("Value %d was inserted.\n", data);
                break;
            case 2:
                printf("Delete: ");
                scanf("%d", &data);
                if (!root) {
                    printf("Data not found\n");
                } 
				else {
                    root = deleteNode(root, data);
                    printf("Data found\n");
                    printf("Value %d was deleted\n", data);
                }
                break;
            case 3:
                printf("Preorder: ");
                preorder(root);
                printf("\n");
                printf("Inorder: ");
                inorder(root);
                printf("\n");
                printf("Postorder: ");
                postorder(root);
                printf("\n");
                break;
            case 4:
                printf("Thank you\n");
                break;
            default:
                printf("Data not found\n");
        }
        printf("\n");
    } while (choice != 4);

    return 0;
}

