#include <iostream>
#include<fstream>
#include<stdio.h>
#include<string.h>
#include<cstdlib>
#include<stdlib.h>
#include<time.h>
#include<conio.h>

using namespace std;


int qnum[10];


struct questions   //stores all 30 questions, with the relavent details of the question
{ char question[300], category[20], option[4][80],rightoption[80],response;
  int correct;
} quest[30];



void intro()     //Main Menu
{
    char choice;
    cout<<"Welcome to the Quiz"<<'\n'<<"You will have to answer 10 questions asked one at a time."<<endl;
    cout<<"Type the correct option A,B,C or D and press enter to answer the questions."<<'\n';
    cout<<"The questions are split into three categories: General, Sports and Music"<<'\n';
    cout<<"At the end of the quiz, your total and category-wise scores will be displayed along with the answers."<<'\n';
    cout<<"Enter A to exit the quiz and any other key to continue."<<endl;
    cin>>choice;
    if(choice=='A')
        exit (0);
    else
        cout<<"Please wait while quiz is being prepared"<<endl;
}



void questiongenerator()  //generates the ten random questions
{
    int num,flag=0;
    srand(time(NULL));
    qnum[0]=rand()%30;
    for(int i=1;i<10;i++)
    {
        label1:
        flag=0;
        srand(time(NULL));
        num  = rand()%30;
        for(int j=0;qnum[j]!='\0';j++)
        {
            if(num==qnum[j])
            {
                flag=1;
                goto label1;
            }
        }
        if(flag==0)
            qnum[i]=num;


    }

}

void result()
{
    for(int i=0;i<10;i++)
    { cout<<"Question Category: ";puts(quest[qnum[i]].category);
      cout<<"Question: ";puts(quest[qnum[i]].question);
      cout<<"Correct Answer: ";puts(quest[qnum[i]].rightoption);
      cout<<"Your Answer: "<<quest[qnum[i]].response<<endl;
      cout<<"Marks Awarded: "<<quest[qnum[i]].correct<<endl<<endl;


    }
}

void categoryresult()
{
    int score[3]={0,0,0},q[3]={0,0,0};
    for(int i=0;i<10;i++)
    {
        if(strcmpi(quest[qnum[i]].category,"General")==0)
        {
            q[0]++;
            if(quest[qnum[i]].correct==1)
                score[0]++;
        }
        else if(strcmpi(quest[qnum[i]].category,"Sports")==0)
        {   q[1]++;
            if(quest[qnum[i]].correct==1)
                score[1]++;
        }
        else
        {
            q[2]++;
            if(quest[qnum[i]].correct==1)
                score[2]++;

        }

    }
    cout<<"Category Wise Marks:"<<endl;
    cout<<"General: "<<score[0]<<" out of "<<q[0]<<endl;
    cout<<"Sports: "<<score[1]<<" out of "<<q[1]<<endl;
    cout<<"Music: "<<score[2]<<" out of "<<q[2]<<endl;


}





int main()
{
    label2:
    system("cls");
    intro();

    fstream f;
    int score=0;
    char line[80];


    f.open("questionbank.txt",ios::in); // opening file

    for(int i=0;i<30;i++)
    {
        while(f.getline(line,80))
        {
            if(strlen(line)==0)
            {
                for(int j=0;j<4;j++)
                {
                    f.getline(line,80);
                    strcpy(quest[i].option[j],line);
                }

                f.getline(line,80);
                strcpy(quest[i].rightoption,line);
                f.getline(line,80);
                strcpy(quest[i].category,line);
                f.getline(line,80);
                break;
            }
            else
            {
                if(strlen(quest[i].question)==0)
                    strcpy(quest[i].question,line);
                else
                    strcat(quest[i].question,line);
            }
        }
    }
    f.close();  //file is closed and questions have been stored



    //displaying questions and getting answers
    questiongenerator();
    for(int i=0;i<10;i++)
    {
        system("cls");
        puts(quest[qnum[i]].question);
        for(int j=0;j<4;j++)
            puts(quest[qnum[i]].option[j]);
        cin>>quest[qnum[i]].response;
        if(quest[qnum[i]].response==quest[qnum[i]].rightoption[0])
            {
                score++;
                quest[qnum[i]].correct=1;
            }
        else
            quest[qnum[i]].correct==0;
    }


    system("cls");
    cout<<"Congratulations. You have completed the quiz."<<'\n'<<"You have got "<<score<<" correct out of 10 questions."<<'\n';
    cout<<"Here are your answers"<<'\n'<<endl;

    result();
    categoryresult();
    cout<<" Your Final Total Score: "<<score<<" out of "<<10<<endl<<endl;
    cout<<"Press any key to go to main menu";
    getch();
    goto label2;


    return 0;
}
