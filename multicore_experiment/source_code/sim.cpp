#include "sim.h"
#define NS 1000000000
#define NS_SQ NS*NS
#define END_TASK 21
#define START_TASK 3
#define START_TASK2 10
#define START_TASK3 13 
#define START_TASK4 20

ofstream DBG;
ofstream month_log;

bool reScheduling_cmp(const Task *a, const Task *b) {
    if (a->ready_time < b->ready_time) {
        return true;
    } else {
        if (a->last_start_time_big < b->last_start_time_big) {
            return true;
        }
        return false;
    }
}
bool cmp(const TaskInfo &a, const TaskInfo &b){
    return a.cost < b.cost;
}
bool ready_cmp(const Task *a, const Task *b) {
    //return a->ready_time_big < b->ready_time_big;
    return a->ready_time < b->ready_time;
}
bool deadline_cmp(const Task *a, const Task *b) {
    return a->deadline_time < b->deadline_time;
}
bool last_start_time_cmp(const Task *a, const Task *b){
    //return a->last_start_time_lit < b->last_start_time_lit;
    return a->last_start_time < b->last_start_time;
}
bool operate_time_cmp(const Processor *a, const Processor *b){
    return a->vth < b->vth;
}
bool index_cmp(const Processor *a, const Processor *b){
    return a->index < b->index;
}
bool slack_cmp(const TaskInfo &a, const TaskInfo &b){
    return a.slack > b.slack;
}
bool spare_core_cmp(const Processor *a, const Processor *b){
    if(a->isProtect == true) {
        return true;
    } else{
        return false;
    }
}
bool sortbysec(const pair<int, double> &a, const pair<int,double> &b) {
	return a.second > b.second;
}


bool Sim::update(Processor *proc){
    string aging_time;
    if(proc->aging_time == "0m"){
        aging_time = "1m";
    } else if(proc->aging_time =="1m"){
        aging_time = "2m";
    } else if(proc->aging_time =="2m"){
        aging_time = "3m";
    } else if(proc->aging_time =="3m"){
        aging_time = "4m";
    } else if(proc->aging_time =="4m"){
        aging_time = "5m";
    } else if(proc->aging_time =="5m"){
        aging_time = "6m";
    } else if(proc->aging_time =="6m"){
        aging_time = "7m";
    } else if(proc->aging_time =="7m"){
        aging_time = "8m";
    } else if(proc->aging_time =="8m"){
        aging_time = "9m";
    } else if(proc->aging_time =="9m"){
        aging_time = "10m";
    } else if(proc->aging_time =="10m"){
        aging_time = "11m";
    } else if(proc->aging_time =="11m"){
        aging_time = "1y";
    } else if(proc->aging_time =="1y"){
        aging_time = "2y";
    } else if(proc->aging_time =="2y"){
        aging_time = "3y";
    } else if(proc->aging_time =="3y"){
        aging_time = "4y";
    } else if(proc->aging_time =="4y"){
        aging_time = "5y";
    } else if(proc->aging_time =="5y"){
        aging_time = "6y";
    } else if(proc->aging_time =="6y"){
        aging_time = "7y";
    } else if(proc->aging_time =="7y"){
        aging_time = "8y";
    } else if(proc->aging_time =="8y"){
        aging_time = "9y";
    } else if(proc->aging_time =="9y"){
        aging_time = "10y";
    } else if(proc->aging_time =="10y"){
        aging_time = "11y";
    } else if(proc->aging_time =="11y"){
        aging_time = "12y";
    } else if(proc->aging_time =="12y"){
        aging_time = "13y";
    } else if(proc->aging_time =="13y"){
        aging_time = "14y";
    } else if(proc->aging_time =="14y"){
        aging_time = "15y";
    } else if(proc->aging_time =="15y"){
        aging_time = "16y";
    } else if(proc->aging_time =="16y"){
        aging_time = "17y";
    } else if(proc->aging_time =="17y"){
        aging_time = "18y";
    } else if(proc->aging_time =="18y"){
        aging_time = "19y";
    } else if(proc->aging_time =="19y"){
        aging_time = "20y";
    } else if(proc->aging_time =="20y"){
        aging_time = "21y";  
    } 
    //else if(proc->aging_time =="21y"){
    //    aging_time = "22y";
    //}  
    map<string, double>::iterator it = vths.find(aging_time);
    if (it == vths.end()) {
        //aging_time = "20y";
        //proc->aging_time = aging_time;
        //cout << "aging time: " << aging_time << endl;
        return 0;
    }
    double next_vth = it->second;
    if(proc->vth >= next_vth){
        set_process_vth(proc, aging_time);
    }
    return 1;
}

void Sim::print(int round){
    wfile << endl;
    wfile << "******************************************************************" << endl;
    wfile << "============================ big core ============================" << endl;
    wfile << "Simulator time: " << aging_time << ", " << operate_time * NS <<endl;
    for(unsigned int i = 0 ; i < Processor_List_big.size() ; ++i){
        wfile << "----------------------------------------------"  << endl;  
        wfile << "core " << i << endl;
        wfile << " Protected:       " << "\t" << Processor_List_big[i]->isProtect << endl;
        wfile << " operate time is: " << "\t" << Processor_List_big[i]->operate_time * NS << " ns" << endl;
        wfile << " age:             " << "\t" << Processor_List_big[i]->core_age * NS << " ns" << endl;
        //total_operate_time += Processor_List_big[i]->operate_time * NS;
        wfile << " aging time is:   " << "\t" << Processor_List_big[i]->aging_time << ", " << Processor_List_big[i]->vth << endl;
    }
    wfile << endl;
    wfile <<  "total operate time on big core: " << "\t" << total_operate_time_big << " ns"<< endl;
    wfile <<  "total energy on big core:       " << "\t" << total_energy_big << " n watts"<< endl;
    //w_policy_file << aging_time << ", " << total_operate_time_big * NS << ", "<< total_energy_big << endl;

    wfile << "============================ lit core ============================" << endl;
    wfile << "Simulator time: " << aging_time << ", " << operate_time * NS <<endl;
    for(unsigned int i = 0 ; i < Processor_List_lit.size() ; ++i){
        wfile << "----------------------------------------------"  << endl;  
        wfile << "core " << i << endl;
        wfile << " operate time is: " << "\t" << Processor_List_lit[i]->operate_time * NS << " ns" << endl;
        //total_operate_time += Processor_List_lit[i]->operate_time * NS;
        wfile << " aging time is: " << "\t" << Processor_List_lit[i]->aging_time << ", " << Processor_List_lit[i]->vth<<endl;
    }
    wfile << endl;
    wfile <<  "total operate time on little core: " << "\t" << total_operate_time_lit << " ns" << endl;
    wfile <<  "total energy on little core:       " << "\t" << total_energy_lit << " n watts" << endl;
    //w_policy_file << aging_time << ", " << total_operate_time_lit * NS << ", " << total_energy_lit << endl;


    wfile << "============================ total ============================" << endl;
    wfile <<  "total operate time is: " << "\t" << total_operate_time << " ns"<< endl;
    wfile <<  "total energy is:       " << "\t" << total_energy << " n watts"<< endl;
    wfile <<  "total executed tasks: "  << "\t" << round*20 << endl;
    wfile <<  "total migrated big tasks: "  << "\t" << mig_btol << endl;
    wfile <<  "total migrated little tasks: "  << "\t" << mig_ltob << endl;
    wfile << "******************************************************************" << endl;
    //w_policy_file << aging_time << ", total: " << total_operate_time * NS << ", " << total_energy << endl;
}

void Sim::reset() {
    isOpen = false;
    overlap_counter = 1;
    aging_time = ""; //reset simulator time (month, year) to ""
    //aging_time = "";
    readyQuere.clear(); //reset ready Queue
    simulation_time = 0.0; //reset simulator time (year)
    total_operate_time_big = 0.0;
    total_operate_time_lit = 0.0;
    total_operate_time = 0.0; //reset total core's operate time (s)
    total_energy_big = 0.0;
    total_energy_lit = 0.0;
    total_energy = 0.0; //reset simulator energy
    operate_time = 0.0; //reset simulator operate time
    period = 0.0;
    //reset each core state to initial
    for(unsigned int i = 0 ; i < Processor_List_big.size() ; ++i){
        Processor_List_big[i]->operate_time = 0.0;
        Processor_List_big[i]->core_age = 0.0;
        Processor_List_big[i]->ori_vth = 0.45;
        Processor_List_big[i]->vth = 0.45;
        Processor_List_big[i]->delta_vth = 0.0;
        Processor_List_big[i]->aging_time = "0m";
        Processor_List_big[i]->available_time = 0.0;
        Processor_List_big[i]->idle_time = 0.0;
        Processor_List_big[i]->total_power = 0.0;
        Processor_List_big[i]->isProtect = false;
        Processor_List_big[i]->isDead = false;
        if(Processor_List_big.size() > 4 && i == 0){
            Processor_List_big[i]->isProtect = true;
        }
        Processor_List_big[i]->index = i;

    }
    for(unsigned int i = 0 ; i < Processor_List_lit.size() ; ++i){
        Processor_List_lit[i]->operate_time = 0.0;
        Processor_List_lit[i]->ori_vth = 0.45;
        Processor_List_lit[i]->vth = 0.45;
        Processor_List_lit[i]->delta_vth = 0.0;
        Processor_List_lit[i]->aging_time = "0m";
        Processor_List_lit[i]->available_time = 0.0;
        Processor_List_lit[i]->idle_time = 0.0;
        Processor_List_lit[i]->total_power = 0.0;
        Processor_List_lit[i]->isProtect = false;
        Processor_List_lit[i]->isDead = false;
        if(Processor_List_lit.size() > 4 && i == 0){
            Processor_List_lit[i]->isProtect = true;
        }
        Processor_List_lit[i]->index = i;
    }

    for(unsigned int i = 0 ; i < Processor_List_big.size() ; ++i){
        //update(Processor_List_big[i]);
    }
    for(unsigned int i = 0 ; i < Processor_List_lit.size() ; ++i){
        //update(Processor_List_lit[i]);
    }
    //=======task graph initialize
    for(unsigned int k = 0 ; k < sorted_List.size() ; ++k){
        sorted_List[k]->deadline_time = 0.0;
        sorted_List[k]->isRelease = false;      
        sorted_List[k]->isCritical = false; 
        sorted_List[k]->isTight = false; 
        sorted_List[k]->ready_time = 0.0;
        
        sorted_List[k]->ready_time_big = 0.0;
        sorted_List[k]->ready_time_big_backup = 0.0;

        sorted_List[k]->ready_time_lit = 0.0;
        sorted_List[k]->ready_time_lit_backup = 0.0;
    }
    //for(unsigned int k = 0 ; k < sorted_List.size() ; ++k){
    //    cout << sorted_List[k]->id << ", "<< sorted_List[k]->deadline_time << endl;
    //}

    vth_counter = 0;  
}

void Sim::parse_vth(){
    string full = "vths.log";
    ifstream file(full.c_str(), ios::in);
    string line, time, value;
    while(getline(file, line, '\n')){
        time = Parseline(line); // time
        value = Parseline(line); // value
        //cout << "time " << time << ", value " << value << endl;
        vths.insert(pair<string, double>( time , atof( value.c_str() ) ));
    }
}

string Sim::Parseline(string &line){
  std::string token("");
  std::string::size_type  index = 0;
  while(line.size() > 0){
    if((line[index] >= '0'  && line[index] <= '9')  || 
       (line[index] >= 'A'  && line[index] <= 'Z')  || 
       (line[index] >= 'a'  && line[index] <= 'z')  ||
       (line[index] == '.') ){
      token += line[index];
      line.erase(line.begin());      
    }
    else if(line[index] == '\0' || token.size() > 0)
      return token;
    else
      line.erase(line.begin());
  }
  return token;    
}

Sim::Sim(vector<Task *> task_list, int num_processor_big, int num_processor_lit, map<string, map<string,double> >& idle_voltage_time_big, map<string, map<string,double> >& idle_voltage_time_lit, 
         vector<voltage_list *>& voltages_big, vector<voltage_list *>& voltages_lit, double critical_ratio, double nonCritical_ratio, vector<vector<unsigned int> > &critical_list) {
    wfile.setf(ios::fixed, ios::floatfield);
    wfile.precision(20);
    w_policy_file.setf(ios::fixed, ios::floatfield);
    w_policy_file.precision(20);
    DBG.setf(ios::fixed, ios::floatfield);
    DBG.precision(20);
    month_log.setf(ios::fixed, ios::floatfield);
    month_log.precision(20);
    vth_file.setf(ios::fixed, ios::floatfield);
    vth_file.precision(20);
    srand( (unsigned)time(NULL) );;// set random srand
    //set crtitcal ratio and non critical ratio
    this->critical_ratio = critical_ratio;
    this->nonCritical_ratio = nonCritical_ratio;
    this->critical_list = critical_list; //set critical tasks list
    //set task graph
    this->task_list = task_list;
    //set voltage and idle power map
    this->idle_voltage_time_big = idle_voltage_time_big;
    this->idle_voltage_time_lit = idle_voltage_time_lit;
    //set voltage list
    this->voltages_big = voltages_big;
    this->voltages_lit = voltages_lit;
    //set each core state

    //set month time
    //double month = 1.0/12.0;
    //for(unsigned int i = 0 ; i < 12 ; ++i){
    /*
    for(unsigned int i = 0 ; i < 11 ; ++i){
        months.push_back(month);
        //cout << month <<endl;
        month = month + (1.0/13.0);
    }
    */

    double month = 1.0/12.0;
    for(unsigned int i = 0 ; i <= 11 ; ++i){
        //switch (i) {
        //    case 0: case 2: case 4: case 6: case 7: case 9: case 11:
        //        months.push_back(month);
        //        month += 0.08493150684;
        //        break;
        //    case 1: case 3: case 5: case 8: case 10:
        //        months.push_back(month);
        //        month += 0.08219178082;
        //        break;
        //}
        months.push_back(month);
        month += 1.0/12.0;
    }


    //parse vth value file, which is in my_backup directory
    parse_vth(); 

    // big cores
    for(int i = 0 ; i < num_processor_big ; ++i){
        Processor *proc = new Processor();
        Processor_List_big.push_back(proc); 
    }
    // little cores
    for(int i = 0 ; i < num_processor_lit ; ++i){
        Processor *proc = new Processor();
        Processor_List_lit.push_back(proc); 
    }
    vth_counter = 0.0;
    isOpen = false;
    no_migration = false;
    reset();//reset some parameter
    mig_btol = 0;
    mig_ltob = 0;
}

void Sim::set_process_vth(Processor *proc, string time){
    map<string, double>::iterator it = vths.find(time);
    if(it == vths.end()){
        throw runtime_error("vth can't find");
    }
    proc->aging_time = time;
    //cout << "proc: " << proc->index << ", " << proc->aging_time << endl;
}

