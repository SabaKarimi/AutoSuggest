#include<bits/stdc++.h>
using namespace std;
class TrieNode{
    public:
        char data;
        unordered_map<char,TrieNode*> child;
        bool isEnd;
        TrieNode(char data){
            this->data = data;
            this->isEnd = false;
        }
};

class Trie{
    private:
        TrieNode* root;
    public:
        Trie(){
            root = new TrieNode(' ');
        }
        void insert(string &);
        void dfs(TrieNode* , vector<string>& , string&);
        vector<string> autoSuggest(string &);
        
};

void Trie :: insert(string &str){
    TrieNode* temp = root;
    for(auto &x:str){
        if(temp->child.find(x) == temp->child.end()){
            temp->child[x] = new TrieNode(x);
        }
        temp = temp->child[x];
    }
    temp->isEnd = true;
}

void Trie :: dfs(TrieNode* temp , vector<string>& words,string& curr){
    for(auto &p : temp->child){
        curr.push_back(p.first);
        dfs(p.second , words , curr);
        curr.pop_back();
    }
    if(temp->isEnd){
        words.push_back(curr);
    }
}
vector<string> Trie :: autoSuggest(string &str){
    TrieNode* temp = root;
    vector<string> words;
    for(auto &x:str){
        if(temp->child.find(x) != temp->child.end()){
            temp = temp->child[x];
        }
        else return words;
    }
    string curr = str;
    dfs(temp , words , curr);
    return words;
}
int main(){
    string str;
    ifstream fin;
    fin.open("words.txt" , ios :: in);
    Trie obj;
    while(!fin.eof()){
        getline(fin , str);
        obj.insert(str);
    }
    cout<<"Enter some text to get suggestions :";
    cin >> str;
    vector<string> words = obj.autoSuggest(str);
    int n = words.size();
    if(n == 0){
        cout<<"Nothing can be suggested";
    }
    else{
        cout<<"The suggestions are :\n";
        for(auto &x:words) cout<<x<<"\n";
    }
    fin.close();
    return 0;
}