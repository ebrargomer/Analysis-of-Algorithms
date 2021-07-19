#include <bits/stdc++.h>
using namespace std;
char letters[10];
int values[10];
int k = 0;

int l4;
char *w1, *w2, *w3;
int i, j, n1, n2, n3, l1, l2, l3 = 0;
int counter = 1;

class Node
{
public:
	char *letter;
	int *value;
	int depth;
	Node(){};
	Node *child[10];
	Node *parent;

	Node(int depth, int size)
	{
		this->depth = depth;
		this->letter = new char[size];
		this->value = new int[size];
		for (int i = 0; i < 10; i++)
		{
			child[i] = NULL;
		}
	};
	~Node(){};
};

class Tree
{
public:
	Node *head;
	Tree() { head = NULL; }
	void createTree(Node *root, char *ltr, int depth, int index);
	void createaDepth(Node *root, char *ltrs, int depth);
	void DFS(string filename);
	void BFS(string filename);
};

int pos(char str[], char x)
{
	int i, l;
	l = strlen(str);
	for (i = 0; i < l; i++)
	{
		if (str[i] == x)
			return i;
	}
}

void Tree::BFS(string filename)
{
	int k = 0;
	clock_t start = clock();

	queue<Node *> q;
	q.push(head);
	k++;
	while (q.empty() == false)
	{
		Node *node = q.front();
		n1 = 0;
		n2 = 0;
		n3 = 0;

		for (j = 0; j < l1; j++)
			n1 = (n1 * 10) + node->value[pos(letters, w1[j])];
		for (j = 0; j < l2; j++)
			n2 = (n2 * 10) + node->value[pos(letters, w2[j])];
		for (j = 0; j < l3; j++)
			n3 = (n3 * 10) + node->value[pos(letters, w3[j])];

		bool equal = true;
		for (int cv1 = 0; cv1 < strlen(letters); cv1++)
		{
			for (int cv2 = cv1 + 1; cv2 < strlen(letters); cv2++)
			{
				if (node->value[cv1] == node->value[cv2])
					equal = false;
			}
		}
		if (n1 + n2 == n3 && n1 >= pow(10, (l1 - 1)) && n2 >= pow(10, (l2 - 1)) && n3 >= pow(10, (l3 - 1)) && equal)
		{

			ofstream outfile;
			outfile.open(filename);

			cout << "Algorithm: BFS" << endl;
			outfile << "Algorithm: BFS" << endl;
			cout << "Number of the visited nodes: " << k << endl;
			outfile << "Number of the visited nodes: " << k << endl;
			cout << "Maximum number of nodes kept in the memory: " << q.size() << endl;
			outfile << "Maximum number of nodes kept in the memory: " << q.size() << endl;
			clock_t end = clock();
			clock_t time_total = end - start;
			cout << "Running time is " << ((double)time_total / CLOCKS_PER_SEC) * 1000 << " milisecond" << endl;	//printing the run time into the screen
			outfile << "Running time is " << ((double)time_total / CLOCKS_PER_SEC) * 1000 << " milisecond" << endl; //printing the run time into the screen
			for (j = 0; j < l4; j++)
			{
				cout << node->letter[j] << ":" << node->value[j] << " ";
				outfile << node->letter[j] << ":" << node->value[j] << " ";
			}
			cout << n1 << " + " << n2 << " = " << n3 << endl;
			outfile.close();
			return;
		}

		for (int i = 0; i < 10; i++)
		{
			if (node->child[i] != NULL)
				q.push(node->child[i]);
			k++;
		}
		q.pop();
	}
}

