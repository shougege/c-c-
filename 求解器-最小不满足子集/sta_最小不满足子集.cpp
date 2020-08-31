#include<algorithm>
#include<cmath>
#include<cstdint>
#include<iostream>
#include<string>
#include<vector>
#include<unistd.h>
#include<fstream>
using namespace std;
static int flag = 0;
static int deletecnt = 0;
static int cnt = 0;
/*
 * enum for different types of return flags defined
*/
enum Cat{
  satisfied,   // when a satisfying assignment has been found
  unsatisfied, // when no satisfying assignment has been found after
               // exhaustively searching
  normal,   // when no satisfying assignment has been found till now, and DPLL()
            // has exited normally
  completed // when the DPLL algorithm has completed execution

};
/*
* class to represent a boolean formula
*/

class Formula{
public:
 // һ�����������洢 ��ÿ��������ֵ
 // -1 ���ܸ�ֵ
 // 0 ��ȷ
 // 1 ����
 vector<int> literals;
 vector<int> literal_frequency; // ���� ���洢ÿ���ı��ĳ��ִ���

 // ���������ڴ洢ÿ���ֵ������Գ��ִ����Ĳ���
 vector<int> literal_polarity;
 // �����洢ÿ���־�
 // ÿ���־䣬�������n�����ģ� ��洢2n
 // ��������Ǹ��ģ� ��洢2n+1
 // ����nΪ������
 vector<vector<int>> clauses;
 Formula() {} //  Ĭ�ϵĹ��캯��
 //  ���ƹ�ʽ�ĸ��ƹ��캯��-����ÿ����Ա
 Formula& operator = (const Formula& f);
 Formula(const Formula &f) {
 	literals = f.literals;
 	clauses = f.clauses;
 	literal_frequency = f.literal_frequency;
 	literal_polarity = f.literal_polarity;
 }
};
Formula& Formula::operator =(const Formula &f){
	literals = f.literals;
 	clauses = f.clauses;
 	literal_frequency = f.literal_frequency;
 	literal_polarity = f.literal_polarity;
}
/*
*  ������ʾSAT�������Ľṹ�͹���
*/
static Formula ff;
class SATSolverDPLL{
private:
	Formula formula;  		//��Ϊ����ĳ�ʼ��ʽ
	int literal_count;  	// ��ʽ�ı�����
	int clause_count;  		// ��ʽ�еľ�����
	int unit_propagate(Formula &); // ִ�е�Ԫ����
	int DPLL(Formula);   			//�ݹ�ִ��DPLL
	int apply_transform(Formula &, int);// ��ÿ���־���Ӧ���ı���ֵ
	void show_result(Formula &, int); // ��ӡ���

public:
 	SATSolverDPLL(){} // ���캯�� Ĭ��
	void initialize(); //  ��ʼ��ֵ
	void solve();      //  ���ý�����
	void mytest(); // ����
	void myrecover(); // �˻�ǰһ��״̬
	void mydelete();
	void dispresult();

};
/*
*	 �����û����� ����ʼ�������������� �ĺ���
*/
void SATSolverDPLL::initialize(){
	char c; // �洢��һ���ַ�
	string s; //   �����ַ���
	ifstream fin("test1.dimacs");
	if(!fin){
		cout << "file not found: " << endl;
	}
	while(!fin.eof()){
		char ch;
		fin >> ch;
		if(ch == 'c'){
			char buf[1024];
			fin.getline(buf,1024);
		}else if(ch == 'p'){
			string buf;
			fin >> buf;
			//cout << "buf" << buf;
			fin >> literal_count; // ������
			fin >> clause_count;
			// ��������
			cnt = clause_count;
			cout << literal_count << clause_count << endl;
			break;
		}else {
			cout << "parse error at char" << endl;
		}
	}
	// ����������Ϊ�ʵ��Ĵ�С�ͳ�ʼֵ
	formula.literals.clear();
	formula.literals.resize(literal_count,-1);
	formula.clauses.clear();
	formula.clauses.resize(clause_count);
	formula.literal_frequency.clear();
	formula.literal_frequency.resize(literal_count,0);
	formula.literal_polarity.clear();
	formula.literal_polarity.resize(literal_count,0);

	ff.literals.clear();
	ff.literals.resize(literal_count,-1);
	ff.clauses.clear();
	ff.clauses.resize(clause_count);
	ff.literal_frequency.clear();
	ff.literal_frequency.resize(literal_count,0);
	ff.literal_polarity.clear();
	ff.literal_polarity.resize(literal_count,0);

	int literal; // �洢������ı�ֵ
	// ���Ӿ��ϵ���
	for(int i = 0; i < clause_count; i++){

		while(true) // �õ������ �ı�
		{
			fin >> literal;

				cout << literal << " ";
				if(literal > 0) // ��������ֵ
				{													//literal    1 2 3 4...  (��һ ��2)
					formula.clauses[i].push_back(2*(literal -1)); //�Ա��2n���� 0 2 4 6...
					//  ���ֵ�����Ƶ�ʺͼ���
					formula.literal_frequency[literal -1]++; // ��ʾ��������pi�� ���ֵ�Ƶ��
					formula.literal_polarity[literal - 1]++;
				} else if(literal < 0){ // �����Ǹ�ֵ						//literal    -1 -2 -3 -4 -5	(��ֵ ��һ ��2 ��1)
				formula.clauses[i].push_back(2 * ((-1)*literal -1) + 1);// �Ա��2n+1����1   3  5  7  9...
				// ���ֵĵ���Ƶ�ʺ͵ݼ�����
				formula.literal_frequency[-1 - literal]++; // ��ʾ��������pi�� ���ֵ�Ƶ��
				formula.literal_polarity[-1 - literal]--;
				} else {
					break; //��0������ת����һ���Ӿ�
				}
	  	}
	  		cout << endl;

	}
}
// �˻�ǰһ��״̬


