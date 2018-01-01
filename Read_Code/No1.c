#include<iostream>
#include<string>
#include<vector>
#include<stack>

using namespace std;

struct ABC {
	int a;

	char str[];
};

int main(){
	struct ABC a;

	string s;
	while(cin>>s){
		stack<char> stk;
		int left = 0;
		int right = 0;
		int flag = 1;
//思路：遇到左边括号，放进栈里面，并设置相关标志位
//第一种情况：第一次遇到右括号，如')'  ']'  '}'
//第二种情况：左右的括号不匹配
//第三种情况：左右括号匹配，设置标志位，弹出比较的括号
		for(int i = 0;i < s.size(); i++){
			if(s[i] == '(' || s[i] == '[' || s[i] == '{'){
				left = 1;
				right = 1;
				stk.push(s[i]);
			} else {
//第一种情况：第一次遇到右括号，如')'  ']'  '}'
				if((s[i] == ')' || s[i] == ']' || s[i] == '}') && stk.empty()){
					right = 1;
					left = 0;
					cout << "false" <<endl;
					break;
				}
				else {
//第二种情况：左右的括号不匹配
					if((s[i] == ')' && stk.top() != '(') || (s[i] == ']' && stk.top() != '[') || (s[i] == '}' && stk.top() != '{')){
					flag = 0;
					right = 1;
					left = 0;

					cout << "false" << endl;
					break;
					}
//第三种情况：左右括号匹配，设置标志位，弹出比较的括号
					if((s[i] == ')' && stk.top() == '(') || (s[i] == ']' && stk.top() == '[') || (s[i] == '}' && stk.top() == '{')){
						right = 1;
						stk.pop();

					}

				}
				

			}
			
		}

		if(!stk.empty() && flag){
			cout << "false"<< endl;
		}
//里面的括号完全匹配
		else if(left == 1) {
			cout << "true" << endl;
		}
//代表所输入的字符串里面没有任何括号
		else if(right == 0){
			cout << "true" << endl;
		}

	}

	

	

	return 0;
}
