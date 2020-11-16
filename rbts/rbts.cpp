#include "pch.h"
#include <iostream>
//#include<bits/stdc++.h>
#include <stack>
#include<set>
#include <string>
#include <fstream>
using namespace std;
using namespace System;
using namespace System::IO;
using namespace System::IO::Ports;

#define ROW 6 
#define COL 4 
int RbtDir = 1;
typedef pair<int, int> Pair;

typedef pair<double, pair<int, int>> pPair;
struct cell
{
    int parent_i, parent_j;
    double f, g, h;
};
bool isValid(int row, int col)
{ 
    return (row >= 0) && (row < ROW) &&
        (col >= 0) && (col < COL);
}
bool isUnBlocked(int grid[][COL], int row, int col)
{
    if (grid[row][col] == 1)
        return (true);
    else
        return (false);
}
bool isDestination(int row, int col, Pair dest)
{
    if (row == dest.first && col == dest.second)
        return (true);
    else
        return (false);
}
double calculateHValue(int row, int col, Pair dest)
{
    // Return using the distance formula 
    return ((double)sqrt((row - dest.first) * (row - dest.first)
        + (col - dest.second) * (col - dest.second)));
}
//      1
//  4       2
//      3

// 1 kr -1


void tracePath(cell cellDetails[][COL], Pair dest)
{
    printf("\nThe Path is ");
    int row = dest.first;
    int col = dest.second;
    string send = "";
    stack<Pair> Path;

    while (!(cellDetails[row][col].parent_i == row
        && cellDetails[row][col].parent_j == col))
    {
        Path.push(make_pair(row, col));
        int temp_row = cellDetails[row][col].parent_i;
        int temp_col = cellDetails[row][col].parent_j;
        
        int df_row = temp_row - row;
        int df_col = temp_col - col;
        if(df_row!=0){
            if (df_row == 1) {
                if (RbtDir==3) {
                    //forward(send);
                    printf("forW ");
                    send = send + "1";
                    printf("%s\n", send.c_str());
                } else if (RbtDir==2) {
                    
                    //turnRight(send);
                    RbtDir = 3;
                    printf("right ");
                    send = send + "2";
                } else if (RbtDir == 4) {
                    //turnLeft(send);
                    RbtDir = 3;
                }
            } else if (df_row == -1) {
                if (RbtDir == 1) {
                    printf("forW ");
                    send = send + "1";
                    printf("%s\n", send.c_str());
                    //forward(send);
                    RbtDir = 1;
                }
                else if (RbtDir == 4) {
                    
                    //turnRight(send);
                    RbtDir = 1;
                    printf("right ");
                    send = send + "2";
                }
                else if (RbtDir == 2) {
                    //turnLeft(send);
                    RbtDir = 1;
                    printf("left ");
                    send = send + "3";
                }
            }
        } else if (df_col != 0) {
            if (df_col == 1) {
                if (RbtDir == 2) {
                    printf("forW ");
                    send = send + "1";
                    printf("%s\n", send.c_str());
                    //forward(send);
                }
                else if (RbtDir == 1) {
                    
                    //turnRight(send);
                    RbtDir = 2;
                    printf("right ");
                    send = send + "2";
                }
                else if (RbtDir == 3) {
                   // turnLeft(send);
                    RbtDir = 2;
                    printf("left ");
                    send = send + "3";
                }
            }
            else if (df_col == -1) {
                if (RbtDir == 4) {
                    printf("forW ");
                    send = send + "1";
                    printf("%s\n", send.c_str());
                    //forward(send);
                }
                else if (RbtDir == 3) {
                    
                    //turnRight(send);
                    RbtDir = 4;
                    printf("right ");
                    send = send + "2";
                }
                else if (RbtDir == 1) {
                    //turnLeft(send);
                    RbtDir = 4;
                    printf("left ");
                    send = send + "3";
                }
            }
        }
        row = temp_row;
        col = temp_col;
    }

    Path.push(make_pair(row, col));
    while (!Path.empty())
    {
        pair<int, int> p = Path.top();
        Path.pop();
        printf("-> (%d,%d) ", p.first, p.second);
    }

    return;
}
void aStarSearch(int grid[][COL], Pair src, Pair dest)
{
    // If the source is out of range 
    if (isValid(src.first, src.second) == false)
    {
        printf("Source is invalid\n");
        return;
    }

    // If the destination is out of range 
    if (isValid(dest.first, dest.second) == false)
    {
        printf("Destination is invalid\n");
        return;
    }

    // Either the source or the destination is blocked 
    if (isUnBlocked(grid, src.first, src.second) == false ||
        isUnBlocked(grid, dest.first, dest.second) == false)
    {
        printf("Source or the destination is blocked\n");
        return;
    }

    // If the destination cell is the same as source cell 
    if (isDestination(src.first, src.second, dest) == true)
    {
        printf("We are already at the destination\n");
        return;
    }

    // Create a closed list and initialise it to false which means 
    // that no cell has been included yet 
    // This closed list is implemented as a boolean 2D array 
    bool closedList[ROW][COL];
    memset(closedList, false, sizeof(closedList));

    // Declare a 2D array of structure to hold the details 
    //of that cell 
    cell cellDetails[ROW][COL];

    int i, j;

    for (i = 0; i < ROW; i++)
    {
        for (j = 0; j < COL; j++)
        {
            cellDetails[i][j].f = FLT_MAX;
            cellDetails[i][j].g = FLT_MAX;
            cellDetails[i][j].h = FLT_MAX;
            cellDetails[i][j].parent_i = -1;
            cellDetails[i][j].parent_j = -1;
        }
    }

    // Initialising the parameters of the starting node 
    i = src.first, j = src.second;
    cellDetails[i][j].f = 0.0;
    cellDetails[i][j].g = 0.0;
    cellDetails[i][j].h = 0.0;
    cellDetails[i][j].parent_i = i;
    cellDetails[i][j].parent_j = j;

    set<pPair> openList;

    // Put the starting cell on the open list and set its 
    // 'f' as 0 
    openList.insert(make_pair(0.0, make_pair(i, j)));

    // We set this boolean value as false as initially 
    // the destination is not reached. 
    bool foundDest = false;

    while (!openList.empty())
    {
        pPair p = *openList.begin();

        // Remove this vertex from the open list 
        openList.erase(openList.begin());

        // Add this vertex to the closed list 
        i = p.second.first;
        j = p.second.second;
        closedList[i][j] = true;

         // To store the 'g', 'h' and 'f' of the 8 successors 
        double gNew, hNew, fNew;

        //----------- 1st Successor (North) ------------ 

        // Only process this cell if this is a valid one 
        if (isValid(i - 1, j) == true)
        {
            // If the destination cell is the same as the 
            // current successor 
            if (isDestination(i - 1, j, dest) == true)
            {
                // Set the Parent of the destination cell 
                cellDetails[i - 1][j].parent_i = i;
                cellDetails[i - 1][j].parent_j = j;
                printf("The destination cell is found\n");
                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }
            // If the successor is already on the closed 
            // list or if it is blocked, then ignore it. 
            // Else do the following 
            else if (closedList[i - 1][j] == false &&
                isUnBlocked(grid, i - 1, j) == true)
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i - 1, j, dest);
                fNew = gNew + hNew;

                // If it isn’t on the open list, add it to 
                // the open list. Make the current square 
                // the parent of this square. Record the 
                // f, g, and h costs of the square cell 
                //                OR 
                // If it is on the open list already, check 
                // to see if this path to that square is better, 
                // using 'f' cost as the measure. 
                if (cellDetails[i - 1][j].f == FLT_MAX ||
                    cellDetails[i - 1][j].f > fNew)
                {
                    openList.insert(make_pair(fNew,
                        make_pair(i - 1, j)));

                    // Update the details of this cell 
                    cellDetails[i - 1][j].f = fNew;
                    cellDetails[i - 1][j].g = gNew;
                    cellDetails[i - 1][j].h = hNew;
                    cellDetails[i - 1][j].parent_i = i;
                    cellDetails[i - 1][j].parent_j = j;
                }
            }
        }

        //----------- 2nd Successor (South) ------------ 

        // Only process this cell if this is a valid one 
        if (isValid(i + 1, j) == true)
        {
            // If the destination cell is the same as the 
            // current successor 
            if (isDestination(i + 1, j, dest) == true)
            {
                // Set the Parent of the destination cell 
                cellDetails[i + 1][j].parent_i = i;
                cellDetails[i + 1][j].parent_j = j;
                printf("The destination cell is found\n");
                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }
            // If the successor is already on the closed 
            // list or if it is blocked, then ignore it. 
            // Else do the following 
            else if (closedList[i + 1][j] == false &&
                isUnBlocked(grid, i + 1, j) == true)
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i + 1, j, dest);
                fNew = gNew + hNew;

                // If it isn’t on the open list, add it to 
                // the open list. Make the current square 
                // the parent of this square. Record the 
                // f, g, and h costs of the square cell 
                //                OR 
                // If it is on the open list already, check 
                // to see if this path to that square is better, 
                // using 'f' cost as the measure. 
                if (cellDetails[i + 1][j].f == FLT_MAX ||
                    cellDetails[i + 1][j].f > fNew)
                {
                    openList.insert(make_pair(fNew, make_pair(i + 1, j)));
                    // Update the details of this cell 
                    cellDetails[i + 1][j].f = fNew;
                    cellDetails[i + 1][j].g = gNew;
                    cellDetails[i + 1][j].h = hNew;
                    cellDetails[i + 1][j].parent_i = i;
                    cellDetails[i + 1][j].parent_j = j;
                }
            }
        }

        //----------- 3rd Successor (East) ------------ 

        // Only process this cell if this is a valid one 
        if (isValid(i, j + 1) == true)
        {
            // If the destination cell is the same as the 
            // current successor 
            if (isDestination(i, j + 1, dest) == true)
            {
                // Set the Parent of the destination cell 
                cellDetails[i][j + 1].parent_i = i;
                cellDetails[i][j + 1].parent_j = j;
                printf("The destination cell is found\n");
                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }

            // If the successor is already on the closed 
            // list or if it is blocked, then ignore it. 
            // Else do the following 
            else if (closedList[i][j + 1] == false &&
                isUnBlocked(grid, i, j + 1) == true)
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i, j + 1, dest);
                fNew = gNew + hNew;

                // If it isn’t on the open list, add it to 
                // the open list. Make the current square 
                // the parent of this square. Record the 
                // f, g, and h costs of the square cell 
                //                OR 
                // If it is on the open list already, check 
                // to see if this path to that square is better, 
                // using 'f' cost as the measure. 
                if (cellDetails[i][j + 1].f == FLT_MAX ||
                    cellDetails[i][j + 1].f > fNew)
                {
                    openList.insert(make_pair(fNew,
                        make_pair(i, j + 1)));

                    // Update the details of this cell 
                    cellDetails[i][j + 1].f = fNew;
                    cellDetails[i][j + 1].g = gNew;
                    cellDetails[i][j + 1].h = hNew;
                    cellDetails[i][j + 1].parent_i = i;
                    cellDetails[i][j + 1].parent_j = j;
                }
            }
        }

        //----------- 4th Successor (West) ------------ 

        // Only process this cell if this is a valid one 
        if (isValid(i, j - 1) == true)
        {
            // If the destination cell is the same as the 
            // current successor 
            if (isDestination(i, j - 1, dest) == true)
            {
                // Set the Parent of the destination cell 
                cellDetails[i][j - 1].parent_i = i;
                cellDetails[i][j - 1].parent_j = j;
                printf("The destination cell is found\n");
                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }

            // If the successor is already on the closed 
            // list or if it is blocked, then ignore it. 
            // Else do the following 
            else if (closedList[i][j - 1] == false &&
                isUnBlocked(grid, i, j - 1) == true)
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i, j - 1, dest);
                fNew = gNew + hNew;

               
                if (cellDetails[i][j - 1].f == FLT_MAX ||
                    cellDetails[i][j - 1].f > fNew)
                {
                    openList.insert(make_pair(fNew,
                        make_pair(i, j - 1)));

                    // Update the details of this cell 
                    cellDetails[i][j - 1].f = fNew;
                    cellDetails[i][j - 1].g = gNew;
                    cellDetails[i][j - 1].h = hNew;
                    cellDetails[i][j - 1].parent_i = i;
                    cellDetails[i][j - 1].parent_j = j;
                }
            }
        }
    }

    // When the destination cell is not found and the open 
    // list is empty, then we conclude that we failed to 
    // reach the destiantion cell. This may happen when the 
    // there is no way to destination cell (due to blockages) 
    if (foundDest == false)
        printf("Failed to find the Destination Cell\n");

    return;
}
//array<System::String^>^ args
int main()
{
    int grid[ROW][COL] =
    {
        { 0, 0, 0, 0},
        { 0, 0, 0, 0},
        { 0, 0, 0, 0},
        { 0, 0, 0, 0},
        { 0, 0, 0, 0},
        { 0, 0, 0, 0},
        
    };

    Pair src = make_pair(5, 3);
    string temp="";
    for (int x = 0; x < 6;x++) {
        for (int y = 0; y < 4; y++) {
            int tempint = grid[x][y];
            std::string s = std::to_string(tempint);
            temp= temp + s +" ";
            //Console::WriteLine(grid[x][y]);
        }

       cout<<temp;
       
       temp = "";
    }
    string myText;

    
    ifstream MyReadFile("C:\\Users\\karlis\\test.txt");

    
    while (getline(MyReadFile, myText)) {
        
        if (myText.find("TASK:") != std::string::npos) {
            myText.erase(0,5);
            
            string Orig = myText.substr(0,2);
            string End= myText.substr(3, 2);
            printf("\n");
            cout << Orig;
            printf("\n");
            cout << End;
            printf("\n");
        }
    }

    // Close the file
    MyReadFile.close();

    
    // Destination is the left-most top-most corner 
    Pair dest = make_pair(1, 0);

    aStarSearch(grid, src, dest);
   // String^ fileName = "C:\\Users\\karlis\\test.txt";
    SerialPort port("COM7", 9600);
    port.Open();
    
        
        //Console::WriteLine("trying to open file {0}...", fileName);
        //StreamReader^ din = File::OpenText(fileName);
        //String^ str;
        //Console::WriteLine(str);
       // Create a text string, which is used to output the text file
    
        
}

