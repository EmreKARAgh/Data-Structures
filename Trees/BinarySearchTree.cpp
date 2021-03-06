#include "pch.h"
#include <iostream>
#include <cstring>
#include <stack> 
class MyObject {
public:
	int data;
	MyObject() = default;
	MyObject(int incomingData) : data(incomingData)
	{
	}

	friend std::ostream& operator<<(std::ostream& out, const MyObject& rhs);


	bool operator==(const MyObject& rhs)
	{
		if (this->data == rhs.data)
			return true;
		return false;
	}
	bool operator<(const MyObject& rhs)
	{
		if (this->data < rhs.data)
			return true;
		return false;
	}
	bool operator>(const MyObject& rhs)
	{
		if (this->data > rhs.data)
			return true;
		return false;
	}

};

std::ostream& operator<<(std::ostream& out, const MyObject& rhs)
{
	out << rhs.data;
	return out;
}


template <typename T>
class BST {
private:
	struct node {
		T data;
		node* right{};
		node* left{};
		node(T incomingData): data(incomingData){}
		node() = default;
		~node() = default;
	};
	node* root{};
	node* search(T incomingData, node* incomingNode) {
		node* temp = incomingNode;
		while (true)
		{
			if (temp == nullptr) {
				std::cout << "Searched Value Not Found!\n";
				return nullptr;
			}
			else if (incomingData < temp->data) {
				temp = temp->left;
			}
			else if (incomingData > temp->data) {
				temp = temp->right;
			}
			else if (incomingData == temp->data) {
				return temp;
			}
		}
	}
	node* findDeleted(node* incomingNode) {
		T incomingData = incomingNode->data;
		if (incomingNode == nullptr) {
			std::cout << "Node Not Found!" ;
			return nullptr;
		}
		else
		{
			int counter = 0;
			node* temp = this->root;
			node* parentNode = nullptr;
			std::string parentNodePosition = " ";
			
			while (true)
			{
				if (temp == nullptr) {
					std::cout << "Node Not Found!";
					return nullptr;
				}
				else if (incomingData < temp->data) {
					parentNode = temp;
					temp = temp->left;
					parentNodePosition = "left";
				}
				else if (incomingData > temp->data) {
					parentNode = temp;
					temp = temp->right;
					parentNodePosition = "right";
				}
				else if (incomingData == temp->data) {
					counter++;
					if (counter == 1) {
						temp = temp->right;
						continue;
					}
					if (!parentNodePosition.compare("right")) {
						parentNode->right = nullptr;
						return nullptr;
					}
					else if (!parentNodePosition.compare("left")) {
						parentNode->left = nullptr;
						return nullptr;
					}
				}
			}
		}

	}
	void preOrder() {
		if (this->root == nullptr) {
			std::cout << "Tree İs Empty!\n";
			return;
		}
		else
		{
			std::stack<node*> myStack;
			myStack.push(this->root);
			while (myStack.size() >0 )
			{
				node* temp = myStack.top();
				myStack.pop();

				std::cout << temp->data << "\n";

				if (temp->right != nullptr)
					myStack.push(temp->right);
				if (temp->left != nullptr)
					myStack.push(temp->left);
			}
		}
	}
	void inorder() {
		if (this->root == nullptr) {
			std::cout << "Tree İs Empty!\n";
			return;
		}
		else {
			node* current = this->root;
			std::stack<node*> myStack;
			int done = 0;
			while (done == 0) {
				if (current != nullptr) {
					myStack.push(current);
					current = current->left;
				}
				else
				{
					if (myStack.size() > 0) {
						current = myStack.top();
						myStack.pop();
						std::cout << current->data <<"\n";
						current = current->right;
					}
					else
					{
						done = 1;
					}
				}
			}
		}
	}
	void postOrder() {
		if (this->root == nullptr) {
			std::cout << "Tree İs Empty!\n";
			return;
		}
		else 
		{
			std::stack<node*> myStack;
			std::stack<node*> myStack2;

			myStack.push(this->root);

			while (myStack.size() !=0 )
			{
				node* temp = myStack.top();
				myStack.pop();
				myStack2.push(temp);

				if (temp->left != nullptr)
					myStack.push(temp->left);
				if (temp->right != nullptr)
					myStack.push(temp->right);
				
			}
			while (myStack2.size() != 0)
			{
				node* temp = myStack2.top();
				myStack2.pop();

				std::cout << temp->data << "\n" ;


			}
		}
	}
public:
	BST() {
		this->root = nullptr;
	}
	~BST() = default;
	void insert(T incomingData) {
		if (this->root == nullptr) {
			this->root = new node(incomingData);
			std::cout << incomingData << " inserted in root \n";
		}
		else
		{
			node* temp = this->root;
			node* parentNode = nullptr;
			std::string parentNodePosition = "right";
			
			while (true)
			{
				if (temp == nullptr) {
					if (!parentNodePosition.compare("right")) {
						std::cout << incomingData << " inserted in " << parentNode->data << "'s right\n";
						parentNode->right = new node(incomingData);
						break;
					}
					else if (!parentNodePosition.compare("left")) {
						std::cout << incomingData << " inserted in " << parentNode->data << "'s left\n";
						parentNode->left = new node(incomingData);
						break;
					}
				}
				else if (incomingData < temp->data) {
					parentNode = temp;
					temp = temp->left;
					parentNodePosition = "left";
				}
				else if (incomingData > temp->data) {
					parentNode = temp;
					temp = temp->right;
					parentNodePosition = "right";
				}
				else if (incomingData == temp->data) {
					std::cout << "Value Already Inserted.\n";
					break;
				}
			}

		}

	}
	node* min(node* incomingNode = nullptr) {
		if (incomingNode == nullptr) {
			incomingNode = this->root;
		}
		if (this->root == nullptr) {
			std::cout << "Tree İs Empty!\n";
			return nullptr;
		}
		else {
			node* temp = incomingNode;
			node* parentNode = nullptr;
			
			while (true)
			{
				if (temp == nullptr) {
					return parentNode;
				}
				else {
					parentNode = temp;
					temp = temp->left;
				}
			}
		}
	}
	node* max(node* incomingNode = nullptr) {
		if (incomingNode == nullptr) {
			incomingNode = this->root;
		}
		if (this->root == nullptr) {
			std::cout << "Tree İs Empty!\n";
			return nullptr;
		}
		else {
			node* temp = incomingNode;
			node* parentNode = nullptr;

			while (true)
			{
				if (temp == nullptr) {
					return parentNode;
				}
				else {
					parentNode = temp;
					temp = temp->right;
				}
			}
		}
	}
	void display(int choice) {
		if (this->root == nullptr) {
			std::cout << "Tree İs Empty!\n";
			return;
		}
		else
		{
			switch (choice)
			{
			case 1: this->preOrder(); break;
			case 2: this->inorder(); break;
			case 3: this->postOrder(); break;
			default:  this->inorder(); break;
			}
		}
	}
	void find(T incomingData) {
		std::cout << (this->search(incomingData, this->root))->data << "found. \n";
	}
	void remove(T incomingData) {
		if (this->root == nullptr) {
			std::cout << "Tree İs Empty!\n";
			return;
		}
		else 
		{
			node* temp = this->root;
			node* parentNode = nullptr;
			std::string parentNodePosition = "right";
			while (true)
			{
				if (temp == nullptr) {
					std::cout << incomingData << " not found!\n";
					break;
				}
				else if (incomingData < temp->data) {
					parentNode = temp;
					temp = temp->left;
					parentNodePosition = "left";
				}
				else if (incomingData > temp->data) {
					parentNode = temp;
					temp = temp->right;
					parentNodePosition = "right";
				}
				else if (incomingData == temp->data) {
					if (temp->right != nullptr && temp->left != nullptr) {
						node* minNode = this->min(temp->right);
						temp->data = minNode->data;
						minNode = this->search(temp->data,temp->right);
						
						if (minNode->right == nullptr && minNode->left == nullptr) {
							this->findDeleted(minNode);
							break;
						}
						else
						{
							if (minNode->right != nullptr) {
								minNode->data = minNode->right->data;
								minNode->right = nullptr;
							}
							else
							{
								minNode->data = minNode->left->data;
								minNode->left = nullptr;
							}
							break;
						}
					}
					else if (temp->right == nullptr && temp->left == nullptr) {
						if (!parentNodePosition.compare("right")) {
							parentNode->right = nullptr;
							break;
						}
						else
						{
							parentNode->left = nullptr;
							break;
						}
					}
					else
					{
						if (temp->right != nullptr) {
							temp->data = temp->right->data;
							temp->right = nullptr;
						}
						else
						{
							temp->data = temp->left->data;
							temp->left = nullptr;
						}
						break;
					}
				}
			}
		}

	}
};

int main()
{
	BST<MyObject> deneme;
	deneme.insert(MyObject(6));
	deneme.insert(MyObject(2));
	deneme.insert(MyObject(10));
	deneme.insert(MyObject(1));
	deneme.insert(MyObject(3));
	deneme.insert(MyObject(8));
	deneme.insert(MyObject(12));
	deneme.insert(MyObject(15));
	deneme.insert(MyObject(7));
	deneme.display(2);
	std::cout <<"Minimum Values is = "<< deneme.min()->data << "\n";
    std::cout << "Maximum Values is = " << deneme.max()->data << "\n";
	deneme.remove(1);
	std::cout << "\n\n ==================================================================== \n\n";
	deneme.display(2);


}