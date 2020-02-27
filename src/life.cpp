

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "console.h"
#include "filelib.h"
#include "grid.h"
#include "gwindow.h"
#include "simpio.h"
#include "lifegui.h"
#include "fstream"
#include "vector.h"
#include "map.h"
#include "strlib.h"
#include "error.h"
#include "grid.h"
using namespace std;
const string ERROR_MSG="Can't open the file specified, please try again: ";
const string PROMPT_FILE_MSG="Grid input file name? ";
const string WRAPPING_OPT="Should the simulation wrap around the grid?";
/* Function prototypes */

string promptUserFile(ifstream & infile, string prompt= "");
void showFileContent(ifstream & infile);
void readFileContent(ifstream &infile, Map<string,int> & mymap, Grid<char> & _grid);
void countNeighbors(Grid<int> & gridOfOccurences, Grid<char> & _mygrid, Grid<char> & _gridcopy);

/*Main Program*/
int main() {
    // TODO: Finish the program!


    cout << "Welcome to the CS 106B Game of Life, \n"
            "a simulation of the lifecycle of a bacteria colony \n"
            "Cells (X)  live and die by the following rules:\n"
            "-A Cell with 1 or fewer neighborhoods dies.\n"
            "- Locations  with 2 neighborhoods remain stable\n"
            "- Locations with 3 neighborhoods will create life\n"
            "A cell with 4 or more neighborhoods dies." << endl;
    ifstream infile;
    promptUserFile(infile, PROMPT_FILE_MSG);
   // showFileContent(infile);
    char choice_letter;
  label:
   cout <<WRAPPING_OPT<<endl;
   cin>> choice_letter;
if (!(choice_letter=='n')&& !(choice_letter=='y')){
    cin.clear();
    goto label;}



        //return choice_letter;
        //cin.clear();




    Map<string, int> grid_params;
    Grid<char> mygrid;//(grid_params.get("n_rows"),grid_params.get("n_columns"));
    Grid<char> newgrid;
    Grid<int> matrixOfFrequency;



    readFileContent(infile, grid_params, mygrid);
    for (int i = 0; i < mygrid.numRows(); ++i) {
        for (int j = 0; j < mygrid.numCols(); ++j) {
            cout<<mygrid.get(i,j);
        }

        cout<<endl;

   }






    pause;
    return 0;
}


string promptUserFile(ifstream &infile, string prompt){
    while (true) {
        cout << prompt;
        string filename;
        getline(cin, filename);
        infile.open(filename.c_str());
        if (!infile.fail()) return filename;
        infile.clear();
        cout<<ERROR_MSG <<endl;
        if (prompt=="") prompt = PROMPT_FILE_MSG;

        }
  }
void showFileContent (ifstream &infile) {
    while (true){
            int ch = infile.get();
            if (ch==EOF) break;
            cout.put(ch);
        }
        infile.close();
}

void readFileContent(ifstream &infile, Map<string, int> & mymap, Grid<char> & _grid){
    string line;
    getline(infile,line);
    mymap["n_rows"]=stoi(line);
    getline(infile,line);
    mymap.put("n_columns",stoi(line));
    int n_col=mymap.get("n_columns");
    int n_rows=mymap.get("n_rows");
    _grid.resize(n_rows+1,n_col+1);
    int j=0;
    while (true){
        string line;
        getline(infile, line);
        if ((toupper(line[0])=='X')||(line[0]=='-')){
            for (int i = 1; i < n_col; ++i) {
                _grid.set(j,i,line[i]);
            char ch=_grid.get(j,i);
                }

            j=j+1;
            if (j==n_rows) break;
            }
        }
     infile.close();


}

void countNeighbors(Grid<int> & gridOfOccurences, Grid<char> & _mygrid, Grid<char> & _gridcopy){
  /* initializes an auxilary grid to allow for framing 0s to which grid of characters will be copied */
    _gridcopy.resize(_mygrid.numRows()+1,_mygrid.numCols()+1);

    /*Copies from Grid to extended grid to allow for easier boundary elements check (out of domain)*/

    gridOfOccurences.resize(_mygrid.numRows(),_mygrid.numCols()); //creates a grid of neighbor counts;

    for (int i=1;i<_gridcopy.numRows();i++){
        for (int j=1;j<_gridcopy.numCols();j++){

            _gridcopy[i][j]=_mygrid[i-1][j-1];
        }
    }
//    cout<<_gridcopy.toString2D() <<endl;
    /* solves 8 neighbors problem for extended grid, by setting first and last row/column to 0 we solve out of bonds problem*/


       int t=0;
       for (int i=1;i<_gridcopy.numRows()-1;i++){

           for (int j=1;j<_gridcopy.numCols()-1;j++){
               t=0;

               if (((_gridcopy[i][j]=='X')||(_gridcopy[i][j]=='-')) && (_gridcopy[i+1][j]=='X')){
                   t+=1;
                   gridOfOccurences[i][j]=t;
               }
               if (((_gridcopy[i][j])=='X' ||(_gridcopy[i][j]=='-') )&&(_gridcopy[i-1][j]=='X')){
                   t+=1;
                   gridOfOccurences[i][j]=t;
               }
               if (((_gridcopy[i][j]=='X')||(_gridcopy[i][j]=='-')) && (_gridcopy[i][j+1]=='X')){
                   t++;
                   gridOfOccurences[i][j]=t;
               }

               if (((_gridcopy[i][j]=='X') ||(_gridcopy[i][j]=='-'))&& (_gridcopy[i][j-1]=='X')){
                   t++;
                   gridOfOccurences[i][j]=t;
               }

               if (((_gridcopy[i][j]=='X')||(_gridcopy[i][j]=='-')) && (_gridcopy[i+1][j+1]=='X')){
                   t+=1;
                   gridOfOccurences.set(i,j,t);
               }

               if (((_gridcopy[i][j])=='X'||(_gridcopy[i][j]=='-')) && (_gridcopy[i-1][j-1]=='X')){
                   t+=1;
                   gridOfOccurences.set(i,j,t);
               }
               if (((_gridcopy[i][j]=='X')||(_gridcopy[i][j]=='-'))&& (_gridcopy[i+1][j-1]=='X')){
                   t+=1;
                   gridOfOccurences.set(i,j,t);
               }
               if (((_gridcopy[i][j]=='X')||(_gridcopy[i][j]=='-')) && (_gridcopy[i-1][j+1]=='X')){
                   t+=1;
                   gridOfOccurences.set(i,j,t);
               }
           }
       }
     cout<<gridOfOccurences.toString2D()<<endl;
       for (int i=1;i<gridOfOccurences.numRows();++i){
           for(int k=0;k<gridOfOccurences.numCols();++k){
               if (gridOfOccurences[i][k]<=1) {
                   _gridcopy[i][k]='-';
               }
               if (gridOfOccurences[i][k]==2){}
               if (gridOfOccurences[i][k]==3){ _gridcopy[i][k]='X';}
               if (gridOfOccurences[i][k]>3){_gridcopy[i][k]='-';}
           }
       }

   }




