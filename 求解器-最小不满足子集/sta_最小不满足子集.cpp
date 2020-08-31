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
 // 一个向量用来存储 给每个变量赋值
 // -1 不能赋值
 // 0 正确
 // 1 错误
 vector<int> literals;
 vector<int> literal_frequency; // 向量 来存储每个文本的出现次数

 // 向量，用于存储每个字的正负性出现次数的差异
 vector<int> literal_polarity;
 // 向量存储每个字句
 // 每个字句，如果变量n是正的， 则存储2n
 // 如果变量是负的， 则存储2n+1
 // 假设n为零索引
 vector<vector<int>> clauses;
 Formula() {} //  默认的构造函数
 //  复制公式的复制构造函数-复制每个成员
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
*  类来表示SAT解算器的结构和功能
*/
static Formula ff;
class SATSolverDPLL{
private:
	Formula formula;  		//作为输入的初始公式
	int literal_count;  	// 公式的变量数
	int clause_count;  		// 公式中的句子数
	int unit_propagate(Formula &); // 执行单元传播
	int DPLL(Formula);   			//递归执行DPLL
	int apply_transform(Formula &, int);// 在每个字句中应用文本的值
	void show_result(Formula &, int); // 打印结果

public:
 	SATSolverDPLL(){} // 构造函数 默认
	void initialize(); //  初始化值
	void solve();      //  调用解算器
	void mytest(); // 测试
	void myrecover(); // 退回前一个状态
	void mydelete();
	void dispresult();

};
/*
*	 接受用户输入 并初始化计算器中属性 的函数
*/
void SATSolverDPLL::initialize(){
	char c; // 存储第一个字符
	string s; //   虚拟字符串
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
			fin >> literal_count; // 变量数
			fin >> clause_count;
			// 遍历此事
			cnt = clause_count;
			cout << literal_count << clause_count << endl;
			break;
		}else {
			cout << "parse error at char" << endl;
		}
	}
	// 将向量设置为适当的大小和初始值
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

	int literal; // 存储传入的文本值
	// 在子句上迭代
	for(int i = 0; i < clause_count; i++){

		while(true) // 得到更多的 文本
		{
			fin >> literal;

				cout << literal << " ";
				if(literal > 0) // 变量是正值
				{													//literal    1 2 3 4...  (减一 乘2)
					formula.clauses[i].push_back(2*(literal -1)); //以表格2n储存 0 2 4 6...
					//  文字的增量频率和极性
					formula.literal_frequency[literal -1]++; // 表示变量几（pi） 出现的频度
					formula.literal_polarity[literal - 1]++;
				} else if(literal < 0){ // 变量是负值						//literal    -1 -2 -3 -4 -5	(正值 减一 乘2 加1)
				formula.clauses[i].push_back(2 * ((-1)*literal -1) + 1);// 以表格2n+1储存1   3  5  7  9...
				// 文字的递增频率和递减极性
				formula.literal_frequency[-1 - literal]++; // 表示变量几（pi） 出现的频度
				formula.literal_polarity[-1 - literal]--;
				} else {
					break; //读0，所以转到下一个子句
				}
	  	}
	  		cout << endl;

	}
}
// 退回前一个状态


void SATSolverDPLL::myrecover(){
	//cout << endl << "退回一个字句" <<  endl;
	clause_count++;
	formula = ff;

}
void SATSolverDPLL::mydelete(){
	//clause_count--;
}
// 测试依次减少 语句；