double Sim::get_Vth_max(string core_type){
    double Vth_max = 0.0;
    if (core_type == "big") {
        for(unsigned int i = 0 ; i < Processor_List_big.size() ; ++i){
            if(Vth_max < Processor_List_big[i]->vth){
                Vth_max = Processor_List_big[i]->vth;
            }
        }
    } else {
        for(unsigned int i = 0 ; i < Processor_List_lit.size() ; ++i){
            if(Vth_max < Processor_List_lit[i]->vth){
                Vth_max = Processor_List_lit[i]->vth;
            }
        }
    }
    return Vth_max;
}
double Sim::get_Vth_min(string core_type){
    double Vth_min = 1000;
    if (core_type == "big") {
        for(unsigned int i = 0 ; i < Processor_List_big.size() ; ++i){
            if(Vth_min > Processor_List_big[i]->vth){
                Vth_min = Processor_List_big[i]->vth;
            }
        }
    } else {
        for(unsigned int i = 0 ; i < Processor_List_lit.size() ; ++i){
            if(Vth_min > Processor_List_lit[i]->vth){
                Vth_min = Processor_List_lit[i]->vth;
            }
        }
    }
    return Vth_min;
}

void Sim::check_slack(vector<TaskInfo > &solutions, Task *task){
    bool isNextCritical = false;
    for(unsigned int i = 0 ; i < task->next.size() ; ++i){
        if(task->next[i]->isCritical){
          isNextCritical = true;
          break;
        }
    } 
    if(isNextCritical){
        if(solutions.size() > 1){
            sort(solutions.begin(), solutions.end(), slack_cmp);
            vector<TaskInfo >::iterator it = solutions.begin();
            while(it != solutions.end() ){
                if(solutions.size() == 1){
                    break;
                }
                else{    
                    double total_time = task->deadline_time - (*it).earliest_start_time;
                    //cout << ((*it).slack / total_time) << endl;
                    if( ( ((*it).slack / total_time) < 0.05 ) && ((*it).v.voltage < 1.2) ){
                        //if( ( ((*it).slack * NS) < 5.0) && ((*it).v.voltage < 1.2) ){
                        solutions.erase(it);
                        it = solutions.begin();
                    }
                    else{
                        it++;
                    }
                }
            }         
        }
    }  
}

void Sim::compute_delta_vth(Processor * proc, string voltage, double exec_time){
    double delta_vth = proc->delta_vth;
    double equal_time = 0.0, alpha = 0.0, beta = 0.1667;
    if(voltage == "08"){
      alpha = 0.0046;
    }else if(voltage == "09"){
      alpha = 0.0048;
    }else if(voltage == "10"){
      alpha = 0.0051;
    }else if(voltage == "11"){
      alpha = 0.0053;
    }else{//voltage = 1.2v
      alpha = 0.0056;
    }
    equal_time = pow(delta_vth/alpha, 1.0/beta);
    proc->delta_vth = alpha * pow( (equal_time + exec_time), beta);
    proc->vth = proc->ori_vth + proc->delta_vth;
}

double Sim::tmp_compute_delta_vth(Processor * proc, string voltage, double exec_time){
    double delta_vth = proc->delta_vth;
    double equal_time = 0.0, alpha = 0.0, beta = 0.1667;
    if(voltage == "08"){
      alpha = 0.0046;
    }else if(voltage == "09"){
      alpha = 0.0048;
    }else if(voltage == "10"){
      alpha = 0.0051;
    }else if(voltage == "11"){
      alpha = 0.0053;
    }else{//voltage = 1.2v
      alpha = 0.0056;
    }
    equal_time = pow(delta_vth/alpha, 1.0/beta);
    proc->delta_vth = alpha * pow( (equal_time + exec_time), beta);
    proc->vth = proc->ori_vth + proc->delta_vth;
    return proc->vth; 
}

bool Sim::ListAssignment(Task *task) {
	
	return 1;
}


bool Sim::SpareCoreAssignment(Task *task) {
    unsigned int i = 0;
    double finish_time;
	if (task->isBig) {
		sort(Processor_List_big.begin(), Processor_List_big.end(), operate_time_cmp);
    	sort(Processor_List_big.begin(), Processor_List_big.end(), spare_core_cmp);
    	vector<TaskInfo > solutions;

		if(task->isCritical){
    	    i = 0;
    	}
    	else{
    	    i = 1;
    	}
    	for(; i < Processor_List_big.size() ; ++i){
    	    for(unsigned int j = 0 ; j < voltages_big.size() ; ++j){
    	        map<string, map<string, Info*> >::iterator it = task->map_voltage_time_big.find(voltages_big[j]->voltage_str);
    	        if(it == task->map_voltage_time_big.end() ){
    	            throw runtime_error("can't find");
    	        }
    	        map<string, Info*>::iterator itt = it->second.find(Processor_List_big[i]->aging_time);
    	        if(itt == it->second.end() ){
    	            cout << "Processor "<< Processor_List_big[i]->index <<" is "<<Processor_List_big[i]->aging_time << endl;
    	            throw runtime_error("proc aging time can't find");
    	        }
    	        TaskInfo taskInfo;
    	        taskInfo.Energy_d = 0.0;
    	        taskInfo.Energy_i = 0.0;
    	        taskInfo.Energy_t = 0.0;
    	        taskInfo.dl_idle_energy = 0.0;
    	        taskInfo.earliest_start_time = max(task->ready_time, Processor_List_big[i]->available_time);
    	        taskInfo.ready_time = task->ready_time;
    	        taskInfo.v.voltage = voltages_big[j]->voltage;
    	        taskInfo.v.voltage_str = voltages_big[j]->voltage_str;
    	        taskInfo.proc_index = Processor_List_big[i]->index;
    	        taskInfo.proc = Processor_List_big[i];
    	        taskInfo.delay = itt->second->delay_big;
    	        taskInfo.dynamic_power = itt->second->avg_power_big;
    	        taskInfo.exec_time = ((double)task->cycle) * itt->second->delay_big;
    	        taskInfo.slack = task->deadline_time - taskInfo.earliest_start_time - taskInfo.exec_time;
    	        taskInfo.cost = 99999.9;
    	        if(taskInfo.slack >= 0.0){
    	            solutions.push_back(taskInfo); 
    	        }           
    	    } 
    	    if(solutions.size() > 0){
    	        break;
    	    }
    	}

        // handle migration
        if (!no_migration) {
            bool doMigrate = false;
            doMigrate = isMigrate(task);
            if (doMigrate) {
                mig_btol++;
                return 1;
            }
        }


    	if(solutions.size() > 0){
    	    sort(solutions.begin(), solutions.end(), slack_cmp);
    	} else {
    	    return 0;
    	}
    	solutions.front().Energy_d = solutions.front().dynamic_power * solutions.front().exec_time;
    	double idle_power = idle_voltage_time_big.find(voltages_big[0]->voltage_str)->second.find( (solutions.front().proc)->aging_time)->second;
    	solutions.front().dl_idle_energy = idle_power * solutions.front().slack;
    	solutions.front().Energy_i = solutions.front().dl_idle_energy;
    	if(task->ready_time > (solutions.front().proc)->available_time){
    	    double idle_time = (task->ready_time - (solutions.front().proc)->available_time);
    	    //(*p_it)->idle_time += idle_time;
    	    solutions.front().Energy_i += (idle_power * idle_time);
    	}
    	solutions.front().Energy_t = solutions.front().Energy_d + solutions.front().Energy_i;

    	finish_time = solutions.front().earliest_start_time + solutions.front().exec_time;
    	if(finish_time > task->deadline_time){
    	    throw runtime_error("impossible");
    	}
    	//update core's information, ex. available time, total power, operate time
    	(solutions.front().proc)->available_time = solutions.front().earliest_start_time + solutions.front().exec_time;
    	(solutions.front().proc)->total_power += (solutions.front().Energy_t - solutions.front().dl_idle_energy);
    	(solutions.front().proc)->operate_time += solutions.front().exec_time;
 
    	//update the NBTI of core
    	compute_delta_vth( solutions.front().proc, solutions.front().v.voltage_str, solutions.front().exec_time * NS);

	} else {
		sort(Processor_List_lit.begin(), Processor_List_lit.end(), operate_time_cmp);
    	sort(Processor_List_lit.begin(), Processor_List_lit.end(), spare_core_cmp);
    	vector<TaskInfo > solutions;
        bool turn_big = true;

		if(task->isCritical){
    	    i = 0;
    	}
    	else{
    	    i = 1;
    	}
    	for(; i < Processor_List_lit.size() ; ++i){
    	    for(unsigned int j = 0 ; j < voltages_lit.size() ; ++j){
    	        map<string, map<string, Info*> >::iterator it = task->map_voltage_time_lit.find(voltages_lit[j]->voltage_str);
    	        if(it == task->map_voltage_time_lit.end() ){
    	            throw runtime_error("can't find");
    	        }
    	        map<string, Info*>::iterator itt = it->second.find(Processor_List_lit[i]->aging_time);
    	        if(itt == it->second.end() ){
    	            cout << "Processor "<< Processor_List_lit[i]->index <<" is "<<Processor_List_lit[i]->aging_time << endl;
    	            throw runtime_error("proc aging time can't find");
    	        }
    	        TaskInfo taskInfo;
    	        taskInfo.Energy_d = 0.0;
    	        taskInfo.Energy_i = 0.0;
    	        taskInfo.Energy_t = 0.0;
    	        taskInfo.dl_idle_energy = 0.0;
    	        taskInfo.earliest_start_time = max(task->ready_time, Processor_List_lit[i]->available_time);
    	        taskInfo.ready_time = task->ready_time;
    	        taskInfo.v.voltage = voltages_lit[j]->voltage;
    	        taskInfo.v.voltage_str = voltages_lit[j]->voltage_str;
    	        taskInfo.proc_index = Processor_List_lit[i]->index;
    	        taskInfo.proc = Processor_List_lit[i];
    	        taskInfo.delay = itt->second->delay_lit;
    	        taskInfo.dynamic_power = itt->second->avg_power_lit;
    	        taskInfo.exec_time = ((double)task->cycle) * itt->second->delay_lit;
                if(taskInfo.ready_time + taskInfo.exec_time < task->deadline_time) {
                    turn_big = false;
                }
    	        taskInfo.slack = task->deadline_time - taskInfo.earliest_start_time - taskInfo.exec_time;
    	        taskInfo.cost = 99999.9;
    	        if(taskInfo.slack >= 0.0){
    	            solutions.push_back(taskInfo); 
    	        }           
                task->exec_time = taskInfo.exec_time;

                //map<string, map<string, Info*> >::iterator it = task->map_voltage_time_lit.find(voltages_lit[j]->voltage_str);
                //if(it == task->map_voltage_time_lit.end() ){
                //    throw runtime_error("can't find");
                //}
                //map<string, Info*>::iterator itt = it->second.find(Processor_List_lit[i]->aging_time);
                //if(itt == it->second.end() ){
                //    cout << "Processor "<< Processor_List_lit[i]->index <<" is "<<Processor_List_lit[i]->aging_time << endl;
                //    throw runtime_error("proc aging time can't find");
                //}
                //TaskInfo taskInfo;
                //taskInfo.Energy_d = 0.0;
                //taskInfo.Energy_i = 0.0;
                //taskInfo.Energy_t = 0.0;
                //taskInfo.dl_idle_energy = 0.0;
                //taskInfo.earliest_start_time = max(task->ready_time_lit, Processor_List_lit[i]->available_time);
                //taskInfo.ready_time = task->ready_time_lit;
                //taskInfo.v.voltage = voltages_lit[j]->voltage;
                //taskInfo.v.voltage_str = voltages_lit[j]->voltage_str;
                //taskInfo.proc_index = Processor_List_lit[i]->index;
                //taskInfo.proc = Processor_List_lit[i];
                //taskInfo.delay = itt->second->delay_lit;
                //taskInfo.dynamic_power = itt->second->avg_power_lit;
                //taskInfo.exec_time = ((double)task->cycle) * itt->second->delay_lit;
                //if(taskInfo.ready_time + taskInfo.exec_time < task->deadline_time) {
                //    turn_big = false;
                //}
                //taskInfo.slack = task->deadline_time - taskInfo.earliest_start_time - taskInfo.exec_time;
                //taskInfo.isAgingSlack = task->deadline_time - task->ready_time_lit - taskInfo.exec_time;
                //taskInfo.cost = 99999.9;
                //// little core symmetric
                //if(taskInfo.slack >= 0.0){
                //    solutions.push_back(taskInfo); 
                //}
                //task->exec_time = taskInfo.exec_time;
    	    } 
    	    if (solutions.size() > 0) {
    	        break;
    	    }
    	}

        if (turn_big) {
            task->isBig = true;
        }

    	if(solutions.size() > 0){
    	    sort(solutions.begin(), solutions.end(), slack_cmp);
    	}
    	else {
            if (task->isBig) {
                bool success = SpareCoreAssignment(task);
                if (success) {
                    return 1;
                } else {
                    return 0;
                }
            } else {
                // handle migration from little to big
                //if (!no_migration) {
                //    bool doMigrate = false;
                //    doMigrate = isMigrate(task);
                //    if (doMigrate) {
                //        mig_ltob++;
                //        return 1;
                //    }
                //} else {
    	        //    return 0;
                //}
    	        return 0;
            }
    	}
    	solutions.front().Energy_d = solutions.front().dynamic_power * solutions.front().exec_time;
    	double idle_power = idle_voltage_time_lit.find(voltages_lit[0]->voltage_str)->second.find( (solutions.front().proc)->aging_time)->second;
    	solutions.front().dl_idle_energy = idle_power * solutions.front().slack;
    	solutions.front().Energy_i = solutions.front().dl_idle_energy;
    	if(task->ready_time > (solutions.front().proc)->available_time){
    	    double idle_time = (task->ready_time - (solutions.front().proc)->available_time);
    	    //(*p_it)->idle_time += idle_time;
    	    solutions.front().Energy_i += (idle_power * idle_time);
    	}
    	solutions.front().Energy_t = solutions.front().Energy_d + solutions.front().Energy_i;

    	//finish_time = solutions.front().earliest_start_time + solutions.front().exec_time;
    	//if(finish_time > task->deadline_time){
    	//    throw runtime_error("impossible");
    	//}
    	////update core's information, ex. available time, total power, operate time
    	//(solutions.front().proc)->available_time = solutions.front().earliest_start_time + solutions.front().exec_time;
    	//(solutions.front().proc)->total_power += (solutions.front().Energy_t - solutions.front().dl_idle_energy);
    	//(solutions.front().proc)->operate_time += solutions.front().exec_time;
 
        //task->exec_time =  solutions[index].exec_time;
        //
    	////update the NBTI of core
    	//compute_delta_vth( solutions.front().proc, solutions.front().v.voltage_str, solutions.front().exec_time * NS);

        unsigned int index = 0;

        finish_time = solutions[index].earliest_start_time + solutions[index].exec_time;
        if(finish_time > task->deadline_time){
            throw runtime_error("impossible");
        }

        (solutions[index].proc)->available_time = solutions[index].earliest_start_time + solutions[index].exec_time;
        (solutions[index].proc)->total_power += (solutions[index].Energy_t - solutions[index].dl_idle_energy);
        (solutions[index].proc)->operate_time += solutions[index].exec_time;

        task->exec_time =  solutions[index].exec_time;
 
        //update the NBTI of core
        compute_delta_vth( solutions[index].proc, solutions[index].v.voltage_str, solutions[index].exec_time * NS);
	
	}


    //check whether the next task is ready or not
    //for(unsigned int i = 0 ; i < task->next.size() ; ++i){
    //    Task *next = task->next[i];
    //    next->num_pre--;
    //    if(finish_time > next->ready_time){
    //        next->ready_time = finish_time;
    //    }
    //    if(next->num_pre == 0 && next->id != END_TASK){
    //        readyQuere.push_back(next);
    //    }
    //}
    //check whether the next task is ready or not
    for(unsigned int i = 0 ; i < task->next.size() ; ++i){
        Task *next = task->next[i];
        next->num_pre--;
        // current task is little and next task is big task
        if (task->isBig != next->isBig) {
            if(finish_time > next->ready_time_big) {
                next->ready_time_big = finish_time;
            }
            next->ready_time = finish_time;
        } else {
            if(finish_time > next->ready_time_lit){
                next->ready_time_lit = finish_time;
            }
            next->ready_time = finish_time;
        }
        // push next tasks into ready queue
        if(next->num_pre == 0 && next->id != END_TASK){
            //cout << next->id << endl;
            readyQuere.push_back(next);
        }
    }
    return 1;  
}



