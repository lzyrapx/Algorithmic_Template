/*  Trie   */
/*  动态建立,注意释放内存  */
const int wide=26;  //每个节点的最大子节点数

struct Trie 
{
    struct Node
    {
        Node(){
            memset(ch,0,sizeof(ch));
            val=0;
        }
        Node *ch[26];
        int val;
    };
    Node *head;

    void init(){

        head=new Node;
    }
    inline int idx(char c)
    {
        return c-'a';
    }
    void insert(char *s,int v) //插入, v 从 1 开始标号
    {   
        int i,len=strlen(s),c;
        Node *p=head,*q;
        for(i = 0;i < len;i++)
        {
            c=idx(s[i]);   //求对应编号
            if(!p->ch[c])
            {
                q = new Node;
                p->ch[c]=q;
            }
            p = p->ch[c];
        }
        p->val = v;
    }
    int find(char *s) //查找
    {    
        int i,len=strlen(s),c;
        Node *p=head;
        for(i = 0;i < len;i++)
        {
            c=idx(s[i]);
            if(!p->ch[c]) return 0;
            p=p->ch[c];
        }
        for(i=0;i<26;i++){
            if(p->ch[i]) return 1;   //s串是模板串中某个串的prefix
        }
        return 2; //存在
    }
    void free(Node *p) //释放内存
    {   
        int i;
        for(i = 0;i < 26;i++){
            if(p->ch[i]){
            	free(p->ch[i]);
            }
        }
        delete p;
    }
}trie;
