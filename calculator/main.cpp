#include <iostream>
#include <vector>
using namespace std; 
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

const int MAXLENGTH=110;

class Matrix{
	private:
		int row;
		int column;
		vector<int> value[MAXLENGTH];
	public:
		void define();
		void read();
		void write();
		Matrix transpose(); //转置 
};

int sizeNum=0;

int main(int argc, char** argv) {

	Matrix a,b;
	cout << endl << "请输入矩阵行数列数" << endl; 
	a.define();
	cout << endl << "请输入矩阵" << endl; 
	a.read();
	
	a.write();
	
	b=a.transpose();
	
	b.write();
	
	system("pause");

/*
	for(int i=0;i<*argv[1]-'0';i++){
		cout << argv[2] << endl; 
	}
	system("pause");
*/
	return 0;
}

void Matrix::define(){
	cin >> row >> column; 
}

void Matrix::read(){
	for(int i=0;i<row;i++){
		for(int j=0;j<column;j++){
			int tmp;
			cin >> tmp;
			value[i].push_back(tmp);
		}
	}
}

void Matrix::write(){
	for(int i=0;i<row;i++){
		cout << value[i][0];
		for(int j=1;j<column;j++){
			cout << " " << value[i][j];
		}
		cout << endl; 
	}
}

Matrix Matrix::transpose(){
	Matrix ret;
	ret.row=column;
	ret.column=row;
	for(int i=0;i<ret.row;i++){
		for(int j=0;j<ret.column;j++){
			ret.value[i].push_back(value[j][i]);
		}
	}
	return ret;
}