bool Sim::isMigrate(Task *task) {
    bool doMigrate = false;
    bool isFull_big = true;
    bool isFull_lit = true;
    double min_waittime = 0.0;
    double waittime = 0.0;
    double exec_time_lit = 0.0;
    double exec_time_big = 0.0;
    double rem_big = 0.0;
    double delay_big = 0.0;
    double delay_lit = 0.0;
    double min_delay_big = 0.0;
    double min_delay_lit = 0.0;
    double bl_ratio = 0.0;
    int cand_edp_big_idx = 0;
    int cand_edp_lit_idx = 0;
    int cand_big_core_idx = 0;
    int cand_lit_core_idx = 0;

    double power_big = 0.0;
    double power_lit = 0.0;
    double EDP_big = 0.0;
    double EDP_lit = 0.0;
    
    double idle_power = 0.0;
    double energy_d_big = 0.0;
    double energy_d_lit = 0.0;

    double slack = 0.0;
    double min_slack = 0.0;
    bool migtobig = false;

    // step1: check big/lit cluster is full or not
    map<string, map<string, Info*> >::iterator it;
    map<string, Info*>::iterator itt;
    if (task->isBig) {
        for(unsigned int i = 0 ; i < Processor_List_big.size() ; ++i) {
            for(unsigned int j = 0 ; j < voltages_big.size() ; ++j) {
                if (!Processor_List_big[i]->isDead) {
                    min_waittime = Processor_List_big[i]->available_time - task->ready_time;
                    it = task->map_voltage_time_big.find(voltages_big[j]->voltage_str);
                    itt = it->second.find(Processor_List_big[i]->aging_time);
                    min_delay_big = itt->second->delay_big;
                    power_big = itt->second->avg_power_big;
                }
            }
        }

        for(unsigned int i = 0 ; i < Processor_List_big.size() ; ++i) {
            for(unsigned int j = 0 ; j < voltages_big.size() ; ++j) {
                //if (!Processor_List_big[i]->isProtect) {
                //if (Processor_List_big[i]->isProtect) {
                    if (!Processor_List_big[i]->isDead) {
                        if (Processor_List_big[i]->available_time <= task->ready_time) {
                            isFull_big = false;
                        } else {
                            waittime = Processor_List_big[i]->available_time - task->ready_time;
                        }
                        if (waittime < min_waittime) {
                            min_waittime = waittime;
                            cand_big_core_idx = i;
                            it = task->map_voltage_time_big.find(voltages_big[j]->voltage_str);
                            itt = it->second.find(Processor_List_big[i]->aging_time);
                            //exec_time_big = ((double)task->cycle) * itt->second->delay_big;
                            min_delay_big = itt->second->delay_big;
                            power_big = itt->second->avg_power_big;
                        }
                    } 
                //}
            }
        }

        it = task->map_voltage_time_lit.find(voltages_lit[0]->voltage_str);
        itt = it->second.find(Processor_List_lit[0]->aging_time);
        min_delay_lit = itt->second->delay_lit;
        power_lit = itt->second->avg_power_lit;
        for(unsigned int i = 0 ; i < Processor_List_lit.size() ; ++i) {
            for(unsigned int j = 0 ; j < voltages_lit.size() ; ++j) {
                //if (!Processor_List_lit[i]->isDead) {
                    it = task->map_voltage_time_lit.find(voltages_lit[j]->voltage_str);
                    itt = it->second.find(Processor_List_lit[i]->aging_time);
                    delay_lit = itt->second->delay_lit;
                    if (delay_lit < min_delay_lit) {
                        cand_lit_core_idx = i;
                        min_delay_lit = delay_lit;

                    }

                    power_lit = itt->second->avg_power_lit;

                    if (Processor_List_lit[i]->available_time < task->ready_time) {
                        isFull_lit = false;
                    }
                //}
            }
        }


        bl_ratio = min_delay_lit / min_delay_big;
        exec_time_big = ((double)task->cycle) * min_delay_big;
        rem_big = exec_time_big - min_waittime/bl_ratio;
        exec_time_lit = min_waittime;

        EDP_big = min_delay_big * min_delay_big * power_big;
        EDP_lit = min_delay_lit * min_delay_lit * power_lit;

        double big_part = 0.0;
        double lit_part = 0.0;
        if (rem_big < exec_time_lit) {
            big_part = rem_big / exec_time_lit;
            lit_part = 1 - big_part;
        
        } else {
            big_part = exec_time_lit / rem_big;
            lit_part = 1 - big_part;
        }

        // big cluster is full and lit cluster is available
        // big => little when big full
        double mg_cost = (double)task->cycle * task->delay_lit * 0.02;
        if (isFull_big && !isFull_lit) { // congestion migration
            if (exec_time_big > mg_cost + rem_big) {
                doMigrate = true;

                // update status for big core
                compute_delta_vth(Processor_List_big[cand_big_core_idx], "10", rem_big * NS);
                Processor_List_big[cand_big_core_idx]->available_time += rem_big;
                
                energy_d_big = power_big * rem_big;
                //idle_power = idle_voltage_time_big.find(voltages_big[0]->voltage_str)->second.find( (Processor_List_big[cand_big_core_idx])->aging_time)->second;
                Processor_List_big[cand_big_core_idx]->total_power += energy_d_big;
                Processor_List_big[cand_big_core_idx]->operate_time += rem_big;
                

                // update status for little core
                compute_delta_vth(Processor_List_lit[cand_lit_core_idx], "08", exec_time_lit * NS);
                Processor_List_lit[cand_lit_core_idx]->available_time += exec_time_lit;
                
                energy_d_lit = power_lit * exec_time_lit;
                Processor_List_lit[cand_lit_core_idx]->total_power += energy_d_lit;
                Processor_List_lit[cand_lit_core_idx]->operate_time += exec_time_lit;

                //update(Processor_List_big[cand_big_core_idx]);
                //update(Processor_List_lit[cand_lit_core_idx]);

                double finish_time_big = Processor_List_big[cand_big_core_idx]->available_time;
                double finish_time_lit = Processor_List_lit[cand_lit_core_idx]->available_time;
                double finish_time = max(finish_time_big, finish_time_lit);

                //check whether the next task is ready or not
                for(unsigned int i = 0 ; i < task->next.size() ; ++i) {
                    Task *next = task->next[i];
                    next->num_pre--;
                    if (task->isBig != next->isBig) {
                        next->ready_time_lit = finish_time;
                    } else {
                        if(finish_time > next->ready_time_big){
                            next->ready_time_big = finish_time;
                        }
                    }
                    next->ready_time = finish_time;

                    if(next->num_pre == 0 && next->id != END_TASK){
                        readyQuere.push_back(next);
                    }
                }
            }
        } 
        //else if (!isFull_big && !isFull_lit) { // EDP migration
        // //else if (!isFull_lit) { // EDP migration
        //     if ( (EDP_big * big_part + EDP_lit * lit_part) < EDP_big) { 
        //         doMigrate = true;
        //         delay_big = 1.0;
        //         delay_lit = 1.0;
        //         double d_b = 0.0;
        //         double d_l = 0.0;
        //         double p_b = 0.0;
        //         double p_l = 0.0;
        //         double exec_big = 0.0;
        //         double exec_lit = 0.0;
        //         int cycle = task->cycle;

        //         int c; // cycle exec on big

        //         for(unsigned int i = 0 ; i < Processor_List_big.size() ; ++i) {
        //             for(unsigned int j = 0 ; j < voltages_big.size() ; ++j) {
        //                 if (!Processor_List_big[i]->isDead) {
        //                     if (Processor_List_big[i]->available_time <= task->ready_time) {
        //                         it = task->map_voltage_time_big.find(voltages_big[j]->voltage_str);
        //                         itt = it->second.find(Processor_List_big[i]->aging_time);
        //                         p_b = itt->second->avg_power_big;
        //                         d_b= itt->second->delay_big;
        //                         if (d_b < delay_big) {
        //                             delay_big = d_b;
        //                             power_big = p_b;
        //                             cand_edp_big_idx = i;
        //                         }
        //                     }
        //                 }
        //             }
        //         }
        //         for(unsigned int i = 0 ; i < Processor_List_lit.size() ; ++i) {
        //             for(unsigned int j = 0 ; j < voltages_lit.size() ; ++j) {
        //                 if (Processor_List_lit[i]->available_time <= task->ready_time) {
        //                     it = task->map_voltage_time_lit.find(voltages_lit[j]->voltage_str);
        //                     itt = it->second.find(Processor_List_lit[i]->aging_time);
        //                     p_l = itt->second->avg_power_lit;
        //                     d_l = itt->second->delay_lit;
        //                     if (d_l < delay_lit) {
        //                         delay_lit = d_l;
        //                         power_lit = p_l;
        //                         cand_edp_lit_idx = i;
        //                     }
        //                 }
        //             }
        //         }

        //         
        //         for (c=0; c<cycle; c++) {
		//			 // the most cycles on little core that can meet deadline
        //             if (c*delay_big + (cycle-c)*delay_lit < task->deadline_time) {
        //                 exec_big = c * delay_big;
        //                 exec_lit = (cycle-c) * delay_lit;
        //                 break;
        //             }
        //         }

        //         // update status for big core
        //         compute_delta_vth(Processor_List_big[cand_edp_big_idx], "10", exec_big * NS);
        //         Processor_List_big[cand_big_core_idx]->available_time += exec_big;
        //         
        //         energy_d_big = power_big * exec_big;
        //         //idle_power = idle_voltage_time_big.find(voltages_big[0]->voltage_str)->second.find( (Processor_List_big[cand_big_core_idx])->aging_time)->second;
        //         Processor_List_big[cand_edp_big_idx]->total_power += energy_d_big;
        //         Processor_List_big[cand_edp_big_idx]->operate_time += exec_big;

        //         // update status for little core
        //         compute_delta_vth(Processor_List_lit[cand_edp_lit_idx], "08", exec_lit * NS);
        //         Processor_List_lit[cand_edp_lit_idx]->available_time += exec_lit;
        //         
        //         energy_d_lit = power_lit * exec_lit;
        //         Processor_List_lit[cand_edp_lit_idx]->total_power += energy_d_lit;
        //         Processor_List_lit[cand_edp_lit_idx]->operate_time += exec_lit;

        //         double finish_time_big = Processor_List_big[cand_edp_big_idx]->available_time;
        //         double finish_time_lit = Processor_List_lit[cand_edp_lit_idx]->available_time;
        //         double finish_time = max(finish_time_big, finish_time_lit);

        //         //check whether the next task is ready or not
        //         for(unsigned int i = 0 ; i < task->next.size() ; ++i) {
        //             Task *next = task->next[i];
        //             next->num_pre--;
        //             if (task->isBig != next->isBig) {
        //                 next->ready_time_lit = finish_time;
        //             } else {
        //                 if(finish_time > next->ready_time_big){
        //                     next->ready_time_big = finish_time;
        //                 }
        //             }
        //             next->ready_time = finish_time;

        //             if(next->num_pre == 0 && next->id != END_TASK){
        //                 readyQuere.push_back(next);
        //             }
        //         }
        //     
        //     }
        //     
        // } 
    } else { // handle little to big migration
        for(unsigned int i = 0 ; i < Processor_List_big.size() ; ++i) {
            for(unsigned int j = 0 ; j < voltages_big.size() ; ++j) {
                //if (!Processor_List_big[i]->isDead) {
                    it = task->map_voltage_time_big.find(voltages_big[j]->voltage_str);
                    itt = it->second.find(Processor_List_big[i]->aging_time);
                    exec_time_big = itt->second->delay_big * (double)task->cycle;
                    slack = task->deadline_time - (Processor_List_big[i]->available_time + exec_time_big);
                    // assign on this core
                    if (slack >= 0) {
                        migtobig = true;
                        cand_big_core_idx = i;
                        exec_time_big = itt->second->delay_big * (double)task->cycle;
                        power_big = itt->second->avg_power_big;
                    }
                //}
            }
        }
        if (migtobig) {
            doMigrate = true;
            compute_delta_vth(Processor_List_big[cand_big_core_idx], "10", exec_time_big * NS);
            Processor_List_big[cand_big_core_idx]->available_time += exec_time_big;
            
            energy_d_big = power_big * exec_time_big;
            //idle_power = idle_voltage_time_big.find(voltages_big[0]->voltage_str)->second.find( (Processor_List_big[cand_big_core_idx])->aging_time)->second;
            Processor_List_big[cand_big_core_idx]->total_power += energy_d_big;
            Processor_List_big[cand_big_core_idx]->operate_time += exec_time_big;

            //update(Processor_List_big[cand_big_core_idx]);
            //update(Processor_List_lit[cand_lit_core_idx]);

            double finish_time = Processor_List_big[cand_big_core_idx]->available_time;

            //check whether the next task is ready or not
            for(unsigned int i = 0 ; i < task->next.size() ; ++i) {
                Task *next = task->next[i];
                next->num_pre--;
                if (task->isBig != next->isBig) {
                    next->ready_time_lit = finish_time;
                } else {
                    if(finish_time > next->ready_time_big){
                        next->ready_time_big = finish_time;
                    }
                }
                next->ready_time = finish_time;

                if(next->num_pre == 0 && next->id != END_TASK){
                    readyQuere.push_back(next);
                }
            }
        }
    }
    return doMigrate; 
}


