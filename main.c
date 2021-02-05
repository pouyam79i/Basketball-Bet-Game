//Coded by Pouya Mohammady tel : @pouya_moh  | ! 9829039 !
// libraries :
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// defenitions
#define MAXCHAR 1028
#define MELICHAR 10
#define MAXNUM 100

// variables
int teams[MAXNUM]={0};
char bettors[MAXNUM][MELICHAR+1]={'\0'};
int bettorsChoice[MAXNUM][2]={0};
int event;

//clears the terminal accoring to their OS
void clear(void){
    #ifdef _WIN32
        system("cls");
    #endif

    #ifdef __unix
        system("clear");
    #endif

    #ifdef __MACH__
        system("clear");
    #endif
}
//This function returns a line from a file 
char *readLine(char *name, int line){
    FILE *myFile;
    myFile = fopen(name, "a+");
    static char tempS[MAXCHAR];
    strcpy(tempS, "\0");
    int counter = 0;
      while(fgets(tempS, MAXCHAR, myFile) != NULL){
            counter++;
            if(counter == line){
                int len = strlen(tempS);
                tempS[len-1]='\0';
                return tempS;
                
            }
        }
        return 0;
}
//This function add a team
int addTeam(){
    int numberOfTeams=0;
    int i;
    for(i=0; i<100; i++){
        if(teams[i]==0){
            teams[i]=1;
            //print name of the team
            //print some reaport!
            numberOfTeams = (i+1);
            break;    
        }
        if(i==99){
            numberOfTeams = (i+1);
            break;
        }
    }    
    return numberOfTeams;
}
//This function decides who the winner will be.
void playingGame(int t1, int t2){

    int randomMatch, winnerN, loserN;
    clock_t c = clock();
    time_t t = time(NULL);
    int cc, tt;
    srand((cc+t1)+(t2+tt));
    randomMatch = rand();
    if((randomMatch%2)==0){
        winnerN = t1;
        loserN = t2;
    }else
    {
        winnerN = t2;
        loserN = t1;
    }
    printf("\n %s Beats ", readLine("teamNames.txt", (winnerN+1)));
    printf("%s !!!", readLine("teamNames.txt", (loserN+1)));
    teams[winnerN]++;
}
//This function displays the main menu
void mainMenu(int numOfTeams, int numOfBettors, int isWrong){

    clear();
    printf("Wellcome to Our Bet Game!\n");
    if(isWrong == 1)
    printf("\nWrong Input Please Enter Again!\n");
    if(numOfTeams <= 1)
    printf("\n%d Team playes this season\n",numOfTeams);
    else{
    printf("\n%d Teams play this season\n", numOfTeams);
    if(numOfTeams==100){
        printf("\n No more team can play at this season!\n");
    }
    }
    if(numOfBettors <= 1)
    printf("\n%d person votes\n", numOfBettors);
    else{
    printf("\n%d people vote\n", numOfBettors);
    if(numOfBettors==100){
        printf("\n No more voters can vote\n");
    }
    }
    printf("\n1 - Add a team ");
    printf("\n2 - Vote for a teams");
    printf("\n3 - Remove your vote");
    printf("\n4 - Start season!");
    printf("\n5 - Exit app!");
    printf("\n");
    if(event!=0){
        printf("\nMessage box : ");
    if(event == 10)
        printf("The entered ID cannot vote any more");
    
    if(event == 11)
        printf("The entered ID is successfully removed!");
    if(event == 9)
        printf("No one has voted");
    }
    printf("\n ");
}
//This function starts the season
int matchMaking(int numberOfTeams, int moreWinner){
    int i, maxPoint=0, j;
    if(moreWinner==0){
    for(i=0; i<numberOfTeams; i++){
        for(j = i+1; j<numberOfTeams; j++){
            playingGame(i, j);
        }
    }
    }
    else
    {
        int chance[100], counter=0;
        for(i=0; i<100; i++){
            if(teams[i]==moreWinner){
                chance[counter]=i;
                counter++;
            }
        }
        clock_t clok = clock();
        int ccc = clok;
        srand(ccc+counter);
        int ran = rand();
        int win = ran % counter;
        teams[chance[win]] += (counter-1);
        printf("\n It seems there a few teams with equal scores \n But %s beats the other team again!", readLine("teamNames.txt", (1+chance[win])));
        return chance[win];
    }

    int winner;
    for(i=0; i<100; i++){
        if(teams[i]==0)
        break;
        if(maxPoint<teams[i]){
        winner = i;
        maxPoint = teams[i];
    }
    }
    moreWinner=0;
    for(i=0; i<numberOfTeams; i++){
        if(teams[i]==maxPoint){
            for(j=i+1; j<numberOfTeams; j++){
                if(teams[j]==maxPoint){
                    moreWinner = maxPoint;
                    break;
                }
            }
        }
    }
    if(moreWinner!=0){
        return matchMaking(numberOfTeams, moreWinner);
    }
    return winner;
}
//show the resulat of bettors
void bettorsResult(int winnerTeam){
     printf("\n\n Winner of this maches is %s , with the highest score : %d \n", readLine("teamNames.txt", (winnerTeam+1)), teams[winnerTeam]);
    int i, j=0;
    int winnerExistance=0;
    int codeOfWinner[MAXNUM]={-1};
    winnerTeam++;
    for(i=0; i<100; i++){
        if(bettors[i]==0)
            break;
        if(bettorsChoice[i][0]==winnerTeam || bettorsChoice[i][1]==winnerTeam){
            codeOfWinner[winnerExistance]=i;
            winnerExistance++;
            printf("\n%s Guess is correct!", bettors[i]);
        }
    }
    if(winnerExistance==0)
    printf("\nWe have no winner between our bettor!\n");
    if (winnerExistance==1)
        printf(" and he wins!");
    if(winnerExistance>1){
        int chance=0;
        srand(time(NULL)+winnerExistance);
        chance = rand();
        chance = chance%winnerExistance;
        printf("\nBut the final is %s !!!! Congragelation :)) ", bettors[chance]);
    }
    return;
}
// Refresh the list of bettors!
int refreshBettorList(){
    int isRefreshed = 0,i,j;
    int numberOfBerttors;
    for(i=0; i<100; i++){
        if(strcmp(bettors[i], "\0")==0){
            for(j=i+1; j<100; j++){
                if(strcmp(bettors[j], "\0") != 0){
                    strcpy(bettors[i],bettors[j]);
                    strcpy(bettors[j], "\0");
                    bettorsChoice[i][0]=bettorsChoice[j][0]; 
                    bettorsChoice[i][1]=bettorsChoice[j][1]; 
                    bettorsChoice[j][0]=0;
                    bettorsChoice[j][1]=0;
                    isRefreshed=0;
                    break;
                }
                else
                {
                    isRefreshed=1;
                }
            }
        }
        if(isRefreshed==1)
            break;
    }
    numberOfBerttors = i;
    return numberOfBerttors;
}
//voteFunction 
void voteFunction(int codeOfBettors, int numberOfTeams, int isWrong){
    clear();
    int input;
    if((isWrong==0 || isWrong==1)&& bettorsChoice[codeOfBettors][0]==0){
    if(isWrong==1)
        printf("\n Wrong Choice!");
    printf("\nyou can choose a team between team 1 and %d", numberOfTeams);
    printf("\nPlease enter your first vote : \n");
    scanf("%d", &input);
    if((input<1)||(input>numberOfTeams)){
        voteFunction(codeOfBettors, numberOfTeams, 1);
        return;
    }
    bettorsChoice[codeOfBettors][0]=input;
    }
    if(((isWrong==0 || isWrong ==1) || (isWrong ==2 || isWrong==3))&&bettorsChoice[codeOfBettors][1]==0){
        if(isWrong==2)
            printf("\nWrong Choice!");
        if(isWrong==3)
            printf("\nYou have voted for this team once! choose another team!");
            printf("\nyou can choose a team between team 1 and %d", numberOfTeams);
        if(bettorsChoice[codeOfBettors][1]==0)
            printf("\nPlease enter your second vote : ");
        else
            printf("\nEdit your second vote : ");
        printf("\nAlso if you do not like to vote for the second time, enter 0 !\n");
        scanf("%d", &input);
        if(input<0 || input>numberOfTeams){
            voteFunction(codeOfBettors, numberOfTeams, 2);
            return;
        }
        if(input==bettorsChoice[codeOfBettors][0]){
            voteFunction(codeOfBettors, numberOfTeams, 3);
            return;
        }
        bettorsChoice[codeOfBettors][1]=input;
        return;
    }
    event = 10;
    return;
}
//Vote Menu
void voteMenu(int codeOfBettor, int numberOfTeams, int isWrong){
    clear();
    int input, i;
    if(isWrong==1)
    printf("Input Invalied! please choose a correct option!\n");
    printf("\nOK you have signed in as \n voter number %d . ID: %s \n", codeOfBettor+1, bettors[codeOfBettor]);
    printf("\n1 - Vote for a team");
    printf("\n2 - See the list of players!");
    scanf("%d", &input);
    switch (input)
    {
    case 1:
        isWrong=0;
        voteFunction(codeOfBettor, numberOfTeams, 0);
        break;
    case 2:
        isWrong=0;
        system("clear");
        for(i=1; i<=numberOfTeams;i++){
            printf("%d - %s \n", (i), readLine("teamNames.txt", i));
        }
        printf("\n To return to privious menu enter!");
        getchar();
        getchar();
        voteMenu(codeOfBettor, numberOfTeams, 0);
        return;
        break;
        break;
    default:
        isWrong=1;
        voteMenu(codeOfBettor, numberOfTeams, isWrong);
        return;
    }
}
//Sign in Menu for bettors
void signInBetting(int numberOfTeams, int isWrong){
    clear();
    char TEMPS[10];    
    // if(isWrong==1)
    // printf("This ID is for another person\nPlease enter your uniqe ID ...");
    if(isWrong==2)
    printf("Please enter your ID correctly\nIt must be 10 number!");
    printf("\n Please Inter your ID :\n");
    scanf("%s", TEMPS);
    int i, len;
    len = strlen(TEMPS);
    if(len>10){
        signInBetting(numberOfTeams, 2);
        return;
    }
    if(len<10){
        int tempi=0;
        char tS[10];
        tempi = 10-len;
        for(i=0; i<10; i++){
            if(i<tempi)
            tS[i]='0';
            else
            tS[i]=TEMPS[i-tempi];
        }
        strcpy(TEMPS, tS);
    }
    for (i=0; i<100; i++){
        if(strcmp(TEMPS, bettors[i])==0){
            voteMenu(i, numberOfTeams, 0);
            return;
        }
    }
    for(i=0; i<100; i++){
        if(strcmp(bettors[i], "\0")==0){
            strcpy(bettors[i], TEMPS);
            break;
        }
    }
    voteMenu(i, numberOfTeams,0);
}
// Betting Options!
void betOnTeamMenu(int numberOfTeams, int isWrong){
    clear();
    int input;
    if(numberOfTeams <2){
        printf("\nThe number of teams is less then 2\nIt should be at least 2\nEnter to return to the main menu");
        getchar();
        getchar();
        return;
    }
    if(isWrong == 1)
    printf("\nInput Invalid! please enter a correct choice!\n");
    printf("\n%d teams are participating at this season!\n", numberOfTeams);
    printf("\n1 - Sign in to vote");
    printf("\n2 - Exit beting menu");
    scanf("%d", &input);
    switch (input)
    {
    case 1:
        signInBetting(numberOfTeams, 0);
        break;
    case 2:
        return;
        break;
    default:
        betOnTeamMenu(numberOfTeams, 1);
        break;
    }
}
//Removes vote
void removeYourVote(int numberOfBettors, int isWrong){
    clear();
    if(isWrong==1)
        printf("Please Enter your ID correctly ! \n");
    if(numberOfBettors==0){
        event = 9;
        return;
    }
    else
    printf("\n Please enter your ID to delete your vote : ");
    printf("\nIf you dont want to leave, enter 0!");
    char TEMPS[MELICHAR];
    scanf("%s", TEMPS);
    if(strcmp(TEMPS, "0\0")==0)
        return;
    int i, len=0;
    len = strlen(TEMPS);
    if(len<10){
        int tempi=0;
        char tS[10];
        tempi = 10-len;
        for(i=0; i<10; i++){
            if(i<tempi)
            tS[i]='0';
            else
            tS[i]=TEMPS[i-tempi];
        }
        strcpy(TEMPS, tS);
    }
    for(i=0; i<numberOfBettors; i++){
        if(strcmp(bettors[i], TEMPS)==0){
            strcpy(bettors[i], "\0");
            bettorsChoice[i][0]= 0;
            bettorsChoice[i][1]= 0;
            refreshBettorList();
            event = 11;
            return;
        }
    }
    removeYourVote(numberOfBettors, 1);
    return;
}
// main app:
int main(int argc, char const *argv[])
{
    int isPlaying;
    isPlaying = 1;
    int isWrong = 0;
    int numOfPlayers = 0;
    int numOfBettors = 0;
    event = 0;
    int winnerTeam;

    while(isPlaying==1){

    numOfBettors = refreshBettorList();
    mainMenu(numOfPlayers, numOfBettors, isWrong);
    
    int choice = -1;
    scanf("%d", &choice);
    switch (choice)
    {
    case 1: // to add a team to the season of games
        event = 0;
        numOfPlayers = addTeam();
        isWrong = 0;
        break;
    case 2:
        isWrong = 0;
        event = 0;
        betOnTeamMenu(numOfPlayers, 0);
        break;
    case 3:
        event = 0;
        removeYourVote(numOfBettors, 0);
        break;
    case 4: // to start the season
        event = 0;
        clear();
        winnerTeam = matchMaking(numOfPlayers, 0);
        bettorsResult(winnerTeam);
        isPlaying=0;
        break;
    case 5: // to exit the app
        event = 0;
        isPlaying = 0;
        break;
    default:
        event = 0;
        isWrong=1;
        break;
    }
    }

    return 0;
}
