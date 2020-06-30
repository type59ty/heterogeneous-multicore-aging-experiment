#include "read_mt.h"
#include "task.h"
#include "parseSTG.h"
#include "sim.h"
#include "parseENV.h"
#include "getTaskProfile.h"
#include "readTaskProfile.h"
#include <string>
#include <sstream>
using namespace std;
void print_clist(vector<vector<unsigned int> >); 
void print_tg(vector<vector<Task *> >); 
void print_port(vector<string> );
string to_string(int);

int main(int argc, char** argv){
//system("./main $benchmark_big $benchmark_lit $NUM_CORE $env $task_graph $policy $Frequency $NUM_IV 
//         $num_input_big @input_port_big $num_output_big @output_port_big $num_input_lit @input_port_lit $num_output_lit @output_port_lit");
/*
argv[1]: bm_big   
argv[2]: bm_lit   
argv[3]: num_core 
argv[4]: env_file 
argv[5]: tg_file  
argv[6]: policy   
argv[7]: frequency
argv[8]: num_iv
argv[9]: num_input_big
*/
    //cout.setf(ios::fixed, ios::floatfield);
    //cout.precision(10);
    //parse env file

    ENV *env = new ENV();
    env->start_parse(argv[4]);
    //get critical ratio and non_critical ratio
    //double critical_ratio = env->get_critical_ratio();
    //double nonCritical_ratio = env->get_nonCritical_ratio();
    
	
	// c499
    //double critical_ratio = 2.5;
    //double nonCritical_ratio = 3.0;
	
	// c432
    double critical_ratio = 3.4;
    double nonCritical_ratio = 3.9;

	// b14
    //double critical_ratio = 2.8;
    //double nonCritical_ratio = 3.2;

    //get critical task list
    vector<vector<unsigned int> > clist = env->get_critical_list();
    //print_clist(clist);
    
    //parse task graph
    ParseSTG *parseSTG = new ParseSTG();
    parseSTG->start_parse(argv[5]);
    vector<vector<Task *> > task_list;  
    
    task_list = parseSTG->get_list();
    //print_tg(task_list);
    
    //parse benchmark information
    int in_big_idx = 9;
    int num_input_big = atoi(argv[in_big_idx]);
    int out_big_idx = 9 + num_input_big + 1;
    int num_output_big = atoi(argv[out_big_idx]);

    int in_lit_idx = 9 + num_input_big + 1 + num_output_big + 1;
    int num_input_lit = atoi(argv[in_lit_idx]);
    int out_lit_idx = 9 + num_input_big + 1 + num_output_big + 1 + num_input_lit + 1;
    int num_output_lit = atoi(argv[out_lit_idx]);


    vector<string> input_port_big;
    vector<string> output_port_big;
    vector<string> input_port_lit;
    vector<string> output_port_lit;

    for(int i  = 0 ; i < num_input_big ; ++i){
        string str(argv[in_big_idx+1 + i]);
        input_port_big.push_back(str);
    }
    for(int i  = 0 ; i < num_output_big ; ++i){
        string str(argv[out_big_idx+1 + i]); 
        output_port_big.push_back(str);
    }
    for(int i  = 0 ; i < num_input_lit ; ++i){
        string str(argv[in_lit_idx+1 + i]);
        input_port_lit.push_back(str);
    }
    for(int i  = 0 ; i < num_output_lit ; ++i){
        string str(argv[out_lit_idx+1 + i]); 
        output_port_lit.push_back(str);
    }

    //cout << "big core\n";
    //cout << "num input: " << num_input_big << endl;
    //cout << "num output: " << num_output_big << endl;
    //print_port(input_port_big);
    //print_port(output_port_big);

    //cout << "little core\n";
    //cout << "num input: " << num_input_lit << endl;
    //cout << "num output: " << num_output_lit << endl;
    //print_port(input_port_lit);
    //print_port(output_port_lit);

    //map task graph to hspice result, ex. delay and power
    GetTaskProfile getTaskProfile(task_list, input_port_big, output_port_big, input_port_lit, output_port_lit, argv[1], argv[2], argv[7], argv[8]);
    //GetTaskProfile getTaskProfile_lit(List_lit, input_port_big, output_port_big, input_port_lit, output_port_lit, argv[1], argv[2], argv[7], argv[8]);
    vector<voltage_list *> voltages_big = getTaskProfile.get_voltage_list("big");
    vector<voltage_list *> voltages_lit = getTaskProfile.get_voltage_list("little");

   

    // print voltage
    //vector<voltage_list *>::iterator it;
    //cout << "big core voltage: \n";
    //for (it = voltages_big.begin(); it != voltages_big.end(); ++it) {
    //    cout << (*it)->voltage << endl;
    //}
    //cout << "little core voltage: \n";
    //for (it = voltages_lit.begin(); it != voltages_lit.end(); ++it) {
    //    cout << (*it)->voltage << endl;
    //}
    
    //vector<Task *>::iterator col;
    //cout << "========task graph========\n";
    //for (col = row->begin(); col != row->end(); ++col) {
    //    cout << "id: " << (*col)->id << endl;
    //    cout << "cycle: " << (*col)->cycle << endl;
    //    cout << "num_pre: " << (*col)->num_pre << endl;
    //    if ((*col)->num_pre > 0) {
    //        cout << "pre id: " << (*col)->pre.back()->id << endl;
    //    }
    //    cout << endl;
    //}


    // read big core benchmark
    ReadTaskProfile readTaskProfile(voltages_big, voltages_lit, getTaskProfile.get_time_list());
    readTaskProfile.readfile_big(argv[1], task_list[0]);
    // read little core benchmark
    readTaskProfile.readfile_lit(argv[2], task_list[0]);
    
    //cout << task_list[0][1]->delay_big << endl;
    //for (int i=0; i<20; i++) {
    //    cout << task_list[0][i]->delay_big << endl;
    //}
    //voltage and idle power map
    map<string, map<string,double> > idle_voltage_time_big = readTaskProfile.get_idle_voltage_time();
    map<string, map<string,double> > idle_voltage_time_lit = readTaskProfile.get_idle_voltage_time();
    int policy = atoi(argv[6]);
    int num_core = atoi(argv[3]);
    int num_core_big = atoi(argv[3]);
    int num_core_lit = atoi(argv[3]);
	if ( (policy == 4) or (policy == 5) ){
		num_core_big++;
	}


    Sim *sim = new Sim(task_list[0], num_core_big, num_core_lit ,idle_voltage_time_big, idle_voltage_time_lit, voltages_big, voltages_lit, critical_ratio, nonCritical_ratio, clist);
    sim->topological_ordering(); 
    sim->start_map(argv[1], argv[2], policy);
    return 0;
}

void print_clist(vector<vector<unsigned int> > clist) {
    //print critical list
    vector< vector<unsigned int> >::iterator row;
    vector<unsigned int>::iterator col;
    cout << "========critical list========\n";
    for (row = clist.begin(); row != clist.end(); ++row) {
      for (col = row->begin(); col != row->end(); ++col) {
          cout << *col << " ";
      }
      cout << endl;
    }

}

void print_tg(vector<vector<Task *> > List) {
    // print task graph
    vector< vector<Task *> >::iterator row;
    vector<Task *>::iterator col;
    cout << "========task graph========\n";
    for (row = List.begin(); row != List.end(); ++row) {
      for (col = row->begin(); col != row->end(); ++col) {
          cout << "id: " << (*col)->id << endl;
          cout << "cycle: " << (*col)->cycle << endl;
          cout << "num_pre: " << (*col)->num_pre << endl;
          if ((*col)->num_pre > 0) {
              cout << "pre id: " << (*col)->pre.back()->id << endl;
          }
          cout << endl;
      }
      cout << endl;
    }
}


void print_port(vector<string> port) {
    vector<string>::iterator it;
    for (it = port.begin(); it != port.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
}

string to_string(int a) {
    ostringstream temp;
    temp << a;
    return temp.str();
}









