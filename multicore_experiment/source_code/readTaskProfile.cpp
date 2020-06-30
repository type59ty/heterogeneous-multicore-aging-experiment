#include "readTaskProfile.h"
ReadTaskProfile::ReadTaskProfile(vector<voltage_list *> voltages_big, vector<voltage_list *> voltages_lit, vector<string > time) {
    this->voltages_big = voltages_big;
    this->voltages_lit = voltages_lit;
    this->time = time;
}
map<string, map<string,double> > ReadTaskProfile::get_idle_voltage_time() {
    return idle_voltage_time;
}

string ReadTaskProfile::Parseline(string &line) {
    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(20);
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
void ReadTaskProfile::readfile_big(char* benchmark, vector<Task *>  taskList) {
    ifstream file;
    string benchmark_name(benchmark);
    stringstream ss;
    ss << (taskList.size()-2);
    string str = ss.str();  
    string path = "benchmark_profile/" + benchmark_name + "_profile_"+ str+".csv";
    file.open(path.c_str(), ios::in);
    if(!file){
      //cout<<"Fail to open file: "<< path <<endl;
      throw runtime_error("Fail to open file:" + path);
    }
    string line("");
    getline(file, line, '\n');
    
    for(unsigned int i = 1 ; i < taskList.size() - 1; ++i){
      for(unsigned int j = 0 ; j < voltages_big.size() ; ++j){
        for(unsigned int k = 0 ; k < time.size() ; ++k ){
          while(getline(file, line, '\n')){
            if(line[0] == '#' || line.empty() ){
              continue;
            }
            else{
              break;
            }
          }
          string voltage_str = Parseline(line);//voltage
          string time_str = Parseline(line);//aged
          Parseline(line);//discard aged(second)
          string delay_str = Parseline(line);//delay
          string power_str = Parseline(line);//power
    
          Info *info = new Info();
          info->delay_big = atof(delay_str.c_str());
          info->avg_power_big = atof(power_str.c_str());
          if(taskList[i]->delay_big > info->delay_big){
            taskList[i]->delay_big = info->delay_big;
          }  
          map<string, map<string, Info*> >::iterator it;
          it = taskList[i]->map_voltage_time_big.find(voltage_str);
          if(it == taskList[i]->map_voltage_time_big.end() ){
            map<string, Info*> map_time;
            map_time.insert(pair<string, Info*>(time_str, info));
            taskList[i]->map_voltage_time_big.insert(pair<string, map<string, Info*> >(voltage_str, map_time) ); 
          }
          else{//find
            it->second.insert(pair<string, Info*>(time_str, info));
          }
        }
      }
    }

    // idle task
    for(unsigned int i = 0 ; i < voltages_big.size() ; ++i){
      for(unsigned int j = 0 ; j < time.size() ; ++j){
        while(getline(file, line, '\n')){
          if(line[0] == '#' || line.empty() ){
            continue;
          }
          else{
            break;
          }
        }
        string voltage_str = Parseline(line);//voltage
        string time_str = Parseline(line);//aged
        Parseline(line);//discard
        string power_str = Parseline(line);//power
        double idle_power = atof(power_str.c_str());
        map<string, map<string, double> >::iterator it;
        it = idle_voltage_time.find(voltage_str);
        if(it == idle_voltage_time.end() ){
          map<string, double> map_idle;
          map_idle.insert(pair<string, double>(time_str, idle_power));
          idle_voltage_time.insert(pair<string, map<string, double> >(voltage_str, map_idle) );         
        }
        else{//find
          it->second.insert(pair<string, double>(time_str, idle_power));
        }
      }
    }
    file.close();
}

void ReadTaskProfile::readfile_lit(char* benchmark, vector<Task *>  taskList){
    ifstream file;
    string benchmark_name(benchmark);
    stringstream ss;
    ss << (taskList.size()-2);
    string str = ss.str();  
    string path = "benchmark_profile/" + benchmark_name + "_profile_"+ str+".csv";
    file.open(path.c_str(), ios::in);
    if(!file){
      //cout<<"Fail to open file: "<< path <<endl;
      throw runtime_error("Fail to open file:" + path);
    }
    string line("");
    getline(file, line, '\n');
    
    for(unsigned int i = 1 ; i < taskList.size() - 1; ++i){
      for(unsigned int j = 0 ; j < voltages_lit.size() ; ++j){
        for(unsigned int k = 0 ; k < time.size() ; ++k ){
          while(getline(file, line, '\n')){
            if(line[0] == '#' || line.empty() ){
              continue;
            }
            else{
              break;
            }
          }
          string voltage_str = Parseline(line);//voltage
          string time_str = Parseline(line);//aged
          Parseline(line);//discard aged(second)
          string delay_str = Parseline(line);//delay
          string power_str = Parseline(line);//power
    
          Info *info = new Info();
          info->delay_lit = atof(delay_str.c_str());
          info->avg_power_lit = atof(power_str.c_str());
          if(taskList[i]->delay_lit > info->delay_lit){
            taskList[i]->delay_lit = info->delay_lit;
          }  
          map<string, map<string, Info*> >::iterator it;
          it = taskList[i]->map_voltage_time_lit.find(voltage_str);
          if(it == taskList[i]->map_voltage_time_lit.end() ){
            map<string, Info*> map_time;
            map_time.insert(pair<string, Info*>(time_str, info));
            taskList[i]->map_voltage_time_lit.insert(pair<string, map<string, Info*> >(voltage_str, map_time) ); 
          }
          else{//find
            it->second.insert(pair<string, Info*>(time_str, info));
          }
        }
      }
    }

    // idle task
    for(unsigned int i = 0 ; i < voltages_lit.size() ; ++i){
      for(unsigned int j = 0 ; j < time.size() ; ++j){
        while(getline(file, line, '\n')){
          if(line[0] == '#' || line.empty() ){
            continue;
          }
          else{
            break;
          }
        }
        string voltage_str = Parseline(line);//voltage
        string time_str = Parseline(line);//aged
        Parseline(line);//discard
        string power_str = Parseline(line);//power
        double idle_power = atof(power_str.c_str());
        map<string, map<string, double> >::iterator it;
        it = idle_voltage_time.find(voltage_str);
        if(it == idle_voltage_time.end() ){
          map<string, double> map_idle;
          map_idle.insert(pair<string, double>(time_str, idle_power));
          idle_voltage_time.insert(pair<string, map<string, double> >(voltage_str, map_idle) );         
        }
        else{//find
          it->second.insert(pair<string, double>(time_str, idle_power));
        }
      }
    }
    file.close();
}