void Tree::DFS(string filename)
{
	clock_t start = clock();
	stack<Node *> s;
	s.push(head);

	while (s.empty() == false)
	{
		Node *node = s.top();
		n1 = 0;
		n2 = 0;
		n3 = 0;
		for (j = 0; j < l1; j++)
			n1 = (n1 * 10) + node->value[pos(letters, w1[j])];
		for (j = 0; j < l2; j++)
			n2 = (n2 * 10) + node->value[pos(letters, w2[j])];
		for (j = 0; j < l3; j++)
			n3 = (n3 * 10) + node->value[pos(letters, w3[j])];

		bool equal = true;
		for (int cv1 = 0; cv1 < strlen(letters); cv1++)
		{
			for (int cv2 = cv1 + 1; cv2 < strlen(letters); cv2++)
			{
				if (node->value[cv1] == node->value[cv2])
					equal = false;
			}
		}
		if (n1 + n2 == n3 && n1 > pow(10, (l1 - 1)) && n2 > pow(10, (l2 - 1)) && n3 > pow(10, (l3 - 1)) && equal)
		{
			ofstream outfile;
			outfile.open(filename);

			cout << "Algorithm: DFS" << endl;
			outfile << "Algorithm: DFS" << endl;
			cout << "Number of the visited nodes: " << k << endl;
			outfile << "Number of the visited nodes: " << k << endl;
			cout << "Maximum number of nodes kept in the memory: " << s.size() << endl;
			outfile << "Maximum number of nodes kept in the memory: " << s.size() << endl;
			clock_t end = clock();
			clock_t time_total = end - start;
			cout << "Running time is " << ((double)time_total / CLOCKS_PER_SEC) * 1000 << " milisecond" << endl;	//printing the run time into the screen
			outfile << "Running time is " << ((double)time_total / CLOCKS_PER_SEC) * 1000 << " milisecond" << endl; //printing the run time into the screen
			for (j = 0; j < l4; j++)
			{
			//	cout << node->letter[j] << ":" << node->value[j] << " ";
				outfile << node->letter[j] << ":" << node->value[j] << " ";
			}
			cout << n1 << " + " << n2 << " = " << n3 << endl;

			outfile.close();
			return;
		}
		s.pop();
		for (int i = 0; i < 10; i++)
		{
			if (node->child[i] != NULL)
				s.push(node->child[i]);
			k++;
		}
	}
}

