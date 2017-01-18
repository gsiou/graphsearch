#include "graph.h"
#include "query_array.h"
#include "job_scheduler.h"

#include <iostream>
#include <stdio.h>
#include <cstdlib>
#define STATIC
//#define DYNAMIC

int main(){
#ifdef STATIC
    StaticGraph graph;
    QueryArray qarr(5000, 5000);
    int line = 0;
    int myChar;
    uint32_t from, to;
    int queries = 0;

    while(1){
        //std::cin.get(myChar);
        myChar = getc(stdin);
        if(myChar == 'S'){
            break;            
        }
        else{
            //std::cin.putback(myChar);
            ungetc(myChar, stdin);
            scanf("%u %u\n", &from, &to);
            //std::cout << "Adding " << from << " " << to << std::endl;
            graph.add(from, to);
        }
    }
    
    while(1){
        myChar = getc(stdin);
        if(myChar == 'F'){
            qarr.addBurst(line);
        }
        else if(myChar == EOF){
            break;
        }
        else if(myChar == 'Q'){
            scanf("%u %u\n", &from, &to);
            queries++;
            //std::cout << "Query " << from << " " << to << std::endl;
            //std::cout << graph.query(from, to) << std::endl;
            qarr.addQuery(from, to, line, 0);
        }
        else if(myChar == 'A'){
            scanf("%u %u\n", &from, &to);
            //graph.add(from, to);
        }
        line++;
    }

    JobScheduler *scheduler = new JobScheduler(&qarr, &graph);
    scheduler->parallelQueryExecution();

    /*

    QueryData* qd;
    for(int i = 0; i < queries; i++){
        qd = qarr.getQuery(i);
        std::cout << qd->queryFrom << " " << qd->queryTo << std::endl;
    }
    */
#endif
}