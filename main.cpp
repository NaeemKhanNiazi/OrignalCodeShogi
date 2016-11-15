#include <iostream>
#include <fstream>
#include <conio.h>
#include <math.h>
#include <windows.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <dir.h>
#include <string.h>

using namespace std;
ofstream gamesave;
ifstream gameload;
void ChangeColor(int color)
{
    HANDLE  hConsole=GetStdHandle(STD_OUTPUT_HANDLE);;
    SetConsoleTextAttribute(hConsole,color);
}

void gotoRowCol(int rpos, int cpos)
{
    int xpos=cpos, ypos = rpos;
    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = xpos;
    scrn.Y = ypos;
    SetConsoleCursorPosition(hOuput,scrn);
}
void initialize(char Board[9][9],string Playername[2])
{
    cout<<"Player Names =";
    cin>>Playername[0];
    cin>>Playername[1];
    Board[0][0]=Board[0][8]='L';
    Board[0][1]=Board[0][7]='N';
    Board[0][2]=Board[0][6]='S';
    Board[0][3]=Board[0][5]='G';
    Board[0][4]='K';

    for(int col=0; col<=8; col++)
    {
        Board[2][col]='P';
    }
    for(int col=0; col<=8; col++)
    {
        Board[1][col]='-';
    }
    Board[1][1]='R';
    Board[1][7]='B';

    for(int row=3; row<=5; row++)
    {
        for(int col=0; col<9; col++)
        {
            Board[row][col]='-';
        }
    }
    Board[8][0]=Board[8][8]='l';
    Board[8][1]=Board[8][7]='n';
    Board[8][2]=Board[8][6]='s';
    Board[8][3]=Board[8][5]='g';
    Board[8][4]='k';
    for(int col=0; col<9; col++)
    {
        Board[7][col]='-';
    }
    Board[7][1]='b';
    Board[7][7]='r';
    for(int col=0; col<9; col++)
    {
        Board[6][col]='p';
    }
}
void PrintBox(int r,int c,int rdim,int cdim,char sym)
{
    ChangeColor(23);
    for(int ri=0; ri<rdim; ri++)
    {
        for(int ci=0; ci<cdim; ci++)
        {
            if(ri==0||ri==rdim-1||ci==0||ci==cdim-1)
            {
                gotoRowCol(r*rdim+ri,c*cdim+ci);
                cout<<sym;
            }
        }
    }
}
void WriteInCenterOfBox(int r,int c,int rdim,int cdim,char B[9][9])
{
    gotoRowCol(r*rdim+rdim/2,c*cdim+cdim/2);
    cout<<B[r][c];
//    switch(symbol)
//    {
//        case 'A':
//        cout<<'G';
//        case
//    }


}
void printBoard(char Board[9][9])
{
    for(int r=0; r<9; r++)
    {
        for(int c=0; c<9; c++)
        {
            PrintBox(r,c,5,7,-37);
            WriteInCenterOfBox(r,c,5,7,Board);
        }
    }
}
void turnchange(int &turn)
{
    if(turn==0)
    {
        turn=1;
    }
    else
        turn=0;
}
bool Selectpiece(int rdim,int cdim,char B[][9],int SC[2],int Ec[2],int Turn,int&sr,int&sc)
{
    gotoRowCol(sr*rdim+rdim/2,sc*cdim+cdim/2);
    int key;
    bool PP=false;
    do
    {
        if(kbhit())
        {
            key=getch();
            if(key==224)

                switch(getch())
                {
                case 72://^
                    if(sr!=0)
                        --sr;
                    gotoRowCol(sr*rdim+rdim/2,sc*cdim+cdim/2);
                    break;
                case 80://v
                    if(sr!=8)
                        ++sr;
                    gotoRowCol(sr*rdim+rdim/2,sc*cdim+cdim/2);
                    break;
                case 75://<
                    if(sc!=0)
                        --sc;
                    gotoRowCol(sr*rdim+rdim/2,sc*cdim+cdim/2);
                    break;
                case 77://<
                    if(sc!=8)
                        ++sc;
                    gotoRowCol(sr*rdim+rdim/2,sc*cdim+cdim/2);
                    break;
                }

            if(key==13)
            {
                SC[0]=sr;
                SC[1]=sc;
                PP=true;
            }
        }
    }
    while(PP==false);

}
bool Iscapitalletter(char letter)
{
    if(letter>='A'&&letter<='Z')
    {
        return true;
    }
    else
        return false;
}
bool Issmallletter(char letter)
{
    if(letter>='a'&&letter<='z')
    {
        return true;
    }
    else
        return false;
}
bool Isvalidselection(int turn,int SC[],char B[9][9],char letter)
{

    if((Iscapitalletter(letter)==true && turn==0))
    {
        return true;
    }
    if((Issmallletter(letter)==true && turn==1))
    {
        return true;
    }

    return false;
}
bool validendposition(int Endcord[2],char Board[9][9],int turn)
{
    char endletter=Board[Endcord[0]][Endcord[1]];
    if(turn==0&& !(Iscapitalletter(endletter)))
    {
        return true;
    }
    if(turn==1&& !(Issmallletter(endletter)))
    {
        return true;
    }
    return false;
}
void movepiece(char Board[9][9],int startcord[2],int Endcord[2])
{
    Board[Endcord[0]][Endcord[1]]=Board[startcord[0]][startcord[1]];
    Board[startcord[0]][startcord[1]]='-';
}

