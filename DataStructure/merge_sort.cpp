/*  merge sort   
   求逆序对数量 */

int num[N],temp[N];
int n;

LL sort(int l,int r)
{
    if(l==r)return 0;
    int i,j,k,mid=(l+r)>>1;
    LL ans;
    sort(l,mid);
    sort(mid+1,r); 
    for(i=k=l,j=mid+1;i<=mid && j<=r;){
        if(num[i]<num[j]){
            ans+=j-mid-1;
            temp[k++]=num[i++];
        }
        else temp[k++]=num[j++];
    }
    while(i<=mid){
        ans+=j-mid-1;
        temp[k++]=num[i++];
    }
    while(j<=r)
        temp[k++]=num[j++];
    for(i=l;i<=r;i++)
        num[i]=temp[i];
    return ans;
}
