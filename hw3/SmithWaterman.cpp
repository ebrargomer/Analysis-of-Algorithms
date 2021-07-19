#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include <algorithm>
#include <string.h>
using namespace std;
int penalty=-4;
int match=1;
int mmatch=-2;
int similarityScore(char a, char b);
int findMax(int array[], int length);

int similarityScore(char a, char b)
{
	if(a==b) return match;
	else return mmatch;
}

int findMax(int array[])
{
	int max = array[0];

	for(int i=1; i<4; i++)
	{
		if(array[i] > max)max = array[i];
		
	}
	return max;
}

int main(int argc, char *argv[])
{
	vector<string> names;
	string inputfile="strings.txt";
	string outputfile="output.txt";
	if (argc>1) inputfile=argv[1]; 
  	if (argc>2) outputfile=argv[2]; //if any other txt file is given as parameter 
  
	ifstream input(inputfile);
	ofstream output (outputfile);
	
	
	string word;
	while(getline(input,word)) names.push_back(word);
		sort(names.begin(),names.end());
		
		string seqA; // sequence A
		string seqB; // sequence B
		int lengthSeqA;
		int lengthSeqB;
		
		for(size_t f =0;f<names.size();f++){
			seqA=names[f];
			for(size_t s=f+1;s<names.size();s++){
				seqB=names[s];
				lengthSeqA = seqA.length();
				lengthSeqB = seqB.length();
							
				// initialize matrix
				double matrix[lengthSeqA+1][lengthSeqB+1];
				for(int i=0;i<=lengthSeqA;i++)
				{
					for(int j=0;j<= lengthSeqB;j++)
					{
						matrix[i][j]=0;
					}
				}
			
				int traceback[4];
			
				//start populating matrix
				for (int i=1;i<=lengthSeqA;i++)
				{
					for(int j=1;j<=lengthSeqB;j++)
			            {
						traceback[0] = matrix[i-1][j-1]+similarityScore(seqA[i-1],seqB[j-1]);
						traceback[1] = matrix[i-1][j]+penalty;
						traceback[2] = matrix[i][j-1]+penalty;
						traceback[3] = 0;
						matrix[i][j] = findMax(traceback);
			        }
				}
	
				// find the max score in the matrix
				int matrix_max = 0;
				for(int i=1;i<=lengthSeqA;i++)
				{
					for(int j=1;j<=lengthSeqB;j++)
					{
						if(matrix[i][j]>matrix_max) 	matrix_max = matrix[i][j];
					}
				}
				output<<seqA<< " - "<<seqB<<endl<<"Score: "<<matrix_max<<" Sequence(s):";
				
				
				if(matrix_max>0){
					deque <int> maxs_i;
					deque <int> maxs_j;
					
					for(int i=1;i<=lengthSeqA;i++)
					{
						for(int j=1;j<=lengthSeqB;j++)
						{
							if(matrix[i][j]==matrix_max)
							{
								maxs_i.push_back(i);
								maxs_j.push_back(j);
							}
						
						}
					}
					
					int	current_i,current_j;
					int num;
					string comp="";
					vector <string>comparisons;
					
					while(maxs_i.size()>0){
						
						current_i=maxs_i.front();
						maxs_i.pop_front();
						
						current_j=maxs_j.front();
						maxs_j.pop_front();
						
						num=matrix[current_i][current_j];
						
						while(num>0){
							
							comp=seqA[current_i-1] + comp;
							current_i--;
							current_j--;
							num=matrix[current_i][current_j];
							
						}
						
						 comparisons.push_back(comp);
						 comp="";
						 
					}
					
					sort(comparisons.begin(),comparisons.end());
					comparisons.erase(unique(comparisons.begin(),comparisons.end()),comparisons.end());
					
					for(size_t vf=0;vf<comparisons.size();vf++)
						output<<" \""<<comparisons[vf]<<"\"";
					
				}
			output<<endl;
		}
	}
	return 0;
}

