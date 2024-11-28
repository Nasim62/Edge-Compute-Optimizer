#include<bits/stdc++.h>
//#include<iostream>
//#include<stdio.h>
//#include<unistd.h>
//#include<sys/types.h>
//#include<string.h>
//#include<map>
//#include<fstream>
#define PEER_PD 5
#define PARENT_PD 10
#define HUB_TO_LEAF_RTT 4
#define CENTRALIZED_RTT 40
using namespace std;

struct computation_spot {
    struct computation_spot *par;
    struct computation_spot *left_peer;
    struct computation_spot *right_peer;
    struct computation_spot *left_child;
    struct computation_spot *right_child;
    int req_count;
    set<int> active_pool;
    vector<pair<int,int>>hit;
    vector<pair<int,int>>miss;
    vector<vector<int>>request_queue;
    vector<pair<int,int>>service_count;
    unordered_map<int,vector<vector<int>>>m;
     computation_spot( )
    {
        par = NULL;
        left_peer=NULL;
        right_peer=NULL;
        left_child=NULL;
        right_child=NULL;
        req_count=0;
    }
};
int c_s=0;
int p_s=0;
int d_s=0;
void intial_provisioning(computation_spot* root,int x,int y){
	int counter=0;
    for(int i=x;i<y;++i){
    	counter++;
        root->active_pool.insert(i);
        if(counter==150)
        break;
    }
}
void assign_parents(vector<computation_spot*>& all_cs) {
    all_cs[0]->par = all_cs[14];
    all_cs[1]->par = all_cs[14];
    all_cs[2]->par = all_cs[15];
    all_cs[3]->par = all_cs[15];
    all_cs[4]->par = all_cs[16];
    all_cs[5]->par = all_cs[16];
    all_cs[6]->par = all_cs[17];
    all_cs[7]->par = all_cs[17];
    all_cs[8]->par = all_cs[18];
    all_cs[9]->par = all_cs[18];
    all_cs[10]->par = all_cs[19];
    all_cs[11]->par = all_cs[19];
    all_cs[12]->par = all_cs[20];
    all_cs[13]->par = all_cs[20];
    all_cs[14]->par = all_cs[21];
    all_cs[15]->par = all_cs[21];
    all_cs[16]->par = all_cs[22];
    all_cs[17]->par = all_cs[22];
    all_cs[18]->par = all_cs[23];
    all_cs[19]->par = all_cs[23];
    all_cs[20]->par = all_cs[24];
    all_cs[21]->par = all_cs[24];
    all_cs[22]->par = all_cs[25];
    all_cs[23]->par = all_cs[25];
    all_cs[24]->par = all_cs[26];
    all_cs[25]->par = all_cs[26];
    all_cs[26]->par = all_cs[27];
    all_cs[27]->par = all_cs[28];

    //---------------------------------------------------------------//
    all_cs[14]->left_child = all_cs[0];
    all_cs[14]->right_child = all_cs[1];
    all_cs[15]->left_child = all_cs[2];
    all_cs[15]->right_child = all_cs[3];
    all_cs[16]->left_child = all_cs[4];
    all_cs[16]->right_child = all_cs[5];
    all_cs[17]->left_child = all_cs[6];
    all_cs[17]->right_child = all_cs[7];
    all_cs[18]->left_child = all_cs[8];
    all_cs[18]->right_child = all_cs[9];
    all_cs[19]->left_child = all_cs[10];
    all_cs[19]->right_child = all_cs[11];
    all_cs[20]->left_child = all_cs[12];
    all_cs[20]->right_child = all_cs[13];
    all_cs[21]->left_child = all_cs[14];
    all_cs[21]->right_child = all_cs[15];
    all_cs[22]->left_child = all_cs[16];
    all_cs[22]->right_child = all_cs[17];
    all_cs[23]->left_child = all_cs[18];
    all_cs[23]->right_child = all_cs[19];
    all_cs[24]->left_child = all_cs[20];
    all_cs[24]->right_child = all_cs[21];
    all_cs[25]->left_child = all_cs[22];
    all_cs[25]->right_child = all_cs[23];
    all_cs[26]->left_child = all_cs[24];
    all_cs[26]->right_child = all_cs[25];
    all_cs[27]->left_child = all_cs[26];
    all_cs[27]->right_child = all_cs[27];
}


//---------------------------------------------------------------------//
bool sort_by_sec_hit(const pair<int,int> &a,
              const pair<int,int> &b)
{
    return (a.second < b.second);
}
bool sort_by_sec_miss(const pair<int,int> &a,
              const pair<int,int> &b)
{
    return (a.second > b.second);
}
//---------------------------------------------------------------------//
bool sort_by_sec(const pair<int,int> &a,
              const pair<int,int> &b)
{
    return (a.second > b.second);
}

vector<vector<int>> pd
    {
        {0,5,1000,1000,1000,1000,1000,1000,10,15,1000,1000,20,25},
        {5,0,5,1000,1000,1000,1000,1000,10,15,1000,1000,20,25},
        {1000,5,0,5,1000,1000,1000,1000,15,10,15,1000,20,25},
        {1000,1000,5,0,5,1000,1000,1000,15,10,15,1000,20,25},
        {1000,1000,1000,5,0,5,1000,1000,1000,15,10,15,25,20},
        {1000,1000,1000,1000,5,0,5,1000,1000,15,10,15,25,20},
        {1000,1000,1000,1000,1000,5,0,5,1000,1000,15,10,25,20},
        {1000,1000,1000,1000,1000,1000,5,0,1000,1000,15,10,25,20},
        {10,10,15,15,1000,1000,1000,1000,0,5,1000,1000,10,15},
        {15,15,10,10,15,15,1000,1000,5,0,5,1000,10,15},
        {1000,1000,15,15,10,10,15,15,1000,5,0,5,15,10},
        {1000,1000,1000,1000,15,15,10,10,1000,1000,5,0,15,10},
        {20,20,20,20,25,25,25,25,10,10,15,15,0,5},
        {25,25,25,25,20,20,20,20,15,15,10,10,5,0}
    };
//-------------------------------------------Decentralized strategy-----------------------------------------------//
void de_periodic_provisioning(computation_spot* root,int&oh){
    	root->req_count=0;
    for(int i=0;i<150;++i){
    	if(root->active_pool.size()>=1)
    	root->active_pool.erase(root->active_pool.begin());
    	else
    	break;
	}
    int c=0;
    sort(root->service_count.begin(),root->service_count.end(),sort_by_sec);
    for(int i=0;i<root->service_count.size() && c<150;++i){
        root->active_pool.insert(root->service_count[i].first);
        c++;
    }  
}