bool Yaxismove(int startcoor[2],int endcoor[2])
{
    if(startcoor[1]==endcoor[1])
        return true;
    else
        return false;
}
bool Yaxispathclean(char Board[9][9],int startcord[2],int Endcord[2])
{
    int maxc,minc;
    if(Endcord[0]>startcord[0])
    {
        maxc=Endcord[0];
        minc=startcord[0];
    }
    else
    {
        minc=Endcord[0];
        maxc=startcord[0];
    }
    int t=maxc-minc-1;
    for(int i=1; i<=t; i++)
    {
        if(Board[minc+i][startcord[1]]!='-')
            return false;
    }
    return true;
}
void savinggame (char Board[9][9],int turn,string players[2])
{
    gamesave.open("save.txt");
    gamesave<<turn<<endl;
    gamesave<<players[0]<<endl;
    gamesave<<players[1]<<endl;
    for(int r=0; r<9; r++)
    {
        for(int c=0; c<9; c++)
        {
            gamesave<<Board[r][c]<<" ";
        }
        gamesave<<endl;
    }
    gamesave.close();
}
//////////////
void savingreplay (char Board[9][9],int turn,string players[2],ofstream &replaysave)
{
    replaysave<<turn<<endl;
    replaysave<<players[0]<<endl;
    replaysave<<players[1]<<endl;
    for(int r=0; r<9; r++)
    {
        for(int c=0; c<9; c++)
        {
            replaysave<<Board[r][c]<<" ";
        }
        replaysave<<endl;
    }
    replaysave<<endl;
    //gamesave.close();
}
/////////////
void loadingreplay(char Board[9][9],int turn,string players[2],ifstream &loadreplay)
{
    // gameload.open("save.txt");
    loadreplay>>turn;
    loadreplay>>players[0];
    loadreplay>>players[1];
    for(int r=0; r<9; r++)
    {
        for(int c=0; c<9; c++)
        {
            loadreplay>>Board[r][c];
        }

    }
}
//////////////
void loadgame(char Board[9][9],int turn,string players[2])
{
    gameload.open("save.txt");
    gameload>>turn;
    gameload>>players[0];
    gameload>>players[1];
    for(int r=0; r<9; r++)
    {
        for(int c=0; c<9; c++)
        {
            gameload>>Board[r][c];
        }

    }
    gameload.close();
}
bool Xaxismove(int startcord[2],int Endcord[2])
{
    if(startcord[0]==Endcord[0])
        return true;
    else
        return false;
}
bool Xaxispathclean(char Board[9][9],int startcord[2],int Endcord[2])
{
    int maxc,minc;
    if(Endcord[1]>startcord[1])
    {
        maxc=Endcord[1];
        minc=startcord[1];
    }
    else
    {
        minc=Endcord[1];
        maxc=startcord[1];
    }
    int t=maxc-minc-1;
    for(int i=1; i<=t; i++)
    {
        if((Board[Endcord[0]][minc+i])!='-')
            return false;
    }
    return true;
}
bool Diagonalmove(int startcord[2],int Endcord[2])
{
    if((abs(Endcord[0]-startcord[0]))==abs(Endcord[1]-startcord[1]))
    {
        return true;
    }
    if(abs(startcord[0]+startcord[1])==abs(Endcord[0]+Endcord[1]))
    {
        return true;
    }
    return false;

}
bool Diagonalclean1(char Board[9][9],int startcord[2],int Endcord[2])
{
    int t=Endcord[1]-startcord[1]-1;
    for(int i=1; i<=t; i++)
    {
        if(Board[startcord[0]+i][startcord[1]+i]!='-')
            return false;
    }
    return true;
}
bool Diagonalclean2(char Board[9][9],int startcord[2],int Endcord[2])
{
    int t=startcord[1]-Endcord[1]-1;
    for(int i=1; i<=t; i++)
    {
        if(Board[startcord[0]-i][startcord[1]-i]!='-')
            return false;
    }
    return true;
}
bool Diagonalclean3(char Board[9][9],int startcord[2],int Endcord[2])
{
    int t=startcord[1]-Endcord[1]-1;
    for(int i=1; i<=t; i++)
    {
        if(Board[startcord[0]+i][startcord[1]-i]!='-')
            return false;
    }
    return true;
}