void SATSolverDPLL::myrecover(){
	//cout << endl << "�˻�һ���־�" <<  endl;
	clause_count++;
	formula = ff;

}
void SATSolverDPLL::mydelete(){
	//clause_count--;
}
// �������μ��� ��䣻

static int flag2 = 1; // 1�� 0 ��
 void SATSolverDPLL::mytest(){
 	ff = formula;
 	Formula(SATSolverDPLL::formula);
 	clause_count--;
 	printf("start display");
 	cout << "��������" <<  literal_count << endl;
 	cout << "�־�����"  <<  clause_count << endl;
 	int literal;
 	for(int i = 0; i < clause_count; i++){
 		cout << "��" << i + 1<< "�־�";
 		for(int tmp = 0; tmp < formula.clauses[i].size(); tmp++){
		    literal = formula.clauses[i][tmp];
		    if(literal % 2 == 0 ){
		    	cout << "����: " << literal/2 + 1 << " ";
		    	literal = literal/2 + 1;
		    	if(i == deletecnt && flag2){
						formula.literal_frequency[literal-1]--;
 		    			formula.literal_polarity[literal -1]--;
				}
			}else{
				cout << "����: " << (-1)*((literal-1)/2 +1) << " ";
				literal = (-1)*((literal-1)/2 +1);
				if(i == deletecnt && flag2){
						formula.literal_frequency[-1 -literal]--;
 		   				 formula.literal_polarity[-1 -literal]++;
				}
			}
 		}
 		cout << endl;
 		if(i == deletecnt && flag2){
 			formula.clauses.erase(formula.clauses.begin() + deletecnt);

 			flag2 = 0;
 			cout << "ɾ��֮��Ĵ�ӡ��" << endl;
 			continue;
		 }
	 }
 }
