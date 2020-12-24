#include<stdio.h>
#include<iostream>
#include<climits>
using namespace std;
void swap(int *x, int *y);
int main()
{
int fram, page, frames[10], pages[30], counter = 0, time[10], flag1, flag2, i,
j, pos, faults = 0;
printf("Enter number of frames: ");
scanf("%d",&fram);
int k;
printf("Enter the value of K:");
scanf("%d",&k);
printf("Enter number of pages: ");
scanf("%d",&page);
printf("Enter reference string: ");
for(i=0;i<page;++i)
{
scanf("%d",&pages[i]);
}
for(i=0;i<fram;++i)
{
frames[i] = -1;
}
for(i=0;i<page;++i)
{
flag1 = flag2 = 0;
for(j=0;j<fram;++j)
{
if(frames[j] == pages[i])
{
counter = counter+1;
time[j] = counter;
flag1 = flag2 = 1;
break;
}
}
if(flag1==0)
{
for(j=0;j<fram;++j)
{
if(frames[j] == -1)
{
counter++;
faults++;
frames[j] = pages[i];
time[j] = counter;
flag2 = 1;
break;
}
}
}
if(flag2 == 0)
{
pos = findLRU(time, fram, k);
counter++;
faults++;
frames[pos] = pages[i];
time[pos] = counter;
}
printf("\n");
for(j=0;j<fram;++j)
{
printf("%d\t", frames[j]);
}
}
printf("\n\nTotal Page Faults = %d", faults);
return 0;
}
int findLRU(int time[], int n,int v){
int i, pos = -1;
int master = kthSmallest(time, n, v);
for(i=0;i<n;i++)
{
if(time[i] == master)
{
pos = i;
break;
}
}
return pos;
}
