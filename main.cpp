#include <bits/stdc++.h>

using namespace std;

struct Query{
    int start, jump, count;
    Query(int s, int j, int c):start(s), jump(j), count(c){}  
};

int main(){
    int mapSize, queriesCount;
    cin >> mapSize >> queriesCount;
    
    vector<int> counts(mapSize, 0);
    
    vector<Query> bruteQueries;
    
    unordered_map<int, vector<Query>> normalQueries;//int stands for the jump

    for(int i = 0; i < queriesCount; i ++){
        int start, count, jump;
        cin >> start >> count >> jump;
        start--;
        Query q = Query(start, jump, count);
        if(count <= sqrt(mapSize)){
            bruteQueries.push_back(q);
        }else{
            normalQueries[jump].push_back(q);
        }
    }
    for(auto q : bruteQueries){
            int n = q.start;
        for(int i = 0; i < q.count; i ++){
            counts[n] ++;
            n += q.jump;
        }
    }

    for(auto it = normalQueries.begin(); it != normalQueries.end(); ++it){
        vector<int> endpoints(mapSize, 0);
        for(auto q : (*it).second){
            endpoints[q.start]++;
            endpoints[q.start + q.jump * q.count] --;
        }
        for(int i = 0; i < mapSize; i ++){
            int val = endpoints[i];
            counts[i] += val;
            int next = i + (*it).first;
            if(val != 0)
                endpoints[next] += val;
        }
    }
    for(auto k : counts){
        cout<<k<<" ";
    }
    return 0;
}