void de_request_distribution(computation_spot* root,vector<int>req,int &hit_count,int &miss_count){

     int absolute_deadline,arrival_time,deadline,leaf_computation_spot,service_type;
     absolute_deadline=req[0];
     arrival_time=req[1];
     deadline=req[2];
     leaf_computation_spot=req[3];
     service_type=req[4];


    if(!root)
    {
        miss_count++;
        return ;
    }
    root->req_count++;
    root->m[service_type].push_back(req);
   //Managing records of requests that i.e. number of requests for same service type
    bool flag2=false;
    for(int k=0;k<root->service_count.size();++k){
         	if(root->service_count[k].first==service_type){
         		root->service_count[k].second=root->service_count[k].second+1;
         		flag2=true;
         		break;
			 }
		 }
		 if(flag2==false){
		 	root->service_count.push_back({service_type,1});
		 }


    if((root->active_pool).find(service_type)!=(root->active_pool).end()){
        root->request_queue.push_back(req);
    }
    else{
           req[0]=req[0]-PARENT_PD;
           de_request_distribution(root->par,req,hit_count,miss_count);
    }
}
void decentralized_approach(int n){
     vector<computation_spot*> all_cs(14);

    for(int i=0;i<14;++i){
        computation_spot* root=new computation_spot();
        all_cs[i]=root;
    }

    assign_parents(all_cs);

     int hit_count=0;
     int miss_count=0;
     int oh=0;

    for(int i=0;i<=7;++i)
        intial_provisioning(all_cs[i],0,150);

    for(int i=8;i<=11;++i)
        intial_provisioning(all_cs[i],150,300);

    for(int i=12;i<=13;++i)
        intial_provisioning(all_cs[i],300,450);



     ifstream ip("dataset.txt",ios::in);

    vector<vector<int>> data(n,vector<int>(5,0));

    for(int i=0;i<n;++i){
        ip>>data[i][1];
        ip>>data[i][2];
        ip>>data[i][3];
        ip>>data[i][4];
        data[i][0]=data[i][1]+data[i][2];
    }

    //Sorting data on the basis of absolute deadline
    sort(data.begin(),data.end());

    //Distributing requests among computation spots
    for(int i=0;i<n;++i){
        data[i][0]= data[i][0]-HUB_TO_LEAF_RTT;
        de_request_distribution(all_cs[data[i][3]],data[i],hit_count,miss_count);
    }

    for(int i=0;i<14;++i){
        for(auto it:all_cs[i]->active_pool){
            vector<vector<int>>service_queue;
            for(int k=0;k<all_cs[i]->request_queue.size();++k){
                if((all_cs[i]->request_queue[k][4])==it)
                    service_queue.push_back(all_cs[i]->request_queue[k]);
            }

             vector<vector<int>>ready_queue;
            for(int arrival_time=0;arrival_time<=99;++arrival_time){
                for(int k=0;k<service_queue.size();++k){
                    if(service_queue[k][1]==arrival_time)
                        ready_queue.push_back(service_queue[k]);
                }
                sort(ready_queue.begin(),ready_queue.end());
                //considering that we have enough computation power to process tasks in one time interval
                for(auto j=0;j<ready_queue.size();++j){
                    if(ready_queue[j][0]-pd[i][ready_queue[j][3]]>=j+1){
                        hit_count++;
                        ready_queue.erase(ready_queue.begin()+j);
                        j--;
                       // break;
                    }
                }
            }
            miss_count+=ready_queue.size();

        }
    }
  
    for(int i=0;i<14;++i){
        de_periodic_provisioning(all_cs[i],oh);
    }

    cout<<"Total no. of req = "<<n<<endl;
    cout<<"Total no. of Hit = "<<hit_count<<endl;
    cout<<"Total no. of Miss = "<<miss_count<<endl;
    cout<<"oh= "<<oh<<endl;


    //Distributing requests among computation spots
 for(int iteration=1;iteration<=1;++iteration){
    srand(time(0));
   	ofstream of2("dataset2.txt",ios::out);
    for(int i=0;i<n;++i){
       //Burst Time = 1 Time Slot
       
       if(i<n/6){
       	int x= rand();
       int arrival_time= ((x)%100);
       int deadline=((x)%157)+5;
       int leaf_computation_spot=(x)%8;
       int service_type=(x)%1000;

       of2 << arrival_time <<" " << deadline <<" " << leaf_computation_spot << " " << service_type << endl;
       continue;
	   }
       
       int x= rand();
       int arrival_time= ((rand())%100);
       int deadline=((rand())%157)+5;
       int leaf_computation_spot=(rand())%8;
       int service_type=(rand())%1000;

       of2 << arrival_time <<" " << deadline <<" " << leaf_computation_spot << " " << service_type << endl;
    }
   of2.close();    
  
    hit_count=0;
    miss_count=0;
    
    vector<unordered_map<int,vector<vector<int>>>>v(14);
    vector<vector<int>> data2;//(n,vector<int>(5,0));
    for(int i=0;i<14;++i){
        all_cs[i]->request_queue.clear();
        all_cs[i]->service_count.clear();
        v[i]=all_cs[i]->m;
        all_cs[i]->m.clear();
    }
    
    for(int i=0;i<8;++i){
    	 unordered_map<int,vector<vector<int>>>m2=v[i];
        for(auto j : m2){
        	int s=floor(((j.second.size())*0)/100);
        	d_s +=s;
        	for(int k=0;k<s;++k){
        		data2.push_back((j.second)[k]);
			}
		}
    }
    //cout<<endl<<d_s<<endl;
    //cout<<n-d_s<<endl;
    
    
    ifstream ip2("dataset2.txt",ios::in);
    srand(time(0));
    vector<int>v2{0,0,0,0,0};
    for(int i=d_s;i<n;++i){
	data2.push_back(v2);	
	}
    for(int i=d_s;i<n;++i){
    	int x;
        ip2>>x;
		data2[i][1]=x;
        ip2>>x;
		data2[i][2]=x;
        ip2>>x;
		data2[i][3]=x;
        ip2>>x;
		data2[i][4]=x;
        data2[i][0]=data2[i][1]+data2[i][2];
    } 
    sort(data2.begin(),data2.end());
    for(int i=0;i<n;++i){
        data2[i][0]= data2[i][0]-HUB_TO_LEAF_RTT;
        de_request_distribution(all_cs[data2[i][3]],data2[i],hit_count,miss_count);
    }
    d_s=0;

    for(int i=0;i<14;++i){
        for(auto it:all_cs[i]->active_pool){
            vector<vector<int>>service_queue;
            for(int k=0;k<all_cs[i]->request_queue.size();++k){
                if((all_cs[i]->request_queue[k][4])==it)
                    service_queue.push_back(all_cs[i]->request_queue[k]);
            }

             vector<vector<int>>ready_queue;
            for(int arrival_time=0;arrival_time<=99;++arrival_time){
                for(int k=0;k<service_queue.size();++k){
                    if(service_queue[k][1]==arrival_time)
                        ready_queue.push_back(service_queue[k]);
                }
                sort(ready_queue.begin(),ready_queue.end());
                //considering that we have enough computation power to process tasks in one time interval
                for(auto j=0;j<ready_queue.size();++j){
                    if(ready_queue[j][0]-pd[i][ready_queue[j][3]]>=j+1){
                        hit_count++;
                        ready_queue.erase(ready_queue.begin()+j);
                        j--;
                       // break;
                    }
                }
            }
            miss_count+=ready_queue.size();

        }
    }
    for(int i=0;i<14;++i){
        de_periodic_provisioning(all_cs[i],oh);
    }
 }


    cout<<"Total no. of req = "<<n<<endl;
    cout<<"Total no. of Hit = "<<hit_count<<endl;
    cout<<"Total no. of Miss = "<<miss_count<<endl;
    cout<<"oh= "<<oh<<endl;
 


}




//---------------------------------------------Completely_Centralized-------------------------------------------------------------------//

void c_periodic_provisioning(computation_spot* root,int&oh){
    root->req_count=0;
    for(int i=0;i<150;++i){
    	if(root->active_pool.size()>=1)
    	root->active_pool.erase(root->active_pool.begin());
    	else
    	break;
	}
    int c=0;
    sort(root->service_count.begin(),root->service_count.end(),sort_by_sec);
    for(int i=0;i<root->service_count.size() && c<150;++i){
        root->active_pool.insert(root->service_count[i].first);
        c++;
    }  
  
}

void c_request_distribution( vector<computation_spot*>& all_cs,vector<int>req){

     int absolute_deadline,arrival_time,deadline,leaf_computation_spot,service_type;
     absolute_deadline=req[0];
     arrival_time=req[1];
     deadline=req[2];
     leaf_computation_spot=req[3];
     service_type=req[4];

    for(int i=0;i<all_cs.size();++i){
    	computation_spot* root=all_cs[i];
        if((all_cs[i])->active_pool.find(service_type)!=(all_cs[i])->active_pool.end()){
         	bool flag2=false;
    
         	for(int k=0;k<root->service_count.size();++k){
         		if(root->service_count[k].first==service_type){
         			root->service_count[k].second=root->service_count[k].second+1;
         			flag2=true;
         			break;
			 	}
		 	}
		 	if(flag2==false){
		 		root->service_count.push_back({service_type,1});
		 	}
			(all_cs[i])->request_queue.push_back(req);
            break;
        }
    }
}
void completely_centralized_approach(int n ){

    vector<computation_spot*> all_cs(14);

    for(int i=0;i<14;++i){
        computation_spot* root=new computation_spot();
        all_cs[i]=root;
    }

    assign_parents(all_cs);

     int hit_count=0;
     int miss_count=0;
     int oh=0;

    intial_provisioning(all_cs[0],0,150);
    intial_provisioning(all_cs[1],150,300);
    intial_provisioning(all_cs[2],300,450);
    intial_provisioning(all_cs[3],450,600);
    intial_provisioning(all_cs[4],600,750);
    intial_provisioning(all_cs[5],750,900);
    intial_provisioning(all_cs[6],850,1000);
    intial_provisioning(all_cs[7],0,150);
    intial_provisioning(all_cs[8],300,450);
    intial_provisioning(all_cs[9],0,150);
    intial_provisioning(all_cs[10],300,450);
    intial_provisioning(all_cs[11],150,300);
    intial_provisioning(all_cs[12],600,750);
    intial_provisioning(all_cs[13],450,600);


    ifstream ip("dataset.txt",ios::in);

    vector<vector<int>> data(n,vector<int>(5,0));

    for(int i=0;i<n;++i){
        ip>>data[i][1];
        ip>>data[i][2];
        ip>>data[i][3];
        ip>>data[i][4];
        data[i][0]=data[i][1]+data[i][2];
    }

    //Sorting data on the basis of absolute deadline
    sort(data.begin(),data.end());

    for(int i=0;i<n;++i){
        data[i][0]=data[i][0] - CENTRALIZED_RTT ;
        c_request_distribution(all_cs,data[i]);
    }

    for(int i=0;i<14;++i){
        for(int k=0;k<all_cs[i]->request_queue.size();++k){
             if((all_cs[i]->request_queue[k][0])>=0)
                 hit_count++;
             else
                miss_count++;
        }
    }


    cout<<"Total no. of req = "<<n<<endl;
    cout<<"Total no. of Hit = "<<hit_count<<endl;
    cout<<"Total no. of Miss = "<<miss_count<<endl;
   // cout<<"oh = "<<oh<<endl;

}

