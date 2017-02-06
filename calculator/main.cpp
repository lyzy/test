#include <iostream>
#include <vector>
using namespace std; 
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

const int MAXLENGTH=110;

class Matrix{
	protected:
		int row;
		int column;
		vector<double> value[MAXLENGTH];
	public:
		Matrix(){		//���캯�� 
			row=column=0;
			for(int i=0;i<MAXLENGTH;i++){
				value[i].clear();
			}
		}
		~Matrix(){		//���������������ݣ� 
		}
		void define(int x,int y);
		void read();
		void write();
		Matrix transpose(); //ת��
		Matrix operator+(const Matrix & x) const;		//const��ʾ����Ա�����������ڲ��ܸı��Ա
		Matrix operator-(const Matrix & x) const;
		Matrix operator*(const Matrix & x) const;
};

//�̳�:������ 
class Phalanx : public Matrix
{
	protected:
		int order;
	public:
		Phalanx(){
			row=column=order=0;
			for(int i=0;i<MAXLENGTH;i++){
				value[i].clear();
			}
		}
		~Phalanx(){
		}
		virtual void define(int x);
		double trace();		//��
		double algebra_cofactor(int x,int y);		//��������ʽ 
		double det();		//����ʽ
};

const Matrix ERROR;//		��Ч����ķ���ֵ 

int sizeNum=0;

int main(int argc, char** argv) {
/* 
	Matrix a,b;
	int n_a,m_a,n_b,m_b;
	cout << endl << "please input the n, m of a: " << endl;
	cin >> n_a >> m_a;
	a.define(n_a,m_a);
	a.read();
	cout << endl << "please input the n, m of b: " << endl;
	cin >> n_b >> m_b;
	b.define(n_b,m_b);
	b.read();
	Matrix c=a*b;
	c.write();


	Phalanx a;
	cout << endl << "please input the order of a" <<endl;
	int input_row,input_column,input_order;
	cin >> input_order;
	a.define(input_order);
	a.read();
	cout << "the trace of a is: " << a.trace() << endl;
	cout << "the det of a is: " << a.det() << endl; 
	cout << "the alfa of a 2 2 is: " << a.algebra_cofactor(2,2) << endl;
/*
	Matrix a,b;
	cout << endl << "�����������������" << endl; 
	a.define();
	cout << endl << "���������" << endl; 
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

//-----------functions of Matrix

void Matrix::define(int x,int y){
	row=x;
	column=y;
}

void Matrix::read(){
	for(int i=0;i<row;i++){
		for(int j=0;j<column;j++){
			double tmp;
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

Matrix Matrix::operator+(const Matrix & x) const{
	Matrix ret;
	ret.define(row,column);
	if (row!=x.row || column!=x.column){
		cerr << "Invalid operation: two matrix shall be the same size\n";
		return ERROR;
	}
	else{
		for(int i=0;i<row;i++){
			for(int j=0;j<column;j++){
				ret.value[i].push_back(value[i][j]+x.value[i][j]);
			}
		}
		return ret;
	}
}

Matrix Matrix::operator-(const Matrix & x) const{
	Matrix ret;
	ret.define(row,column);
	if (row!=x.row || column!=x.column){
		cerr << "Invalid operation: two matrix shall be the same size\n";
		return ERROR;
	}
	else{
		for(int i=0;i<row;i++){
			for(int j=0;j<column;j++){
				ret.value[i].push_back(value[i][j]-x.value[i][j]);
			}
		}
		return ret;
	}
}

Matrix Matrix::operator*(const Matrix & x) const{
	Matrix ret;
	ret.define(row,x.column);
	if (column != x.row){
		cerr << "Invalid operation: cannot multiply\n";
		return ERROR;
	}
	else{
		for(int i=0;i<ret.row;i++){
			for(int j=0;j<ret.column;j++){
				double cur=0;
				for(int k=0;k<column;k++){
					cur += value[i][k]*x.value[k][j];
				}
				ret.value[i].push_back(cur);
			}
		}
		return ret;
	}
}

//---------------functions of Phalanx 

void Phalanx::define(int x){
	order=row=column=x;
	
}

double Phalanx::trace(){
	double ret=0;
	for(int i=0;i<order;i++){
		ret+=value[i][i];
	}
	return ret; 
}

double Phalanx::algebra_cofactor(int x,int y){
	Phalanx newPhalanx;
	newPhalanx.define(order-1);
	x--,y--;
	for(int i=0;i<x;i++){
		newPhalanx.value[i]=value[i];
		newPhalanx.value[i].erase(newPhalanx.value[i].begin()+y);
	}
	for(int i=x;i<newPhalanx.order;i++){
		newPhalanx.value[i]=value[i+1];
		newPhalanx.value[i].erase(newPhalanx.value[i].begin()+y);
	}
	if ((x+y)&1==1){
		return -newPhalanx.det(); 
	}
	else{
		return newPhalanx.det();
	}
}

double Phalanx::det(){
	double ret=0;
	if (order==1){
		return value[0][0];
	}
	if (order==2){
		return value[0][0]*value[1][1]-value[0][1]*value[1][0];
	}
	for(int i=0;i<order;i++){
		ret+=value[i][0]*algebra_cofactor(i+1,1);
	}
	return ret;
}