void Tree::createaDepth(Node *root, char *ltrs, int depth)
{
	Node *newnode = new Node(depth, strlen(ltrs));
	for (int i = 0; i < strlen(ltrs); i++)
	{
		newnode->letter[i] = ltrs[i];
		newnode->value[i] = -1;
		newnode->parent = NULL;
	}
	head = newnode;
	root = head;
	int index = 0;
	for (int i = 0; i < 10; i++)
		createTree(root, ltrs, i, index);

	if (strlen(ltrs) > 1)
	{
		index++;
		for (int j = 0; j < 10; j++)
		{
			root = newnode;
			root = root->child[j];
			for (int i = 0; i < 10; i++)
				createTree(root, ltrs, i, index);
		}
	}
	if (strlen(ltrs) > 2)
	{
		index++;
		for (int k = 0; k < 10; k++)
		{
			newnode = newnode->child[k];
			for (int j = 0; j < 10; j++)
			{
				root = newnode;
				root = root->child[j];
				for (int i = 0; i < 10; i++)
					createTree(root, ltrs, i, index);
			}
			newnode = newnode->parent;
		}
	}
	if (strlen(ltrs) > 3)
	{
		index++;
		for (int m = 0; m < 10; m++)
		{
			newnode = newnode->child[m];
			for (int k = 0; k < 10; k++)
			{
				newnode = newnode->child[k];
				for (int j = 0; j < 10; j++)
				{
					root = newnode;
					root = root->child[j];
					for (int i = 0; i < 10; i++)
						createTree(root, ltrs, i, index);
				}
				newnode = newnode->parent;
			}
			newnode = newnode->parent;
		}
	}
	if (strlen(ltrs) > 4)
	{
		index++;
		for (int f = 0; f < 10; f++)
		{
			newnode = newnode->child[f];
			for (int m = 0; m < 10; m++)
			{
				newnode = newnode->child[m];
				for (int k = 0; k < 10; k++)
				{
					newnode = newnode->child[k];
					for (int j = 0; j < 10; j++)
					{
						root = newnode;
						root = root->child[j];
						for (int i = 0; i < 10; i++)
							createTree(root, ltrs, i, index);
					}
					newnode = newnode->parent;
				}
				newnode = newnode->parent;
			}
			newnode = newnode->parent;
		}
	}
	if (strlen(ltrs) > 5)
	{
		index++;
		for (int p = 0; p < 10; p++)
		{
			newnode = newnode->child[p];
			for (int f = 0; f < 10; f++)
			{
				newnode = newnode->child[f];
				for (int m = 0; m < 10; m++)
				{
					newnode = newnode->child[m];
					for (int k = 0; k < 10; k++)
					{
						newnode = newnode->child[k];
						for (int j = 0; j < 10; j++)
						{
							root = newnode;
							root = root->child[j];

							for (int i = 0; i < 10; i++)
								createTree(root, ltrs, i, index);
						}
						newnode = newnode->parent;
					}
					newnode = newnode->parent;
				}
				newnode = newnode->parent;
			}
			newnode = newnode->parent;
		}
	}
	if (strlen(ltrs) > 6)
	{
		index++;
		for (int s = 0; s < 10; s++)
		{
			newnode = newnode->child[s];
			for (int p = 0; p < 10; p++)
			{
				newnode = newnode->child[p];
				for (int f = 0; f < 10; f++)
				{
					newnode = newnode->child[f];
					for (int m = 0; m < 10; m++)
					{
						newnode = newnode->child[m];
						for (int k = 0; k < 10; k++)
						{
							newnode = newnode->child[k];
							for (int j = 0; j < 10; j++)
							{
								root = newnode;
								root = root->child[j];

								for (int i = 0; i < 10; i++)
									createTree(root, ltrs, i, index);
							}
							newnode = newnode->parent;
						}
						newnode = newnode->parent;
					}
					newnode = newnode->parent;
				}
				newnode = newnode->parent;
			}
			newnode = newnode->parent;
		}
	}
	if (strlen(ltrs) > 7)
	{
		index++;
		for (int sv = 0; sv < 10; sv++)
		{
			newnode = newnode->child[sv];
			for (int s = 0; s < 10; s++)
			{
				newnode = newnode->child[s];
				for (int p = 0; p < 10; p++)
				{
					newnode = newnode->child[p];
					for (int f = 0; f < 10; f++)
					{
						newnode = newnode->child[f];
						for (int m = 0; m < 10; m++)
						{
							newnode = newnode->child[m];
							for (int k = 0; k < 10; k++)
							{
								newnode = newnode->child[k];
								for (int j = 0; j < 10; j++)
								{
									root = newnode;
									root = root->child[j];

									for (int i = 0; i < 10; i++)
										createTree(root, ltrs, i, index);
								}
								newnode = newnode->parent;
							}
							newnode = newnode->parent;
						}
						newnode = newnode->parent;
					}
					newnode = newnode->parent;
				}
				newnode = newnode->parent;
			}
			newnode = newnode->parent;
		}
	}
}

void Tree::createTree(Node *root, char *ltrs, int depth, int index)
{
	Node *newnode = new Node(depth, strlen(ltrs));
	for (int i = 0; i < strlen(ltrs); i++)
	{

		newnode->letter[i] = ltrs[i];
		if (index == i)
			newnode->value[i] = depth;
		else
			newnode->value[i] = root->value[i];

		root->child[depth] = newnode;
		newnode->parent = root;
		counter++;
	}
}
void assign(char str[])
{
	int i, j, l;
	l = strlen(str);
	for (i = 0; i < l; i++)
	{
		for (j = l4 - 1; j >= 0; j--)
		{
			if (letters[j] == str[i])
				break;
		}
		if (j == -1)
		{
			letters[l4] = str[i];
			l4++;
		}
	}
}
int main(int argc, char *argv[])
{

	if (argc < 5)
	{
		cout << "not enough input" << endl;
		return -1;
	}
	string tr= argv[1];
	string filename = (argv[5]);

	Tree mytree;

	w1=argv[2];
	w2=argv[3];
	w3=argv[4];

	l1 = strlen(w1);
	l2 = strlen(w2);
	l3 = strlen(w3);
	l4 = 0;
	assign(w1);
	assign(w2);
	assign(w3);

	cout << letters << endl; //harfler
	mytree.createaDepth(mytree.head, letters, -1);
	if (tr == "BFS")
		mytree.BFS(filename);
	else if (tr == "DFS")
		mytree.DFS(filename);
	else
		return -2;
}