//-------------------------------------------------------------- Co-ordinated Approach --------------------------------------------------------------------//
void co_periodic_provisioning(computation_spot* root,int&oh){
	root->req_count=0;
    for(int i=0;i<150;++i){
    	if(root->active_pool.size()>=1)
    	root->active_pool.erase(root->active_pool.begin());
    	else
    	break;
	}
    int c=0;
    sort(root->service_count.begin(),root->service_count.end(),sort_by_sec);
    for(int i=0;i<root->service_count.size() && c<150;++i){
    	if(root->left_child && (root->left_child->active_pool.find(root->service_count[i].first)!=root->left_child->active_pool.end()))
    	continue;
    	if(root->right_child && (root->right_child->active_pool.find(root->service_count[i].first)!=root->right_child->active_pool.end()))
    	continue;
        root->active_pool.insert(root->service_count[i].first);
        c++;
    }
   
}
void co_request_distribution(computation_spot* root,vector<int>req,int &hit_count,int &miss_count){

     int absolute_deadline,arrival_time,deadline,leaf_computation_spot,service_type;
     absolute_deadline=req[0];
     arrival_time=req[1];
     deadline=req[2];
     leaf_computation_spot=req[3];
     service_type=req[4];
     
    if(!root)
    {
        miss_count++;
        return ;
    }

    root->req_count++;
    root->m[service_type].push_back(req);
    
     //Managing records of requests that i.e. number of requests for same service type
    bool flag2=false;
    
         for(int k=0;k<root->service_count.size();++k){
         	if(root->service_count[k].first==service_type){
         		root->service_count[k].second=root->service_count[k].second+1;
         		flag2=true;
         		break;
			 }
		 }
		 if(flag2==false){
		 	root->service_count.push_back({service_type,1});
		 }


    if((root->active_pool).find(service_type)!=(root->active_pool).end()){
        root->request_queue.push_back(req);
    }
    else{
        req[0]=req[0]-PARENT_PD;
        co_request_distribution(root->par,req,hit_count,miss_count);
    }
}
void coordinated_approach(int n){
     vector<computation_spot*> all_cs(14);

    for(int i=0;i<14;++i){
        computation_spot* root=new computation_spot();
        all_cs[i]=root;
    }

    assign_parents(all_cs);

     int hit_count=0;
     int miss_count=0;
     int oh=0;



    for(int i=0;i<=7;++i)
        intial_provisioning(all_cs[i],0,150);

    for(int i=8;i<=11;++i)
        intial_provisioning(all_cs[i],150,300);

    for(int i=12;i<=13;++i)
        intial_provisioning(all_cs[i],300,450);


    vector<vector<int>> data(n,vector<int>(5,0));
    ifstream ip("dataset.txt",ios::in);
    for(int i=0;i<n;++i){
        ip>>data[i][1];
        ip>>data[i][2];
        ip>>data[i][3];
        ip>>data[i][4];
        data[i][0]=data[i][1]+data[i][2];
    }
   

    //Sorting data on the basis of absolute deadline
    sort(data.begin(),data.end());

    //Distributing requests among computation spots
    for(int i=0;i<n;++i){
        data[i][0]= data[i][0]-HUB_TO_LEAF_RTT;
        co_request_distribution(all_cs[data[i][3]],data[i],hit_count,miss_count);
    }
    /*ofstream of6("Before_Provisioning_test.txt",ios::out);
    for(int i=0;i<8;++i){
    	 
    	 of6<<endl<<endl<<endl;
    	 of6<<"computation spot"<<i+1<<endl;
        for(auto j : all_cs[i]->service_count){
        	of6<<"service type = "<<j.first<<"  number of reqs = "<<j.second<<endl;
		}
    }*/
    for(int i=0;i<14;++i){
        for(auto it:all_cs[i]->active_pool){
            vector<vector<int>>service_queue;
            for(int k=0;k<all_cs[i]->request_queue.size();++k){
                if((all_cs[i]->request_queue[k][4])==it)
                    service_queue.push_back(all_cs[i]->request_queue[k]);
            }

             vector<vector<int>>ready_queue;
            for(int arrival_time=0;arrival_time<=99;++arrival_time){
                for(int k=0;k<service_queue.size();++k){
                    if(service_queue[k][1]==arrival_time)
                        ready_queue.push_back(service_queue[k]);
                }
                sort(ready_queue.begin(),ready_queue.end());
                //considering that we have enough computation power to process tasks in one time interval
                for(auto j=0;j<ready_queue.size();++j){
                    if(ready_queue[j][0]-pd[i][ready_queue[j][3]]>=j+1){
                        hit_count++;
                        ready_queue.erase(ready_queue.begin()+j);
                        j--;
                       // break;
                    }
                }
            }
            miss_count+=ready_queue.size();

        }
    }
  
    

    cout<<"Total no. of req = "<<n<<endl;
    cout<<"Total no. of Hit = "<<hit_count<<endl;
    cout<<"Total no. of Miss = "<<miss_count<<endl;
    cout<<"oh= "<<oh<<endl;
    
    
    for(int i=0;i<14;++i){
        co_periodic_provisioning(all_cs[i],oh);
    }

    //------------------------------------------------------------//
      //Distributing requests among computation spots
 for(int iteration=1;iteration<=10;++iteration){
 	srand(time(0));
   	ofstream of2("dataset2.txt",ios::out);
    for(int i=0;i<n;++i){
       //Burst Time = 1 Time Slot
       
       if(i<n/6){
       	int x= rand();
       int arrival_time= ((x)%100);
       int deadline=((x)%157)+5;
       int leaf_computation_spot=(x)%8;
       int service_type=(x)%1000;

       of2 << arrival_time <<" " << deadline <<" " << leaf_computation_spot << " " << service_type << endl;
       continue;
	   }
       
       int x= rand();
       int arrival_time= ((rand())%100);
       int deadline=((rand())%157)+5;
       int leaf_computation_spot=(rand())%8;
       int service_type=(rand())%1000;

       of2 << arrival_time <<" " << deadline <<" " << leaf_computation_spot << " " << service_type << endl;
    }
   of2.close();
	
    hit_count=0;
    miss_count=0;
    
    
    vector<unordered_map<int,vector<vector<int>>>>v(14);
    vector<vector<int>> data2;//(n,vector<int>(5,0));
    for(int i=0;i<14;++i){
        all_cs[i]->request_queue.clear();
        all_cs[i]->service_count.clear();
        v[i]=all_cs[i]->m;
        all_cs[i]->m.clear();
    }

    for(int i=0;i<8;++i){
    	unordered_map<int,vector<vector<int>>>m2=v[i];
        for(auto j : m2){
        	int s=floor(((j.second.size())*0)/100);
        	c_s +=s;
        	for(int k=0;k<s;++k){
        		data2.push_back((j.second)[k]);
			}
		}
    }
    //cout<<endl<<c_s<<endl;
    //cout<<n-c_s<<endl;
    
    
    ifstream ip2("dataset2.txt",ios::in);
    srand(time(0));
    vector<int>v2{0,0,0,0,0};
    for(int i=c_s;i<n;++i){
	data2.push_back(v2);	
	}
    for(int i=c_s;i<n;++i){
    	int x;
        ip2>>x;
		data2[i][1]=x;
        ip2>>x;
		data2[i][2]=x;
        ip2>>x;
		data2[i][3]=x;
        ip2>>x;
		data2[i][4]=x;
        data2[i][0]=data2[i][1]+data2[i][2];
    } 
    sort(data2.begin(),data2.end());
    for(int i=0;i<n;++i){
        data2[i][0]= data2[i][0]-HUB_TO_LEAF_RTT;
        co_request_distribution(all_cs[data2[i][3]],data2[i],hit_count,miss_count);
    }
   /* ofstream of7("After_Provisioning_test.txt",ios::out);
    for(int i=0;i<8;++i){
    	 //map<int,vector<vector<int>>>m2=v[i];
    	 of7<<"computation spot"<<i+1<<endl;
        //int x=m2.size();
        for(auto j : all_cs[i]->m){
        	of7<<"service type = "<<j.first<<"  number of reqs = "<<j.second.size()<<endl;
		}
    }*/
    c_s=0;
    for(int i=0;i<14;++i){
        for(auto it:all_cs[i]->active_pool){
            vector<vector<int>>service_queue;
            for(int k=0;k<all_cs[i]->request_queue.size();++k){
                if((all_cs[i]->request_queue[k][4])==it)
                    service_queue.push_back(all_cs[i]->request_queue[k]);
            }

             vector<vector<int>>ready_queue;
            for(int arrival_time=0;arrival_time<=99;++arrival_time){
                for(int k=0;k<service_queue.size();++k){
                    if(service_queue[k][1]==arrival_time)
                        ready_queue.push_back(service_queue[k]);
                }
                sort(ready_queue.begin(),ready_queue.end());
                //considering that we have enough computation power to process tasks in one time interval
                for(auto j=0;j<ready_queue.size();++j){
                    if(ready_queue[j][0]-pd[i][ready_queue[j][3]]>=j+1){
                        hit_count++;
                        ready_queue.erase(ready_queue.begin()+j);
                        j--;
                       // break;
                    }
                }
            }
            miss_count+=ready_queue.size();

        }
    }
    for(int i=0;i<14;++i){
        co_periodic_provisioning(all_cs[i],oh);
    }
 }


    cout<<"Total no. of req = "<<n<<endl;
    cout<<"Total no. of Hit = "<<hit_count<<endl;
    cout<<"Total no. of Miss = "<<miss_count<<endl;
    cout<<"oh= "<<oh<<endl;
}

