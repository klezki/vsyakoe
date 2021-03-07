struct tree
{
	long key;
	char balance;
	tree* left;
	tree* right;
	tree* pops;

	tree(const long& k, tree* dad) : key(k), pops(dad), left(nullptr), right(nullptr), balance(0) {};
	~tree(void)
	{
		if (left) delete left;
		if (right) delete right;
	}
};


struct AVL
{
	enum turn { left = true, right = false };
	enum after { insertion = true, removal = false };
	
	tree* root = nullptr;
	
	
	AVL() {};

	~AVL()
	{
		delete root;
	}

	tree* search(long key)
	{
		if (root == nullptr) return nullptr;
		tree* p = root;
		while (p->key != key)
		{
			if (key < p->key)
			{
				if (p->left) p = p->left;
				else return p;
			}
			else
			{
				if (p->right) p = p->right;
				else return p;
			}
		}
		return p;
	}

	tree* rotate(tree* A, bool _turn)
	{
		tree* B;
		if (_turn) //left
		{
			B = A->right;
			B->pops = A->pops;
			if (A->pops != nullptr)
			{
				if (A == A->pops->left) A->pops->left = B;
				else A->pops->right = B;
			}
			else root = B;
			A->pops = B;
			A->right = B->left;
			if (B->left != nullptr) B->left->pops = A;
			B->left = A;
			return B;
		}
		else
		{
			B = A->left;
			B->pops = A->pops;
			if (A->pops != nullptr)
			{
				if (A == A->pops->left) A->pops->left = B;
				else A->pops->right = B;
			}
			else root = B;
			A->pops = B;
			A->left = B->right;
			if (B->right != nullptr) B->right->pops = A;
			B->right = A;
			return B;
		}
	}

	tree* prerotate(tree* p, bool _turn)
	{
		if (_turn) //left
		{
			if (p->right->balance == -1)
			{
				rotate(p->right, turn::right);
				p = rotate(p, turn::left);
				switch (p->balance)
				{
				case -1:
					p->left->balance = 0;
					p->right->balance = 1;
					break;
				case 0:
					p->left->balance = 0;
					p->right->balance = 0;
					break;
				case 1:
					p->left->balance = -1;
					p->right->balance = 0;
					break;
				}
				p->balance = 0;
			}
			else
			{
				p = rotate(p, turn::left);
				switch (p->balance)
				{
				case 1:
					p->balance = 0;
					p->left->balance = 0;
					break;
				case 0:
					p->balance = -1;
					p->left->balance = 1;
					break;
				}
			}
		}
		else
		{
			if (p->left->balance == 1)
			{
				rotate(p->left, turn::left);
				p = rotate(p, turn::right);
				switch (p->balance)
				{
				case -1:
					p->left->balance = 0;
					p->right->balance = 1;
					break;
				case 0:
					p->left->balance = 0;
					p->right->balance = 0;
					break;
				case 1:
					p->left->balance = -1;
					p->right->balance = 0;
					break;
				}
				p->balance = 0;
			}
			else
			{
				p = rotate(p, turn::right);
				switch (p->balance)
				{
				case -1:
					p->balance = 0;
					p->right->balance = 0;
					break;
				case 0:
					p->balance = 1;
					p->right->balance = -1;
					break;
				}
			}
		}
		return p;
	}

	void restore(tree* p, bool when)
	{
		if (when == after::insertion)
		{
			if (p->balance == 0) return;
			while (p->pops)
			{
				if (p == p->pops->left) p->pops->balance--;
				else p->pops->balance++;
				p = p->pops;
				switch (p->balance)
				{
				case 2:
					p = prerotate(p, turn::left);
					if (p->balance == 0) return;
					break;
				case -2:
					p = prerotate(p, turn::right);
					if (p->balance == 0) return;
					break;
				case 0:
					return;
				default:
					break;
				}
			}
		}
		else
		{
			switch (p->balance)
			{
			case 2:
				p = prerotate(p, turn::left);
				if (p->balance != 0) return;
				break;
			case -2:
				p = prerotate(p, turn::right);
				if (p->balance != 0) return;
				break;
			case 0:
				break;
			default:
				return;
			}
			while (p->pops)
			{
				if (p == p->pops->left) p->pops->balance++;
				else p->pops->balance--;
				p = p->pops;
				switch (p->balance)
				{
				case 2:
					p = prerotate(p, turn::left);
					if (p->balance != 0) return;
					break;
				case -2:
					p = prerotate(p, turn::right);
					if (p->balance != 0) return;
					break;
				case 0:
					break;
				default:
					return;
				}
			}
		}
	}

	void add(long key)
	{
		if (root == nullptr)
		{
			root = new tree(key, nullptr);
			return;
		}
		tree* p = search(key);
		if (p->key == key) return;
		if (key < p->key)
		{
			p->left = new tree(key, p);
			p->balance--;
		}
		else
		{
			p->right = new tree(key, p);
			p->balance++;
		}
		restore(p, after::insertion);
	}


	void destroy(tree* p)
	{
		if (p->left == nullptr)
		{
			if (p->right == nullptr)
			{
				if (p == root)
				{
					delete root;
					root = nullptr;
					return;
				}
				if (p == p->pops->left)
				{
					p = p->pops;
					delete p->left;
					p->left = nullptr;
					p->balance++;
				}
				else
				{
					p = p->pops;
					delete p->right;
					p->right = nullptr;
					p->balance--;
				}
			}
			else
			{
				if (p == root)
				{
					root = p->right;
					p->right = nullptr;
					root->pops = nullptr;
					delete p;
					return;
				}
				if (p == p->pops->left)
				{
					p->pops->left = p->right;
					p->right = nullptr;
					p = p->pops;
					delete p->left->pops;
					p->left->pops = p;
					p->balance++;
				}
				else
				{
					p->pops->right = p->right;
					p->right = nullptr;
					p = p->pops;
					delete p->right->pops;
					p->right->pops = p;
					p->balance--;
				}
			}
		}
		else
		{
			tree* r = p->left;
			while (r->right) r = r->right;
			p->key = r->key;
			destroy(r);
			return;
		}
		restore(p, after::removal);
	}

	void searchanddestroy(long key)
	{
		if (root == nullptr) return;
		tree* p = search(key);
		if (key == p->key) destroy(p);
	}

};