/*
*�ڸ�����ʽ��ִ�е�λ�ֱ��ʵĺ���

*������f-ִ�е�Ԫ�����Ĺ�ʽ

*����ֵ��int-��Ԫ�������������״̬����Ա

*Catö�ٵ�Cat����satisfied-��ʽ������

*Cat����δ����-��ʽ��������

*Cat����normal-�����˳�

*/
int SATSolverDPLL::unit_propagate(Formula &f){
	bool unit_clause_found = false;//�洢��ǰ�����Ƿ��ҵ�unit�Ӿ�
	if(f.clauses.size() == 0) // ��� ��ʽ�������־�
	{
		return Cat::satisfied; // ��ȫ����
	}
	do {
		unit_clause_found = false;
		// ����f�е��־�
		for(int i = 0; i< f.clauses.size();i++){
			if(f.clauses[i].size() == 1) //����Ӿ�Ĵ�С��1��������һ����Ԫ�Ӿ�
			{
				unit_clause_found = true;
				// 0-���Ϊtrue��1-���Ϊfalse���������ı�
				f.literals[f.clauses[i][0] /2] = f.clauses[i][0] % 2;
				// һ�����䣬����Ƶ���Խ�����Ϊ�ر�
				f.literal_frequency[f.clauses[i][0] /2] = -1;
				// ���˸���Ӧ�õ�f
				int result = apply_transform(f,f.clauses[i][0]/2);
				//����⵼�¹�ʽ��������㣬
				// ���ؽ����־
				if(result == Cat::satisfied || result == Cat::unsatisfied){
					return result;
				}
				break; // �˳�ѭ���Դ�һ��ʼ�ͼ����һ��unit�Ӿ�
			} else if(f.clauses[i].size() == 0) //��������Ӿ�Ϊ��
			{
				return Cat::unsatisfied;//�����ʽ�������֧���ǲ��������
			}
		}
	} while(unit_clause_found);
	return Cat::normal ; // ������������λ�ֱ�����������
}

/*

*������ֵӦ���ڸ�����ʽ�е������Ӿ�

*������f-ҪӦ���ڵĹ�ʽ

*literal_to_apply-�ո����õ�literal

*����ֵ��int-����״̬��־��Cat enum��һ����Ա

*Cat��������-��ʽ������

*Cat����δ����-��ʽ��������

*Cat����normal-�����˳�

*/
int SATSolverDPLL::apply_transform(Formula &f,int literal_to_apply)
{
	// 0���� 1Ϊ��
	int value_to_apply = f.literals[literal_to_apply];
	for(int i = 0; i <f.clauses.size();i++){
		// �����Ӿ��еı���
		for(int j = 0; j <f.clauses[i].size();j++){
			//	���������ģ������ֵļ��������ļ�����ͬ
			//����Ӧ�ã��������ָ��Ϊtrue������
			//��ֵΪfalseʱ��������ָ�ֵ������ڱ��Ӿ���
			//���ڱ������ʵ
			if((2 * literal_to_apply + value_to_apply) == f.clauses[i][j])
			{
				f.clauses.erase(f.clauses.begin()+i);//���б���ɾ�����Ӿ�
				i--; // ���õ�����
				if(f.clauses.size() == 0)//������е����ɾ���ˣ���ʽ��������
				{
					return Cat::satisfied;
				}
				break; // ����һ������
			} else if(f.clauses[i][j] / 2 == literal_to_apply)// �������෴�ļ��Գ���
			{
				f.clauses[i].erase(f.clauses[i].begin() + j);//���Ӿ���ɾ�����֣���Ϊ���Ǵ����
				j--; // ���õ���
				if(f.clauses[i].size() == 0)// ����Ӿ�Ϊ�գ���ǰ��ʽ��������
				{
					return Cat::unsatisfied;
				}
				break; //�Ƶ���һ���Ӿ�
			}
		}
	}
	// �������˴������ܽ������˳�
	return Cat::normal;
}

