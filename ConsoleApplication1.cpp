//Copyright @Ax1aL -Radu
//this code will work only if some rules are
//respected for the input example:
/*CREATE TABLE "Planet"
			("Planet_ID" NUMBER(10, 0),
				"Name" VARCHAR2(255),
				"Star_ID" NUMBER(10, 0),
				PRIMARY KEY("Planet_ID"),
				FOREIGN KEY("Star_ID") REFERENCES "Star"("Star_ID")
				);*/
//INSERT INTO table_name (column1, column2, column3, ...) first part with the names of the columns
//VALUES(value1, value2, value3, ...); second part values of the columns


#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	//opening the input and output files
	ifstream f("test.txt");
	ofstream o("output.txt");


	char s[256]{};//the string for taking line by line from input file
	char outputInsert[512]{ "INSERT INTO " };//the first part that is the same for each table
	char outputValues[5][512]{};//5 different input for each row
	for (int i = 0; i < 5; ++i)
		strcpy_s(outputValues[i], "VALUES (");//the beginning is the same for all outputs of the second part


	
	while (f>>s) {
		
		//check each case the beginning of the collum(chould have used a switch)

		if (s[0] == 'P') {//Primary Key
			f >> s;
			f >> s;
			continue;
		}

		if (s[0] == 'F') {//Foreign key
			f >> s; f >> s; f >> s; f >> s;
			continue;
		}

		if (s[0] == 'C' ) {//Create Table
			f >> s;
			f >> s;
			strcat_s(outputInsert, s);
			strcat_s(outputInsert, " (");
			continue;
		}

		if (s[0] == ')') {//if arrived at the end of the table creation
			outputInsert[strlen(outputInsert) - 1] = ')';
			
			for (int i = 0; i < 5; ++i) {//add the finishing part
				outputValues[i][strlen(outputValues[i]) - 1] = ')';
				strcat_s(outputValues[i], ";");
			}
			for (int i = 0; i < 5; ++i) {//print out to the file
				o << outputInsert << " " << outputValues[i] << "\n";
			}

			strcpy_s(outputInsert, "INSERT INTO ");//restart the strings
			for (int i = 0; i < 5; ++i) {
				strcpy_s(outputValues[i], "VALUES (");
			}
			continue;
		}

		if (s[0] == '(') {//at the beginning take the first  column name 
			memmove(s, s + 1, strnlen(s, 256));//remove the parentheses
		}
		char t[256]{};//temp string
		memcpy(t, s + 1, strnlen(s, 256) - 2);//remove the ""
		//strcat_s(t, "\0"); doesnt work
		strcat_s(outputInsert, s);
		strcat_s(outputInsert, ",");//for the next value
		f >> s;//we get the type of the column :Number,String or Date
	
		
		switch (s[0]) {//depending on the first letter
			case 'N': {//NUMBER
					strcat_s(outputValues[0], "1,");//could have found a nicer way but it does the work for only 5 lines
					strcat_s(outputValues[1], "2,");
					strcat_s(outputValues[2], "3,");
					strcat_s(outputValues[3], "4,");
					strcat_s(outputValues[4], "5,");
			
				break;
			}
			case 'V': {//VARCHAR
				for (int i = 0; i < 5; ++i) {
					strcat_s(outputValues[i], t);
				}
				strcat_s(outputValues[0], "1,");
				strcat_s(outputValues[1], "2,");
				strcat_s(outputValues[2], "3,");
				strcat_s(outputValues[3], "4,");
				strcat_s(outputValues[4], "5,");
				break;
			}
			case 'D': {//DATE

				for (int i = 0; i < 5; ++i) {
					strcat_s(outputValues[i], "DATE");
				}
				strcat_s(outputValues[0], "1,");
				strcat_s(outputValues[1], "2,");
				strcat_s(outputValues[2], "3,");
				strcat_s(outputValues[3], "4,");
				strcat_s(outputValues[4], "5,");


				break;
			}
			default: {cout << "Not good!"; }//we should get here
		}




	}


   
}



