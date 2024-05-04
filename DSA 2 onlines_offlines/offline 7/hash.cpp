#include<bits/stdc++.h>
using namespace std;
class HashTable
{
public:
    HashTable *next,**container;
    string key;
    int value;
    int actual_size;
    int c;
    string collision_method,hash_name;
    int min_size;
    int no_of_collisions;
    int total_probes;
    HashTable()
    {

    }
    HashTable(int min_size,string collision_method)
    {
        this->min_size=min_size;
        this->collision_method=collision_method;
        c=1;
        actual_size=next_prime();
        container=new HashTable*[actual_size+1]();
        for(int i=0; i<actual_size; i++)
        {
            container[i]=NULL;

        }
        no_of_collisions=0;
        total_probes=0;
    }
    HashTable* create_node(string data,int value)
    {
        HashTable *node=new HashTable();
        node->key=data;
        node->value=value;
        node->next=NULL;
        return node;
    }


    int next_prime()
    {
        int a=min_size;
        while(!isprime(a))
        {
            a++;
        }
        return a;

    }
    int isprime(int n)
    {
        int i;
        for(i=2; i*i<=n; i++)
        {
            if(n%i==0)
            {
                return 0;
            }
        }
        return 1;
    }
    void setHashName(string name)
    {
        hash_name=name;
    }
    int Hash1(string key)
    {


        const unsigned int m = 0x5bd1e995;
        const int r = 24;

        unsigned int hash = 0;

        for (char c : key)
        {
            unsigned int k = static_cast<unsigned int>(c);
            k *= m;
            k ^= k >> r;
            k *= m;

            hash *= m;
            hash ^= k;
        }

        return hash % actual_size;

    }
    int Hash2(string key)
    {

        const unsigned int FNV_prime = 16777619;
        unsigned int hash = 2166136261;

        for (char c : key)
        {
            hash ^= static_cast<unsigned int>(c);
            hash *= FNV_prime;
        }
        return hash % actual_size;
    }
    int auxHash(string k)
    {
        int count=0;
        for(int i=0; i<k.length(); i++)
        {
            count++;
        }
        int simple=count+100;
        return simple;
    }
    int DoubleHash(string k,int i)
    {
        int a;
        if(hash_name=="Hash1")
        {
            a=(Hash1(k)+i*auxHash(k))%actual_size;
        }
        else
        {
            a=(Hash2(k)+i*auxHash(k))%actual_size;
        }

        return a;
    }
    int custom_probing(string k,int i)
    {
        int C1=2;
        int C2=5;
        int a;
        if(hash_name=="Hash1")
        {
            a=(Hash1(k)+C1*i*auxHash(k)+C2*(i*i))%actual_size;
        }
        else
        {
            a=(Hash2(k)+C1*i*auxHash(k)+C2*(i*i))%actual_size;
        }

        return a;
    }
    void Insert(string key,int value)
    {
        no_of_collisions=0;
        if(value<actual_size)
        {
            int position ;
            if(hash_name=="Hash1")
            {
                position=Hash1(key);
            }
            else
            {

                position=Hash2(key);

            }



            if (collision_method == "Chaining")
            {
                HashTable *current_node = container[position];
                while (current_node != NULL)
                {
                    if (key == current_node->key)
                    {

                        return;
                    }
                    current_node = current_node->next;
                }
                if (container[position] == NULL)
                {
                    container[position] = create_node(key,value);

                }
                else
                {
                    current_node = container[position];
                    while (current_node->next != NULL)
                    {
                        current_node = current_node->next;
                    }
                    current_node->next = create_node(key,value);
                    no_of_collisions++;
                }
            }
            else if (collision_method == "Double Hashing")
            {
                int i = 0;
                int temp_position = position;

                while (container[temp_position] != NULL && i < actual_size)
                {
                    if (container[temp_position]->key == key)
                    {

                        return;
                    }
                    if (container[temp_position]->key == "" || container[temp_position]->key == key)
                    {

                        container[temp_position] = create_node(key,value);
                        return;
                    }
                    temp_position = DoubleHash(key, i);
                    i++;
                    no_of_collisions++;
                }
                if (i < actual_size)
                {
                    container[temp_position] = create_node(key, value);

                }

            }
            else if (collision_method == "Custom Probing")
            {
                int i = 0;
                int temp_position = position;
                while (container[temp_position] != NULL && i<actual_size)
                {
                    if(container[temp_position]->key==key)
                    {
                        return;
                    }
                    if(container[temp_position]->key=="" || container[temp_position]->key==key)
                    {
                        container[temp_position]=create_node(key,value);
                        return;
                    }
                    temp_position = custom_probing(key,i);
                    ++i;
                    no_of_collisions++;
                }
                if(i<actual_size)
                {
                    container[temp_position] =create_node(key,value);
                }

            }
        }
    }
    int Find(string key)
    {
        int position;
        if(hash_name=="Hash1")
        {
            position=Hash1(key);
        }
        else
        {
            position=Hash2(key);
        }
        total_probes=0;
        if(collision_method=="Chaining")
        {
            HashTable *node=container[position];
            while(node!=NULL)
            {
                if(node->key==key)
                {
                    total_probes++;
                    return node->value;

                }
                node=node->next;
                total_probes++;
            }
        }
        else if(collision_method=="Double Hashing")
        {

            int i = 0;
            int temp_position = position;

            while (container[temp_position] != NULL && i < actual_size)
            {
                if (container[temp_position]->key == key)
                {
                    if (container[temp_position]->value != -1)
                    {
                        total_probes++;
                        return container[temp_position]->value;
                    }
                    return -1;
                }
                temp_position = DoubleHash(key, i);
                total_probes++;
                i++;
            }

        }
        else if(collision_method=="Custom Probing")
        {
            int i=0;
            int temp_position=position;
            while(container[temp_position] !=NULL && i<actual_size)
            {
                if(container[temp_position]->key==key)
                {
                    if(container[temp_position]->value !=-1)
                    {
                        total_probes++;
                        return container[temp_position]->value;
                    }
                    return -1;

                }
                temp_position=custom_probing(key,i);
                total_probes++;
                i++;


            }

        }
        return -1;
    }
    void Delete(string key)
    {
        int position;
        if(hash_name=="Hash1")
        {
            position=Hash1(key);
        }
        else
        {
            position=Hash2(key);
        }
        if(collision_method=="Chaining")
        {
            HashTable *current = container[position];
            HashTable *prev = NULL;

            while (current != NULL && current->key != key)
            {
                prev = current;
                current = current->next;
            }

            if (current == NULL)
            {
                return;
            }

            if (prev != NULL)
            {
                prev->next = current->next;
            }
            else
            {
                container[position] = current->next;
            }

            delete current;

        }

        else if (collision_method == "Double Hashing")
        {
            int i = 0;
            int temp_position = position;

            while (container[temp_position] != NULL && i < actual_size)
            {
                if (container[temp_position]->key == key)
                {
                    container[temp_position]->key = "";
                    container[temp_position]->value = -1;
                    return;
                }
                temp_position = DoubleHash(key, i);
                i++;
            }
        }

        else if(collision_method=="Custom Probing")
        {
            int i=0;
            int temp_position=position;
            while (container[temp_position] != NULL && i < actual_size)
            {
                if (container[temp_position]->key == key)
                {
                    container[temp_position]->key = "";
                    container[temp_position]->value = -1;
                    return;
                }
                temp_position = custom_probing(key, i);
                i++;
            }
        }
    }


};
string random_word_generator()
{

    string s="abcdefghijklmnopqrstuvwxyz";
    string random_word="";
    int length_of_word=5+rand()%6;
    for(int i=0; i<length_of_word; i++)
    {
        random_word+=s[rand()%26];
    }
    return random_word;
}
int main()
{

    cout << setw(20) << "Hash Table Size:" << setw(40) << "Collision Resolution Method:"
         << setw(20) << "Hash1" << setw(40) << "Hash2" << endl;
    cout << setw(40) << "" << setw(40) << "No of collisions" << setw(20) << "Average probes"
         << setw(20) << "No of collisions" << setw(20) << "Average probes" << endl;


    vector<string> word_store;
    for (int i = 0; i < 10000; i++)
    {
        word_store.push_back(random_word_generator());
    }
    vector<int>index;
    vector<int>index2;

    for(int i=0; i<1000; i++)
    {
        int a=rand()%5000;
        index2.push_back(a);
    }
    for(int i=0; i<1000; i++)
    {
        int a=rand()%10000;
        index.push_back(a);
    }
    vector<int>size_of_hash= {5000,10000,20000};


    vector<string> methods = {"Chaining", "Double Hashing", "Custom Probing"};
    for(const int &indexsize:size_of_hash)
    {

        cout  <<setw(20)<< indexsize;
        for (const string& method : methods)
        {
            int first=0;
            int kl=0;
            HashTable h1(indexsize, method);
            h1.setHashName("Hash1");
            int total_collisions_hash1=0;
            int total_collisions_hash2=0;


            for(int i=0; i<10000; i++)
            {

                h1.Insert(word_store[i],i+1);
                total_collisions_hash1+=h1.no_of_collisions;
            }


            int total_probes_hash1 = 0;
            int total_probes_hash2 = 0;

            if(indexsize==5000)
            {
                for(int i=0; i<index2.size(); i++)
                {
                    string word = word_store[index2[i]];
                    h1.no_of_collisions=0;
                    h1.total_probes=0;
                    h1.Find(word);
                    total_probes_hash1+=h1.total_probes;
                }
            }
            else
            {
                for(int i=0; i<index.size(); i++)
                {
                    string word = word_store[index[i]];
                    h1.no_of_collisions=0;
                    h1.total_probes=0;
                    h1.Find(word);
                    total_probes_hash1+=h1.total_probes;
                }

            }





            h1.no_of_collisions=0;
            h1.total_probes=0;
            HashTable h2(indexsize,method);
            h2.setHashName("Hash2");

            for(int i=0; i<10000; i++)
            {

                h2.Insert(word_store[i],i+1);
                total_collisions_hash2+=h2.no_of_collisions;
            }
            if(indexsize==5000)
            {

                for(int i=0; i<index2.size(); i++)
                {
                    string word = word_store[index2[i]];
                    h2.no_of_collisions=0;
                    h2.total_probes=0;
                    h2.Find(word);
                    total_probes_hash2+=h2.total_probes;
                }
            }
            else
            {
                for(int i=0; i<index.size(); i++)
                {
                    string word = word_store[index[i]];
                    h2.no_of_collisions=0;
                    h2.total_probes=0;
                    h2.Find(word);
                    total_probes_hash2+=h2.total_probes;
                }
            }
            cout<<endl;
            cout <<setw(40)<< setw(60) << method << setw(20) << total_collisions_hash1
                 << setw(20) << total_probes_hash1 * 1.0 / 1000 << setw(20) << total_collisions_hash2
                 << setw(20) << total_probes_hash2 * 1.0 / 1000 << endl;
            cout<<"............................................................................................................................................................................."<<endl;

        }
    }


}
