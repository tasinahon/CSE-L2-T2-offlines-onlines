#include<bits/stdc++.h>
using namespace std;
using namespace std::chrono;
ofstream out("out_avl.txt");
ofstream out2("report_avl.txt");

template <class T>
class avl_tree
{
public:
    T data;
    int height;
    avl_tree<T> *left, *right;
    avl_tree<T>* root;
    vector<int>inorder;
    int d;
    double totalF;
    string str;
    avl_tree()
    {

    }
    avl_tree<T>* create_avl_tree(T val)
    {
        avl_tree<T>*newn=new avl_tree();
        newn->data=val;
        newn->left=NULL;
        newn->right=NULL;
        newn->height=1;
        return newn;
    }
    void insert_call(T val)
    {
        root=Insert(root,val);

    }
    void delete_call(T val)
    {

        root=Deletion(root,val);

    }



    int height_each_node(avl_tree<T>* n)
    {
        if(n==NULL)
        {
            return 0;
        }
        return n->height;
    }

    int balance_or_not(avl_tree<T>* n)
    {
        if (n == NULL)
        {
            return 0;
        }
        return height_each_node(n->left) - height_each_node(n->right);
    }

    avl_tree<T>* left_rotation(avl_tree<T>* b)
    {
        avl_tree<T>*a=b->right;
        avl_tree<T> *e=a->left;

        a->left=b;
        b->right=e;
        b->height=1+max(height_each_node(b->left),height_each_node(b->right));
        a->height=1+max(height_each_node(a->left),height_each_node(a->right));

        return a;

        /*a                        b
        -   -                      -  -
        -     -          left          -    -
        b         c     <-------   d       a
        -  -                                -  -
        -      -                             -    -
        d            e                          e       c  */


    }
    avl_tree<T>* right_rotation(avl_tree<T>* a)
    {

        avl_tree<T>* b=a->left;
        avl_tree<T>*e=b->right;



        b->right=a;
        a->left=e;
        /*a                        b
        -   -                      -  -
        -     -                    -    -
        b         c     ------->    d       a
        -  -                                -  -
        -      -                             -    -
        d            e                          e       c  */

        a->height=1+max(height_each_node(a->left),height_each_node(a->right));
        b->height=1+max(height_each_node(b->left),height_each_node(b->right));
        return b;



    }

    avl_tree<T>* Insert(avl_tree<T>* root, T data)
    {
        if (root == NULL)
            return  create_avl_tree(data);

        if (data < root->data)
        {
            root->left = Insert(root->left, data);
        }

        else if (data > root->data)
        {
            root->right = Insert(root->right, data);
        }

        else
            return root;
        root->height = 1 + max(height_each_node(root->left), height_each_node(root->right));

        int h = balance_or_not(root);

        if (h > 1 )     //LL
        {
            if(data < root->left->data)
            {
                return right_rotation(root);
            }

        }

        if (h > 1 )       //LR
        {
            if(data > root->left->data)
            {
                root->left =left_rotation(root->left);
            }

            return right_rotation(root);
        }

        if (h < -1)      //RR
        {
            if(data > root->right->data)
            {
                return left_rotation(root);
            }


        }

        if (h < -1)      //RL
        {
            if(data < root->right->data)
            {
                root->right =right_rotation(root->right);
            }

            return left_rotation(root);
        }

        return root;
    }


