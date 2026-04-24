#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>

// -------------------------------------------------------
//  DATA STRUCTURES
// -------------------------------------------------------
typedef struct {
    int  cid;
    char cname[30];
    int  votes;
} CANDIDATE;

// -------------------------------------------------------
//  GLOBALS  (all in-memory, nothing saved to disk)
// -------------------------------------------------------
CANDIDATE candidateArray[20];   // max 20 candidates
int       numberOfCandidates = 0;
int       totalVoters        = 0;
char      studentVotes[200];    // '0' = not voted, '1'..'9' = voted for that candidate
int       electionReady      = 0; // 1 after admin sets up the election

// -------------------------------------------------------
//  ADMIN AUTHENTICATION
// -------------------------------------------------------
int authenticateAdmin() {
    char username[20], password[10];

    printf("\n  Enter username : ");
    scanf("%s", username);
    if (strcmp(username, "admin") != 0)
        return 0;

    printf("  Enter password : ");
    int i = 0;
    for (i = 0; i < 5; i++) {
        password[i] = getch();
        printf("*");
    }
    password[i] = '\0';

    if (strcmp(password, "admin") != 0)
        return 0;

    return 1;
}

// -------------------------------------------------------
//  SETUP A NEW ELECTION
// -------------------------------------------------------
void initiateNewElection() {
    printf("\n\n--- New Election Setup ---\n");

    printf("Total number of voters  : ");
    scanf("%d", &totalVoters);

    printf("Number of candidates    : ");
    scanf("%d", &numberOfCandidates);

    // Reset votes
    for (int i = 0; i < totalVoters; i++)
        studentVotes[i] = '0';

    for (int i = 0; i < numberOfCandidates; i++) {
        candidateArray[i].cid   = i + 1;
        candidateArray[i].votes = 0;
        printf("Name of candidate %d    : ", i + 1);
        scanf(" %[^\n]", candidateArray[i].cname);
    }

    electionReady = 1;
    printf("\nElection is ready! Students can now vote.\n");
}

// -------------------------------------------------------
//  RESULTS
// -------------------------------------------------------
void showResults() {
    if (!electionReady) {
        printf("\n  No election has been set up yet!");
        getch();
        return;
    }

    int totalVoted = 0;
    int maxVotes   = -1;
    int winnerId   = -1;
    int tie        = 0;

    printf("\n\n========== ELECTION RESULTS ==========\n");
    for (int i = 0; i < numberOfCandidates; i++) {
        printf("  %d. %-20s -> %d vote(s)\n",
               candidateArray[i].cid,
               candidateArray[i].cname,
               candidateArray[i].votes);
        totalVoted += candidateArray[i].votes;

        if (candidateArray[i].votes > maxVotes) {
            maxVotes = candidateArray[i].votes;
            winnerId = i;
            tie      = 0;
        } else if (candidateArray[i].votes == maxVotes) {
            tie = 1;
        }
    }

    printf("--------------------------------------\n");
    printf("  Total votes cast : %d / %d\n", totalVoted, totalVoters);
    if (totalVoters > 0)
        printf("  Voting percentage: %d%%\n", (totalVoted * 100) / totalVoters);

    printf("--------------------------------------\n");
    if (tie)
        printf("  Result : ** IT'S A TIE **\n");
    else if (winnerId != -1)
        printf("  Winner : %s with %d vote(s)\n",
               candidateArray[winnerId].cname,
               maxVotes);
    printf("======================================\n");
    getch();
}

// -------------------------------------------------------
//  ADMIN PANEL
// -------------------------------------------------------
void adminPanel() {
    if (authenticateAdmin() != 1) {
        printf("\n  Wrong username or password!\n");
        getch();
        return;
    }

    printf("\n  Logged in successfully! (Press Enter)");
    getch();

    char input;
    while (1) {
        printf("\n\n--- Admin Menu ---");
        printf("\n  1. Setup New Election");
        printf("\n  2. View Results");
        printf("\n  3. Logout");
        printf("\n  Option: ");
        scanf(" %c", &input);

        switch (input) {
            case '1':
                initiateNewElection();
                break;
            case '2':
                showResults();
                break;
            case '3':
                return;
            default:
                printf("\n  Invalid option!");
                getch();
        }
    }
}

// -------------------------------------------------------
//  STUDENT PANEL
// -------------------------------------------------------
void studentPanel() {
    if (!electionReady) {
        printf("\n  Election has not been set up yet. Contact admin.\n");
        getch();
        return;
    }

    int rollNo;
    char voteInput;

    while (1) {
        printf("\n\n  Enter your Roll Number (0 to go back): ");
        scanf("%d", &rollNo);

        if (rollNo == 0)
            return;

        if (rollNo < 1 || rollNo > totalVoters) {
            printf("  Invalid roll number! Valid range: 1 to %d\n", totalVoters);
            getch();
            continue;
        }

        if (studentVotes[rollNo - 1] != '0') {
            printf("  Roll No. %d has already voted!\n", rollNo);
            getch();
            continue;
        }

        // Show candidates
        printf("\n  --- Candidates ---\n");
        for (int i = 0; i < numberOfCandidates; i++)
            printf("  %d. %s\n", candidateArray[i].cid, candidateArray[i].cname);

        printf("\n  Enter your vote (1-%d): ", numberOfCandidates);
        voteInput = getch();
        printf("%c\n", voteInput);

        int choice = voteInput - '0';
        if (choice < 1 || choice > numberOfCandidates) {
            printf("  Invalid vote! Try again.\n");
            getch();
            continue;
        }

        // Record the vote in memory
        studentVotes[rollNo - 1] = voteInput;
        candidateArray[choice - 1].votes++;

        printf("\n  Vote recorded successfully! Thank you.\n");
        getch();
    }
}