bool Sim::Task2Cluster(Task *task, int policy) {
    bool success = false;
    bool suc_mig = false;
    bool doMigrate = false;
    if (task->isBig) {
        //DBG << "  *ready time:   \t" << task->ready_time *NS << endl;
        //DBG << "  ready time:    \t" << task->ready_time_big *NS << endl;
        //DBG << "  deadline time: \t" << task->deadline_time *NS << endl;
        if (policy == 1 || policy == 3) { // asymmetric
            success = Task2BigCore(task);
        } else if (policy == 0 || policy == 2) { // symmetric
            success = Sym_Task2BigCore(task);
        }
        //success = Task2BigCore(task);
        if (!success) {
            //doMigrate = isMigrate(task);
            //if (doMigrate) {
            //    mig_btol++;
            //    success = true;
            //} else {
            //    cout << "Fail in big cluster\n";
            //}
            //cout << "Fail in big cluster\n";
        }
    } else {
        //DBG << "  *ready time:   \t" << task->ready_time *NS << endl;
        //DBG << "  ready time:    \t" << task->ready_time_lit *NS << endl;
        //DBG << "  deadline time: \t" << task->deadline_time *NS << endl;
        success = Task2LitCore(task);
        if (!success) {
            if (policy == 2 || policy == 3) { // with migration
            //if (policy == 2 || policy == 3 || policy == 1 || policy == 0) { // with migration
                if (task->isBig) {
                    //cout << "Task " << task->id << " become big task" << endl;
                    success = Task2Cluster(task, policy);
                } else {
                    suc_mig = isMigrate(task);
                    if (suc_mig) {
                        success = true;
                        mig_ltob++;
                    } else {
                        //cout << "Fail in little cluster\n";
                    }
                }
            } else { // no migration
                if (task->isBig) {
                    success = Task2Cluster(task, policy);
                    //cout << "Task " << task->id << " become big task" << endl;
                } else {
                    //cout << "Fail in little cluster\n";
                }
            }
        }
    }
    return success;
}

bool Sim::Task2LitCore(Task *task) {
    sort(Processor_List_lit.begin(), Processor_List_lit.end(), operate_time_cmp);

    vector<vector<TaskInfo> > scheduler;
    vector<TaskInfo > solutions;
    vector<unsigned int> free_core;

    Vth_max_lit = get_Vth_max("lit");
    Vth_min_lit = get_Vth_min("lit");
    
    bool turn_big = true;

    for(unsigned int i = 0 ; i < Processor_List_lit.size() ; ++i) {
        scheduler.push_back(vector<TaskInfo>() );
        for(unsigned int j = 0 ; j < voltages_lit.size() ; ++j){
            //if (!Processor_List_big[i]->isDead) {
                map<string, map<string, Info*> >::iterator it = task->map_voltage_time_lit.find(voltages_lit[j]->voltage_str);
                if(it == task->map_voltage_time_lit.end() ){
                    throw runtime_error("can't find");
                }
                map<string, Info*>::iterator itt = it->second.find(Processor_List_lit[i]->aging_time);
                if(itt == it->second.end() ){
                    cout << "Processor "<< Processor_List_lit[i]->index <<" is "<<Processor_List_lit[i]->aging_time << endl;
                    throw runtime_error("proc aging time can't find");
                }
                TaskInfo taskInfo;
                taskInfo.Energy_d = 0.0;
                taskInfo.Energy_i = 0.0;
                taskInfo.Energy_t = 0.0;
                taskInfo.dl_idle_energy = 0.0;
                taskInfo.earliest_start_time = max(task->ready_time_lit, Processor_List_lit[i]->available_time);
                taskInfo.ready_time = task->ready_time_lit;
                taskInfo.v.voltage = voltages_lit[j]->voltage;
                taskInfo.v.voltage_str = voltages_lit[j]->voltage_str;
                taskInfo.proc_index = Processor_List_lit[i]->index;
                taskInfo.proc = Processor_List_lit[i];
                taskInfo.delay = itt->second->delay_lit;
                taskInfo.dynamic_power = itt->second->avg_power_lit;
                taskInfo.exec_time = ((double)task->cycle) * itt->second->delay_lit;
                if(taskInfo.ready_time + taskInfo.exec_time < task->deadline_time) {
                    turn_big = false;
                }
                taskInfo.slack = task->deadline_time - taskInfo.earliest_start_time - taskInfo.exec_time;
                taskInfo.isAgingSlack = task->deadline_time - task->ready_time_lit - taskInfo.exec_time;
                taskInfo.cost = 99999.9;
                // little core symmetric
                if (task->ready_time_lit >= Processor_List_lit[i]->available_time) {
                    free_core.push_back(Processor_List_lit[i]->index);
                }
                if(taskInfo.slack >= 0.0){
                    solutions.push_back(taskInfo); 
                }
                task->exec_time = taskInfo.exec_time;
            //}
        }
    }

    if (turn_big) {
        task->isBig = true;
    }
    //cout << endl;
    if(solutions.size() > 0){
        sort(solutions.begin(), solutions.end(), slack_cmp);
        task->exec_time = solutions[0].exec_time;
    } else {
        //cout << "\nno solution in little cluster" << endl;
        return 0;
    }

    solutions.front().Energy_d = solutions.front().dynamic_power * solutions.front().exec_time;
    double idle_power = idle_voltage_time_lit.find(voltages_lit[0]->voltage_str)->second.find( (solutions.front().proc)->aging_time)->second;
    solutions.front().dl_idle_energy = idle_power * solutions.front().slack;
    solutions.front().Energy_i = solutions.front().dl_idle_energy;
    if(task->ready_time_lit > (solutions.front().proc)->available_time){
        double idle_time = (task->ready_time_lit - (solutions.front().proc)->available_time);
        //(*p_it)->idle_time += idle_time;
        solutions.front().Energy_i += (idle_power * idle_time);
    }
    solutions.front().Energy_t = solutions.front().Energy_d + solutions.front().Energy_i; 
    
    unsigned int index = 0;

    double finish_time = solutions[index].earliest_start_time + solutions[index].exec_time;
    if(finish_time > task->deadline_time){
        throw runtime_error("impossible");
    }

    (solutions[index].proc)->available_time = solutions[index].earliest_start_time + solutions[index].exec_time;
    (solutions[index].proc)->total_power += (solutions[index].Energy_t - solutions[index].dl_idle_energy);
    (solutions[index].proc)->operate_time += solutions[index].exec_time;

    task->exec_time =  solutions[index].exec_time;
 
    //update the NBTI of core
    compute_delta_vth( solutions[index].proc, solutions[index].v.voltage_str, solutions[index].exec_time * NS);

    //DBG << "  exec time:     \t" << solutions[index].exec_time *NS << endl;
    //DBG << "   free: ";
    //for (unsigned int i=0; i<free_core.size(); ++i) {
    //    DBG << free_core[i] << " ";
    //}
    //DBG << endl;
    //DBG << "  ----- In Lit core " << "(" << solutions[index].proc_index << ")" << " -----------------------" << endl;
    //DBG << "  early st time: \t" << solutions[index].earliest_start_time *NS << endl;
    //DBG << "  finish time:   \t" << finish_time *NS << endl; 
    //DBG << "  -------------------------------------------" << endl;

    //check whether the next task is ready or not
    for(unsigned int i = 0 ; i < task->next.size() ; ++i){
        Task *next = task->next[i];
        next->num_pre--;
        // current task is little and next task is big task
        if (task->isBig != next->isBig) {
            if(finish_time > next->ready_time_big) {
                next->ready_time_big = finish_time;
            }
            next->ready_time = finish_time;
        } else {
            if(finish_time > next->ready_time_lit){
                next->ready_time_lit = finish_time;
            }
            next->ready_time = finish_time;
        }
        // push next tasks into ready queue
        if(next->num_pre == 0 && next->id != END_TASK){
            //cout << next->id << endl;
            readyQuere.push_back(next);
        }
    }
    //cout << "  ready time:  " << task->ready_time_lit*NS << endl;
    //cout << "  finish time: " << finish_time*NS << endl;


    return 1;
}

bool Sim::Sym_Task2BigCore(Task *task) {
    sort(Processor_List_big.begin(), Processor_List_big.end(), operate_time_cmp);

    vector<vector<TaskInfo> > scheduler;
    vector<TaskInfo > solutions;
    vector<unsigned int> free_core;

    Vth_max_big = get_Vth_max("big");
    Vth_min_big = get_Vth_min("big");

    for(unsigned int i = 0 ; i < Processor_List_big.size() ; ++i) {
        scheduler.push_back(vector<TaskInfo>() );
        for(unsigned int j = 0 ; j < voltages_big.size() ; ++j){
            //if (!Processor_List_big[i]->isDead) {
                map<string, map<string, Info*> >::iterator it = task->map_voltage_time_big.find(voltages_big[j]->voltage_str);
                if(it == task->map_voltage_time_big.end() ){
                    throw runtime_error("can't find");
                }
                map<string, Info*>::iterator itt = it->second.find(Processor_List_big[i]->aging_time);
                if(itt == it->second.end() ){
                    cout << "Processor "<< Processor_List_big[i]->index <<" is "<<Processor_List_big[i]->aging_time << endl;
                    throw runtime_error("proc aging time can't find");
                }
                TaskInfo taskInfo;
                taskInfo.Energy_d = 0.0;
                taskInfo.Energy_i = 0.0;
                taskInfo.Energy_t = 0.0;
                taskInfo.dl_idle_energy = 0.0;
                taskInfo.earliest_start_time = max(task->ready_time_big, Processor_List_big[i]->available_time);
                taskInfo.ready_time = task->ready_time_big;
                taskInfo.v.voltage = voltages_big[j]->voltage;
                taskInfo.v.voltage_str = voltages_big[j]->voltage_str;
                taskInfo.proc_index = Processor_List_big[i]->index;
                taskInfo.proc = Processor_List_big[i];
                taskInfo.delay = itt->second->delay_big;
                taskInfo.dynamic_power = itt->second->avg_power_big;
                taskInfo.exec_time = ((double)task->cycle) * itt->second->delay_big;
                taskInfo.slack = task->deadline_time - taskInfo.earliest_start_time - taskInfo.exec_time;
                taskInfo.isAgingSlack = task->deadline_time - task->ready_time_big - taskInfo.exec_time;
                taskInfo.cost = 99999.9;
                // little core symmetric
                if (task->ready_time_big >= Processor_List_big[i]->available_time) {
                    free_core.push_back(Processor_List_big[i]->index);
                }
                if(taskInfo.slack >= 0.0){
                    solutions.push_back(taskInfo); 
                }
                task->exec_time = taskInfo.exec_time;
            //}
        }
    }

    // handle migration
    if (!no_migration) {
        bool doMigrate = false;
        doMigrate = isMigrate(task);
        if (doMigrate) {
            mig_btol++;
            return 1;
        }
    }

    if(solutions.size() > 0){
        sort(solutions.begin(), solutions.end(), slack_cmp);
        task->exec_time = solutions[0].exec_time;
    } else {
        //cout << "\nno solution in big cluster" << endl;
        return 0;
    }

    solutions.front().Energy_d = solutions.front().dynamic_power * solutions.front().exec_time;
    double idle_power = idle_voltage_time_big.find(voltages_big[0]->voltage_str)->second.find( (solutions.front().proc)->aging_time)->second;
    solutions.front().dl_idle_energy = idle_power * solutions.front().slack;
    solutions.front().Energy_i = solutions.front().dl_idle_energy;
    if(task->ready_time > (solutions.front().proc)->available_time){
        double idle_time = (task->ready_time - (solutions.front().proc)->available_time);
        //(*p_it)->idle_time += idle_time;
        solutions.front().Energy_i += (idle_power * idle_time);
    }
    solutions.front().Energy_t = solutions.front().Energy_d + solutions.front().Energy_i; 
    
    unsigned int index = 0;

    double finish_time = solutions[index].earliest_start_time + solutions[index].exec_time;
    if(finish_time > task->deadline_time){
        throw runtime_error("impossible");
    }

    (solutions[index].proc)->available_time = solutions[index].earliest_start_time + solutions[index].exec_time;
    (solutions[index].proc)->total_power += (solutions[index].Energy_t - solutions[index].dl_idle_energy);
    (solutions[index].proc)->operate_time += solutions[index].exec_time;
 
    task->exec_time = solutions[index].exec_time;

    //update the NBTI of core
    compute_delta_vth( solutions[index].proc, solutions[index].v.voltage_str, solutions[index].exec_time * NS);

    //DBG << "  exec time:     \t" << solutions[index].exec_time *NS << endl;
    //DBG << "   free: ";
    //for (unsigned int i=0; i<free_core.size(); ++i) {
    //    DBG << free_core[i] << " ";
    //}
    //DBG << endl;
    //DBG << "  ----- In Big core " << "(" << solutions[index].proc_index << ")" << " -----------------------" << endl;
    //DBG << "  early st time: \t" << solutions[index].earliest_start_time *NS << endl;
    //DBG << "  finish time:   \t" << finish_time *NS << endl; 
    //DBG << "  -------------------------------------------" << endl;

    //check whether the next task is ready or not
    for(unsigned int i = 0 ; i < task->next.size() ; ++i){
        Task *next = task->next[i];
        next->num_pre--;
        // current task is little and next task is big task
        if (task->isBig != next->isBig) {
            if(finish_time > next->ready_time_big) {
                next->ready_time_big = finish_time;
            }
            next->ready_time = finish_time;
        } else {
            if(finish_time > next->ready_time_big){
                next->ready_time_big = finish_time;
            }
            next->ready_time = finish_time;
        }
        // push next tasks into ready queue
        if(next->num_pre == 0 && next->id != END_TASK){
            //cout << next->id << endl;
            readyQuere.push_back(next);
        }
    }
    return 1;

}

