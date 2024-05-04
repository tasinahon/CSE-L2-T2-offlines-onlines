#include<bits/stdc++.h>
using namespace std;
ifstream in("in.txt");
ofstream out("out.txt");
class Binomial_heap
{
public:
    Binomial_heap *next, *child, *parent, *combined_heap;
    int degree, data;

    Binomial_heap()
    {

    }

    Binomial_heap* create_binomial_node(int data)
    {
        Binomial_heap *node = new Binomial_heap();
        node->data = data;
        node->next = NULL;
        node->child = NULL;
        node->parent = NULL;
        node->degree = 0;
        return node;
    }

    Binomial_heap* union_binomial_heap(Binomial_heap* heap1, Binomial_heap* heap2)
    {
        Binomial_heap *combined_heap = merge_binomial_heap(heap1, heap2);
        Binomial_heap *previous_heap = NULL;
        Binomial_heap *current_heap = combined_heap;
        Binomial_heap *next_heap = NULL;
        if(combined_heap != NULL)
        {
            next_heap=combined_heap->next;
        }


        while (next_heap != NULL)
        {
            if (current_heap->degree != next_heap->degree ||
                    (next_heap->next != NULL && next_heap->degree == next_heap->next->degree))
            {
                previous_heap = current_heap;
                current_heap = next_heap;
            }
            else
            {
                if (current_heap->data <= next_heap->data)
                {
                    current_heap->next = next_heap->next;
                    next_heap->parent = current_heap;
                    next_heap->next = current_heap->child;
                    current_heap->child = next_heap;
                    current_heap->degree++;
                }
                else
                {
                    if (previous_heap == NULL)
                    {
                        combined_heap = next_heap;
                    }
                    else
                    {
                        previous_heap->next = next_heap;
                    }
                    current_heap->parent = next_heap;
                    current_heap->next = next_heap->child;
                    next_heap->child = current_heap;
                    next_heap->degree++;
                    current_heap = next_heap;
                }
            }
            next_heap = current_heap->next;
        }


        return combined_heap;
    }



    Binomial_heap* merge_binomial_heap(Binomial_heap* heap1, Binomial_heap* heap2)
    {
        Binomial_heap* combined_heap = NULL;
        Binomial_heap* track_of_merged_heap = NULL;

        if (heap1 == NULL)
        {
            return heap2;
        }
        else if (heap2 == NULL)
        {
            return heap1;
        }

        while (heap1 != NULL && heap2 != NULL)
        {
            if (heap1->degree <= heap2->degree)
            {
                if (track_of_merged_heap == NULL)
                {
                    combined_heap = heap1;
                }
                else
                {
                    track_of_merged_heap->next = heap1;
                }
                track_of_merged_heap = heap1;
                heap1 = heap1->next;
            }
            else
            {
                if (track_of_merged_heap == NULL)
                {
                    combined_heap = heap2;
                }
                else
                {
                    track_of_merged_heap->next = heap2;
                }
                track_of_merged_heap = heap2;
                heap2 = heap2->next;
            }
        }

        if (heap1 != NULL)
        {
            track_of_merged_heap->next = heap1;

        }
        if (heap2 != NULL)
        {
            track_of_merged_heap->next = heap2;

        }



        return combined_heap;
    }


    void Insert(int data)
    {
        Binomial_heap* h = create_binomial_node(data);
        combined_heap = union_binomial_heap(combined_heap, h);
    }

    Binomial_heap* Find_Min()
    {
        Binomial_heap *heap1 = combined_heap;
        Binomial_heap *heap2 = combined_heap;
        while (heap1 != NULL)
        {
            if (heap1->data < heap2->data)
            {
                heap2 = heap1;
            }
            heap1 = heap1->next;
        }
        return heap2;
    }

    Binomial_heap* Extract_Min()
    {
        Binomial_heap *minimum_node = Find_Min();
        if (minimum_node == NULL)
        {
            return combined_heap;
        }


        Binomial_heap *current = combined_heap;
        Binomial_heap *previous = NULL;
        while (current != minimum_node)
        {
            previous = current;
            current = current->next;
        }

        if (previous != NULL)
        {
            previous->next = current->next;
        }
        else
        {
            combined_heap = current->next;
        }


        Binomial_heap *reversed_children = Reverse(minimum_node->child);


        combined_heap = union_binomial_heap(combined_heap, reversed_children);


        return minimum_node;
    }


    Binomial_heap* Reverse(Binomial_heap* heap)
    {
        Binomial_heap *previous = NULL;
        Binomial_heap *next = NULL;
        while (heap != NULL)
        {
            next = heap->next;
            heap->next = previous;
            previous = heap;
            heap = next;
        }
        return previous;
    }

    void print_heap(Binomial_heap* root, int c)
    {
        if (root == NULL)
        {
            return;
        }

        queue<pair<Binomial_heap*, int>> q;
        q.push({root, c});

        bool levelPrinted = false;

        while (!q.empty())
        {
            Binomial_heap* node = q.front().first;
            int level = q.front().second;
            q.pop();

            if (level != c)
            {
                cout << endl;
                out<<endl;
                c = level;
                levelPrinted = false;
            }

            if (!levelPrinted)
            {
                cout << "Level " << level << " : ";
                out << "Level " << level << " : ";
                levelPrinted = true;
            }

            cout << node->data << " ";
            out << node->data << " ";

            if (node->child != NULL)
            {
                Binomial_heap* temp = node->child;
                int childLevel = level + 1;
                while (temp != NULL)
                {
                    q.push({temp, childLevel});
                    temp = temp->next;
                }
            }
        }
    }



    void print()
    {
        Binomial_heap* curr = combined_heap;
        cout<<"Printing Binomial Heap.."<<endl;
        out<<"Printing Binomial Heap.."<<endl;
        while (curr != NULL)
        {
            int c=0;
            cout<<"Binomial Tree, B"<<curr->degree<<endl;
            out<<"Binomial Tree, B"<<curr->degree<<endl;
            this->print_heap(curr,c);
            curr = curr->next;
            cout<<endl;
            out<<endl;
        }
    }


};

int main()
{
    Binomial_heap heap;
    heap.combined_heap = NULL;

    string a,str;



    while(!in.eof())
    {
        getline(in,str);


        if(str[0]=='E')
        {

            Binomial_heap *h=heap.Extract_Min();
            cout<<"Extract-Min returned: "<<h->data<<endl;
            out<<"Extract-Min returned: "<<h->data<<endl;
        }
        else if(str[0]=='P')
        {

            heap.print();
        }
        if(str[0]=='I')
        {
            string sd;
            for(int i=2; i<str.size(); i++)
            {
                sd+=str[i];
            }
            istringstream s(sd);
            int b;
            s>>b;
            // cout<<b<<endl;
            heap.Insert(b);
        }
        else if(str[0]=='F')
        {
            Binomial_heap *h=heap.Find_Min();
            cout<<"Find-Min returned: "<<h->data<<endl;
            out<<"Find-Min returned: "<<h->data<<endl;
        }
        else if(str[0]=='U')
        {
            istringstream iss(str.substr(2));
            vector<int> nums;
            int num;
            while (iss >> num)
            {
                nums.push_back(num);
            }

            Binomial_heap heap2;
            heap2.combined_heap = NULL;
            for (int i = 0; i < nums.size(); i++)
            {
                heap2.Insert(nums[i]);
            }

            heap.combined_heap = heap.union_binomial_heap(heap.combined_heap, heap2.combined_heap);



        }
    }

    return 0;
}

