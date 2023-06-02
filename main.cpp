#include<iostream>
#include<fstream>
#include<string>
#include<queue>
#include <unordered_map>
using namespace std;
class Huffman
{
	struct HNode
	{
		int freq;
		char character;
		HNode* left, * right;
		HNode()
		{
			this->freq = 0;
			character = NULL;
			left = NULL;
			right = NULL;
		}
		HNode(int freq, char character)
		{
			this->freq = freq;
			this->character = character;
			left = NULL;
			right = NULL;
		}
		bool isleaf()
		{
			return !(left && right);
		}
	};
	struct compareFreq
	{
		bool operator()(HNode* temp1, HNode* temp2)
		{
			return temp1->freq > temp2->freq;
		}
	};
	HNode* root;
	void print_Codes(HNode* ptr, string str = "")
	{
		if (ptr == NULL)
		{
			return;
		}
		if (ptr->isleaf())
		{
			cout << " Character : " << ptr->character << " Frequency : " << ptr->freq << "\n Code : " << str << "\n\n";
		}
		print_Codes(ptr->left, str + "1");
		print_Codes(ptr->right, str + "0");
	}
	void deleteAll(HNode* ptr)
	{
		if (ptr)
		{
			deleteAll(ptr->left);
			deleteAll(ptr->right);
			delete ptr;
		}
	}
public:
	Huffman()
	{
		root = NULL;
	}
	void createHuffman(char* filename)
	{
		ifstream fin(filename);
		if (fin.is_open())
		{
			unordered_map<char, int> hash_map;
			while (!fin.eof())
			{
				string temp;
				getline(fin, temp);
				for (int i = 0; i < (int)temp.size(); i++)
				{
					if (temp[i] > 31 && temp[i] < 127)
					{
						hash_map[temp[i]]++;
					}
				}
			}
			priority_queue<HNode*, vector<HNode*>, compareFreq> min_heap;
			for (auto it : hash_map)
			{
				HNode* temp = new HNode(it.second, it.first);
				min_heap.push(temp);
			}
			int x = (int)min_heap.size();
			while (x > 1)
			{
				HNode* temp = new HNode;
				temp->left = min_heap.top();
				min_heap.pop();
				temp->right = min_heap.top();
				min_heap.pop();
				temp->freq = temp->right->freq + temp->left->freq;
				min_heap.push(temp);
				x--;
			}
			root = min_heap.top();
		}
		else
		{
			cout << "File not opened\n";
		}
		fin.close();
	}
	void print_Code()
	{
		print_Codes(root);
	}
	~Huffman()
	{
		deleteAll(root);
	}
};
int main()
{
	Huffman obj;
	char filename[] = "data.txt";
	obj.createHuffman(filename);
	obj.print_Code();
	return 0;
}