bool Sim::Task2BigCore(Task *task) {
    sort(Processor_List_big.begin(), Processor_List_big.end(), operate_time_cmp);
    //decide the protected cores
    // big cluster asymmetric
    //unsigned int tmp_overlap_counter = overlap_counter;
    unsigned int tmp_overlap_counter = 1;
    for(unsigned int i = 0 ; i < Processor_List_big.size() ; ++i) {
        if (tmp_overlap_counter > 0) {
            Processor_List_big[i]->isProtect = true;
            tmp_overlap_counter--;
        } else {
            Processor_List_big[i]->isProtect = false;
        }
    }
    sort(Processor_List_big.begin(), Processor_List_big.end(), index_cmp);
    vector<vector<TaskInfo> > scheduler;
    vector<TaskInfo > solutions;
    vector<unsigned int> free_core;

    Vth_max_big = get_Vth_max("big");
    Vth_min_big = get_Vth_min("big");
    //Vth_max = 0.584154;
    //Vth_min = 0.45;


    double alpha = 0.05;
    double beta = 0.95;
    for(unsigned int i = 0 ; i < Processor_List_big.size() ; ++i) {
        scheduler.push_back(vector<TaskInfo>() );
        for(unsigned int j = 0 ; j < voltages_big.size() ; ++j){
            //if (!Processor_List_big[i]->isDead) {
                map<string, map<string, Info*> >::iterator it = task->map_voltage_time_big.find(voltages_big[j]->voltage_str);
                if(it == task->map_voltage_time_big.end() ){
                    throw runtime_error("can't find");
                }
                map<string, Info*>::iterator itt = it->second.find(Processor_List_big[i]->aging_time);
                if(itt == it->second.end() ){
                    cout << "Processor "<< Processor_List_big[i]->index <<" is "<<Processor_List_big[i]->aging_time << endl;
                    throw runtime_error("proc aging time can't find");
                }
                TaskInfo taskInfo;
                taskInfo.Energy_d = 0.0;
                taskInfo.Energy_i = 0.0;
                taskInfo.Energy_t = 0.0;
                taskInfo.dl_idle_energy = 0.0;
                taskInfo.earliest_start_time = max(task->ready_time_big, Processor_List_big[i]->available_time);
                taskInfo.ready_time = task->ready_time_big;
                taskInfo.v.voltage = voltages_big[j]->voltage;
                taskInfo.v.voltage_str = voltages_big[j]->voltage_str;
                taskInfo.proc_index = Processor_List_big[i]->index;
                taskInfo.proc = Processor_List_big[i];
                taskInfo.delay = itt->second->delay_big;
                taskInfo.dynamic_power = itt->second->avg_power_big;
                taskInfo.exec_time = ((double)task->cycle) * itt->second->delay_big;
                taskInfo.slack = task->deadline_time - taskInfo.earliest_start_time - taskInfo.exec_time;
                taskInfo.isAgingSlack = task->deadline_time - task->ready_time_big - taskInfo.exec_time;
                taskInfo.cost = 99999.9;

                //if (isAsymmetric) {
                //    scheduler.back().push_back(taskInfo);
                //} else { //symmetric
                //    if (taskInfo.slack >= 0.0) {
                //        solutions.push_back(taskInfo);
                //    }
                //}

                scheduler.back().push_back(taskInfo);

                if (task->ready_time_big >= Processor_List_big[i]->available_time) {
                    free_core.push_back(Processor_List_big[i]->index);
                }
            //}
        }
        //if (isAsymmetric) {
        //} else { //symmetric
        //    if (solutions.size() > 0) {
        //        break;
        //    }
        //}

    }

    // handle task migration
    if (!no_migration) {
        bool doMigrate = false;
        doMigrate = isMigrate(task);
        if (doMigrate) {
            mig_btol++;
            return 1;
        }
    }


    unsigned int index = 0;
    //compute alpha and beta
    //if (isAsymmetric) {
        for (unsigned int i = 0 ; i < Processor_List_big.size() ; i++) {
            unsigned int num_violation = 0;
            for (unsigned int j = 0 ; j < voltages_big.size() ; j++) {
                if (scheduler[i][j].slack < 0.0 && scheduler[i][j].ready_time >= scheduler[i][j].earliest_start_time){
                    num_violation++;
                }      
            }
            if (num_violation == voltages_big.size()){
                continue;
            }
            else{
                alpha = ((double)( (i * voltages_big.size()) + num_violation + 1 )) / ((double) (voltages_big.size() * Processor_List_big.size()) );
                if(alpha > 1.0){
                    alpha = 1.0;
                }
                beta = 1.0 - alpha;
                break;  
            }
        }
        //compute the cost value of each solution
        for(unsigned int i = 0 ; i < scheduler.size(); ++i ){
            for(unsigned int j = 0 ; j < scheduler[i].size(); ++j ){
                if(scheduler[i][j].slack >= 0.0){
                    scheduler[i][j].cost = alpha * ( ( (scheduler[i][j].proc)->vth - Vth_min_big )/ Vth_min_big ) + beta * ( (Vth_max_big - (scheduler[i][j].proc)->vth)/ Vth_max_big );
                    solutions.push_back(scheduler[i][j]); 
                }     
            }
        }
        if (solutions.size() > 1){
            sort(solutions.begin(), solutions.end(), cmp);
            solutions.erase(solutions.begin()+ (solutions.size()/2),solutions.end());
            //check_slack(solutions, task);
        } else if(solutions.size() == 1){
        } else { // 0
            //cout << "no solution, return 0" << endl;
            return 0;
        } 
    //} else { //symmetric
    //    if (solutions.size() > 0) {
    //        sort(solutions.begin(), solutions.end(), slack_cmp);
    //    } else {
    //        return 0;
    //    }
    //}

    //if (isAsymmetric) {
        //double min_vth = 1.7976931348623158e+308;
        ////double min_energy = 1.7976931348623158e+308;
        //for(unsigned int i = 0 ; i < solutions.size() ; ++i){
        //    solutions[i].Energy_d = solutions[i].dynamic_power * solutions[i].exec_time;
        //    if( (solutions[i].proc)->aging_time == "21y"){
        //        throw runtime_error("Algorithm2");
        //    }
        //    double idle_power = idle_voltage_time_big.find(voltages_big[0]->voltage_str)->second.find( (solutions[i].proc)->aging_time)->second;
        //    solutions[i].dl_idle_energy = idle_power * solutions[i].slack;
        //    solutions[i].Energy_i = solutions[i].dl_idle_energy;
        //    if(task->ready_time_big > (solutions[i].proc)->available_time){
        //        double idle_time = (task->ready_time_big - (solutions[i].proc)->available_time);
        //        solutions[i].Energy_i += (idle_power * idle_time);
        //    } 
        //    solutions[i].Energy_t = solutions[i].Energy_d + solutions[i].Energy_i;
        //    double tmp_vth = tmp_compute_delta_vth( solutions[i].proc, solutions[i].v.voltage_str, solutions[i].exec_time * NS);
        //    if(tmp_vth < min_vth){
        //        min_vth = tmp_vth;
        //        index = i;        
        //    }
        //    //if(solutions[i].Energy_t < min_energy){
        //    //  min_energy = solutions[i].Energy_t;
        //    //  index = i;
        //    //}
        //}   
    //} else { //symmetric
    //    solutions.front().Energy_d = solutions.front().dynamic_power * solutions.front().exec_time;
    //    double idle_power = idle_voltage_time_big.find(voltages_big[0]->voltage_str)->second.find((solutions.front().proc)->aging_time)->second;
    //    solutions.front().dl_idle_energy = idle_power * solutions.front().slack;
    //    solutions.front().Energy_i = solutions.front().dl_idle_energy;
    //    if (task->ready_time > (solutions.front().proc)->available_time) {
    //        double idle_time = (task->ready_time - (solutions.front().proc)->available_time);
    //        //(*p_it)->idle_time += idle_time;
    //        solutions.front().Energy_i += (idle_power * idle_time);
    //    }
    //    solutions.front().Energy_t = solutions.front().Energy_d + solutions.front().Energy_i;
    //}
    solutions.front().Energy_d = solutions.front().dynamic_power * solutions.front().exec_time;
    double idle_power = idle_voltage_time_big.find(voltages_big[0]->voltage_str)->second.find( (solutions.front().proc)->aging_time)->second;
    solutions.front().dl_idle_energy = idle_power * solutions.front().slack;
    solutions.front().Energy_i = solutions.front().dl_idle_energy;
    if(task->ready_time > (solutions.front().proc)->available_time){
        double idle_time = (task->ready_time - (solutions.front().proc)->available_time);
        //(*p_it)->idle_time += idle_time;
        solutions.front().Energy_i += (idle_power * idle_time);
    }
    solutions.front().Energy_t = solutions.front().Energy_d + solutions.front().Energy_i; 
   
 
    double finish_time = solutions[index].earliest_start_time + solutions[index].exec_time;
    if(finish_time > task->deadline_time){
        throw runtime_error("impossible");
    }

    //update core's information, ex. available time, total power, operate time
    (solutions[index].proc)->available_time = solutions[index].earliest_start_time + solutions[index].exec_time;
    (solutions[index].proc)->total_power += (solutions[index].Energy_t - solutions[index].dl_idle_energy);
    (solutions[index].proc)->operate_time += solutions[index].exec_time;

    task->exec_time = solutions[index].exec_time;
 
    //update the NBTI of core
    compute_delta_vth( solutions[index].proc, solutions[index].v.voltage_str, solutions[index].exec_time * NS);

    
    //DBG << "  exec time:     \t" << solutions[index].exec_time *NS << endl;
    //DBG << "   free: ";
    //for (unsigned int i=0; i<free_core.size(); ++i) {
    //    DBG << free_core[i] << " ";
    //}
    //DBG << endl;
    //DBG << "  ----- In Big core " << "(" << solutions[index].proc_index << ")" << " -----------------------" << endl;
    //DBG << "  early st time: \t" << solutions[index].earliest_start_time *NS << endl;
    //DBG << "  finish time:   \t" << finish_time *NS << endl; 
    //DBG << "  -------------------------------------------" << endl;

    //check whether the next task is ready or not
    for(unsigned int i = 0 ; i < task->next.size() ; ++i){
        Task *next = task->next[i];
        next->num_pre--;
        if (task->isBig != next->isBig) {
            next->ready_time_lit = finish_time;
        } else {
            if(finish_time > next->ready_time_big){
                next->ready_time_big = finish_time;
                //cout << "next task " << next->id << ", " << next->ready_time_big*NS << endl;
            }
        }
        next->ready_time = finish_time;
        if(next->num_pre == 0 && next->id != END_TASK){
            //cout << next->id << endl;
            readyQuere.push_back(next);
        }
    }
    return 1;
}


void Sim::topological_ordering(){
    queue<Task *> Q;
    for(unsigned int i = 0 ; i < task_list.size() ; ++i){
        if(task_list[i]->num_pre == 0){
            Q.push(task_list[i]);
        }
    }
    for(unsigned int i = 0 ; i < task_list.size() ; ++i){
        if(Q.empty()){
            cout << "cycle!!!!" << endl;
            break;
        }
        Task *task = Q.front();
        Q.pop();
        sorted_List.push_back(task);
        for(unsigned int j = 0 ; j < task->next.size() ; ++j){
            Task *next = task->next[j];
            next->num_pre--;
            if(next->num_pre == 0){
                Q.push(next);
            }
        }
    }
}

