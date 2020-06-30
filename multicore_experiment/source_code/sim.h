#ifndef SIM
#define SIM
#include <vector>
#include <queue>
#include "read_mt.h"
#include "task.h"
#include <iostream>
#include <cmath>
#include <time.h>
#include <stdexcept>
#include "getTaskProfile.h"
#include <sys/stat.h>
using namespace std;

class DebugInfo{
public:
  int id;
  int proc_index;
  string aging_time;
  double ready_time;
  double last_start_time;
  double deadline_time;
  double voltage;
  double delay;
  double dynamic_power;
  double exec_time;
  double finish_time;
  double Energy_t; 
private:
};

class Processor{
public:
  unsigned int index;
  double available_time;
  double operate_time;
  double core_age;
  double idle_time;
  double ori_vth;
  double vth;
  double delta_vth;
  string aging_time; 
  double total_power;
  bool isProtect;
  bool isDead;
private:
};

class backupTaskInfo{
public:
  int id;
  bool isCritical;
  double deadline_time;
  double ratio;
  double period;
  unsigned int overlap_counter;
private:
};

class TaskInfo{
public:
  double slack;
  double isAgingSlack;
  double exec_time;
  double cost;
  double dynamic_power;
  double delay;
  double Energy_d;//dynamic
  double Energy_i;//idle
  double Energy_t;//total
  voltage_list v;
  unsigned int proc_index;
  Processor *proc;
  double earliest_start_time;
  double ready_time;
  double dl_idle_energy;
private:
}; 

class Sim{
public:
  void reset();
  vector<Task *> readyQuere;
  Task * highPriorityTask();
  void computeLastStartTime(Task* task);
  void ADA_computeLastStartTime(Task* task);
  vector<DebugInfo> debugList;
  void print_debugList(vector<DebugInfo> &debugList);
  Sim(vector<Task *> task_list, int num_processor_big,  int num_processor_lit, map<string, map<string,double> >& idle_voltage_time_big, map<string, map<string,double> >& idle_voltage_time_lit, 
         vector<voltage_list *>& voltages_big, vector<voltage_list *>& voltages_lit, double critical_ratio, double nonCritical_ratio, vector<vector<unsigned int> > &critical_list);
  void topological_ordering();
  void start_map(char *benchmark_name_big, char *benchmark_name_lit, int policy);
  void fix_taskgraph(string str_benchmark_name_big, string str_benchmark_name_lit, int policy);
  void random_taskgraph(string str_benchmark_name, int policy);
  void set_process_vth(Processor *, string time);
  bool checkFull(Task *task, string cluster);
  double checkWaittime(Task *task);
  bool ListAssignment(Task *task);
  bool SpareCoreAssignment(Task *task);
  bool isMigrate(Task *task);
  bool Task2Cluster(Task *task, int policy);
  bool Task2BigCore(Task *task);
  bool Sym_Task2BigCore(Task *task);
  bool Task2LitCore(Task *task);
  bool VariationAwareTaskToCoreAssignment(Task *task);
  void setDeadline(vector<unsigned int> &);
  bool update(Processor *core);
  double operate_time;
  string aging_time;
  double gamma;
  double period;
  //unsigned int counter;
  fstream wfile, w_policy_file, vth_file;
  //ofstream DBG;
  double vth_counter;
  bool isOpen;
  void protected_core(vector<TaskInfo > &solutions, Task *task);
  void check_slack(vector<TaskInfo > &solutions, Task *task);
  void write_file(string policy);
  void reScheduling();
  void ratioRelease(Task *task, Task *pre_task, double ratio);
  unsigned int checkCriticalOverlap();
  double simulation_time;
  void parse_vth();
  void compute_delta_vth(Processor *, string voltage, double exec_time);
  double tmp_compute_delta_vth(Processor *, string voltage, double exec_time);
  void print(int round);
  map<string, double> vths;
  double Vth_max_big;
  double Vth_max_lit;
  double Vth_min_big;
  double Vth_min_lit;
  double get_Vth_max(string core_type);
  double get_Vth_min(string core_type);
  double get_protect_Vth_max();
  double get_protect_Vth_min();
  string Parseline(string &line);
  //vector<vector<Task *> > List;
  vector<Task *> task_list;
  vector<double > months;
  vector<voltage_list * > voltages_big;
  vector<voltage_list * > voltages_lit;
  map<string, map<string,double> > idle_voltage_time_big;
  map<string, map<string,double> > idle_voltage_time_lit;
  vector<Task *> sorted_List;
  
  vector<Task *> critical_List;  
  vector<vector<Task * > > critical_couple_list;
  map<int, vector<Task *> > overlap_task_map;
  vector<Task *> overlap_task_list;
  
  vector<Processor *> Processor_List_big;
  vector<Processor *> Processor_List_lit;
  double total_energy_big;
  double total_energy_lit;
  double total_energy;
  double total_operate_time_big;
  double total_operate_time_lit;
  double total_operate_time;
  unsigned int overlap_counter;
  bool isRescheduling;
  bool isAsymmetric;
  vector<vector<unsigned int> > critical_list;//input
  double critical_ratio;
  double nonCritical_ratio;

  int mig_btol;
  int mig_ltob;
  bool no_migration;
};
#endif
