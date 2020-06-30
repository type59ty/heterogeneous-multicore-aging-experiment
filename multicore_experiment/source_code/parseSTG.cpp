#include "parseSTG.h"
vector<vector<Task *> > ParseSTG::get_list(){
  return List;
}
string ParseSTG::parse_line(string &line){
    string token("");
    string::size_type  index = 0;
    while(line.size() > 0){
        if((line[index] >= '0' && line[index] <= '9')){
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
void ParseSTG::start_parse(char *file_name){
    ifstream file;
    file.open(file_name, ios::in);
    for(int p = 0 ; p < 1 ; p++){
        List.push_back(vector<Task *>() );
        int exec_counter(0);
        //ifstream file(file_name, ios::in);
        string line("");
        getline(file, line, '\n');
        int num_task = atoi(line.c_str());
        num_task+=2;
        for(int i = 0 ; i < num_task ; ++i){
            Task *task = new Task();
            List.back().push_back(task);
        }
        for(int i = 0 ; i < num_task; ++i){
            getline(file, line, '\n');
            Task *task = List.back().at(i);
            task->id = atoi(parse_line(line).c_str());
            task->cycle = atoi(parse_line(line).c_str());
            exec_counter += task->cycle;
            task->num_pre = atoi(parse_line(line).c_str());
            task->num_pre_backup = task->num_pre;
            for(int j = 0 ; j < task->num_pre ; ++j){
                int pre_id = atoi(parse_line(line).c_str());
                task->pre.push_back(List.back().at(pre_id) );
                List.back().at(pre_id)->next.push_back(task);
                List.back().at(pre_id)->map_next.insert(pair<int, Task *>(task->id, task));
            }
        } 
    }
    file.close();
}