//----------------------------------------------------------------- Proposed Approach -----------------------------------------------------------------------//



//---------------------------------------------------//
void pro_request_distribution(computation_spot* root,vector<int>req,int &hit_count,int &miss_count){
	int absolute_deadline,arrival_time,deadline,leaf_computation_spot,service_type;
     absolute_deadline=req[0];
     arrival_time=req[1];
     deadline=req[2];
     leaf_computation_spot=req[3];
     service_type=req[4];


    if(!root)
    {
        miss_count++;
        return ;
    }

    root->req_count++;
    root->m[service_type].push_back(req);
     //Managing records of requests that i.e. number of requests for same service type
    bool flag2=false;
   	for(int k=0;k<root->service_count.size();++k){
         	if(root->service_count[k].first==service_type){
         		root->service_count[k].second=root->service_count[k].second+1;
         		flag2=true;
         		break;
			 }
		 }
		 if(flag2==false){
		 	root->service_count.push_back({service_type,1});
		 }

    if((root->active_pool).find(service_type)!=(root->active_pool).end()){
        root->request_queue.push_back(req);
    }
    else{
        if(root->left_peer && root->left_peer->active_pool.find(service_type)!= root->left_peer->active_pool.end()){
            req[0]=req[0]- PEER_PD;
            pro_request_distribution(root->left_peer,req,hit_count,miss_count);
        }
        else if(root->right_peer && root->right_peer->active_pool.find(service_type)!=root->right_peer->active_pool.end()){
            req[0]=req[0]- PEER_PD;
            pro_request_distribution(root->right_peer,req,hit_count,miss_count);
        }
        else{
           req[0]=req[0]- PARENT_PD;
           pro_request_distribution(root->par,req,hit_count,miss_count);
        }
    }
}

