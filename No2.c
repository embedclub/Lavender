#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;
//思路：两个数组记录，其中一个从小到大排序,另一个find命令查找位置;
void printOrder(const int input[], int len, int output[]);

int main(){
	string str;
	while(getline(cin, str)){
		int output[100];
		int input[100];
		int tmpIndex =0;
		char tmp[2] = {0,0};
		vector<int> inputV;
		for(int i = 0; str[i] != '\0'; i++){
			if(str[i] == ','){
				//把字符串转换成整型数
				inputV.push_back(atoi(tmp));
                tmpIndex = 0;
                tmp[0] = 0;
                tmp[1] = 0;
			} else{
				tmp[tmpIndex++] = str[i];
			}
		}
		inputV.push_back(atoi(tmp));
        for(int i=0; i<(int)inputV.size(); i++){
            input[i] = inputV[i];
        }
        printOrder(input, inputV.size(), output);
        for(int i=0; i<(int)inputV.size()-1; i++){
            cout << output[i] << ", ";
        }
        cout << output[inputV.size()-1] << endl;
	}

	return 0;
}


void printOrder(const int input[], int len, int output[])
{
	vector<int> tmp, tmp2;
	for(int i = 0; i < len; i++){
		tmp.push_back(input[i]);
	}
	tmp2 = tmp;
	sort(tmp.begin(), tmp.end());
	int outputIndex = 0;
	for(int i = len - 1; i >= 0; i--){
		vector<int>::iterator ite = find(tmp2.begin(), tmp2.end(), tmp[i]);
		output[outputIndex++] = ite - tmp2.begin();
		while(ite != tmp2.end()){
			ite = find(ite + 1, tmp2.end(), tmp[i]);
			if(ite == tmp2.end())
				break;
			output[outputIndex++] = ite - tmp2.begin();
			i--;
		}

	}

}