void Sim::setDeadline(vector<unsigned int> &critical_task_list){
    // task on big core
	int nb = 0;
	int nl = 0;
	vector< pair<int, double> > vp_big;
	vector< pair<int, double> > vp_lit;
    vector<Task *>::iterator it = sorted_List.begin();
    double min_ratio = 100.0;
    while(it != sorted_List.end()) {
        Task *task = *it;
        double exec_time_big = 0.0, finish_time_big = 0.0;
        double exec_time_lit = 0.0, finish_time_lit = 0.0;
        if(task->id != 0 && task->id != END_TASK ) {
            for(unsigned int i = 0 ; i < critical_task_list.size() ; ++i){
                if( (int)critical_task_list[i] == task->id){
                    exec_time_big = task->delay_big * (double)task->cycle * critical_ratio;
                    exec_time_lit = task->delay_lit * (double)task->cycle * critical_ratio;
                    task->isCritical = true;
                    task->ratio = critical_ratio;
                    //task->multithread = true;
                    break;
                }
                else{
                    exec_time_big = task->delay_big * (double)task->cycle * nonCritical_ratio;
                    exec_time_lit = task->delay_lit * (double)task->cycle * nonCritical_ratio;
                    task->isCritical = false;
                    task->ratio = nonCritical_ratio;
                    //task->multithread = false;
                }
            }
            // common
            //task->deadline_time = task->ready_time_big + exec_time_big; // deadline depends on big core

            // big core
            finish_time_big  = task->ready_time_big + exec_time_big;
            task->finish_time_big = finish_time_big;
            task->min_finish_time_big = task->ready_time_big + (task->delay_big * (double)task->cycle); // without ratio
            task->last_start_time_big = task->deadline_time - (task->delay_big * (double)task->cycle);


            // little core
            finish_time_lit  = task->ready_time_lit + exec_time_lit;
            task->finish_time_lit = finish_time_lit;
            task->min_finish_time_lit = task->ready_time_lit + (task->delay_lit * (double)task->cycle);
            task->last_start_time_lit = task->deadline_time - (task->delay_lit * (double)task->cycle);

            if (task->isBig) {
                task->exec_time = task->delay_big * (double)task->cycle;
				task->last_start_time = task->last_start_time_big;
                //task->exec_time = exec_time_big;
            } else {
                task->exec_time = task->delay_lit * (double)task->cycle;
				task->last_start_time = task->last_start_time_lit;
                //task->exec_time = exec_time_lit;
            }
            task->deadline_time = task->ready_time_big + exec_time_big; // deadline depends on big core
            //task->deadline_time = task->deadline_time * 1.8;
            //task->deadline_time = task->deadline_time * 1.4;

            //if (task->finish_time_lit > task->deadline_time) {
            //if (task->min_finish_time_lit > task->deadline_time) {
            //task->deadline_time = task->deadline_time * 1.2;
            if (task->min_finish_time_lit > task->deadline_time) {
                task->isBig = true;
				vp_big.push_back( make_pair<int,double>(task->id, task->min_finish_time_lit) );
				nb++;
            } else {
                task->isBig = false;
				vp_lit.push_back( make_pair<int,double>(task->id, task->min_finish_time_lit) );
				nl++;
            }

            //task->ratio = exec_time/(task->min_exec_time * (double)task->cycle);
            if(task->ratio < min_ratio){
                min_ratio = task->ratio;
            }
        }
        // update ready time of next task
        for (unsigned int i = 0 ; i < task->next.size() ; ++i){
            //Task *next = task->next[i];

            //next->ready_time_big = finish_time_big;
            //next->ready_time_big_backup = next->ready_time_big;

            ////next->ready_time_lit = finish_time_lit;
            //next->ready_time_lit = task->min_finish_time_lit;
            //next->ready_time_lit_backup = next->ready_time_lit;

            Task *next = task->next[i];
            next->ready_time_big = task->min_finish_time_big;
            next->ready_time_big_backup = next->ready_time_big;
            next->ready_time_lit = task->min_finish_time_lit;
            next->ready_time_lit_backup = next->ready_time_lit;

        }
        it++;     
    }

	if (nl > 10) {
		int r = nl - 10;
		sort(vp_lit.begin(), vp_lit.end(), sortbysec);
		for (int i=0; i<r; ++i) {
			vector<Task *>::iterator it = sorted_List.begin();
			while(it != sorted_List.end()) {
    		    Task *task = *it;
				if (task->id == vp_lit[i].first) {
					task->isBig = true;
				}
				it++;
			}
		}
	}


    //it = sorted_List.begin();
    vector<Task *>::iterator it2 = sorted_List.begin();
    while(it2 != sorted_List.end()) {
        Task *task = *it2;
        if(task->id != 0 && task->id != END_TASK ){
            //cout << "task: " << task->id << endl;
            for (unsigned int i = 0 ; i < task->next.size() ; ++i) {
                /*
                Task *next = task->next[i];
                if (next->isBig != task->isBig) {
                    if (next->isBig) { // little -> big
                            next->ready_time = task->finish_time_lit;
                            next->ready_time_big = task->finish_time_lit;
                            next->ready_time_big_backup = next->ready_time_big;
                    } else { // big -> little
                            next->ready_time = task->finish_time_big;
                            next->ready_time_lit = task->finish_time_big;
                            next->ready_time_lit_backup = next->ready_time_lit;
                    }
                } else {
                    if (next->isBig) { // big -> big
                            next->ready_time = task->finish_time_big;
                            next->ready_time_big = task->finish_time_big;
                            next->ready_time_big_backup = next->ready_time_big;
                    } else { // little -> little
                            next->ready_time = task->finish_time_lit;
                            next->ready_time_lit = task->finish_time_lit;
                            next->ready_time_lit_backup = next->ready_time_lit;
                    }
                }
                */
                if (!task->isBig) {
                    //task->deadline_time += task->deadline_time * 0.1; // for c432
                    task->deadline_time += task->deadline_time * 0.04; // for b14
                    //task->deadline_time += task->deadline_time * 0.16; // for c1908
                    //task->deadline_time += task->deadline_time * 0.1;
                }
                Task *next = task->next[i];
                //if(next->id != END_TASK ) {
                    //next->deadline_time += task->deadline_time * 0.35;  // for c432, b14
                    //next->deadline_time += task->deadline_time * 0.35;  // for c432, b14
                    next->deadline_time += task->deadline_time * 0.28;  // for c432, b14
                    //next->deadline_time += task->deadline_time * 0.39;   // for c1908
                    //next->deadline_time += task->deadline_time * 0.30; // for c499
                    if (next->isBig != task->isBig) {
                        if (next->isBig) { // little -> big
                                next->ready_time = task->min_finish_time_lit;
                                next->ready_time_big = task->min_finish_time_lit;
                                next->ready_time_big_backup = next->ready_time_big;
                        } else { // big -> little
                                next->ready_time = task->min_finish_time_big;
                                next->ready_time_lit = task->min_finish_time_big;
                                next->ready_time_lit_backup = next->ready_time_lit;
                        }
                    } else {
                        if (next->isBig) { // big -> big
                                next->ready_time = task->min_finish_time_big;
                                next->ready_time_big = task->min_finish_time_big;
                                next->ready_time_big_backup = next->ready_time_big;
                        } else { // little -> little
                                next->ready_time = task->min_finish_time_lit;
                                next->ready_time_lit = task->min_finish_time_lit;
                                next->ready_time_lit_backup = next->ready_time_lit;
                        }
                    }

                    //if (next->isBig != task->isBig) {
                    //    if (next->isBig) { // little -> big
                    //            next->ready_time = task->finish_time_lit;
                    //            //next->ready_time = task->min_finish_time_lit;
                    //            next->ready_time_big = task->finish_time_lit;
                    //            //next->ready_time_big = task->min_finish_time_lit;
                    //            next->ready_time_big_backup = next->ready_time_big;
                    //    } else { // big -> little
                    //            next->ready_time = task->finish_time_big;
                    //            next->ready_time_lit = task->finish_time_big;
                    //            next->ready_time_lit_backup = next->ready_time_lit;
                    //    }
                    //} else {
                    //    if (next->isBig) { // big -> big
                    //            next->ready_time = task->finish_time_big;
                    //            next->ready_time_big = task->finish_time_big;
                    //            next->ready_time_big_backup = next->ready_time_big;
                    //    } else { // little -> little
                    //            next->ready_time = task->finish_time_lit;
                    //            //next->ready_time = task->min_finish_time_lit;
                    //            next->ready_time_lit = task->finish_time_lit;
                    //            //next->ready_time_lit = task->min_finish_time_lit;
                    //            next->ready_time_lit_backup = next->ready_time_lit;
                    //    }
                    //}
                //}
                //cout << "task " << task->id << ", " << task->ready_time *NS << endl;
                //cout << "    next " << next->id << ", " << next->ready_time *NS<< endl;
            }
        }
        it2++;        
    }

    string tlabel;
    string clabel;
    int nbtask = 0;
    int nltask = 0;
    for(unsigned int i = 1 ; i < sorted_List.size()-1 ; ++i){
        if (sorted_List[i]->isBig) {
            //cout << "Task " << i <<" is big task\n";
            nbtask++;
        } else {
            //cout << "Task " << i <<" is lit task\n";
            nltask++;
        }
    }

    wfile << "Number of big task: " << nbtask << endl;
    wfile << "Number of lit task: " << nltask << endl;
    wfile << endl;

    wfile << "============================ Task on big core ============================" << endl;
    for(unsigned int i = 0 ; i < sorted_List.size() ; ++i){
        //if (sorted_List[i]->isBig) {
            if (sorted_List[i]->isBig) {
                tlabel = ", Big task";
            } else {
                tlabel = ", Lit task";
            }
            if (sorted_List[i]->isCritical) {
                clabel = "Critical task";
            } else {
                clabel = "Non Critical task";
            }
            wfile << "---------------------------------------------------------------------------" << endl;
            wfile << "id: " << sorted_List[i]->id << tlabel << endl;
            //wfile << "  ready time:      " << "\t" << sorted_List[i]->ready_time_big *NS << " ns | deadline " << sorted_List[i]->deadline_time * NS << " ns" << endl;
            wfile << "  ready time:      " << "\t" << sorted_List[i]->ready_time *NS << " ns | deadline " << sorted_List[i]->deadline_time * NS << " ns" << endl;
            wfile << "  exec time:       " << "\t" << sorted_List[i]->delay_big * (double)sorted_List[i]->cycle * NS << " ns " << endl;
            wfile << "  finish time:     " << "\t" << sorted_List[i]->finish_time_big *NS << " ns " << endl;
            wfile << "  min finish time: " << "\t" << sorted_List[i]->min_finish_time_big *NS << " ns " << endl;
            wfile << "  slack:           " << "\t" << sorted_List[i]->deadline_time * NS - sorted_List[i]->finish_time_big *NS << " ns " << endl;
            //wfile << "  last_start_time: " << "\t" << sorted_List[i]->last_start_time_big *NS << " ns | deadline " << sorted_List[i]->deadline_time * NS << " ns" << endl;
            wfile << "  " << clabel << endl;
            //wfile << "  Critical ratio:  " << "\t" << sorted_List[i]->ratio << endl;
        //}
    }
    wfile << endl << endl;
    wfile << "============================ Task on lit core ============================" << endl;
    for(unsigned int i = 0 ; i < sorted_List.size() ; ++i){
        //if (!sorted_List[i]->isBig) {
            if (sorted_List[i]->isBig) {
                tlabel = ", Big task";
            } else {
                tlabel = ", Lit task";
            }
            if (sorted_List[i]->isCritical) {
                clabel = "Critical task";
            } else {
                clabel = "Non Critical task";
            }
            wfile << "---------------------------------------------------------------------------" << endl;
            wfile << "id: " << sorted_List[i]->id << tlabel << endl;
            //wfile << "  ready time:      " << "\t" << sorted_List[i]->ready_time_lit *NS << " ns | deadline " << sorted_List[i]->deadline_time * NS << " ns" << endl;
            wfile << "  ready time:      " << "\t" << sorted_List[i]->ready_time *NS << " ns | deadline " << sorted_List[i]->deadline_time * NS << " ns" << endl;
            wfile << "  exec time:       " << "\t" << sorted_List[i]->delay_lit * (double)sorted_List[i]->cycle * NS << " ns " << endl;
            wfile << "  finish time:     " << "\t" << sorted_List[i]->finish_time_lit *NS << " ns " << endl;
            wfile << "  min finish time: " << "\t" << sorted_List[i]->min_finish_time_lit *NS << " ns " << endl;
            wfile << "  slack:           " << "\t" << sorted_List[i]->deadline_time * NS - sorted_List[i]->min_finish_time_lit *NS << " ns " << endl;
            //wfile << "  last_start_time: " << "\t" << sorted_List[i]->last_start_time_lit *NS << " ns | deadline " << sorted_List[i]->deadline_time * NS << " ns" << endl;
            wfile << "  " << clabel << endl;
            //wfile << "  Critical ratio:  " << "\t" << sorted_List[i]->ratio << endl;
        //}
    }
    wfile << "=========================================================================" << endl << endl;

}

void Sim::start_map(char *benchmark_name_big, char *benchmark_name_lit, int policy) {
    string str_benchmark_name_big = benchmark_name_big;
    string str_benchmark_name_lit = benchmark_name_lit;
    //int policy = atoi(char_policy);
    fix_taskgraph(str_benchmark_name_big, str_benchmark_name_lit, policy);
}

void Sim::computeLastStartTime(Task* task) {
    task->last_start_time_big = 1.7e+308;
    task->last_start_time_lit = 1.7e+308;
    // big core
    for (unsigned int i = 0 ; i < Processor_List_big.size() ; ++i) {
        //if (!Processor_List_big[i]->isDead) {
            if (Processor_List_big[i]->aging_time == "21y") {
                //cout << "Processor "<< i << " aging is 21y" << endl;
                throw runtime_error("impossible case");
            }
            double min_delay = task->map_voltage_time_big.find(voltages_big.back()->voltage_str)->second.find(Processor_List_big[i]->aging_time)->second->delay_big;
            double min_exec_time = task->cycle * min_delay; // minimun execution time on the processor
            double tmp_last_start_time = task->deadline_time - min_exec_time;		
            if (task->last_start_time_big > tmp_last_start_time) {
                task->last_start_time_big = tmp_last_start_time;
            }        
        //}
    } 
    // little core
    for (unsigned int i = 0 ; i < Processor_List_lit.size() ; ++i) {
        //if (!Processor_List_lit[i]->isDead) {
            if (Processor_List_lit[i]->aging_time == "21y") {
                //cout << "Processor "<< i << " aging is 21y" << endl;
                throw runtime_error("impossible case");
            }
            double min_delay = task->map_voltage_time_lit.find(voltages_lit.back()->voltage_str)->second.find(Processor_List_lit[i]->aging_time)->second->delay_lit;
            double min_exec_time = task->cycle * min_delay; // minimun execution time on the processor
            double tmp_last_start_time = task->deadline_time - min_exec_time;		
            if (task->last_start_time_lit > tmp_last_start_time) {
                task->last_start_time_lit = tmp_last_start_time;
            }        
        //}
    } 
	if (task->isBig) {
		task->last_start_time = task->last_start_time_big;
	} else {
		task->last_start_time = task->last_start_time_lit;
	}
}

void Sim::ADA_computeLastStartTime(Task* task) {
    task->last_start_time_big = 1.7e+308;
    task->last_start_time_lit = 1.7e+308;
    // big core
    for (unsigned int i = 0 ; i < Processor_List_big.size() ; ++i) {
        //if (!Processor_List_big[i]->isDead) {
            if (Processor_List_big[i]->aging_time == "21y") {
                //cout << "Processor "<< i << " aging is 21y" << endl;
                throw runtime_error("impossible case");
            }
            double min_delay = task->map_voltage_time_big.find(voltages_big.back()->voltage_str)->second.find(Processor_List_big[i]->aging_time)->second->delay_big;
            double min_exec_time = task->cycle * min_delay; // minimun execution time on the processor
            double tmp_last_start_time = task->deadline_time - min_exec_time;		
            if (task->last_start_time_big > tmp_last_start_time) {
                task->last_start_time_big = tmp_last_start_time;
            }        
        //}
    } 
    // little core
    for (unsigned int i = 0 ; i < Processor_List_lit.size() ; ++i) {
        //if (!Processor_List_lit[i]->isDead) {
            if (Processor_List_lit[i]->aging_time == "21y") {
                //cout << "Processor "<< i << " aging is 21y" << endl;
                throw runtime_error("impossible case");
            }
            double min_delay = task->map_voltage_time_lit.find(voltages_lit.back()->voltage_str)->second.find(Processor_List_lit[i]->aging_time)->second->delay_lit;
            double min_exec_time = task->cycle * min_delay; // minimun execution time on the processor
            double tmp_last_start_time = task->deadline_time - min_exec_time;		
            if (task->last_start_time_lit > tmp_last_start_time) {
                task->last_start_time_lit = tmp_last_start_time;
            }        
    } 
	if (task->isBig) {
		task->last_start_time = task->last_start_time_big;
	} else {
		task->last_start_time = task->last_start_time_lit;
	}
}

Task* Sim::highPriorityTask() {
    Task* highest_task = NULL;
    sort(readyQuere.begin(), readyQuere.end(), ready_cmp);
    /*
    if (readyQuere.size() > 0) {
        highest_task = readyQuere.front();  
    } else {
        cout << "impossible case: readyQueue is empty" << endl;
    }
    */
    if (readyQuere.size() > 1) {
        //if (readyQuere[0]->ready_time_big < readyQuere[1]->ready_time_big) {//minimun ready time task
        if (readyQuere[0]->ready_time < readyQuere[1]->ready_time) {//minimun ready time task
            computeLastStartTime(readyQuere.front());
            highest_task = readyQuere.front();
        } else { //readyQuere[0]->ready_time >= readyQuere[1]->ready_time
            for (unsigned int i = 0 ; i < readyQuere.size() ; ++i) {
                computeLastStartTime(readyQuere[i]);
            }
            sort(readyQuere.begin(), readyQuere.end(), last_start_time_cmp);
            highest_task = readyQuere.front();  
        }
    } else if (readyQuere.size() == 1 ) { // only one task in ready queue
        computeLastStartTime(readyQuere.front());
        highest_task = readyQuere.front();
    } else { //readyQueue.empty
        //cout << "impossible case: readyQueue is empty" << endl;
        throw runtime_error("impossible case: readyQueue is empty");
    }
    return highest_task;
}

