#include <iostream>
#include <vector>
using namespace std;

struct  Distance
{
    int previous_data;
    double cost;
};
typedef struct Distance Distance;

std::vector<int> FindSolutioin(std::vector<int> data, double metric){
    int size = data.size();
    Distance solutions[size];
    for(int i=0; i<size; i++){
        solutions[i].cost = 10000000; //initiate cost to be large at each point
    }
    solutions[0].cost = 0; 
    solutions[0].previous_data = 0;

    for(int i=0; i<size; i++){   
        for(int j= i-1; j>=0; j--){
            double currentCost = solutions[j].cost + std::abs(std::abs(data[i]-data[j])-metric);
            if (currentCost<solutions[i].cost){
                solutions[i].previous_data = j;
                solutions[i].cost = currentCost;
            }
        }
    }
    vector<int> selected_points_index;
    int i= size-1;
    selected_points_index.push_back(i);//always select last
    while (solutions[i].previous_data != 0)
    {
        i = solutions[i].previous_data;
        selected_points_index.push_back(i);
    }
    selected_points_index.push_back(0);//always select first
    return selected_points_index;
}

std::vector<int> REMOVE(std::vector<int> data){// this function can probably be merged into FindSolutioin yet need to think more.
    double distance_min = 10000.0;
    int index =0;
    for(int i=0; i < data.size(); i++){
        for(int j= i-1; j>=0; j--){
            double distance = abs(data[i] -data[j]);
            if(distance<distance_min){
                index = i;
                distance_min = distance;
            }
        }
    }
    if(index == 0){//if minimal happens around 0, remove 1
        data.erase(data.begin()+1);
    }
    else if(index == data.size()-1){//if minimal happens around last, remove last-1
        data.erase(data.begin()+data.size()-2);
    }
    else
    data.erase(data.begin()+index);
    return data;
}

void DeepProgram()
{
    std::vector<int> data = {0,1,1,1,1,1,1,1,2,3,4,5,6,7,8,9,10,11,12,13,14,33,50,66,100,101,102};
    int num_sel;
    cout << "Choose how many data points to select: " << endl;
    cin >> num_sel; 

    int size = data.size();
    int range = data[data.size()-1] - data[0];
    double metric = range/(double)(num_sel-1);
    std::vector<int> result =  FindSolutioin(data,metric);
    while(result.size() < num_sel){//refine metric, need to think more here about half its size
        metric = metric/2 ;
        result = FindSolutioin(data,metric);
    }

    std::vector<int> newdata;
    for (int i = 0; i<result.size(); i++){
        newdata.push_back(data[result[i]]);
    }
    std::reverse(newdata.begin(),newdata.end());

    while(newdata.size()>num_sel){//remove a data that is most close to each other
        newdata = REMOVE(newdata);
    }

    cout << "---------------------- RESUTL --------------------" << endl;
    for (int i = 0; i < newdata.size(); i++){
       cout << newdata[i] << " ";
    }
    cout << " " << endl;
}