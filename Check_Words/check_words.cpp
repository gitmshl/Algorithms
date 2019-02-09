#include <iostream>
#include <cstring>
#include <windows.h>
#include <fstream>

using namespace std;

const int MAX_LENGTH_WORD = 25;

int change(char c)
{
    int n = (int) c;
    return n-97;
}

struct TRYE
{
    bool word;
    char data;
    TRYE* next;

    TRYE()
    {
        word = false;
        data = '&';
        next = NULL;
    }
};

TRYE* root1 = new TRYE[27];

void Insert(char* F, int Size, int iteration = 0, TRYE* root = root1)
    {
        if (root != NULL)
        {
            root[change(F[iteration])].data = F[iteration];
            if (iteration == (Size-1))
            {
                root[change(F[iteration])].word = true;
                return;
            }

            if (root[change(F[iteration])].next == NULL)
            {
                root[change(F[iteration])].next = new TRYE[27];
            }
            Insert(F, Size, iteration+1, root[change(F[iteration])].next);
        }
        else cout << "NULL\n";
    }

bool Search(char* F, int Size, int iteration = 0, TRYE* root = root1)
{
    if (root == NULL) return false;
    if (iteration == (Size-1))
    {
        if (root[change(F[iteration])].word) return true;
        return false;
    }
    return Search(F, Size, iteration+1, root[change(F[iteration])].next);
}

void Prototype_Show(char* current_word, int current_word_size, TRYE* root, char current_letter)
{
    if (root == NULL) { cout << "root == NULL. Dangerous\n"; return; }

    if (root[change(current_letter)].word)
    {
        cout << "---";
        for (int i = 0; i < current_word_size; i++)
            cout << current_word[i];
        cout << "\n";
    }

    TRYE* child = root[change(current_letter)].next; /// работаем очень осторожно с этим, ибо
                                            /// при удалении(автоматическом) переменной child, освобо
                                            /// дится место root[] !!!

    if (child != NULL)
    {
        for (int i = 0; i < 27; i++)
        {
            if (child[i].data != '&')
            {
                current_word[current_word_size] = child[i].data;
                Prototype_Show(current_word, current_word_size + 1, child, child[i].data);
            }
        }
    }

    child = NULL;           /// Это нужно, чтобы не удалить части массива root
}

void Prototype(char* F, int Size, TRYE* root = root1, int iteration = 0)
{
    if (iteration < (Size - 1))
    {
        if (root == NULL) { cout << "---Not Found\n"; return;}
        Prototype(F, Size, root[change(F[iteration])].next, iteration + 1);
    }
    else
    {
        if (root == NULL) { cout << "---Not Found\n"; return; }

        if (root[change(F[iteration])].data == '&')
            { cout << "---Not Found\n"; return;}
        else
        {
            char* common_word = new char[MAX_LENGTH_WORD];

            for (int i = 0; i < Size; i++)
                common_word[i] = F[i];

            Prototype_Show(common_word, Size, root, F[Size-1]);
        }
    }
}

int main()
{
   ifstream fin("words.txt");

   while (true)
   {
       char word[25];
       if (!(fin >> word)) break;
        int l = strlen(word);
        //cout << word << " " << l << "\n";
        Insert(word, l);
   }
   cout << "yes\n";




    while (true)
    {
        char word1[MAX_LENGTH_WORD], command[20];

        cin >> word1 >> command;
       // cout << "check: " << word1 << " " << command << "\n";
        if (!strcmp(command, "."))
        {
            if (Search(word1, strlen(word1)))
                cout << "----exists\n";
            else cout << "----not exists\n";
        }
        else if (!strcmp(command, ".."))
        {
            Prototype(word1, strlen(word1));
        }
        else if (!strcmp(command, "...")) break;
        else if (!strcmp(command, ",")) system("cls");
    }
    return 0;
}