/*

*�����Ը�����ʽִ�еݹ�DPLL

*������f-Ҫ����ִ��DPLL�Ĺ�ʽ

*����ֵ��int-����״̬��־��Cat enum��һ����Ա

*Cat����normal-�����˳�

*Cat����completed-���ҵ�������˳��ݹ�����

*��ʽ

*/
int SATSolverDPLL::DPLL(Formula f){
	// �Թ�ʽִ�е�λ����
	int result = unit_propagate(f);
	if(result == Cat::satisfied)//�����ʽ���㣬����ʾ���������
	{
		show_result(f,result);
		return Cat::completed;
	}else if(result == Cat::unsatisfied) //�����ʽ�ڴ˲������֧����������
	{
		return Cat::normal;
	}
	//�ҳ�f��Ƶ�����ı�������������һ��
	//�ѷ���ֵ�ѷ�������еĴ��ֶ�����Ϊ-1
	//�����������
	int i = distance(f.literal_frequency.begin(),
	max_element(f.literal_frequency.begin(),f.literal_frequency.end()));
	// ��Ҫ�������Σ�һ��Ϊ�棬��һ��Ϊ��
	for(int j = 0; j<2; j++){
		Formula new_f = f; // �ڵݹ�֮ǰ���ƹ�ʽ
		if(new_f.literal_polarity[i] >0) //������������Ե����������ϴ�
		{
			new_f.literals[i] = j;//�ȷ�������
		}else {
			new_f.literals[i] = (j+1)%2; //�ȷ��为��
		}
		new_f.literal_frequency[i] = -1; // ��Ƶ������Ϊ-1���ڽ�������
		int transform_result = apply_transform(new_f,i);//������Ӧ���������־�
		if(transform_result == Cat::satisfied) // �����ʽ���㣬����ʾ���������
		{
			show_result(new_f,transform_result);
			return Cat::completed;
		}else if(transform_result == Cat::unsatisfied) //�����ʽ�ڴ˷�֧�в����㣬����������
		{
			continue;
		}
		int dpll_result = DPLL(new_f); //���¹�ʽ�ݹ����DPLL
		if(dpll_result == Cat::completed)  //��������������ɣ�
		{
			return dpll_result;
		}
	}
	// ����ؼ�����˴�����������������
	return Cat::normal;
}
/*

*��������ʾ�������Ľ��

*������f-����ʽ���������ʾΪ������ʱ

*result-�����־��Catö�ٵĳ�Ա

*/

void SATSolverDPLL::show_result(Formula &f,int result){
	if(result == Cat::satisfied) // �����ʽ�ǿ������
	{
		cout << "SAT" << endl;
		for(int i = 0; i<f.literals.size();i++){
			if(i != 0){
				cout << " ";
			}
			if(f.literals[i] != -1){
				cout << pow(-1,f.literals[i]) * (i+1);
			}else // ���ڿ��Խ�������һ��ֵ���ı�����������ָ���丳ֵΪtrue
			{
				cout << (i+1);
			}
		}
		cout << " 0";
		flag = 0;
	}else // �����ʽ��������
	{
		cout << "UNSAT";
		flag = 1;
		//flag2 = 0;
	}

}
/*

*�������ý�����

*/

void SATSolverDPLL::solve(){
	// DPLL��ԭ��ʽ�����ս���������ع鵽���
	// ��ʽ���κη�֧�ж��������㣬����ǲ��������
	int result = DPLL(formula);
	if(result == Cat::normal){
		// ������ʽ��������һ��α��ʽ�������
		show_result(formula,Cat::unsatisfied);

	}
//	tmpclause_count = SATSolverDPLL::clause_count;
	//	tmpliteral_count = SATSolverDPLL::literal_count;
	//	ff = SATSolverDPLL::formula;
}
void SATSolverDPLL::dispresult(){

	int literal;

		cout << "��С�������Ӽ�" << endl;
	for(int i =0 ; i< clause_count; i++){
		cout << "��" << i + 1<< "�־�";
		for(int tmp = 0; tmp < formula.clauses[i].size(); tmp++){
			literal = formula.clauses[i][tmp];
			//cout << literal << " ";
			if(literal % 2 == 0 ){
		    	cout << "����: " << literal/2 + 1 << " ";
		    	literal = literal/2 + 1;

			}else{
				cout << "����: " << (-1)*((literal-1)/2 +1) << " ";
				literal = (-1)*((literal-1)/2 +1);

		}
	}
		cout << endl;
	}
}
int main(){
	SATSolverDPLL solver;
	solver.initialize();
	solver.solve();
	if(flag == 0)
    {
        cout << "���������������Ӽ���˵��";
        return 0;
    }
	//cnt--;
	while(--cnt) {
		solver.mytest();
		solver.solve();
		flag2 = 1;// ��ȥɾ��
		if(flag == 0) // ����������
		{

			solver.myrecover();
			deletecnt++;

		}
		else{
			solver.mydelete();
		}
		cout <<endl;
	}

	solver.dispresult();

	return 0;
}