//---------------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------------//
void pro_periodic_provisioning1(computation_spot* root, int& oh) {
    root->req_count = 0;
    
    for (int i = 0; i < 120; ++i) {
        if (root->active_pool.size() >= 1)
            root->active_pool.erase(root->active_pool.begin());
        else
            break;
    }
    
    int c = 0;
    sort(root->service_count.begin(), root->service_count.end(), sort_by_sec_miss);
    
    for (int i = 0; i < root->service_count.size() && c < 120; ++i) {
        if (root->left_peer && (root->left_peer->active_pool.find(root->service_count[i].first) != root->left_peer->active_pool.end()))
            continue;
        if (root->left_child && (root->left_child->active_pool.find(root->service_count[i].first) != root->left_child->active_pool.end()))
            continue;
        if (root->right_child && (root->right_child->active_pool.find(root->service_count[i].first) != root->right_child->active_pool.end()))
            continue;
        
        root->active_pool.insert(root->service_count[i].first);
        c++;
    }
  
    // Additional modifications to increase hit rate
    sort(root->service_count.begin(), root->service_count.end(), sort_by_sec_miss);
    
    for (int i = 0; i < root->service_count.size() && c < 120; ++i) {
        if (root->left_peer && (root->left_peer->active_pool.find(root->service_count[i].first) != root->left_peer->active_pool.end()))
            continue;
        if (root->left_child && (root->left_child->active_pool.find(root->service_count[i].first) != root->left_child->active_pool.end()))
            continue;
        if (root->right_child && (root->right_child->active_pool.find(root->service_count[i].first) != root->right_child->active_pool.end()))
            continue;
        
        root->active_pool.insert(root->service_count[i].first);
        c++;
    }
}

 void proposed_approach1(int n){
     vector<computation_spot*> all_cs(14);

    for(int i=0;i<14;++i){
        computation_spot* root=new computation_spot();
        all_cs[i]=root;
    }

    assign_parents(all_cs);

     int hit_count=0;
     int miss_count=0;
     int oh=0;

        all_cs[0]->right_peer=all_cs[1];

        all_cs[1]->left_peer=all_cs[0];
        all_cs[1]->right_peer=all_cs[2];

        all_cs[2]->left_peer=all_cs[1];
        all_cs[2]->right_peer=all_cs[3];

        all_cs[3]->left_peer=all_cs[2];
        all_cs[3]->right_peer=all_cs[4];

        all_cs[4]->left_peer=all_cs[3];
        all_cs[4]->right_peer=all_cs[5];

        all_cs[5]->left_peer=all_cs[4];
        all_cs[5]->right_peer=all_cs[6];

        all_cs[6]->left_peer=all_cs[5];
        all_cs[6]->right_peer=all_cs[7];

        all_cs[7]->left_peer=all_cs[6];

        all_cs[8]->right_peer=all_cs[9];

        all_cs[9]->left_peer=all_cs[8];
        all_cs[9]->right_peer=all_cs[10];

        all_cs[10]->left_peer=all_cs[9];
        all_cs[10]->right_peer=all_cs[11];

        all_cs[11]->left_peer=all_cs[10];

        all_cs[12]->right_peer=all_cs[13];

        all_cs[13]->right_peer=all_cs[12];

        /* intial_provisioning(all_cs[0],0,150);
         intial_provisioning(all_cs[1],150,300);
         intial_provisioning(all_cs[2],300,450);
         intial_provisioning(all_cs[3],0,150);
         intial_provisioning(all_cs[4],150,300);
         intial_provisioning(all_cs[5],300,450);
         intial_provisioning(all_cs[6],0,150);
         intial_provisioning(all_cs[7],150,300);


         intial_provisioning(all_cs[8],450,600);
         intial_provisioning(all_cs[9],600,750);
         intial_provisioning(all_cs[10],750,900);
         intial_provisioning(all_cs[11],900,1000);

          intial_provisioning(all_cs[12],750,900);
          intial_provisioning(all_cs[13],450,600); 
          
          
         intial_provisioning(all_cs[0],0,100);
         intial_provisioning(all_cs[1],100,200);
         intial_provisioning(all_cs[2],200,300);
         intial_provisioning(all_cs[3],0,100);
         intial_provisioning(all_cs[4],100,200);
         intial_provisioning(all_cs[5],200,300);
         intial_provisioning(all_cs[6],0,100);
         intial_provisioning(all_cs[7],100,200);


         intial_provisioning(all_cs[8],300,400);
         intial_provisioning(all_cs[9],400,500);
         intial_provisioning(all_cs[10],500,600);
         intial_provisioning(all_cs[11],600,700);

          intial_provisioning(all_cs[12],600,700);
          intial_provisioning(all_cs[13],700,800);
          
        /* intial_provisioning(all_cs[0],0,125);
         intial_provisioning(all_cs[1],125,250);
         intial_provisioning(all_cs[2],250,375);
         intial_provisioning(all_cs[3],0,125);
         intial_provisioning(all_cs[4],125,250);
         intial_provisioning(all_cs[5],250,375);
         intial_provisioning(all_cs[6],0,125);
         intial_provisioning(all_cs[7],125,250);


         intial_provisioning(all_cs[8],375,500);
         intial_provisioning(all_cs[9],500,625);
         intial_provisioning(all_cs[10],625,750);
         intial_provisioning(all_cs[11],750,875);

          intial_provisioning(all_cs[12],750,875);
          intial_provisioning(all_cs[13],875,1000);*/
    

    vector<vector<int>> data(n,vector<int>(5,0));
    ifstream ip("dataset.txt",ios::in);
    for(int i=0;i<n;++i){
        ip>>data[i][1];
        ip>>data[i][2];
        ip>>data[i][3];
        ip>>data[i][4];
        data[i][0]=data[i][1]+data[i][2];
    }
     
    
    //Sorting data on the basis of absolute deadline
    sort(data.begin(),data.end());

    //Distributing requests among computation spots
    for(int i=0;i<n;++i){
        data[i][0]= data[i][0] - HUB_TO_LEAF_RTT;
        pro_request_distribution(all_cs[data[i][3]],data[i],hit_count,miss_count);
    }
    
    ofstream of6("Before_Provisioning_test_proposed.txt",ios::out);
    for(int i=0;i<8;++i){
    	 of6<<endl<<endl<<endl;
    	 of6<<"computation spot"<<i+1<<endl;
        for(auto j : all_cs[i]->service_count){
        	of6<<"service type = "<<j.first<<"  number of reqs = "<<j.second<<endl;
		}
    }
    
    
    for(int i=0;i<14;++i){
        for(auto it:all_cs[i]->active_pool){
            vector<vector<int>>service_queue;
            for(int k=0;k<all_cs[i]->request_queue.size();++k){
                if((all_cs[i]->request_queue[k][4])==it)
                    service_queue.push_back(all_cs[i]->request_queue[k]);
            }
            vector<vector<int>>ready_queue;
            for(int arrival_time=0;arrival_time<=99;++arrival_time){
                for(int k=0;k<service_queue.size();++k){
                    if(service_queue[k][1]==arrival_time)
                        ready_queue.push_back(service_queue[k]);
                }
                sort(ready_queue.begin(),ready_queue.end());
                //considering that we have enough computation power to process tasks in one time interval
                for(auto j=0;j<ready_queue.size();++j){
                    if(ready_queue[j][0]-pd[i][ready_queue[j][3]]>=j+1){
                        hit_count++;
                        ready_queue.erase(ready_queue.begin()+j);
                        j--;
                       // break;
                    }
                }
            }
            miss_count+=ready_queue.size();
        }
    }
  
    

    cout<<"Total no. of req = "<<n<<endl;
    cout<<"Total no. of Hit = "<<hit_count<<endl;
    cout<<"Total no. of Miss = "<<miss_count<<endl;
    cout<<"oh= "<<oh<<endl;
    
    for(int i=0;i<14;++i){
        pro_periodic_provisioning1(all_cs[i],oh);
    }
    
   //------------------------------------------------------------//
      //Distributing requests among computation spots
  for(int iteration=1;iteration<=5;++iteration){
    srand(time(0));
   	ofstream of2("dataset2.txt",ios::out);
    for(int i=0;i<n;++i){
       //Burst Time = 1 Time Slot
       
       if(i<n/6){
       	int x= rand();
       int arrival_time= ((x)%100);
       int deadline=((x)%157)+5;
       int leaf_computation_spot=(x)%8;
       int service_type=(x)%1000;

       of2 << arrival_time <<" " << deadline <<" " << leaf_computation_spot << " " << service_type << endl;
       continue;
	   }
       
       int x= rand();
       int arrival_time= ((rand())%100);
       int deadline=((rand())%157)+5;
       int leaf_computation_spot=(rand())%8;
       int service_type=(rand())%1000;

       of2 << arrival_time <<" " << deadline <<" " << leaf_computation_spot << " " << service_type << endl;
    }
   of2.close(); 
      
    hit_count=0;
    miss_count=0;
    vector<unordered_map<int,vector<vector<int>>>>v(14);
    vector<vector<int>> data2;//(n,vector<int>(5,0));
    for(int i=0;i<14;++i){
        all_cs[i]->request_queue.clear();
        all_cs[i]->service_count.clear();
        v[i]=all_cs[i]->m;
        all_cs[i]->m.clear();
    }
    for(int i=0;i<8;++i){
    	unordered_map<int,vector<vector<int>>>m2=v[i];
        for(auto j : m2){
        	int s=floor(((j.second.size())*0)/100);
        	p_s +=s;
        	for(int k=0;k<s;++k){
        		data2.push_back((j.second)[k]);
			}
		}
	}
	//cout<<endl<<p_s<<endl;
    //cout<<n-p_s<<endl;
    
    
    ifstream ip2("dataset2.txt",ios::in);
    srand(time(0));
    vector<int>v2{0,0,0,0,0};
    for(int i=p_s;i<n;++i){
	data2.push_back(v2);	
	}
    for(int i=p_s;i<n;++i){
    	int x;
        ip2>>x;
		data2[i][1]=x;
        ip2>>x;
		data2[i][2]=x;
        ip2>>x;
		data2[i][3]=x;
        ip2>>x;
		data2[i][4]=x;
        data2[i][0]=data2[i][1]+data2[i][2];
    } 
    sort(data2.begin(),data2.end());
    
    for(int i=0;i<n;++i){
        data2[i][0]= data2[i][0]-HUB_TO_LEAF_RTT;
        pro_request_distribution(all_cs[data2[i][3]],data2[i],hit_count,miss_count);
    }
    
    p_s=0;
    
    for(int i=0;i<14;++i){
        for(auto it:all_cs[i]->active_pool){
            vector<vector<int>>service_queue;
            for(int k=0;k<all_cs[i]->request_queue.size();++k){
                if((all_cs[i]->request_queue[k][4])==it)
                    service_queue.push_back(all_cs[i]->request_queue[k]);
            }

             vector<vector<int>>ready_queue;
            for(int arrival_time=0;arrival_time<=99;++arrival_time){
                for(int k=0;k<service_queue.size();++k){
                    if(service_queue[k][1]==arrival_time)
                        ready_queue.push_back(service_queue[k]);
                }
                sort(ready_queue.begin(),ready_queue.end());
                //considering that we have enough computation power to process tasks in one time interval
                for(auto j=0;j<ready_queue.size();++j){
                    if(ready_queue[j][0]-pd[i][ready_queue[j][3]]>=j+1){
                        hit_count++;
                        ready_queue.erase(ready_queue.begin()+j);
                        j--;
                       // break;
                    }
                }
            }
            miss_count+=ready_queue.size();

        }
    } 
    for(int i=0;i<14;++i){
        pro_periodic_provisioning1(all_cs[i],oh);
    }
 }

    cout<<"Total no. of req = "<<n<<endl;
    cout<<"Total no. of Hit = "<<hit_count<<endl;
    cout<<"Total no. of Miss = "<<miss_count<<endl;
    cout<<"oh= "<<oh<<endl;
}
//---------------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------------//
void pro_periodic_provisioning2(computation_spot* root,int&oh){
	root->req_count=0;
   for(int i=0;i<120;++i){
   	    if(root->active_pool.size()>=1)
    	root->active_pool.erase(root->active_pool.begin());
    	else
    	break;
	}
    int c=0;
    sort(root->service_count.begin(),root->service_count.end(),sort_by_sec);
    for(int i=0;i<root->service_count.size() && c<120;++i){
    	if(root->left_peer && (root->left_peer->active_pool.find(root->service_count[i].first)!=root->left_peer->active_pool.end()))
    	continue;
    	if(root->left_child && (root->left_child->active_pool.find(root->service_count[i].first)!=root->left_child->active_pool.end()))
    	continue;
    	if(root->right_child && (root->right_child->active_pool.find(root->service_count[i].first)!=root->right_child->active_pool.end()))
    	continue;
        root->active_pool.insert(root->service_count[i].first);
        c++;
    }
  
}

