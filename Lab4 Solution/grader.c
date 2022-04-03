/*
CSc332 OS Lab
Instructor: Sujoy Debnath
Author: Mohammed Fahad
Task 4 Part 2 : Average Grader.Reads the "grades.txt" file and calculate average grades for n number of students for each chapter's each homework and displays those averages. "
*/


#include<stdio.h>

#include<stdlib.h>

void worker(int x,int y,int x_no, int y_no , int arr[][x*y])//total chapter and total homework count in each chapter for array size determination , passed chapter_no and homework_no for which avg and maximum grade is to be calculated

{

int i,sum=0;

float avg;



for(i=0;i<10;i++)

{

sum=sum+arr[i][y_no];



}

avg=sum/10;//calculate avg marks for homeworks

printf(" In %d chapter Homework %d : \n",x_no+1,y_no+1);

printf(" average:%f \t \n",avg);

}

void manager(int x,int y,int x_no,int arr[][x*y])//total chapters,total homework count, chapter no which is to handled,and original array

{

int i,j;

for(i=x_no*y,j=0;j<y;i++,j++)//passing homework no for chapter no=x_no

worker(x,y,x_no,i,arr);

}

int main()//director function

{

FILE *fp;

int x,y,i=0,j=0;

printf("enter no of chapters : ");

scanf("%d",&x);

printf("enter no of Homework : ");

scanf("%d",&y);

int a[10][x*y];//total no of columns will be x*y

fp=fopen("grades.txt","r");

for(i=0;i<10;i++)//reading a file

{

for(j=0;j<x*y;j++)

{

fscanf(fp,"%d ",&a[i][j]);//storing file contents into array

}

}

for(i=0;i<10;i++)//display array content

{

for(j=0;j<y*x;j++)

{

printf("%d\t",a[i][j]);

}

printf("\n");

}

for(i=0;i<x;i++)

manager(x,y,i,a);//created manager function for chapters_no

fclose(fp);//closing of file

}