void Sim::ratioRelease(Task *task, Task *pre_task, double ratio) {
    pre_task->ratio = ratio;
    pre_task->isTight = true;
    double pre_exec_time = pre_task->delay_big * (double)pre_task->cycle;
    pre_task->deadline_time = pre_task->ready_time + (pre_exec_time * pre_task->ratio);
    pre_task->last_start_time_big = pre_task->deadline_time - pre_exec_time;
    for (unsigned int i = 0; i < pre_task->next.size(); ++i) {
        Task *next = pre_task->next[i];
        next->ready_time = pre_task->deadline_time;
        double next_exec_time = next->delay_big * (double)next->cycle;
        next->ready_time_big_backup = next->ready_time;
        next->min_finish_time_big = next->ready_time + next_exec_time;
        next->ratio = (next->deadline_time - next->ready_time) / next_exec_time;
    }
}

unsigned int Sim::checkCriticalOverlap() {
    critical_List.clear();
    overlap_task_map.clear();
    overlap_task_list.clear();
    critical_couple_list.clear();
    double min_ratio = 100.0;
    //find the minimum ratio
    for (unsigned int i = 0; i < sorted_List.size(); ++i) {
        if (sorted_List[i]->id != 0 && sorted_List[i]->id != END_TASK) {
            if (sorted_List[i]->ratio < min_ratio) {
                min_ratio = sorted_List[i]->ratio;
            }
        }
    }
    //cout << "min_ratio: "<<min_ratio << endl;
    for (unsigned int i = 0; i < sorted_List.size(); ++i) {
        if (sorted_List[i]->ratio == min_ratio || sorted_List[i]->isTight == true) {
            critical_List.push_back(sorted_List[i]);
            sorted_List[i]->isCritical = true;
        } else {
            sorted_List[i]->isCritical = false;
        }
    }
    //find the maxmium overlap number at same time
    vector<Task *> arrl;
    vector<Task *> exit;
    for (unsigned int i = 0; i < critical_List.size(); ++i) {
        arrl.push_back(critical_List[i]);
        exit.push_back(critical_List[i]);
    }
    sort(arrl.begin(), arrl.end(), ready_cmp);
    sort(exit.begin(), exit.end(), deadline_cmp);
    unsigned int num_overlap = 1, max_overlap = 1;
    unsigned int next_index = 1, index = 0;
    double time = arrl[0]->ready_time;
    vector<Task *> Tmp_overlap_list;
    Tmp_overlap_list.push_back(arrl[0]);
    while (next_index < arrl.size() && index < arrl.size()) {
        if (arrl[next_index]->ready_time < exit[index]->deadline_time) {
            Tmp_overlap_list.push_back(arrl[next_index]);
            num_overlap++;
            if (num_overlap > max_overlap) {
                max_overlap = num_overlap;
                time = arrl[next_index]->ready_time;
            }
            next_index++;
        } else {
            unsigned int erase_index = 0;
            for (; erase_index < Tmp_overlap_list.size(); ++erase_index) {
                if (Tmp_overlap_list[erase_index]->id == exit[index]->id) {
                    break;
                }
            }
            Tmp_overlap_list.erase(Tmp_overlap_list.begin() + erase_index);
            num_overlap--;
            index++;
        }
    }
    /*cout << "Max overlap = " << max_overlap << endl;*/
    //check all the overlap couple task
    for (unsigned int i = 0; i < critical_List.size(); ++i) {
        for (unsigned int j = i + 1; j < critical_List.size(); ++j) {
            vector<Task *> couple;
            couple.push_back(critical_List[i]);
            couple.push_back(critical_List[j]);
            if ((critical_List[i]->ready_time < critical_List[j]->deadline_time) && (critical_List[i]->deadline_time > critical_List[j]->ready_time)) {
                map<int, vector<Task *> >::iterator it = overlap_task_map.find(critical_List[i]->id);
                //cout << critical_List[i]->id << ", " << critical_List[j]->id << endl;
                if (it == overlap_task_map.end()) {
                    vector<Task *> tmp;
                    tmp.push_back(critical_List[j]);
                    overlap_task_map.insert(pair<int, vector<Task *> >(critical_List[i]->id, tmp));
                    if (!critical_List[i]->isRelease) {
                        overlap_task_list.push_back(critical_List[i]);
                    }
                } else {
                    it->second.push_back(critical_List[j]);
                }
                it = overlap_task_map.find(critical_List[j]->id);
                if (it == overlap_task_map.end()) {
                    vector<Task *> tmp;
                    tmp.push_back(critical_List[i]);
                    overlap_task_map.insert(pair<int, vector<Task *> >(critical_List[j]->id, tmp));
                    if (!critical_List[j]->isRelease) {
                        overlap_task_list.push_back(critical_List[j]);
                    }
                } else {
                    it->second.push_back(critical_List[i]);
                }
                critical_couple_list.push_back(couple);
            }
        }
    }
    sort(overlap_task_list.begin(), overlap_task_list.end(), reScheduling_cmp);
    return max_overlap;
}

void Sim::reScheduling() {
    overlap_counter = checkCriticalOverlap();
    //overlap_counter = 1;
    while (!overlap_task_list.empty()) {
        Task *task = overlap_task_list.front();
        task->isRelease = true;
        if (task->ready_time == 0) { //top
            overlap_task_list.erase(overlap_task_list.begin());
            continue;
        }
        map<int, vector<Task *> >::iterator it = overlap_task_map.find(task->id); //find overlap task of this task
        unsigned int counter = 0;
        Task *overlap_task = NULL;
        for (unsigned int i = 0; i < it->second.size(); i++) {
            overlap_task = it->second[i];
            if (overlap_task->ready_time == 0.0) {
                counter++;
            }
        }
        if (counter == it->second.size()) { //all overlap tasks of this task are at top
                                            //if(counter == it->second.size() || (overlap_task->pre.front()->id == task->pre.front()->id) ){//all overlap tasks of this task are at top
            overlap_task_list.erase(overlap_task_list.begin());
            continue;
        }
        //Task *pre_task = task->pre.front();
        Task *pre_task = NULL;
        double Max_deadline = 0.0;
        for (unsigned int i = 0; i < task->pre.size(); ++i) {
            if (task->pre[i]->deadline_time > Max_deadline) {
                Max_deadline = task->pre[i]->deadline_time;
                pre_task = task->pre[i];
            }
        }
        //if the pre task is critical
        //if(pre_task->isCritical || pre_task->id == START_TASK || pre_task->id == START_TASK2){
        if (pre_task->isCritical) {
            overlap_task_list.erase(overlap_task_list.begin());
            continue;
        }
        vector<Task> backup_Task_List;
        double pre_ratio = pre_task->ratio;
        while (1) {
            pre_ratio = pre_ratio - 0.1;
            backup_Task_List.clear();
            for (unsigned int i = 0; i < sorted_List.size(); ++i) {
                Task tmp_task;
                tmp_task.isCritical = sorted_List[i]->isCritical;
                tmp_task.isRelease = sorted_List[i]->isRelease;
                tmp_task.isTight = sorted_List[i]->isTight;
                tmp_task.ratio = sorted_List[i]->ratio;
                tmp_task.deadline_time = sorted_List[i]->deadline_time;
                tmp_task.last_start_time_big = sorted_List[i]->last_start_time_big;
                tmp_task.ready_time = sorted_List[i]->ready_time;
                tmp_task.ready_time_big_backup = sorted_List[i]->ready_time_big_backup;
                tmp_task.min_finish_time_big = sorted_List[i]->min_finish_time_big;
                backup_Task_List.push_back(tmp_task);
            }
            ratioRelease(task, pre_task, pre_ratio);
            double min_task_ratio = task->ratio;
            for (unsigned int i = 0; i < pre_task->next.size(); ++i) {
                if (pre_task->next[i]->ratio < min_task_ratio) {
                    min_task_ratio = pre_task->next[i]->ratio;
                }
            }
            //cout << min_task_ratio << endl;
            if (min_task_ratio <= pre_task->ratio) {
                for (unsigned int i = 0; i < sorted_List.size(); ++i) {
                    sorted_List[i]->isCritical = backup_Task_List[i].isCritical;
                    sorted_List[i]->isRelease = backup_Task_List[i].isRelease;
                    sorted_List[i]->isTight = backup_Task_List[i].isTight;
                    sorted_List[i]->ratio = backup_Task_List[i].ratio;
                    sorted_List[i]->deadline_time = backup_Task_List[i].deadline_time;
                    sorted_List[i]->last_start_time_big = backup_Task_List[i].last_start_time_big;
                    sorted_List[i]->ready_time = backup_Task_List[i].ready_time;
                    sorted_List[i]->ready_time_big_backup = backup_Task_List[i].ready_time_big_backup;
                    sorted_List[i]->min_finish_time_big = backup_Task_List[i].min_finish_time_big;
                }
                continue;
            } else {
                break;
            }
        }
        //ratioRelease(task, pre_task, task->ratio);
        unsigned int this_time_overlap = checkCriticalOverlap();
        if (this_time_overlap >= overlap_counter) { //bad
            for (unsigned int i = 0; i < sorted_List.size(); ++i) {
                sorted_List[i]->isCritical = backup_Task_List[i].isCritical;
                sorted_List[i]->ratio = backup_Task_List[i].ratio;
                sorted_List[i]->deadline_time = backup_Task_List[i].deadline_time;
                sorted_List[i]->last_start_time_big = backup_Task_List[i].last_start_time_big;
                sorted_List[i]->ready_time = backup_Task_List[i].ready_time;
                sorted_List[i]->ready_time_big_backup = backup_Task_List[i].ready_time_big_backup;
                sorted_List[i]->min_finish_time_big = backup_Task_List[i].min_finish_time_big;
            }
            checkCriticalOverlap();
        } else {
            task->isCritical = false;
            overlap_counter = this_time_overlap;
        }
    }
    wfile << endl
          << "reScheduling: " << endl;
    for (unsigned int i = 0; i < sorted_List.size(); ++i) {
        wfile << "id: " << sorted_List[i]->id << endl;
        wfile << " ready time " << sorted_List[i]->ready_time * NS << " ns deadline " << sorted_List[i]->deadline_time * NS << " ns" << endl;
        wfile << " finish time " << sorted_List[i]->min_finish_time_big * NS << " ns " << endl;
        wfile << " Critical ratio " << sorted_List[i]->ratio << endl;
        wfile << " last_start_time " << sorted_List[i]->last_start_time_big * NS << " ns deadline " << sorted_List[i]->deadline_time * NS << " ns" << endl;
    }
}

