/**
 * This sample program shows how TReX will respond to an attack on the system, simulated by the burn() function
 */

#include "app.h"
#include <stdlib.h>

SYSTIM tim;
ID badid;

const T_CALM pk_calm;

void burn(int time) {
    SYSTIM prev, now;
    get_tim(&now);
    prev = now;
    int count=0;
    while(count < time) {
        while(prev == now){
            get_tim(&now);
        }
        count++;
        prev=now;
    }
}


// a cyclic handler to activate a task
void task_activator(intptr_t tskid) {
    ER ercd = act_tsk(tskid);
    assert(ercd == E_OK);
}

char run_log[1000];
int idx=0;

// a periodic task 
void periodic_task_1(intptr_t unused) {
	del_alm(badid);	
	run_log[idx++]='1';
	foo();
	del_alm(badid);
	burn(100);
	trex_start_alarm(3);

}

// a periodic task 
void periodic_task_2(intptr_t unused) {
	del_alm(badid);	
	run_log[idx++]='2';
	burn(500);
	trex_start_alarm(3);
}

void foo(void){
	RELTIM tm = 20;
	trex_start_alarm(tm);
	burn(110); //delay return by 110 ms
}

void main_task(intptr_t unused) {
	badid = 1;
	ev3_sta_cyc(CYC_PRD_TSK_1);
	tslp_tsk(50);
	ev3_sta_cyc(CYC_PRD_TSK_2);
	tslp_tsk(4000);
	ev3_stp_cyc(CYC_PRD_TSK_1);
	ev3_stp_cyc(CYC_PRD_TSK_2);
	run_log[idx] = '\0';
	printf("log = %s\n", run_log);
}
