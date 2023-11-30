#include<bits/stdc++.h>
using namespace std;

pair<vector<int>, int>
way_last(int v, vector<vector<int>>& c, unordered_set<int> b = {}){
  auto last=c.size()-1;
  pair<vector<int>, int> ans{vector<int>{v},numeric_limits<int>::max()};

  if (v!=last){
    for(int t=c.size()-1; t>=0; --t){
      if(c[v][t]!=0 && b.count(t)==0){
        b.insert(t);
        auto [suffix, weight]=way_last(t,c,b);

        if(weight==0){
          b.erase(t);
          continue;
        }

        for(auto v_s : suffix){
          ans.first.push_back(v_s);
        }

        ans.second=min(ans.second,min(weight, c[v][t]));
        return ans;
      }
    }
  }

  if (ans.first.back()!=last){
    ans.second=0;
  }

  return ans;
}

void
change_on(int v, vector<int>& way, vector<vector<int>> &f, vector<vector<int>> &c){
  for(int i=1; i<way.size(); ++i){
    int l=way[i-1],r=way[i];
    
    if(c[l][r]!=0){
      f[l][r]+=v;
    } else{
      f[l][r]-=v;
    }
  }
}

void
emerge_co(vector<vector<int>> &f, vector<vector<int>> &c){
  for(int l=0; l<f.size(); ++l){
    for(int r=0; r<f.size(); ++r){
      if(c[l][r]==0){
        continue;
      }

      c[l][r]=c[l][r]-f[l][r];
      c[r][l]=f[l][r];
    }
  }
}

int
main(void){
  ifstream in{"in.txt"};
  ofstream out{"out.txt"};

  int nx,ny;
  in>>nx>>ny;

  vector<vector<int>> g(1+nx+ny+1);

  // X, Y
  for(int f=1; f<=nx; ++f){
    for(int t; in>>t && 0!=t; g[f].emplace_back(t+nx));
  }

  // s, X
  for(int t=0; t<nx; ++t){
    g[0].emplace_back(1+t);
  }

  // Y, t
  for(int f=0; f<ny; ++f){
    g[f+1+nx].emplace_back(g.size()-1);
  }

//for(int x=0; x<g.size(); ++x){
//  cout<<x<<": ";
//  for(int i=0; i<g[x].size(); ++i){
//    cout<<g[x][i]<<' ';
//  }
//  cout<<'\n';
//}

  // c(l,r)
  vector<vector<int>> c(g.size(),vector<int>(g.size())); 
  for(int f=0; f<g.size(); ++f){
    for(int t : g[f]){
      c[f][t]=1;
    }
  }

  // f(l,r)
  vector<vector<int>> f(g.size(),vector<int>(g.size()));

//for(int i=0; i<c.size(); ++i){
//  for(int j=0; j<c.size(); ++j){
//    out<<c[i][j]<<' ';
//  }
//  out<<'\n';
//}


  int q=numeric_limits<int>::max();
  while(q>0){
    auto [w,q_w]=way_last(0,c);
    q=q_w;
  //for(auto v:w){
  //  cout<<v<<' ';
  //}
  //cout<<'\n';
    if(q>0){
      change_on(q,w,f,c);
      emerge_co(f,c);
    }
  }

  //for(int i=0; i<f.size(); ++i){
  //  for(int j=0; j<f.size(); ++j){
  //    cout<<f[i][j]<<' ';
  //  }
  //  cout<<'\n';
  //}

  for(int v=1; v<=nx; ++v){
    bool m=0;
    for(int r : g[v]){
      if(f[v][r]!=0){
        r-=nx;
        out<<r<<' ';
        m=1;
        break;
      }
    }
    if(!m){
      out<<0<<' ';
    }
  }
}
