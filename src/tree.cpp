
#include <vector>
struct Node
{

    int val;
    Node *parent;
    Node *left;
    Node *right;

};

class tree
{

    public:

        tree(Node *root)
        {
            this->root = root;
        }

        Node *root;

        void add(Node *addent)
        {
            
            Node *current;

            current = this->root;

            this->underadd(current, addent);

        }



    private:

        void underadd(Node *current, Node *addent)
        {

            if(current->left == NULL)
            {
                current->left = addent;
            }

            else if((current->right == NULL) && (current->left != NULL))
            {
                current->right = addent;
            }

            else
            {
                current = current->left;
                this->underadd(current, addent);
            }

        }

};

int main()
{
    return 0;
}

