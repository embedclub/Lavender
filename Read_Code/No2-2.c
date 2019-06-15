#include<iostream>
#include<vector>
#include<string>
#include<list>
using namespace std;
struct Node{
    int id;
    int pri;
};
int main(){
    string str;
    vector<int> input;
    list<Node> printlist;
    while(getline(cin,str)){
        for(int i=0;i<str.size();i++)
            if(str[i]>='1'&&str[i]<='9')
                input.push_back(str[i]-'0');

        struct Node tmp;
        for(int j=0;j<input.size();j++){
            tmp.id=j;
            tmp.pri=input[j];
            printlist.push_back(tmp);
        }
        list<Node>::iterator it;
        list<Node>::iterator the_max;

        while(printlist.size()!=0){
            the_max=printlist.begin();
            for(it=printlist.begin();it!=printlist.end();it++){
                if((*it).pri>(*the_max).pri){
                    tmp=printlist.front();
                    printlist.pop_front();
                    printlist.push_back(tmp);
                    break;
                }
            }
            if(it==printlist.end()){
                cout<<(*the_max).id;
                if(printlist.size()==1){
                    cout<<endl;
                }else{
                    cout<<", ";
                }
                printlist.pop_front();
            }

        }
        input.clear();
        printlist.clear();
    }
}