void proposed_approach2(int n){
     vector<computation_spot*> all_cs(14);

    for(int i=0;i<14;++i){
        computation_spot* root=new computation_spot();
        all_cs[i]=root;
    }

    assign_parents(all_cs);

     int hit_count=0;
     int miss_count=0;
     int oh=0;

        all_cs[0]->right_peer=all_cs[1];

        all_cs[1]->left_peer=all_cs[0];
        all_cs[1]->right_peer=all_cs[2];

        all_cs[2]->left_peer=all_cs[1];
        all_cs[2]->right_peer=all_cs[3];

        all_cs[3]->left_peer=all_cs[2];
        all_cs[3]->right_peer=all_cs[4];

        all_cs[4]->left_peer=all_cs[3];
        all_cs[4]->right_peer=all_cs[5];

        all_cs[5]->left_peer=all_cs[4];
        all_cs[5]->right_peer=all_cs[6];

        all_cs[6]->left_peer=all_cs[5];
        all_cs[6]->right_peer=all_cs[7];

        all_cs[7]->left_peer=all_cs[6];

        all_cs[8]->right_peer=all_cs[9];

        all_cs[9]->left_peer=all_cs[8];
        all_cs[9]->right_peer=all_cs[10];

        all_cs[10]->left_peer=all_cs[9];
        all_cs[10]->right_peer=all_cs[11];

        all_cs[11]->left_peer=all_cs[10];

        all_cs[12]->right_peer=all_cs[13];

        all_cs[13]->right_peer=all_cs[12];

        /* intial_provisioning(all_cs[0],0,150);
         intial_provisioning(all_cs[1],150,300);
         intial_provisioning(all_cs[2],300,450);
         intial_provisioning(all_cs[3],0,150);
         intial_provisioning(all_cs[4],150,300);
         intial_provisioning(all_cs[5],300,450);
         intial_provisioning(all_cs[6],0,150);
         intial_provisioning(all_cs[7],150,300);


         intial_provisioning(all_cs[8],450,600);
         intial_provisioning(all_cs[9],600,750);
         intial_provisioning(all_cs[10],750,900);
         intial_provisioning(all_cs[11],900,1000);

          intial_provisioning(all_cs[12],750,900);
          intial_provisioning(all_cs[13],450,600); */
          
         /* 
         intial_provisioning(all_cs[0],0,100);
         intial_provisioning(all_cs[1],100,200);
         intial_provisioning(all_cs[2],200,300);
         intial_provisioning(all_cs[3],0,100);
         intial_provisioning(all_cs[4],100,200);
         intial_provisioning(all_cs[5],200,300);
         intial_provisioning(all_cs[6],0,100);
         intial_provisioning(all_cs[7],100,200);


         intial_provisioning(all_cs[8],300,400);
         intial_provisioning(all_cs[9],400,500);
         intial_provisioning(all_cs[10],500,600);
         intial_provisioning(all_cs[11],600,700);

          intial_provisioning(all_cs[12],600,700);
          intial_provisioning(all_cs[13],700,800);*/
          
        /* intial_provisioning(all_cs[0],0,125);
         intial_provisioning(all_cs[1],125,250);
         intial_provisioning(all_cs[2],250,375);
         intial_provisioning(all_cs[3],0,125);
         intial_provisioning(all_cs[4],125,250);
         intial_provisioning(all_cs[5],250,375);
         intial_provisioning(all_cs[6],0,125);
         intial_provisioning(all_cs[7],125,250);


         intial_provisioning(all_cs[8],375,500);
         intial_provisioning(all_cs[9],500,625);
         intial_provisioning(all_cs[10],625,750);
         intial_provisioning(all_cs[11],750,875);

          intial_provisioning(all_cs[12],750,875);
          intial_provisioning(all_cs[13],875,1000);*/
         intial_provisioning(all_cs[0],0,120);
         intial_provisioning(all_cs[1],120,240);
         intial_provisioning(all_cs[2],240,360);
         intial_provisioning(all_cs[3],0,120);
         intial_provisioning(all_cs[4],120,240);
         intial_provisioning(all_cs[5],240,360);
         intial_provisioning(all_cs[6],0,120);
         intial_provisioning(all_cs[7],120,240);


         intial_provisioning(all_cs[8],360,480);
         intial_provisioning(all_cs[9],480,600);
         intial_provisioning(all_cs[10],600,720);
         intial_provisioning(all_cs[11],720,840);

          intial_provisioning(all_cs[12],720,840);
          intial_provisioning(all_cs[13],840,960);
    

    vector<vector<int>> data(n,vector<int>(5,0));
    ifstream ip("dataset.txt",ios::in);
    for(int i=0;i<n;++i){
        ip>>data[i][1];
        ip>>data[i][2];
        ip>>data[i][3];
        ip>>data[i][4];
        data[i][0]=data[i][1]+data[i][2];
    }
     
    
    //Sorting data on the basis of absolute deadline
    sort(data.begin(),data.end());

    //Distributing requests among computation spots
    for(int i=0;i<n;++i){
        data[i][0]= data[i][0] - HUB_TO_LEAF_RTT;
        pro_request_distribution(all_cs[data[i][3]],data[i],hit_count,miss_count);
    }
    
    ofstream of6("Before_Provisioning_test_proposed.txt",ios::out);
    for(int i=0;i<8;++i){
    	 of6<<endl<<endl<<endl;
    	 of6<<"computation spot"<<i+1<<endl;
        for(auto j : all_cs[i]->service_count){
        	of6<<"service type = "<<j.first<<"  number of reqs = "<<j.second<<endl;
		}
    }
    
    
    for(int i=0;i<14;++i){
        for(auto it:all_cs[i]->active_pool){
            vector<vector<int>>service_queue;
            for(int k=0;k<all_cs[i]->request_queue.size();++k){
                if((all_cs[i]->request_queue[k][4])==it)
                    service_queue.push_back(all_cs[i]->request_queue[k]);
            }
            vector<vector<int>>ready_queue;
            for(int arrival_time=0;arrival_time<=99;++arrival_time){
                for(int k=0;k<service_queue.size();++k){
                    if(service_queue[k][1]==arrival_time)
                        ready_queue.push_back(service_queue[k]);
                }
                sort(ready_queue.begin(),ready_queue.end());
                //considering that we have enough computation power to process tasks in one time interval
                for(auto j=0;j<ready_queue.size();++j){
                    if(ready_queue[j][0]-pd[i][ready_queue[j][3]]>=j+1){
                        hit_count++;
                        ready_queue.erase(ready_queue.begin()+j);
                        j--;
                       // break;
                    }
                }
            }
            miss_count+=ready_queue.size();
        }
    }
  
    

    cout<<"Total no. of req = "<<n<<endl;
    cout<<"Total no. of Hit = "<<hit_count<<endl;
    cout<<"Total no. of Miss = "<<miss_count<<endl;
    cout<<"oh= "<<oh<<endl;
    
    for(int i=0;i<14;++i){
        pro_periodic_provisioning2(all_cs[i],oh);
    }
    
   //------------------------------------------------------------//
      //Distributing requests among computation spots
  for(int iteration=1;iteration<=5;++iteration){
    srand(time(0));
   	ofstream of2("dataset2.txt",ios::out);
    for(int i=0;i<n;++i){
       //Burst Time = 1 Time Slot
       
       if(i<n/6){
       	int x= rand();
       int arrival_time= ((x)%100);
       int deadline=((x)%157)+5;
       int leaf_computation_spot=(x)%8;
       int service_type=(x)%1000;

       of2 << arrival_time <<" " << deadline <<" " << leaf_computation_spot << " " << service_type << endl;
       continue;
	   }
       
       int x= rand();
       int arrival_time= ((rand())%100);
       int deadline=((rand())%157)+5;
       int leaf_computation_spot=(rand())%8;
       int service_type=(rand())%1000;

       of2 << arrival_time <<" " << deadline <<" " << leaf_computation_spot << " " << service_type << endl;
    }
   of2.close(); 
      
    hit_count=0;
    miss_count=0;
    vector<unordered_map<int,vector<vector<int>>>>v(14);
    vector<vector<int>> data2;//(n,vector<int>(5,0));
    for(int i=0;i<14;++i){
        all_cs[i]->request_queue.clear();
        all_cs[i]->service_count.clear();
        v[i]=all_cs[i]->m;
        all_cs[i]->m.clear();
    }
    for(int i=0;i<8;++i){
    	unordered_map<int,vector<vector<int>>>m2=v[i];
        for(auto j : m2){
        	int s=floor(((j.second.size())*0)/100);
        	p_s +=s;
        	for(int k=0;k<s;++k){
        		data2.push_back((j.second)[k]);
			}
		}
	}
	//cout<<endl<<p_s<<endl;
    //cout<<n-p_s<<endl;
    
    
    ifstream ip2("dataset2.txt",ios::in);
    srand(time(0));
    vector<int>v2{0,0,0,0,0};
    for(int i=p_s;i<n;++i){
	data2.push_back(v2);	
	}
    for(int i=p_s;i<n;++i){
    	int x;
        ip2>>x;
		data2[i][1]=x;
        ip2>>x;
		data2[i][2]=x;
        ip2>>x;
		data2[i][3]=x;
        ip2>>x;
		data2[i][4]=x;
        data2[i][0]=data2[i][1]+data2[i][2];
    } 
    sort(data2.begin(),data2.end());
    
    for(int i=0;i<n;++i){
        data2[i][0]= data2[i][0]-HUB_TO_LEAF_RTT;
        pro_request_distribution(all_cs[data2[i][3]],data2[i],hit_count,miss_count);
    }
    
    p_s=0;
    
    for(int i=0;i<14;++i){
        for(auto it:all_cs[i]->active_pool){
            vector<vector<int>>service_queue;
            for(int k=0;k<all_cs[i]->request_queue.size();++k){
                if((all_cs[i]->request_queue[k][4])==it)
                    service_queue.push_back(all_cs[i]->request_queue[k]);
            }

             vector<vector<int>>ready_queue;
            for(int arrival_time=0;arrival_time<=99;++arrival_time){
                for(int k=0;k<service_queue.size();++k){
                    if(service_queue[k][1]==arrival_time)
                        ready_queue.push_back(service_queue[k]);
                }
                sort(ready_queue.begin(),ready_queue.end());
                //considering that we have enough computation power to process tasks in one time interval
                for(auto j=0;j<ready_queue.size();++j){
                    if(ready_queue[j][0]-pd[i][ready_queue[j][3]]>=j+1){
                        hit_count++;
                        ready_queue.erase(ready_queue.begin()+j);
                        j--;
                       // break;
                    }
                }
            }
            miss_count+=ready_queue.size();

        }
    } 
    for(int i=0;i<14;++i){
        pro_periodic_provisioning2(all_cs[i],oh);
    }
 }

    cout<<"Total no. of req = "<<n<<endl;
    cout<<"Total no. of Hit = "<<hit_count<<endl;
    cout<<"Total no. of Miss = "<<miss_count<<endl;
    cout<<"oh= "<<oh<<endl;

}
//---------------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------------//
void pro_periodic_provisioning3(computation_spot* root,int&oh){
	root->req_count=0;
   for(int i=0;i<120;++i){
   	    if(root->active_pool.size()>=1)
    	root->active_pool.erase(root->active_pool.begin());
    	else
    	break;
	}
    int c=0;
    sort(root->service_count.begin(),root->service_count.end(),sort_by_sec);
    for(int i=0;i<root->service_count.size() && c<120;++i){
    	if(root->left_peer && (root->left_peer->active_pool.find(root->service_count[i].first)!=root->left_peer->active_pool.end()))
    	continue;
    	if(root->left_child && (root->left_child->active_pool.find(root->service_count[i].first)!=root->left_child->active_pool.end()))
    	continue;
    	if(root->right_child && (root->right_child->active_pool.find(root->service_count[i].first)!=root->right_child->active_pool.end()))
    	continue;
        root->active_pool.insert(root->service_count[i].first);
        c++;
    }
  
}