static int flag2 = 1; // 1进 0 出
 void SATSolverDPLL::mytest(){
 	ff = formula;
 	Formula(SATSolverDPLL::formula);
 	clause_count--;
 	printf("start display");
 	cout << "变量数：" <<  literal_count << endl;
 	cout << "字句数："  <<  clause_count << endl;
 	int literal;
 	for(int i = 0; i < clause_count; i++){
 		cout << "第" << i + 1<< "字句";
 		for(int tmp = 0; tmp < formula.clauses[i].size(); tmp++){
		    literal = formula.clauses[i][tmp];
		    if(literal % 2 == 0 ){
		    	cout << "变量: " << literal/2 + 1 << " ";
		    	literal = literal/2 + 1;
		    	if(i == deletecnt && flag2){
						formula.literal_frequency[literal-1]--;
 		    			formula.literal_polarity[literal -1]--;
				}
			}else{
				cout << "变量: " << (-1)*((literal-1)/2 +1) << " ";
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
 			cout << "删除之后的打印：" << endl;
 			continue;
		 }
	 }
 }
/*
*在给定公式中执行单位分辨率的函数

*参数：f-执行单元解析的公式

*返回值：int-单元解析后解算器的状态，成员

*Cat枚举的Cat：：satisfied-公式已满足

*Cat：：未满足-公式不再满足

*Cat：：normal-正常退出

*/
int SATSolverDPLL::unit_propagate(Formula &f){
	bool unit_clause_found = false;//存储当前迭代是否找到unit子句
	if(f.clauses.size() == 0) // 如果 公式不包含字句
	{
		return Cat::satisfied; // 完全满足
	}
	do {
		unit_clause_found = false;
		// 迭代f中的字句
		for(int i = 0; i< f.clauses.size();i++){
			if(f.clauses[i].size() == 1) //如果子句的大小是1，则它是一个单元子句
			{
				unit_clause_found = true;
				// 0-如果为true，1-如果为false，则设置文本
				f.literals[f.clauses[i][0] /2] = f.clauses[i][0] % 2;
				// 一旦分配，重置频率以将其标记为关闭
				f.literal_frequency[f.clauses[i][0] /2] = -1;
				// 将此更改应用到f
				int result = apply_transform(f,f.clauses[i][0]/2);
				//如果这导致公式满足或不满足，
				// 返回结果标志
				if(result == Cat::satisfied || result == Cat::unsatisfied){
					return result;
				}
				break; // 退出循环以从一开始就检查另一个unit子句
			} else if(f.clauses[i].size() == 0) //如果给定子句为空
			{
				return Cat::unsatisfied;//这个公式在这个分支中是不可满足的
			}
		}
	} while(unit_clause_found);
	return Cat::normal ; // 如果到达这里，单位分辨率正常结束
}

/*

*将文字值应用于给定公式中的所有子句

*参数：f-要应用于的公式

*literal_to_apply-刚刚设置的literal

*返回值：int-返回状态标志，Cat enum的一个成员

*Cat：：满意-公式已满足

*Cat：：未满足-公式不再满足

*Cat：：normal-正常退出

*/
int SATSolverDPLL::apply_transform(Formula &f,int literal_to_apply)
{
	// 0是真 1为假
	int value_to_apply = f.literals[literal_to_apply];
	for(int i = 0; i <f.clauses.size();i++){
		// 迭代子句中的变量
		for(int j = 0; j <f.clauses[i].size();j++){
			//	如果这是真的，则文字的极性与它的极性相同
			//正在应用，即，如果指定为true，则在
			//赋值为false时，它会出现负值，因此在本子句中
			//现在变成了现实
			if((2 * literal_to_apply + value_to_apply) == f.clauses[i][j])
			{
				f.clauses.erase(f.clauses.begin()+i);//从列表中删除该子句
				i--; // 重置迭代器
				if(f.clauses.size() == 0)//如果所有的条款都删除了，公式就满足了
				{
					return Cat::satisfied;
				}
				break; // 到下一个句子
			} else if(f.clauses[i][j] / 2 == literal_to_apply)// 文字以相反的极性出现
			{
				f.clauses[i].erase(f.clauses[i].begin() + j);//从子句中删除文字，因为它是错误的
				j--; // 重置迭代
				if(f.clauses[i].size() == 0)// 如果子句为空，则当前公式不可满足
				{
					return Cat::unsatisfied;
				}
				break; //移到下一个子句
			}
		}
	}
	// 如果到达此处，功能将正常退出
	return Cat::normal;
}

/*

*函数对给定公式执行递归DPLL

*参数：f-要对其执行DPLL的公式

*返回值：int-返回状态标志，Cat enum的一个成员

*Cat：：normal-正常退出

*Cat：：completed-已找到结果，退出递归所有

*方式

*/
int SATSolverDPLL::DPLL(Formula f){
	// 对公式执行单位传播
	int result = unit_propagate(f);
	if(result == Cat::satisfied)//如果公式满足，则显示结果并返回
	{
		show_result(f,result);
		return Cat::completed;
	}else if(result == Cat::unsatisfied) //如果公式在此不满足分支，正常返回
	{
		return Cat::normal;
	}
	//找出f中频率最大的变量，它将是下一个
	//已分配值已分配变量中的此字段重置为-1
	//命令忽略他们
	int i = distance(f.literal_frequency.begin(),
	max_element(f.literal_frequency.begin(),f.literal_frequency.end()));
	// 需要申请两次，一次为真，另一次为假
	for(int j = 0; j<2; j++){
		Formula new_f = f; // 在递归之前复制公式
		if(new_f.literal_polarity[i] >0) //如果具有正极性的文字数量较大
		{
			new_f.literals[i] = j;//先分配正数
		}else {
			new_f.literals[i] = (j+1)%2; //先分配负数
		}
		new_f.literal_frequency[i] = -1; // 将频率重置为-1以在将来忽略
		int transform_result = apply_transform(new_f,i);//将更改应用于所有字句
		if(transform_result == Cat::satisfied) // 如果公式满足，则显示结果并返回
		{
			show_result(new_f,transform_result);
			return Cat::completed;
		}else if(transform_result == Cat::unsatisfied) //如果公式在此分支中不满足，则正常返回
		{
			continue;
		}
		int dpll_result = DPLL(new_f); //对新公式递归调用DPLL
		if(dpll_result == Cat::completed)  //传播结果（如果完成）
		{
			return dpll_result;
		}
	}
	// 如果控件到达此处，则函数已正常返回
	return Cat::normal;
}
/*

*函数以显示解算器的结果

*参数：f-当公式被满足或显示为不满足时

*result-结果标志，Cat枚举的成员

*/

void SATSolverDPLL::show_result(Formula &f,int result){
	if(result == Cat::satisfied) // 如果公式是可满足的
	{
		cout << "SAT" << endl;
		for(int i = 0; i<f.literals.size();i++){
			if(i != 0){
				cout << " ";
			}
			if(f.literals[i] != -1){
				cout << pow(-1,f.literals[i]) * (i+1);
			}else // 对于可以接受任意一个值的文本，可以任意指定其赋值为true
			{
				cout << (i+1);
			}
		}
		cout << " 0";
		flag = 0;
	}else // 如果公式不可满足
	{
		cout << "UNSAT";
		flag = 1;
		//flag2 = 0;
	}

}
/*

*函数调用解算器

*/

void SATSolverDPLL::solve(){
	// DPLL对原公式的最终结果如果正规回归到最后，
	// 则公式在任何分支中都不能满足，因此是不可满足的
	int result = DPLL(formula);
	if(result == Cat::normal){
		// 参数公式在这里是一个伪公式，结果是
		show_result(formula,Cat::unsatisfied);

	}
//	tmpclause_count = SATSolverDPLL::clause_count;
	//	tmpliteral_count = SATSolverDPLL::literal_count;
	//	ff = SATSolverDPLL::formula;
}
void SATSolverDPLL::dispresult(){

	int literal;

		cout << "最小不满足子集" << endl;
	for(int i =0 ; i< clause_count; i++){
		cout << "第" << i + 1<< "字句";
		for(int tmp = 0; tmp < formula.clauses[i].size(); tmp++){
			literal = formula.clauses[i][tmp];
			//cout << literal << " ";
			if(literal % 2 == 0 ){
		    	cout << "变量: " << literal/2 + 1 << " ";
		    	literal = literal/2 + 1;

			}else{
				cout << "变量: " << (-1)*((literal-1)/2 +1) << " ";
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
        cout << "不存在最少满足子集的说法";
        return 0;
    }
	//cnt--;
	while(--cnt) {
		solver.mytest();
		solver.solve();
		flag2 = 1;// 进去删除
		if(flag == 0) // 满足的情况下
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
