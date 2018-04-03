/*    HASH
   数字HASH,开散列,邻接表   */

const int MOD=4001,STA=1000010;  //MOD为表长,STA为表大小

struct Hash{
    int first[MOD],next[STA],size;
    LL f[STA],sta[STA];   //sta[]存放状态,f[]为对应状态的权值
    void init(){
        size=0;
        mem(first,-1);
    }
    int find_add(LL st,LL ans){   //查找,如果未查找到则添加   
        int i,u=st%MOD;
        for(i=first[u];i!=-1;i=next[i]){
            if(sta[i]==st){
                f[i]+=ans;   //状态累加,注意啦
                return 1;   //已存在状态
            }
        }
        sta[size]=st;
        f[size]=ans;
        next[size]=first[u];
        first[u]=size++;
    }
}hs;