/* void pro_periodic_provisioning3(computation_spot* root, int& oh) { //our approach 
    // Clear the active pool
    root->active_pool.clear();

    // Sort the service count in descending order
    sort(root->service_count.begin(), root->service_count.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second;
    });
    // Add services to the active pool based on availability and demand
    for (const auto& service : root->service_count) {
        const int serviceType = service.first;

        // Check if the service is active in the peers or children
        bool isServiceActive = false;
        if (root->left_peer && root->left_peer->active_pool.count(serviceType)) {
            isServiceActive = true;
        } else if (root->left_child && root->left_child->active_pool.count(serviceType)) {
            isServiceActive = true;
        } else if (root->right_child && root->right_child->active_pool.count(serviceType)) {
            isServiceActive = true;
        }

        // If the service is not active, add it to the active pool
        if (!isServiceActive) {
            root->active_pool.insert(serviceType);
        }
    }
}*/

void proposed_approach3(int n){
     vector<computation_spot*> all_cs(14);

    for(int i=0;i<14;++i){
        computation_spot* root=new computation_spot();
        all_cs[i]=root;
    }

    assign_parents(all_cs);

     int hit_count=0;
     int miss_count=0;
     int oh=0;

        all_cs[0]->right_peer=all_cs[1];

        all_cs[1]->left_peer=all_cs[0];
        all_cs[1]->right_peer=all_cs[2];

        all_cs[2]->left_peer=all_cs[1];
        all_cs[2]->right_peer=all_cs[3];

        all_cs[3]->left_peer=all_cs[2];
        all_cs[3]->right_peer=all_cs[4];

        all_cs[4]->left_peer=all_cs[3];
        all_cs[4]->right_peer=all_cs[5];

        all_cs[5]->left_peer=all_cs[4];
        all_cs[5]->right_peer=all_cs[6];

        all_cs[6]->left_peer=all_cs[5];
        all_cs[6]->right_peer=all_cs[7];

        all_cs[7]->left_peer=all_cs[6];

        all_cs[8]->right_peer=all_cs[9];

        all_cs[9]->left_peer=all_cs[8];
        all_cs[9]->right_peer=all_cs[10];

        all_cs[10]->left_peer=all_cs[9];
        all_cs[10]->right_peer=all_cs[11];

        all_cs[11]->left_peer=all_cs[10];

        all_cs[12]->right_peer=all_cs[13];

        all_cs[13]->right_peer=all_cs[12];

         intial_provisioning(all_cs[0],0,150);
         intial_provisioning(all_cs[1],150,300);
         intial_provisioning(all_cs[2],300,450);
         intial_provisioning(all_cs[3],0,150);
         intial_provisioning(all_cs[4],150,300);
         intial_provisioning(all_cs[5],300,450);
         intial_provisioning(all_cs[6],0,150);
         intial_provisioning(all_cs[7],150,300);


         intial_provisioning(all_cs[8],450,600);
         intial_provisioning(all_cs[9],600,750);
         intial_provisioning(all_cs[10],750,900);
         intial_provisioning(all_cs[11],900,1000);

          intial_provisioning(all_cs[12],750,900);
          intial_provisioning(all_cs[13],450,600); 
          
        /*  
         intial_provisioning(all_cs[0],0,100);
         intial_provisioning(all_cs[1],100,200);
         intial_provisioning(all_cs[2],200,300);
         intial_provisioning(all_cs[3],0,100);
         intial_provisioning(all_cs[4],100,200);
         intial_provisioning(all_cs[5],200,300);
         intial_provisioning(all_cs[6],0,100);
         intial_provisioning(all_cs[7],100,200);


         intial_provisioning(all_cs[8],300,400);
         intial_provisioning(all_cs[9],400,500);
         intial_provisioning(all_cs[10],500,600);
         intial_provisioning(all_cs[11],600,700);

          intial_provisioning(all_cs[12],600,700);
          intial_provisioning(all_cs[13],700,800);*/
          
         /*intial_provisioning(all_cs[0],0,125);
         intial_provisioning(all_cs[1],125,250);
         intial_provisioning(all_cs[2],250,375);
         intial_provisioning(all_cs[3],0,125);
         intial_provisioning(all_cs[4],125,250);
         intial_provisioning(all_cs[5],250,375);
         intial_provisioning(all_cs[6],0,125);
         intial_provisioning(all_cs[7],125,250);


         intial_provisioning(all_cs[8],375,500);
         intial_provisioning(all_cs[9],500,625);
         intial_provisioning(all_cs[10],625,750);
         intial_provisioning(all_cs[11],750,875);

          intial_provisioning(all_cs[12],750,875);
          intial_provisioning(all_cs[13],875,1000);*/
    

    vector<vector<int>> data(n,vector<int>(5,0));
    ifstream ip("dataset.txt",ios::in);
    for(int i=0;i<n;++i){
        ip>>data[i][1];
        ip>>data[i][2];
        ip>>data[i][3];
        ip>>data[i][4];
        data[i][0]=data[i][1]+data[i][2];
    }
     
    
    //Sorting data on the basis of absolute deadline
    sort(data.begin(),data.end());

    //Distributing requests among computation spots
    for(int i=0;i<n;++i){
        data[i][0]= data[i][0] - HUB_TO_LEAF_RTT;
        pro_request_distribution(all_cs[data[i][3]],data[i],hit_count,miss_count);
    }
    
    ofstream of6("Before_Provisioning_test_proposed.txt",ios::out);
    for(int i=0;i<8;++i){
    	 of6<<endl<<endl<<endl;
    	 of6<<"computation spot"<<i+1<<endl;
        for(auto j : all_cs[i]->service_count){
        	of6<<"service type = "<<j.first<<"  number of reqs = "<<j.second<<endl;
		}
    }
    
    
    for(int i=0;i<14;++i){
        for(auto it:all_cs[i]->active_pool){
            vector<vector<int>>service_queue;
            for(int k=0;k<all_cs[i]->request_queue.size();++k){
                if((all_cs[i]->request_queue[k][4])==it)
                    service_queue.push_back(all_cs[i]->request_queue[k]);
            }
            vector<vector<int>>ready_queue;
            for(int arrival_time=0;arrival_time<=99;++arrival_time){
                for(int k=0;k<service_queue.size();++k){
                    if(service_queue[k][1]==arrival_time)
                        ready_queue.push_back(service_queue[k]);
                }
                sort(ready_queue.begin(),ready_queue.end());
                //considering that we have enough computation power to process tasks in one time interval
                for(auto j=0;j<ready_queue.size();++j){
                    if(ready_queue[j][0]-pd[i][ready_queue[j][3]]>=j+1){
                        hit_count++;
                        ready_queue.erase(ready_queue.begin()+j);
                        j--;
                       // break;
                    }
                }
            }
            miss_count+=ready_queue.size();
        }
    }
  
    

    cout<<"Total no. of req = "<<n<<endl;
    cout<<"Total no. of Hit = "<<hit_count<<endl;
    cout<<"Total no. of Miss = "<<miss_count<<endl;
    cout<<"oh= "<<oh<<endl;
    
    for(int i=0;i<14;++i){
        pro_periodic_provisioning3(all_cs[i],oh);
    }
    
   //------------------------------------------------------------//
      //Distributing requests among computation spots
  for(int iteration=1;iteration<=5;++iteration){
    srand(time(0));
   	ofstream of2("dataset2.txt",ios::out);
    for(int i=0;i<n;++i){
       //Burst Time = 1 Time Slot
       
       if(i<n/6){
       	int x= rand();
       int arrival_time= ((x)%100);
       int deadline=((x)%157)+5;
       int leaf_computation_spot=(x)%8;
       int service_type=(x)%1000;

       of2 << arrival_time <<" " << deadline <<" " << leaf_computation_spot << " " << service_type << endl;
       continue;
	   }
       
       int x= rand();
       int arrival_time= ((rand())%100);
       int deadline=((rand())%157)+5;
       int leaf_computation_spot=(rand())%8;
       int service_type=(rand())%1000;

       of2 << arrival_time <<" " << deadline <<" " << leaf_computation_spot << " " << service_type << endl;
    }
   of2.close();    
    hit_count=0;
    miss_count=0;
    vector<unordered_map<int,vector<vector<int>>>>v(14);
    vector<vector<int>> data2;//(n,vector<int>(5,0));
    for(int i=0;i<14;++i){
        all_cs[i]->request_queue.clear();
        all_cs[i]->service_count.clear();
        v[i]=all_cs[i]->m;
        all_cs[i]->m.clear();
    }
    for(int i=0;i<8;++i){
    	unordered_map<int,vector<vector<int>>>m2=v[i];
        for(auto j : m2){
        	int s=floor(((j.second.size())*0)/100);
        	p_s +=s;
        	for(int k=0;k<s;++k){
        		data2.push_back((j.second)[k]);
			}
		}
	}
	//cout<<endl<<p_s<<endl;
    //cout<<n-p_s<<endl;
    
    
    ifstream ip2("dataset2.txt",ios::in);
    srand(time(0));
    vector<int>v2{0,0,0,0,0};
    for(int i=p_s;i<n;++i){
	data2.push_back(v2);	
	}
    for(int i=p_s;i<n;++i){
    	int x;
        ip2>>x;
		data2[i][1]=x;
        ip2>>x;
		data2[i][2]=x;
        ip2>>x;
		data2[i][3]=x;
        ip2>>x;
		data2[i][4]=x;
        data2[i][0]=data2[i][1]+data2[i][2];
    } 
    sort(data2.begin(),data2.end());
    
    for(int i=0;i<n;++i){
        data2[i][0]= data2[i][0]-HUB_TO_LEAF_RTT;
        pro_request_distribution(all_cs[data2[i][3]],data2[i],hit_count,miss_count);
    }
    
    p_s=0;
    
    for(int i=0;i<14;++i){
        for(auto it:all_cs[i]->active_pool){
            vector<vector<int>>service_queue;
            for(int k=0;k<all_cs[i]->request_queue.size();++k){
                if((all_cs[i]->request_queue[k][4])==it)
                    service_queue.push_back(all_cs[i]->request_queue[k]);
            }

             vector<vector<int>>ready_queue;
            for(int arrival_time=0;arrival_time<=99;++arrival_time){
                for(int k=0;k<service_queue.size();++k){
                    if(service_queue[k][1]==arrival_time)
                        ready_queue.push_back(service_queue[k]);
                }
                sort(ready_queue.begin(),ready_queue.end());
                //considering that we have enough computation power to process tasks in one time interval
                for(auto j=0;j<ready_queue.size();++j){
                    if(ready_queue[j][0]-pd[i][ready_queue[j][3]]>=j+1){
                        hit_count++;
                        ready_queue.erase(ready_queue.begin()+j);
                        j--;
                       // break;
                    }
                }
            }
            miss_count+=ready_queue.size();

        }
    } 
    for(int i=0;i<14;++i){
        pro_periodic_provisioning3(all_cs[i],oh);
    }
 }

    cout<<"Total no. of req = "<<n<<endl;
    cout<<"Total no. of Hit = "<<hit_count<<endl;
    cout<<"Total no. of Miss = "<<miss_count<<endl;
    cout<<"oh= "<<oh<<endl;


 

}

