#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
template <typename T> struct SplayTree {
	struct Node {
		Node(){}
		Node(T value_arg): value{value_arg} {}
		T value{}; //!< Value associated with node
		array<Node *, 2> child{}; //!< Left and right children
		Node *parent{}; //!< Pointer to parent
		//Node *path_parent{};
		bool side() const {
			/*! Returns true if child is on the right, and false otherwise*/
			return parent->child[1] == this;
		}
		void rotate() {
			/*! Rotate node x around its parent */
			const auto p = parent;
			const bool i = side();

			if (p->parent) {
				p->parent->attach(p->side(), this);
			} else {
				parent = nullptr;
			}
			p->attach(i, child[!i]);
			attach(!i, p);
		}
		void splay() {
			/*! Splay node x. x will become the root of the tree*/
			for(;parent;rotate()) {
				if (parent->parent) {
					(side() == parent->side() ? parent: this)->rotate();
				}
			}
		}
		array<Node *, 2> split() {
			splay();
			const auto right = child[1];
			if (right) {
				right->parent = nullptr;
			}
			this->right = nullptr;
			return {this, right};
		}
		void attach(bool side, Node *const new_) {
			/*! Attach node new_ as the node's side children*/
			if (new_) {
				new_->parent = this;
			}
			child[side] = new_;
		}
	};
	/** @brief Splay tree node */
	/*! Splay tree iterator */
	struct iterator {
		using iterator_category = bidirectional_iterator_tag;
		using value_type = T;
		using pointer = T *;
		using reference = T &;
		using difference_type = ll;
	      public:
		void operator--() { advance<false>(); }
		void operator++() { advance<true>(); }
		const T &operator*() { return node->value; }
		Node *node;
		iterator(Node *node_arg) : node(node_arg) {}
		bool operator==(const iterator oth) const {
			return node == oth.node;
		}
		bool operator!=(const iterator oth) const {return !(*this == oth);}
	      private:
		template <bool dir> void advance() {
			if (node->child[1]) {
				node = extremum<!dir>(node->child[1]);
				return;
			}
			for (; node->parent && node->side() == dir; node = node->parent)
				;
			node = node->parent;
		}
	};
	Node *root{}; /*!< Root node */
	ll size_{};   /*!< Size of the splay tree*/
	SplayTree() {}
	~SplayTree() { destroy(root); }
	static void destroy(Node *const node) {
		/*! Destroy the subtree node */
		if (!node) {
			return;
		}
		for (Node *const child : node->child) {
			destroy(child);
		}
		delete node;
	}
	void insert(Node *const x) {
		/*! Insert node x into the splay tree*/
		++size_;
		if (!root) {
			root = x;
			return;
		}
		auto y = root;
		while (true) {
			auto &nw = y->child[x->value > y->value];
			if (!nw) {
				nw = x;
				nw->parent = y;
				root = nw;
				nw->splay();
				return;
			}
			y = nw;
		}
		return;
	}
	void insert(const T &key) {
		/*! Insert key key into the splay tree*/
		insert(new Node{key});
	}
	void erase(Node *const x) {
		/*! Erase node x from the splay tree*/
		assert(x);
		x->splay();
		root = join(x->child[0], x->child[1]);
		delete x;
		--size_;
	}
	/** @brief Erases the node with key key from the splay tree */
	void erase(const T &key) { erase(find(key)); }
	template <bool i> static Node *extremum(Node * x) {
		/*! Return the extremum of the subtree x. Minimum if i is false,
		 * maximum if i is true.*/
		assert(x);
		for(; x->child[i]; x = x->child[i]);
		return x;
	}
	static Node *join(Node *const a, Node *const b) {
		if (!a) {
			b->parent = nullptr;
			return b;
		}
		Node *const mx = extremum<true>(a);
		mx->splay();
		assert(mx->child[1] == nullptr);
		mx->child[1] = b;
		mx->parent = nullptr;
		return mx;
	}
    /*! Returns node with key key*/
	Node *find(const T &key) {
		auto x = root;
		while(x && key != x->value){
			const auto next = x->child[key > x->value];
			if(!next){
				x->splay();
			}
			x = next;
		}
		return x;
	}
	/**
     * @brief Returns the number of nodes in the splay tree.
     */
    size_t size() const { return size_; }
	bool empty() const { return size() == 0; }
	iterator begin() { return iterator{extremum<false>(root)}; }
	iterator end() { return iterator{nullptr}; }
};
int main()
{ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    const int N=1000*100;
    SplayTree<int>t;
    for(int i=1;i<=N;i++){
        t.insert(rand()*rand());
    }
    /*for(int i=1;i<=N;i++){
        t.kustuta(rand());
    }*/
    return 0;
}