bool Diagonalclean4(char Board[9][9],int startcord[2],int Endcord[2])
{
    int t=startcord[0]-Endcord[0]-1;
    for(int i=1; i<=t; i++)
    {
        if(Board[startcord[0]-i][startcord[1]+i]!='-')
            return false;
    }
    return true;
}
bool legalpawnmove(char Board[9][9],int startcord[2],int Endcord[2],int turn)
{
    int r;
    if (turn==0&&startcord[1]==Endcord[1])
    {
        r=Endcord[0]-startcord[0];
        if(r==1)
        {
            return true;
        }
    }
    if (turn==1&&startcord[1]==Endcord[1])
    {
        r=startcord[0]-Endcord[0];
        if(r==1)
        {
            return true;
        }
    }
    return false;
}
bool legalrookmove(char Board[9][9],int startcord[2],int Endcord[2])
{
    bool check=(Yaxismove(startcord,Endcord)&&Yaxispathclean(Board,startcord,Endcord))||(Xaxismove(startcord,Endcord)&&Xaxispathclean(Board,startcord,Endcord));
    if(check==true)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool legalbishopmove(char Board[9][9],int startcord[2],int Endcord[2])
{
    bool check=Diagonalmove(startcord,Endcord);

    if((startcord[1]<Endcord[1]&&startcord[0]<Endcord[0])&&check==true)
    {
        if(Diagonalclean1(Board,startcord,Endcord)==true)
        {
            return true;
        }
    }
    if((startcord[1]>Endcord[1]&&startcord[0]>Endcord[0])&&check==true)
    {
        if(Diagonalclean2(Board,startcord,Endcord)==true)
        {
            return true;
        }
    }
    if((startcord[1]>Endcord[1]&&startcord[0]<Endcord[0])&&check==true)
    {
        if(Diagonalclean3(Board,startcord,Endcord)==true)
        {
            return true;
        }
    }


    if((startcord[1]<Endcord[1]&&startcord[0]>Endcord[0])&&check==true)
    {
        if(Diagonalclean4(Board,startcord,Endcord)==true)
        {
            return true;
        }
    }

    return false;
}
bool legalsilvergeneralmove(char Board[9][9],int startcord[2],int Endcord[2],int turn)
{
    int r1,r2;
    r1=abs(Endcord[0]-startcord[0]);
    r2=abs(Endcord[1]-startcord[1]);
    if(r1==1&&r2==1)
    {
        return true;
    }
    if(turn==0)
    {
        r1=Endcord[0]-startcord[0];
        if(r1==1&&r2==0)
        {
            return true;
        }
    }
    if(turn==1)
    {
        r1=startcord[0]-Endcord[0];
        if(r1==1&&r2==0)
        {
            return true;
        }
    }
    return false;
}
bool legalgoldgeneralmove(char Board[9][9],int startcord[2],int Endcord[2],int turn)
{
    if(turn==0)
    {
        int r1,r2,r3;

        r1=abs(Endcord[0]-startcord[0]);
        r2=abs(Endcord[1]-startcord[1]);
        r3=Endcord[0]-startcord[0];
        if((r1==0 && r2==1)||(r1==1 && r2==0)||(r3==1 && r2==1) )
        {
            return true;
        }
        return false;

    }
    else if(turn==1)
    {
        int r1,r2,r3;

        r1=abs(Endcord[0]-startcord[0]);
        r2=abs(Endcord[1]-startcord[1]);
        r3=startcord[0]-Endcord[0];
        if((r1==0 && r2==1)||(r1==1 && r2==0)||(r3==1 && r2==1) )
        {
            return true;
        }
        return false;

    }
}
bool legalkingmove(char Board[9][9],int startcord[2],int Endcord[2])
{
    int r2=abs(Endcord[1]-startcord[1]);
    int r1=abs(Endcord[0]-startcord[0]);
    if(r1==1&&r2==1)
    {
        return true;
    }
    if((r1==1&&r2==0)||(r2==1&&r1==0))
    {
        return true;
    }
    return false;
}
bool legalknightmove(char Board[9][9],int startcord[2],int Endcord[2],int turn)
{
    int r1;
    int r2=abs(Endcord[1]-startcord[1]);
    if(turn==0)
    {
        r1=(Endcord[0]-startcord[0]);
        if(r1==2&&r2==1)
        {
            return true;
        }
    }
    if(turn==1)
    {
        r1=startcord[0]-Endcord[0];
        if(r1==2&&r2==1)
        {
            return true;
        }
    }
    return false;
}
bool legallansmove(char Board[9][9],int startcord[2],int Endcord[2],int turn)
{
    int r;
    bool check=Yaxismove(startcord,Endcord)&&Yaxispathclean(Board,startcord,Endcord);
    if(turn==0&&check==true)
    {
        r=Endcord[0]-startcord[0];
        if(r>=1&&r<=8)
        {
            return true;
        }
    }
    if(turn==1&&check==true)
    {
        r=startcord[0]-Endcord[0];
        if(r>=1&&r<=8)
        {
            return true;
        }
    }
    return false;
}
bool legalpromotedbishopmove(char Board[9][9],int startcord[2],int Endcord[2])
{
    if(legalbishopmove(Board,startcord,Endcord)==true||(legalkingmove(Board,startcord,Endcord)==true))
    {
        return true;
    }
    return false;

}
bool legalpromotedrookmove(char Board[9][9],int startcord[2],int Endcord[2])
{
    if(legalrookmove(Board,startcord,Endcord)==true||(legalkingmove(Board,startcord,Endcord)==true))
    {
        return true;
    }
    return false;

}
bool legalmoves( char Board[9][9],int startcord[2],int Endcord[2],int turn)
{
    char symbol;
    symbol=Board[startcord[0]][startcord[1]];
    switch(symbol)
    {
    case 'p':
    case 'P':
        return legalpawnmove(Board,startcord,Endcord,turn);
        break;
    case 'r':
    case 'R':
        return legalrookmove(Board,startcord,Endcord);
        break;
    case 'b':
    case 'B':
        return legalbishopmove(Board,startcord,Endcord);
        break;
    case 's':
    case 'S':
        return legalsilvergeneralmove(Board,startcord,Endcord,turn);
        break;
    case 'n':
    case 'N':
        return legalknightmove(Board,startcord,Endcord,turn);
        break;
    case 'g':
    case 'G':
        return legalgoldgeneralmove(Board,startcord,Endcord,turn);
        break;
    case 'K':
    case 'k':
        return legalkingmove(Board,startcord,Endcord);
        break;
    case 'L':
    case 'l':
        return legallansmove(Board,startcord,Endcord,turn);
        break;
    case 'H':
    case 'h':
        return legalpromotedbishopmove(Board,startcord,Endcord);
        break;
    case 'Z':
    case 'z':
        return legalpromotedrookmove(Board,startcord,Endcord);
        break;
    case 'A':
    case 'a':
        return legalgoldgeneralmove(Board,startcord,Endcord,turn);
        break;
    case 'c':
    case 'C':
        return legalgoldgeneralmove(Board,startcord,Endcord,turn);
        break;
    case 'd':
    case 'D':
        return legalgoldgeneralmove(Board,startcord,Endcord,turn);
        break;
    case 'e':
    case 'E':
        return legalgoldgeneralmove(Board,startcord,Endcord,turn);
        break;
    }
    return false;
}
void kingcoordinate(char Board[9][9],int kingcord[2],int turn)
{
    char king;
    if(turn==0)
    {
        king='K';
    }
    else
        king='k';
    for(int i=0; i<9; i++)
    {
        for(int j=0; j<9; j++)
        {
            if(Board[i][j]==king)
            {
                kingcord[0]=i;
                kingcord[1]=j;
                return;
            }
        }
    }
}
bool check(char Board[9][9],int turn)
{
    int Startingcord[2];
    int kingcord[2];
    kingcoordinate(Board,kingcord,turn);
    if(turn==0)
    {
        for(int i=0; i<9; i++)
        {
            for(int j=0; j<9; j++)
            {
                Startingcord[0]=i;
                Startingcord[1]=j;
                if((Isvalidselection(1,Startingcord,Board,Board[i][j]))&&legalmoves(Board,Startingcord,kingcord,1)==true)
                {
                    return true;
                }
            }
        }
    }
    if(turn==1)
    {
        for(int i=0; i<9; i++)
        {
            for(int j=0; j<9; j++)
            {
                Startingcord[0]=i;
                Startingcord[1]=j;
                if(legalmoves(Board,Startingcord,kingcord,0)==true&&(Isvalidselection(0,Startingcord,Board,Board[i][j])))
                {
                    return true;
                }
            }
        }

    }
    return false;
}
bool checklegalmove(char Board[9][9],int startcord[2],int Endcord[2],int turn)
{
    char tempchar=Board[Endcord[0]][Endcord[1]];
    movepiece(Board,startcord,Endcord);
    if(check(Board,turn)==true)
    {
        movepiece(Board,Endcord,startcord);
        Board[Endcord[0]][Endcord[1]]=tempchar;
        return false;
    }
    else
    {
        movepiece(Board,Endcord,startcord);
        Board[Endcord[0]][Endcord[1]]=tempchar;
        return true;
    }
}
bool Alllegalmovies(char Board[9][9],int turn)
{
    int tempstartcord[2];
    int tempEndcord[2];
    for(int i=0; i<9; i++)
    {
        for(int j=0; j<9; j++)
        {
            for(int r=0; r<9; r++)
            {
                for(int s=0; s<9; s++)
                {
                    tempstartcord[0]=i;
                    tempstartcord[1]=j;
                    gotoRowCol(1,65);
                    //cout<<Board[i][j];
                    tempEndcord[0]=r;
                    tempEndcord[1]=s;
                    if(Isvalidselection(turn,tempstartcord,Board,Board[i][j])&&!Isvalidselection(turn,tempEndcord,Board,Board[r][s]))
                    {

                        if((legalmoves(Board,tempstartcord,tempEndcord,turn)==true)&&(checklegalmove(Board,tempstartcord,tempEndcord,turn)==true))
                        {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}
bool checkmate(char Board[9][9],int turn)
{
    if(check(Board,turn)==true&&Alllegalmovies(Board,turn)==false)
    {
        return true;

    }
    else
        return false;
}
bool stalemate(char Board[9][9],int turn)
{
    if(Alllegalmovies(Board,turn)==false)

   {
    if(check(Board,turn)==false)
    {
        return true;

    }
   }
    else
        return false;
}

void promotion(char Board[9][9],int startcord[2],int Endcord[2],int turn)

{
    if(turn==0)
    {
        char symbol=Board[startcord[0]][startcord[1]];
        if(Iscapitalletter(symbol)==true)
        {
            char option;
            if(Endcord[0]==6||Endcord[0]==7||Endcord[0]==8)
            {
                if((Endcord[0]==7||Endcord[0]==6)&&(symbol=='P'))
                {
                    gotoRowCol(9,64);
                    cout<<"if you want to Promote "<<symbol<<" Press Y= ";
                    cin>>option;
                    if(option=='Y'||option=='y')
                        Board[startcord[0]][startcord[1]]='A';
                }
                else if(Endcord[0]==8&&(symbol=='P'))
                    Board[startcord[0]][startcord[1]]='A';



                if((Endcord[0]==7||Endcord[0]==6)&&(symbol=='L'))
                {
                    gotoRowCol(9,64);
                    cout<<"if you want to Promote "<<symbol<<" Press Y= ";
                    cin>>option;
                    if(option=='Y'||option=='y')
                        Board[startcord[0]][startcord[1]]='C';
                }
                else if(Endcord[0]==8&&(symbol=='L'))
                    Board[startcord[0]][startcord[1]]='C';



                if((Endcord[0]==6||Endcord[0]==7||Endcord[0]==8)&&symbol=='B')
                {
                    gotoRowCol(9,64);
                    cout<<"if you want to Promote "<<symbol<<" Press Y= ";
                    cin>>option;
                    if(option=='Y'||option=='y')
                        Board[startcord[0]][startcord[1]]='H';
                }



                if((Endcord[0]==6||Endcord[0]==7||Endcord[0]==8)&&symbol=='S')
                {
                    gotoRowCol(9,64);
                    cout<<"if you want to Promote "<<symbol<<" Press Y= ";
                    cin>>option;
                    if(option=='Y'||option=='y')
                        Board[startcord[0]][startcord[1]]='D';
                }



                if((Endcord[0]==6)&&symbol=='N')
                {
                    gotoRowCol(9,64);
                    cout<<"if you want to Promote "<<symbol<<" Press Y= ";
                    cin>>option;
                    if(option=='Y'||option=='y')
                        Board[startcord[0]][startcord[1]]='E';
                }
                else if((Endcord[0]==7||Endcord[0]==8)&&symbol=='N')
                    Board[startcord[0]][startcord[1]]='E';



                if((Endcord[0]==6||Endcord[0]==7||Endcord[0]==8)&&symbol=='R')
                {
                    gotoRowCol(9,64);
                    cout<<"if you want to Promote "<<symbol<<" Press Y= ";
                    cin>>option;
                    if(option=='Y'||option=='y')
                        Board[startcord[0]][startcord[1]]='Z';
                }

            }

            if((Endcord[0]!=6||Endcord[0]!=7||Endcord[0]!=8)&&(startcord[0]==6||startcord[0]==7||startcord[0]==8))
            {
                if(symbol=='R')
                {
                    gotoRowCol(9,64);
                    cout<<"if you want to Promote "<<symbol<<" Press Y= ";
                    cin>>option;
                    if(option=='Y'||option=='y')
                        Board[startcord[0]][startcord[1]]='Z';
                }
                if(symbol=='B')
                {
                    gotoRowCol(9,64);
                    cout<<"if you want to Promote "<<symbol<<" Press Y= ";
                    cin>>option;
                    if(option=='Y'||option=='y')
                        Board[startcord[0]][startcord[1]]='H';

                }
                if(symbol=='S')
                {
                    gotoRowCol(9,64);
                    cout<<"if you want to Promote "<<symbol<<" Press Y= ";
                    cin>>option;
                    if(option=='Y'||option=='y')
                        Board[startcord[0]][startcord[1]]='D';

                }
            }


        }
    }
    else if(turn==1)

    {
        char symbol=Board[startcord[0]][startcord[1]];
        if(Issmallletter(symbol)==true)
        {
            char option;
            if(Endcord[0]==0||Endcord[0]==1||Endcord[0]==2)
            {
                if((Endcord[0]==1||Endcord[0]==2)&&(symbol=='p'))
                {
                    gotoRowCol(9,64);
                    cout<<"if you want to Promote "<<symbol<<" Press Y= ";
                    cin>>option;
                    if(option=='Y'||option=='y')
                        Board[startcord[0]][startcord[1]]='a';
                }
                else if(Endcord[0]==0&&(symbol=='p'||symbol=='l'))
                    Board[startcord[0]][startcord[1]]='a';

                if((Endcord[0]==1||Endcord[0]==2)&&(symbol=='l'))
                {
                    gotoRowCol(9,64);
                    cout<<"if you want to Promote "<<symbol<<" Press Y= ";
                    cin>>option;
                    if(option=='Y'||option=='y')
                        Board[startcord[0]][startcord[1]]='c';
                }
                else if(Endcord[0]==0&&(symbol=='p'||symbol=='l'))
                    Board[startcord[0]][startcord[1]]='c';


                if((Endcord[0]==0||Endcord[0]==1||Endcord[0]==2)&&symbol=='b')
                {
                    gotoRowCol(9,64);
                    cout<<"if you want to Promote "<<symbol<<" Press Y= ";
                    cin>>option;
                    if(option=='Y'||option=='y')
                        Board[startcord[0]][startcord[1]]='h';
                }



                if((Endcord[0]==0||Endcord[0]==1||Endcord[0]==2)&&symbol=='s')
                {
                    gotoRowCol(9,64);
                    cout<<"if you want to Promote "<<symbol<<" Press Y= ";
                    cin>>option;
                    if(option=='Y'||option=='y')
                        Board[startcord[0]][startcord[1]]='d';
                }



                if((Endcord[0]==2)&&symbol=='n')
                {
                    gotoRowCol(9,64);
                    cout<<"if you want to Promote "<<symbol<<" Press Y= ";
                    cin>>option;
                    if(option=='Y'||option=='y')
                        Board[startcord[0]][startcord[1]]='e';
                }
                else if((Endcord[0]==1||Endcord[0]==0)&&symbol=='n')
                    Board[startcord[0]][startcord[1]]='e';



                if((Endcord[0]==0||Endcord[0]==1||Endcord[0]==2)&&symbol=='r')
                {
                    gotoRowCol(9,64);
                    cout<<"if you want to Promote "<<symbol<<" Press Y= ";
                    cin>>option;
                    if(option=='Y'||option=='y')
                        Board[startcord[0]][startcord[1]]='Z';
                }
            }
            if((Endcord[0]!=0||Endcord[0]!=1||Endcord[0]!=2)&&(startcord[0]==0||startcord[0]==1||startcord[0]==2))
            {
                if(symbol=='r')
                {
                    gotoRowCol(9,64);
                    cout<<"if you want to Promote "<<symbol<<" Press Y= ";
                    cin>>option;
                    if(option=='Y'||option=='y')
                        Board[startcord[0]][startcord[1]]='z';
                }
                if(symbol=='b')
                {
                    gotoRowCol(9,64);
                    cout<<"if you want to Promote "<<symbol<<" Press Y= ";
                    cin>>option;
                    if(option=='Y'||option=='y')
                        Board[startcord[0]][startcord[1]]='h';

                }
                if(symbol=='s')
                {
                    gotoRowCol(9,64);
                    cout<<"if you want to Promote "<<symbol<<" Press Y= ";
                    cin>>option;
                    if(option=='Y'||option=='y')
                        Board[startcord[0]][startcord[1]]='d';

                }
            }
        }
    }
    return;
}

void highlightlegalpos(char Board[9][9],int startcord[2],int turn,int rdim,int cdim)
{
    int tEndcord[2];
    for(int i=0; i<9; i++)
    {
        for(int j=0; j<9; j++)
        {
            tEndcord[0]=i;
            tEndcord[1]=j;
            char symbol=Board[i][j];
            if(Isvalidselection(turn,startcord,Board,symbol)==false&&legalmoves(Board,startcord,tEndcord,turn)==true)
            {
                PrintBox(i,j,rdim,cdim,'*');
            }

        }
    }
}
void undosavinggame(char Board[9][9],int turn,string players[2])
{
    gamesave.open("hhh.txt");
    gamesave<<turn<<endl;
    gamesave<<players[0]<<endl;
    gamesave<<players[1]<<endl;
    for(int r=0; r<9; r++)
    {
        for(int c=0; c<9; c++)
        {
            gamesave<<Board[r][c]<<" ";
        }
        gamesave<<endl;
    }
    gamesave.close();
}
void undoloadgame(char Board[9][9],int turn,string players[2])
{
    gameload.open("hhh.txt");
    gameload>>turn;
    gameload>>players[0];
    gameload>>players[1];
    for(int r=0; r<9; r++)
    {
        for(int c=0; c<9; c++)
        {
            gameload>>Board[r][c];
        }

    }
    gameload.close();
}
void smallpiececount(char Board[9][9],int startcord[2],int Endcord[2],int turn,int smallpiececounter[7])
{
    if(turn==0&&Board[Endcord[0]][Endcord[1]]!='-'&&Isvalidselection(turn,startcord,Board,Board[Endcord[0]][Endcord[1]])==false)
    {
        switch(Board[Endcord[0]][Endcord[1]])
        {
        case 'p':
        case 'a':
            smallpiececounter[0]++;
            break;
        case 'l':
        case 'c':
            smallpiececounter[1]++;
            break;
        case 's':
        case 'd':
            smallpiececounter[2]++;
            break;
        case 'n':
        case 'e':
            smallpiececounter[3]++;
            break;
        case 'b':
        case 'h':
            smallpiececounter[4]++;
            break;
        case 'r':
        case 'z':
            smallpiececounter[5]++;
            break;
        case 'g':
            smallpiececounter[6]++;
            break;


        }

    }

}

void Bigpiececount(char Board[9][9],int startcord[2],int Endcord[2],int turn,int Bigpiececounter[7])
{
    if(turn==1&&Board[Endcord[0]][Endcord[1]]!='-'&&Isvalidselection(turn,startcord,Board,Board[Endcord[0]][Endcord[1]])==false)
    {
        switch(Board[Endcord[0]][Endcord[1]])
        {
        case 'P':
        case 'A':
            Bigpiececounter[0]++;
            break;
        case 'L':
        case 'C':
            Bigpiececounter[1]++;
            break;
        case 'S':
        case 'D':
            Bigpiececounter[2]++;
            break;
        case 'N':
        case 'E':
            Bigpiececounter[3]++;
            break;
        case 'B':
        case 'H':
            Bigpiececounter[4]++;
            break;
        case 'R':
        case 'Z':
            Bigpiececounter[5]++;
            break;
        case 'G':
            Bigpiececounter[6]++;
            break;


        }

    }
}
bool legalsmallpiecedrop(char symbol,int turn,int smallpiececounter[7])
{
    if(turn==0)
    {
        switch(symbol)
        {
        case 'P':
            if(smallpiececounter[0]>0);
            return true;
        case 'L':
            if(smallpiececounter[1]>0)
                return true;
        case 'S':
            if(smallpiececounter[2]>0)
                return true;
        case 'N':
            if(smallpiececounter[3]>0)
                return true;
        case 'B':
            if(smallpiececounter[4]>0)
                return true;
        case 'R':
            if(smallpiececounter[5]>0)
                return true;
        case 'G':
            if(smallpiececounter[6]>0)
                return true;
        }
    }
    return false;
}

bool legalbigpiecedrop(char symbol,int turn,int Bigpiececounter[7])
{
    if(turn==1)
    {
        switch(symbol)
        {
        case 'p':
            Bigpiececounter[0]>0;
            return true;
        case 'l':
            if(Bigpiececounter[1]>0)
                return true;
        case 's':
            if(Bigpiececounter[2]>0)
                return true;
        case 'n':
            if(Bigpiececounter[3]>0)
                return true;
        case 'b':
            if(Bigpiececounter[4]>0)
                return true;
        case 'r':
            if(Bigpiececounter[5]>0)
                return true;
        case 'g':
            if(Bigpiececounter[6]>0)
                return true;
        }
    }
    return false;
}
bool Possibledroping(int turn,int smallpiececounter[7],int Bigpiececounter[7],char symbol)
{
    if(legalbigpiecedrop(symbol,turn,Bigpiececounter)==true)
    {
        return true;
    }
    if(legalsmallpiecedrop(symbol,turn,smallpiececounter)==true)
    {
        return true;
    }
    return false;
}
bool legalpawndroping(int dropingcord[2],char Board[9][9],int turn)
{
    for(int i=0; i<9; i++)
    {
        for(int j=0; j<9; j++)
        {
            if(turn==0 && Board[i][j]=='P' && dropingcord[1]==j)
            {
                if(i!=dropingcord[0])
                {
                    return false;
                }
            }
            else if(turn==1 && Board[i][j]=='p' && dropingcord[1]==j)
            {
                if(i!=dropingcord[0])
                {
                    return false;
                }
            }
        }
    }
    return true;
}
bool Droping(char Board[9][9],int turn,int dropingcord[2],int Endcord[2],int Bigpiececounter[7],int smallpiececounter[7],char &dropsymbol)
{
    gotoRowCol(3,65);
    cout<<"Turn "<<turn<<" Enter piece for Droping = ";
    cin>>dropsymbol;
    gotoRowCol(4,65);
    cout<<"Enter Your Droping Coordinates= ";
    cin>>dropingcord[0];
    cin>>dropingcord[1];
    if(Board[dropingcord[0]][dropingcord[1]]!='-')
    {
        return false;
    }
    if(Board[dropingcord[0]][dropingcord[1]]=='-'&&Possibledroping(turn,smallpiececounter,Bigpiececounter,dropsymbol)==true)
    {
        for(int i=0; i<9; i++)
        {
            for(int j=0; j<9; j++)
            {
                Endcord[0]=i;
                Endcord[1]=j;
                Board[dropingcord[0]][dropingcord[1]]=dropsymbol;
                if(legalmoves(Board,dropingcord,Endcord,turn)==true)
                {
                    if(Isvalidselection(turn,dropingcord,Board,dropsymbol)==true)
                    {
                        if(dropsymbol=='L'||dropsymbol=='B'||dropsymbol=='R'||dropsymbol=='N'||dropsymbol=='G')
                        {
                            return true;
                        }
                        if(dropsymbol=='l'||dropsymbol=='b'||dropsymbol=='r'||dropsymbol=='n'||dropsymbol=='g')
                        {
                            return true;
                        }
                    }
                    if((dropsymbol=='P'||dropsymbol=='p')&&(legalpawndroping(dropingcord,Board,turn)==true))
                    {

                        //if((checkmate(Board,turn)==true)
                        return true;
                    }
                }

            }
        }

    }
    Board[dropingcord[0]][dropingcord[1]]='-';
    return false;
}
bool legaldroping(int turn,int Bigpiececounter[7],int smallpiececounter[7])
{
    bool droping=false;
    for(int i=0; i<7; i++)
    {
        if(turn==0)
        {
            if(smallpiececounter[i]>0)
            {
                droping=true;
            }
        }
        if(turn==1)
        {
            if(Bigpiececounter[i]>0)

            {
                droping=true;
            }
        }
    }
    return droping;
}
void Bigdroppiececounter(char B[][9],int Turn,int EC[2],int Bigpiececounter[7])
{
    if(Turn==1 )
    {
        switch(B[EC[0]][EC[1]])
        {
        case 'p':
            Bigpiececounter[0]--;
            break;
        case 'l':
            Bigpiececounter[1]--;
            break;
        case 'n':
            Bigpiececounter[2]--;
            break;
        case 'g':
            Bigpiececounter[3]--;
            break;
        case 's':
            Bigpiececounter[4]--;
            break;
        case 'b':
            Bigpiececounter[5]--;
            break;
        case 'r':
            Bigpiececounter[6]--;
            break;
        }
    }
}
void smalldroppiececounter(char B[][9],int Turn,int EC[2],int smallpiececounter[7])
{
    if(Turn==0 )
    {
        switch(B[EC[0]][EC[1]])
        {
        case 'P':
            smallpiececounter[0]--;
            break;
        case 'L':
            smallpiececounter[1]--;
            break;
        case 'N':
            smallpiececounter[2]--;
            break;
        case 'G':
            smallpiececounter[3]--;
            break;
        case 'S':
            smallpiececounter[4]--;
            break;
        case 'B':
            smallpiececounter[5]--;
            break;
        case 'R':
            smallpiececounter[6]--;
            break;
        }
    }
}
void Dropingoption(int smallpiececounter[7],int Bigpiececounter[7])
{
    gotoRowCol(8,65);
    cout<<"Droping Piece";
    gotoRowCol(9,65);
    cout<<"Turn 0";
    gotoRowCol(10,65);
    cout<<"P = "<<smallpiececounter[0];
    gotoRowCol(11,65);
    cout<<"L = "<<smallpiececounter[1];
    gotoRowCol(12,65);
    cout<<"S = "<<smallpiececounter[2];
    gotoRowCol(13,65);
    cout<<"N = "<<smallpiececounter[3];
    gotoRowCol(14,65);
    cout<<"B = "<<smallpiececounter[4];
    gotoRowCol(15,65);
    cout<<"R = "<<smallpiececounter[5];
    gotoRowCol(16,65);
    cout<<"G = "<<smallpiececounter[6];


    gotoRowCol(9,85);
    cout<<"Turn 1";
    gotoRowCol(10,85);
    cout<<" p = "<<Bigpiececounter[0];
    gotoRowCol(11,85);
    cout<<" l = "<<Bigpiececounter[1];
    gotoRowCol(12,85);
    cout<<" s = "<<Bigpiececounter[2];
    gotoRowCol(13,85);
    cout<<" n = "<<Bigpiececounter[3];
    gotoRowCol(14,85);
    cout<<" b = "<<Bigpiececounter[4];
    gotoRowCol(15,85);
    cout<<" r = "<<Bigpiececounter[5];
    gotoRowCol(16,85);
    cout<<" g = "<<Bigpiececounter[6];
}

int main()
{
    ChangeColor(20);

    string Playername[2];
    char Board[9][9];
    int turn=1;
    int Startcord[2];
    int Endcord[2];
    int sr=0;
    int sc=0;
    int rdim=5;
    int cdim=7;
    char dropsymbol;
    int Bigpiececounter[7]= {};
    int smallpiececounter[7]= {};
    char letter;
    ofstream replaysave;
    ifstream replayload;

    int optionforgame;
    gotoRowCol(6,65);
    cout<<"Press 1 = New Game"<<endl;
    gotoRowCol(7,65);
    cout<<"Press 2 = Load Game"<<endl;
    gotoRowCol(8,65);
    cout<<"Press 3 = Reply Game"<<endl;
    gotoRowCol(1,1);
    cout<<"Press Button = ";
    cin>>optionforgame;
    if(optionforgame==1)
        initialize(Board,Playername);
    if(optionforgame==2)
        loadgame(Board,turn,Playername);
    if(optionforgame==3)
    {
        replayload.open("replay.txt");
        while(1)
        {
            loadingreplay(Board,turn,Playername,replayload);
            printBoard(Board);
            for(int i=0; i<=1000000; i++)
            {

            }
        }
    }
    replaysave.open("replay.txt");
    do
    {
        turnchange(turn);
        savingreplay(Board,turn,Playername,replaysave);
        savinggame (Board,turn,Playername);
        system("cls");
        printBoard(Board);
        if(check(Board,turn)==true)
        {
            gotoRowCol(6,65);
            if(turn==0)
            {
                gotoRowCol(6,64);
                cout<<"Player "<<Playername[0]<<" of Turn 0 you are in check";
            }
            if(turn==1)
            {
                gotoRowCol(7,64);
                cout<<"Player "<<Playername[1]<<" of Turn 1 you are in check";
            }
        }
       if(checkmate(Board,turn)==true)//&&checklegalmove(Board,Startcord,Endcord,turn)==false)
        {
            gotoRowCol(8,64);
            cout<<turn<<" You are In Check-Mate";
            gotoRowCol(9,64);
            cout<<"You win "<<(turn+1)%2;
            getch();
        }
//         if(stalemate(Board,turn)==true)
//        {
//            gotoRowCol(8,64);
//            cout<<"Draw";
//            getch();
//        }
        gotoRowCol(2,64);
        cout<<" Press D for Droping = ";
        Dropingoption(smallpiececounter,Bigpiececounter);
        char droping=getch();
        Dropingoption(smallpiececounter,Bigpiececounter);
        if((droping=='D'||droping=='d')&&(legaldroping(turn,Bigpiececounter,smallpiececounter)==true))
        {

            if(Droping(Board,turn,Startcord,Endcord,Bigpiececounter,smallpiececounter,dropsymbol)==true)
            {
                if(Possibledroping(turn,smallpiececounter,Bigpiececounter,dropsymbol)==true)
                {
                    Endcord[0]=Startcord[0];
                    Endcord[1]=Startcord[1];
                    smalldroppiececounter(Board,turn,Endcord,smallpiececounter);
                    Bigdroppiececounter(Board,turn,Endcord,Bigpiececounter);
                    continue;
                }
            }
        }
        if(droping=='D'||droping=='d')
        {
            if((legaldroping(turn,Bigpiececounter,smallpiececounter)==false)||(Droping(Board,turn,Startcord,Endcord,Bigpiececounter,smallpiececounter,dropsymbol)==false))
            {
                turnchange(turn);
                continue;
            }
        }
        else if(droping!='d'||droping!='D')
        {
            do
            {
                if(turn==0)
                {
                    gotoRowCol(47,2);
                    cout<<"Player "<<Playername[0]<<" of Turn "<<turn<<" Select Your Piece = ";
                }
                if(turn==1)
                {
                    gotoRowCol(47,2);
                    cout<<"Player "<<Playername[0]<<" of Turn "<<turn<<" Select Your Piece = ";
                }
                Selectpiece(rdim,cdim,Board,Startcord,Endcord,turn,sr,sc);
                letter=Board[Startcord[0]][Startcord[1]];
            }
            while(Isvalidselection(turn,Startcord,Board,letter)==false);
            highlightlegalpos(Board,Startcord,turn,rdim,cdim);
            do
            {
                if(turn==0)
                {
                    gotoRowCol(49,2);
                    cout<<"Player "<<Playername[0]<<" of Turn "<<turn<<" Select Your End Position = ";
                }
                if(turn==1)
                {
                    gotoRowCol(49,2);
                    cout<<"Player "<<Playername[0]<<" of Turn "<<turn<<" Select Your End Position = ";
                }
                Selectpiece(rdim,cdim,Board,Endcord,Startcord,turn,sr,sc);
            }
            while(validendposition(Endcord,Board,turn)==false);


            if(legalmoves(Board,Startcord,Endcord,turn)==true)
            {
                smallpiececount(Board,Startcord,Endcord,turn,smallpiececounter);
                Bigpiececount(Board,Startcord,Endcord,turn,Bigpiececounter);
            }

            if(legalmoves(Board,Startcord,Endcord,turn)==false||checklegalmove(Board,Startcord,Endcord,turn)==false)
            {
                turnchange(turn);
                continue;
            }
        }

        promotion(Board,Startcord,Endcord,turn);
        undosavinggame(Board,turn,Playername);
        movepiece(Board,Startcord,Endcord);
        savinggame (Board,turn,Playername);
        printBoard(Board);
        gotoRowCol(20,65);
        cout<<"Press Z for Undo";
        char undo=getch();
        if(undo=='z'||undo=='Z')
        {
            undoloadgame(Board,turn,Playername);
            printBoard(Board);
            turnchange(turn);
        }
        gotoRowCol(21,65);
        cout<<"Press r for Redo";
        char r=getch();
        if(r=='r'||r=='R')
        {
            loadgame(Board,turn,Playername);
            turnchange(turn);
            continue;
        }
    }
    while(checkmate(Board,turn)==false);

    return 0;
}