int main(){

    int n;
    cout<<"Enter number of requests"<<endl;
   // int n =100000;
    cin>>n;

     srand(time(0));

    ofstream of("dataset.txt",ios::out);
    for(int i=0;i<n;++i){
       //Burst Time = 1 Time Slot
       int x= rand();
       int arrival_time= (x)%100;
       int deadline=((x)%157)+5;
       int leaf_computation_spot=(x)%8;
       int service_type=(x)%1000;
       of << arrival_time <<" " << deadline <<" " << leaf_computation_spot << " " << service_type << endl;
    }
   of.close();
   
   srand(time(0));
   ofstream of2("dataset2.txt",ios::out);
    for(int i=0;i<n;++i){
       //Burst Time = 1 Time Slot
       
       if(i<n/6){
       	int x= rand();
       int arrival_time= ((x)%100);
       int deadline=((x)%157)+5;
       int leaf_computation_spot=(x)%8;
       int service_type=(x)%1000;

       of2 << arrival_time <<" " << deadline <<" " << leaf_computation_spot << " " << service_type << endl;
       continue;
	   }
       
       int x= rand();
       int arrival_time= ((rand())%100);
       int deadline=((rand())%157)+5;
       int leaf_computation_spot=(rand())%8;
       int service_type=(rand())%1000;

       of2 << arrival_time <<" " << deadline <<" " << leaf_computation_spot << " " << service_type << endl;
    }
   of2.close();

   ofstream of3("dataset3.txt",ios::out);
    for(int i=0;i<n;++i){
       //Burst Time = 1 Time Slot
       int x= rand();
       int arrival_time= ((rand())%100);
       int deadline=((rand())%157)+5;
       int leaf_computation_spot=(rand())%8;
       int service_type=(rand())%1000;

       of3 << arrival_time <<" " << deadline <<" " << leaf_computation_spot << " " << service_type << endl;
    }
   of3.close();


  // decentralized_approach(n);
   cout<<endl;

  // completely_centralized_approach(n);
   cout<<endl;

   //coordinated_approach(n);
   cout<<endl;
   
//    proposed_approach1(n);

//    cout<<endl;
   
//    proposed_approach2(n);
   
//    cout<<endl;
   
   proposed_approach3(n);

    return 0;
}