void Sim::fix_taskgraph(string str_benchmark_name_big, string str_benchmark_name_lit, int policy){
    if (policy == 0 || policy == 1 || policy == 4) {
        no_migration = true;
    }
    for(unsigned int i = 0 ; i < critical_list.size(); ++i) {//for每一個case i.e., (1,2) or (1,3)
        string wfile_name = "./result/big_little/";
		//wfile_name += "/c499_c499d";
		string fold = str_benchmark_name_lit + "_" + str_benchmark_name_big;
		wfile_name += fold;
        mkdir(wfile_name.c_str(), 0777);
        string policy_name = "";
        //policy_name = "Asymmetric";
        switch (policy) {
            case 0:
                isAsymmetric = false;
                isRescheduling = false;
                policy_name = "Sym";
                break;
            case 1:
                isAsymmetric = true;
                isRescheduling = true;
                policy_name = "Asym";
                break;
            case 2:
                isAsymmetric = false;
                isRescheduling = false;
                policy_name = "Sym_mig";
                break;
            case 3:
                isAsymmetric = true;
                isRescheduling = true;
                policy_name = "Asym_mig";
                break;
			case 4:
                isAsymmetric = false;
                isRescheduling = false;
                policy_name = "Spare";
                break;
			case 5:
                isAsymmetric = false;
                isRescheduling = false;
                policy_name = "Spare_mig";
                break;
        }
        //isAsymmetric = true;
        //isRescheduling = false; 
        stringstream ss; 
        ss << critical_list[i].size();
        string str = ss.str();
        wfile_name += "/" + str;
        mkdir(wfile_name.c_str(), 0777);
        wfile_name += "/Task";
        string wfile_name_backup = wfile_name;
        DBG.open("debug.log", ios::out);

        // for each critical task in critical list
        for(unsigned int j = 0 ; j < critical_list[i].size() ; ++j) {
            stringstream ss;
            ss << critical_list[i][j];
            string str = "";
            if(j < critical_list[i].size()-1)
                str = ss.str() + "_";
            else
                str = ss.str();
            wfile_name += str;
        }
		string month_file = wfile_name + "/" + policy_name + "_month.csv";
		//month_log.open(month_file.c_str(), ios::out);
		//month_log << "aging_time, " << "energy_month, " << "power_month, " << "operate_time_month, " << endl;
		//cout << month_file << endl;
        //cout << "wf: " << wfile_name << endl;
        mkdir(wfile_name.c_str(), 0777);
        string w_policy_name = wfile_name + "/" + policy_name + ".log";
        wfile_name += "/" + policy_name + ".csv";

        
        cout << wfile_name << endl;
        wfile.open(wfile_name.c_str(), ios::out);//open
        w_policy_file.open(w_policy_name.c_str(), ios::out);//open

        wfile <<"Critical task: ";
        for(unsigned int j = 0 ; j < critical_list[i].size() ; ++j){
            wfile << critical_list[i][j] << " ";
        }     
        wfile << endl << endl;
        wfile << "Critical ratio: "<< critical_ratio << endl;
        wfile << "nonCritical ratio: "<< nonCritical_ratio << endl;
        wfile << endl << endl;
        
        reset();//reset simulator, including core, task graph

        //set task graph deadline 
        setDeadline(critical_list[i]); 


        //if (isRescheduling) {
        //    reScheduling();
        //} else {
        //    overlap_counter = checkCriticalOverlap();
        //}

        //for(unsigned int j = 0 ; j < sorted_List.size() ; ++j) {
        //    cout << "task\t" << sorted_List[j]->id << ",\t" << sorted_List[j]->deadline_time << endl;
        //}

        //cout << "period: " << period << endl;
        //set the task of task graph to critical or non-critical
        for(unsigned int j = 0 ; j < sorted_List.size() ; ++j){
            //cout << sorted_List[k]->id << " "<< sorted_List[k]->ratio << " " << sorted_List[k]->isTight << endl;
            if(sorted_List[j]->ratio == critical_ratio ){
              sorted_List[j]->isCritical = true;
            } else if( sorted_List[j]->ratio < nonCritical_ratio ){
              sorted_List[j]->isCritical = true;
            } else{
              sorted_List[j]->isCritical = false;
            }
        }
        //set the period of task graph
        for(unsigned int j = 0 ; j < sorted_List.size() ; ++j){
            if(sorted_List[j]->deadline_time > period){
                // maximum deadline time
                period = sorted_List[j]->deadline_time;
            }
        }
        //if (round == 0) {
        //}

        bool isEnd = false;
        int round = 0;
        mig_btol = 0;
        mig_ltob = 0;
        operate_time = 0.0;
        simulation_time = 0.0;
        readyQuere.clear();
        int bugcnt1 = 0;
        int bugcnt2 = 0;

		double optime_last1 = 0.0;
		double optime_last2 = 0.0;

		double energy_last1 = 0.0;
		double energy_last2 = 0.0;
		double energy_last3 = 0.0;
		double energy_last_month = 0.0;

		double energy_this_month = 0.0;

		// for list assignment //
		vector<Task *> task_list;
        for (unsigned int j = 0 ; j < sorted_List.size() ; ++j) {
			task_list.push_back(sorted_List[j]);
		}
		
		
		////////////////////////


        while (!isEnd) {
            // big cluster
            for (unsigned int j = 0 ; j < Processor_List_big.size() ; ++j) {
                //DBG << "core " << Processor_List_big[j]->index << ", " << Processor_List_big[j]->aging_time << endl;
                Processor_List_big[j]->available_time = 0.0;
                Processor_List_big[j]->total_power = 0.0;
                Processor_List_big[j]->operate_time = 0.0;
            }
            // little cluster
            for (unsigned int j = 0 ; j < Processor_List_lit.size() ; ++j) {
                Processor_List_lit[j]->available_time = 0.0;
                Processor_List_lit[j]->total_power = 0.0;
                Processor_List_lit[j]->operate_time = 0.0;
            }

            //for (unsigned int j = 0 ; j < sorted_List.size() ; ++j) {
            //    if (round == 0) {
            //        Task *task = sorted_List[j];
            //        cout << "task " << task->id << ", " << task->ready_time*NS << endl;
            //        for (unsigned int k = 0 ; k < task->next.size() ; ++k) {
            //            Task *next = task->next[k];
            //            cout << "   next " << next->id << ", " << next->ready_time*NS << endl;
            //        }
            //        cout << endl;
            //    }
            //}

            //for each period, we need to reset the ready time of each task 
            for (unsigned int j = 0 ; j < sorted_List.size() ; ++j) {
                if(sorted_List[j]->id == 0 || sorted_List[j]->id == END_TASK) {
                    sorted_List[j]->ready_time = 0.0;
                    sorted_List[j]->ready_time_big = 0.0;
                    sorted_List[j]->ready_time_lit = 0.0;
                    sorted_List[j]->ready_time_big_backup = 0.0;       
                }
                else if (sorted_List[j]->id != START_TASK  && sorted_List[j]->id != START_TASK2 &&
                         sorted_List[j]->id != START_TASK3 && sorted_List[j]->id != START_TASK4) { //not the first task
                    sorted_List[j]->ready_time = -1.0;
                    sorted_List[j]->ready_time_big = -1.0;
                    sorted_List[j]->ready_time_lit = -1.0;
                    sorted_List[j]->ready_time_big_backup = -1.0;  
                }
            }
            //if tasks can be execute, push it into ready queue      
            for (unsigned int j = 0 ; j < sorted_List.size() ; ++j) {
                //reset the dependency of task
                sorted_List[j]->num_pre = sorted_List[j]->num_pre_backup;
                if (sorted_List[j]->id != 0 && sorted_List[j]->id != END_TASK) {
                    if (sorted_List[j]->ready_time == 0.0) {
                        readyQuere.push_back(sorted_List[j]);
                    }
                } 
            }
            //DBG << "********** Round " << round << " **********" << endl;
            
            while(readyQuere.size() != 0){
                //get a highest priority task
                Task *highest_task = highPriorityTask();

                
                //DBG << "Task: " << highest_task->id << ", " << highest_task->isBig << endl;
                //cout << "id: " << highest_task->id << endl;
                if (highest_task == NULL) {
                    //cout << "highest_task == NULL" << endl;
                    isEnd = true;
                    throw runtime_error("highest_task == NULL");
                    break;
                }
                bool success = false;
                //cout << "task id: " << highest_task->id << ", " << highest_task->isBig << endl;

				if (policy < 4) {
					// baseline and migration policy
					success = Task2Cluster(highest_task, policy);
				} else if (policy == 4) {
					// spare-core policy
					success = SpareCoreAssignment(highest_task);
				
				} else if (policy == 5) {
				    // spare-core migration policy
					success = SpareCoreAssignment(highest_task);
				}

                //if (Processor_List_big[0]->isDead) {
                //    cout << "here" << endl;
                //    cout << round << endl;
                //}

                if(!success) {
                    //cout << "Not success!" << endl;
                    //print_debugList(debugList);
                    wfile << endl;
                    wfile << endl;
                    wfile << "////////////////////// Not success! //////////////////////" << endl;
                    if (highest_task->isBig) {
                        wfile << "failed task id: " << highest_task->id << " (big task)" << endl;
                        wfile << "  ready time is:      " << highest_task->ready_time * NS << endl;
                        wfile << "  exec time is:       " << highest_task->exec_time * NS << endl;
                        //wfile << "  exec time is:       " << (double)highest_task->cycle * highest_task->delay_big * NS << endl;
                        //wfile << "  last_start_time is: " << highest_task->last_start_time_big * NS << endl;
                        wfile << "  deadline time is:   " << highest_task->deadline_time * NS << endl;
                    } else {
                        wfile << "failed task id: " << highest_task->id << " (little task)" << endl;
                        wfile << "  ready time is:      " << highest_task->ready_time * NS << endl;
                        wfile << "  exec time is:       " << highest_task->exec_time * NS << endl;
                        //wfile << "  last_start_time is: " << highest_task->last_start_time_lit * NS << endl;
                        wfile << "  deadline time is:   " << highest_task->deadline_time * NS << endl;
                    }
                    wfile << "-------------- big cluster available time --------------" << endl;
                    for(unsigned int j = 0 ; j < Processor_List_big.size() ; ++j){
                        wfile << "core " << Processor_List_big[j]->index << ": " << endl;
                        wfile << "  earliest start time: " << max(highest_task->ready_time, Processor_List_big[j]->available_time)*NS << endl;
                    }
                    wfile << "-------------- little cluster available time --------------" << endl;
                    for(unsigned int j = 0 ; j < Processor_List_lit.size() ; ++j){
                        wfile << "core " << Processor_List_lit[j]->index << ": " << endl; 
                        //wfile << "  available time: " << Processor_List_lit[j]->available_time * NS << endl;
                        wfile << "  earliest start time: " << max(highest_task->ready_time, Processor_List_lit[j]->available_time)*NS << endl;
                    }
                    wfile << "//////////////////////////////////////////////////////////" << endl;
                    wfile << "//////////////////////////////////////////////////////////" << endl;
                    int bt = 0;
                    int lt = 0;
                    for (unsigned int s=0; s<sorted_List.size(); ++s) {
                        if (sorted_List[s]->id != 0 && sorted_List[s]->id != 21) {
                            if (sorted_List[s]->isBig) {
                                bt++;
                                //wfile << "Task " << sorted_List[s]->id << ", Big task"
                            } else {
                                lt++;
                            }
                        }
                    }
                    wfile << "Big task: " << bt << endl;
                    wfile << "Lit task: " << lt << endl;
                    wfile << "//////////////////////////////////////////////////////////" << endl;
                    isEnd = true;
                    break; 
                }
                readyQuere.erase(readyQuere.begin());
            }
            //DBG << readyQuere.size() << ", " << isEnd << endl;
            //cout << endl;

            //update the simulator operate time
            operate_time = operate_time + period;

            // big core
            //update simulator's information, ex. energy and total operate time
            for (unsigned int j = 0 ; j < Processor_List_big.size() ; ++j) {
                //if (!Processor_List_big[j]->isDead) {
                    if(period > Processor_List_big[j]->available_time){
                        map<string, map<string,double> >::iterator it = idle_voltage_time_big.find(voltages_big[0]->voltage_str); 
                        map<string,double>::iterator itt = it->second.find(Processor_List_big[j]->aging_time);
                        //if aging time is exceed observation window
                        if(itt == it->second.end()){
                            throw runtime_error("impossible case: because before update NBTI");
                            //cout << "impossible case: because before update NBTI" << endl;
                        }
                        //compute idle power of each core if needed
                        double idle_power = itt->second;
                        Processor_List_big[j]->total_power =  Processor_List_big[j]->total_power + (idle_power * (period - Processor_List_big[j]->available_time) );
                    }
                    total_energy_big += Processor_List_big[j]->total_power * NS_SQ;
                    total_operate_time_big += Processor_List_big[j]->operate_time * NS;
                    Processor_List_big[j]->core_age += Processor_List_big[j]->operate_time; 


					energy_this_month +=  Processor_List_big[j]->total_power * NS_SQ;
                //}
            }  
            // little core
            for (unsigned int j = 0 ; j < Processor_List_lit.size() ; ++j) {
                //if (!Processor_List_lit[j]->isDead) {
                    if(period > Processor_List_lit[j]->available_time){
                        map<string, map<string,double> >::iterator it = idle_voltage_time_lit.find(voltages_lit[0]->voltage_str); 
                        map<string,double>::iterator itt = it->second.find(Processor_List_lit[j]->aging_time);
                        //if aging time is exceed observation window
                        if(itt == it->second.end()){
                            throw runtime_error("impossible case: because before update NBTI");
                            //cout << "impossible case: because before update NBTI" << endl;
                        }
                        //compute idle power of each core if needed
                        double idle_power = itt->second;
                        Processor_List_lit[j]->total_power =  Processor_List_lit[j]->total_power + (idle_power * (period - Processor_List_lit[j]->available_time) );
                    }
                    total_energy_lit += Processor_List_lit[j]->total_power * NS_SQ;
                    total_operate_time_lit += Processor_List_lit[j]->operate_time * NS;

					energy_this_month +=  Processor_List_lit[j]->total_power * NS_SQ;
                //}
            }

            total_energy = total_energy_big + total_energy_lit;
            total_operate_time = total_operate_time_big + total_operate_time_lit;

            //isEnd = true;
            //simulation_time =  (this->operate_time * NS) / 31536000.0;
            simulation_time = (operate_time * 31.7097919); // 31.7097919 is about to NS / 31536000
            //simulation_time = (total_operate_time/NS * 31.7097919); // 31.7097919 is about to NS / 31536000
            stringstream ss, mm;
            string int2str;
            /*
            if(simulation_time < 1){
                unsigned int j = 0;
                while(j < months.size()){ // j < 11
                  if(simulation_time < months[j]){
                    break;
                  }      
                  ++j;
                }
                ss << j;
                // month
                int2str = ss.str() + "m";
            } else {
                double tmp_simulation_time = simulation_time;
                ss << (int)simulation_time;
                while(tmp_simulation_time >= 1) {
                    tmp_simulation_time = tmp_simulation_time - 1;
                }
                unsigned int j = 0;
                while(j < months.size()){
                    if(tmp_simulation_time < months[j]){
                        break;
                    }      
                    ++j;
                }
                mm << j;
                int2str = ss.str() + "y_" + mm.str() + "m";
            }
            */
            if(simulation_time < 1){
                int j = 0;
                while(j < months.size()){ // j < 11
                  if(simulation_time < months[j]){
                    break;
                  }      
                  ++j;
                }
                if (j==12) j--;
                ss << j;

                int2str = ss.str() + "m";
            } else {
                double tmp_simulation_time = simulation_time;
                int year = tmp_simulation_time / 1;
                ss << year;
                //tmp_simulation_time = tmp_simulation_time % 1.00547945205;
                //tmp_simulation_time = fmod(tmp_simulation_time, 1);
                tmp_simulation_time = tmp_simulation_time - year;
                
                int j = 0;
                while(j < months.size()){
                    if(tmp_simulation_time < months[j]){
                        break;
                    }      
                    ++j;
                }

                if (j==12) j--;

                mm << j;

                int2str = ss.str() + "y_" + mm.str() + "m";
            }
            
            //double num_year = operate_time * NS / 31536000;


            //update simulator's information and each core's NBTI
            
            for(unsigned int j = 0 ; j < Processor_List_big.size() ; ++j){
                if( !update(Processor_List_big[j]) ) {
                    isEnd = true;
                    cout << policy_name << " :End in big cluster" << endl;
                }
            }
            for(unsigned int j = 0 ; j < Processor_List_lit.size() ; ++j){
                if( !update(Processor_List_lit[j]) ) {
                    isEnd = true;
                    //cout << "End in little cluster" << endl;
                }
            }

            if (isEnd) {//stop in timing violation or core's aging effect
                if(aging_time == ""){
                    aging_time = "0m";
                }
                print(round);

				optime_last2 = optime_last1;
				optime_last1 = total_operate_time;

				energy_last3 = energy_last2;
				energy_last2 = energy_last1;
				energy_last1 = total_energy;
				energy_last_month = energy_last2 - energy_last3;

				double power_month = (energy_last1 - energy_last2) / (optime_last1 - optime_last2);
				//month_log << aging_time << ", " << energy_this_month << ", " << power_month << ", " << (optime_last1 - optime_last2) << endl;

				energy_this_month = 0.0;

            } else if (aging_time != int2str) {

				optime_last2 = optime_last1;
				optime_last1 = total_operate_time;

				energy_last3 = energy_last2;
				energy_last2 = energy_last1;
				energy_last1 = total_energy;
				energy_last_month = energy_last2 - energy_last3;

				double power_month = (energy_last1 - energy_last2) / (optime_last1 - optime_last2);

			    //month_log << aging_time << ", " << energy_this_month << ", " << (energy_last1 - energy_last2) << ", " << power_month << ", " << (optime_last1 - optime_last2) << ", " << period << endl;

				energy_this_month = 0.0;

                aging_time = int2str;
                print(round);
            }
            // } else {
            //     aging_time = int2str;
            //     print();
            // }

            round++;

            //DBG << "****************************" << endl << endl;
        }

        // write the final lifetime
        w_policy_file << aging_time << ", " << total_operate_time_big * NS << ", " << total_energy_big << endl;
        w_policy_file << aging_time << ", " << total_operate_time_lit * NS << ", " << total_energy_lit << endl;
        w_policy_file << aging_time << ", " << total_operate_time * NS     << ", " << total_energy << endl;
        w_policy_file << aging_time << ", " << total_operate_time * NS     << ", " << energy_last_month << endl;

        DBG.close();
		month_log.close();
        w_policy_file.close();
        wfile.close();
        //cout << "iteration: " << round << endl;
        cout << policy_name << " aging time: " << aging_time << endl;
        cout << "migrate from B to L: " << mig_btol << endl;
        cout << "migrate from L to B: " << mig_ltob << endl;
        int tot = mig_btol + mig_ltob;
        cout << "(it, mig) = " << round << ", " << tot << endl;
    }
}