    T inorder_successor(avl_tree<T> *node)
    {
        int minimum=node->data;
        while(node->left!=NULL)
        {
            minimum=node->left->data;
            node=node->left;
        }
        return minimum;
    }
    avl_tree<T>* Deletion(avl_tree<T>*root,int val)
    {
        if(root==NULL)
        {
            return root;
        }
        if(val<root->data)
        {
            root->left=Deletion(root->left,val);
        }
        else if(val>root->data)
        {
            root->right=Deletion(root->right,val);
        }
        else
        {
            if(root->left==NULL )
            {
                return root->right;
            }
            else if(root->right==NULL )
            {

                return root->left;

            }

            root->data=inorder_successor(root->right);
            root->right=Deletion(root->right,root->data);


        }


        root->height = 1 + max(height_each_node(root->left), height_each_node(root->right));

        int h = balance_or_not(root);

        if (h > 1 )      //LL
        {
            if(balance_or_not(root->left)>=0)
            {
                return right_rotation(root);
            }
        }



        if (h < -1 )      //RR
        {
            if(balance_or_not(root->right)<=0)
            {
                return left_rotation(root);
            }
        }




        if (h > 1)         //LR
        {
            if( balance_or_not(root->left)<0)
            {
                root->left =left_rotation(root->left);
            }

            return right_rotation(root);
        }
        if (h < -1)           //RL
        {
            if(balance_or_not(root->right)>0)
            {
                root->right =right_rotation(root->right);
            }

            return left_rotation(root);
        }

        return root;
    }
    bool Find(T data)
    {
        avl_tree<T>*x=NULL;
        if(root!=NULL)
        {
            auto start = std::chrono::high_resolution_clock::now();
            x=finditem(root,data);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> duration = end - start;
            totalF += duration.count();
        }

        if(x==NULL)
        {

            return 0;
        }
        else
        {

            return 1;
        }


    }
    avl_tree<T>* finditem(avl_tree<T> *root,T data)
    {
        if(root==NULL)
        {

            return NULL;
        }
        if(data==root->data)
        {

            return root;
        }

        if(data<root->data)
        {
            return finditem(root->left,data);
        }
        if(data>root->data)
        {
            return finditem(root->right,data);
        }


    }
    void traversal(avl_tree<T>*root)
    {
        if(root==NULL)
        {
            return ;
        }
        traversal(root->left);
        inorder.push_back(root->data);
        traversal(root->right);
    }
    void print_traversal()
    {
        for(int i=0; i<inorder.size(); i++)
        {
            out<<inorder[i]<<" ";
        }
        out<<"\n";
        inorder.clear();
    }
    string print(avl_tree<T>*root)
    {
        if (root == NULL)
            //str+=" ,";
            //return str;
            return " ";


        str +=to_string(root->data);


        if(d==0)
        {
            if (root->left == NULL && root->right == NULL)

                return str;
        }


        str += ('(');
        print(root->left);
        str += (',');
        // str += ('(');
        print(root->right);
        str += (')');

        return str;
    }

};

int main()
{
    ifstream in("in.txt");
    string st;
    int a;
    avl_tree<int> g;
    g.root=NULL;
    g.d=0;
    double totalI=0.0,totalD=0.0,totalT=0.0;
    g.totalF=0.0;
    while(getline(in,st))
    {

        if(st[0]=='I')
        {
            string sd="";
            for(int i=2; i<st.size(); i++)
            {
                sd+=st[i];
            }
            istringstream s(sd);
            s>>a;
            /*auto start = std::chrono::high_resolution_clock::now();
            g.insert_call(a);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> duration = end - start;
            totalI += duration.count();
            cI++;*/
            auto start_time = std::chrono::high_resolution_clock::now();
            g.insert_call(a);
            auto end_time = std::chrono::high_resolution_clock::now();
            auto execution_time_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
            double execution_time_ms = static_cast<double>(execution_time_ns) / 1e6;
            totalI += execution_time_ms;
            g.str="";
            string sy=g.print(g.root);
            out<<sy<<endl;


        }
        else if(st[0]=='D')
        {
            string sd="";
            for(int i=2; i<st.size(); i++)
            {
                sd+=st[i];
            }
            istringstream s(sd);
            s>>a;
            auto start = std::chrono::high_resolution_clock::now();
            g.delete_call(a);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> duration = end - start;
            totalD += duration.count();
            g.str="";
            string sy=g.print(g.root);
            out<<sy<<endl;

        }
        else if(st[0]=='F')
        {
            string sd="";
            for(int i=2; i<st.size(); i++)
            {
                sd+=st[i];
            }
            istringstream s(sd);
            s>>a;

            if(!g.Find(a))
            {
                out<<"not found"<<endl;
            }
            else
            {
                out<<"found"<<endl;
            }


        }
        else
        {
            auto start = std::chrono::high_resolution_clock::now();
            g.traversal(g.root);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> duration = end - start;
            totalT += duration.count();
            g.print_traversal();

        }
    }


    out2<<"operation time (ms)"<<endl;
    out2<<"insert"<<" "<<totalI<<endl;
    out2<<"delete"<<" "<<totalD<<endl;
    out2<<"search"<<" "<<g.totalF<<endl;
    out2<<"trav"<<" "<<totalT<<endl;
    out2<<"total"<<" "<<totalI+totalD+g.totalF+totalT<<endl;

}
