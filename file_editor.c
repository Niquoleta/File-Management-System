#include <stdio.h>
#include <stdlib.h>
#include <string.h>   

#define MAX_LINE_LENGTH 1024

    
    /* File Operations
    ======================================
        */
    void createFile(char *filename)  {
        FILE *fptr; //a pointer of type FILE
        fptr = fopen(filename, "w"); //this will  Create a file with the name given before
        printf("File %s has been created .\n", filename);
        fclose(fptr); // this will close the file
    }
    void NamingFile(char *filename){
        //fgets(filename, sizeof(filename), stdin);  //store the input in filename
        filename[strcspn(filename, "\n")] = '\0';// Remove the newline character added by fgets
        createFile(filename);   // call the function which create a file
    }
    
    //Copy the file contents to a new file.
    void copy_file(const char *source, const char *destination) {
        FILE *src = fopen(source, "r"); //Open the source file in read mode.
        if (src == NULL) {
            perror("Failed to open source file"); //If the source file fails to open, an error message is displayed.
            return;
        }
        
        FILE *dest = fopen(destination, "w"); //Open the target file in write mode.
        if (dest == NULL) {
            perror("Failed to create destination file"); //If the target file fails to be created, an error message is displayed
            fclose(src); //Close source file.
            return;
        }
        
        char buffer[MAX_LINE_LENGTH]; //The buffer is used to store the read data.
        while (fgets(buffer, MAX_LINE_LENGTH, src) != NULL) { //Read the source file until the end.
            fputs(buffer, dest); //Writes the read data to the destination file.
        }
        
        fclose(src); //Close source file
        fclose(dest); //Close object file
    }
    
    void showFile(char *filename) {
        FILE *fptr;
        fptr = fopen(filename, "r");//this will open a file in read mode
        char myString[99999];// this will store the content of the file 
        //if file exist
        if(fptr != NULL) { 
                                                  //this will read the content store it in myString variable then display it
        while(fgets(myString, 99999, fptr)) { 
          printf("%s", myString);
            }
                                          // in case the file does not exist 
      } else {
        printf("Not able to open the file.");
      }
                                           // Close the file
      fclose(fptr);
        }
    
     void deleteFile(char *filename) {
                            //the remove function is built-in to stdio.h to delete files
            if (remove(filename) == 0) {
                printf("File %s deleted successfully.\n", filename);} 
                            // the perror is a library function used to Prints the message and the reason for the error. 
            else {
                perror("Error deleting file"); }}
    
    
        //Show file content
    void display_file(const char *filename) {
        FILE *file = fopen(filename, "r"); //Open the file in read mode
        if (file == NULL) {
            perror("Failed to open file"); //If the file fails to open, an error message is displayed.
            return;
        }
    
    char buffer[MAX_LINE_LENGTH]; //The buffer is used to store the read data
    while (fgets(buffer, MAX_LINE_LENGTH, file) != NULL) { //Read the file until the end
        printf("%s", buffer); //Print the read data
    }
    
    fclose(file); //closed message
        
    }
    
    /* Line Operations
    ======================================
    */

    
    void appendLine(char *filename){
        FILE *fptr;
        char myLine[100];
        fptr = fopen(filename, "a"); // will Open a file in append mode
        if (fptr == NULL) {
            printf("Error: Could not append file %s\n", filename);
        return; }
                          // Ask the user to input some text then append it at the end of the file
        else{
            printf("Enter what do you want to add at the end of the file: \n");
            fgets(myLine, sizeof(myLine), stdin);
                          // Remove the newline character from input if it exists
            myLine[strcspn(myLine, "\n")] = '\0';
    
                          // Append some text to the file
          fprintf(fptr, " \n %s",myLine);
          printf("Line has been appended to %s .\n", filename);}
    
          fclose(fptr);// Close the file
    }
    
    //Displays the specified line in the file
   void showLine(char *filename, int lineNumber){
       FILE *file = fopen(filename, "r");
       int count=0;
       char buffer[1000];
       int i;
       
      // if the file failed to open, exit with an error message and status
     
        if (file == NULL)
          {
            printf("Error opening file.\n");
            return;
          }
       
        for (i=0; i<lineNumber;i++){ //loops to line number
            if (feof(file)){
                printf("The file has less than %d lines \n",  lineNumber);
                fclose(file);
                return;
              }  
            fgets(buffer, 1000,file); // gets a line of text from a file and stores in buffer, unless line is longer that 1000, 
            
                
       }
       printf("%s",buffer);
       fclose(file);
       
       
    }

void deleteLine(char *filename, int deleteLine ) {
        // File pointers for the original and temp file
        FILE *fptr, *tempPtr;

        // buffer will store each line from the original file
        // myLine will store the new line of text the user inserts
        // writeLine stores the line number where new line is to be inserted
        char buffer[100];
        char myLine[100];
        
        // Flush stdin to get rid of the \n char from the scan
        fflush(stdin);

        fptr = fopen(filename, "r"); // will open the original file in reading mode
        tempPtr = fopen("temp", "w"); // opens the temp file to write 

        // Check if one of the files failed to open, if either did exit
        if (fptr == NULL || tempPtr == NULL){
            printf("Error opening file(s).\n");
            return;
        }

        // Continue reading file as long as keepReading is non-zero
        // Keep track of currentLine (counter)
        int currentLine = 1;

        while(1) {
            // If we've reached the end of the file, it can stop reading
            if (feof(fptr)){
                break;
            }
            
            // Read the next line of the file into the buffer
            fgets(buffer, sizeof(buffer), fptr);

            // If we've reached the line to delete,
            // the program will write the new text then the line(s) of text after
            // that are currently in the original file 
            if (currentLine != deleteLine){
                fputs(buffer, tempPtr);
            }
            // Increment to go to the next line
            currentLine++;
        }

        fclose(fptr);
        fclose(tempPtr);

        // Then we delete the original file, rename the temp file to our original file's name
        remove(filename);
        rename("temp", filename);
        if (currentLine < deleteLine){
            printf("Line number is out of bounds \n");
        }
        else{
        printf("Text has been deleted from Line %d of %s.\n", deleteLine, filename);
        }

        return;  
    }


// writeLine stores the line number where new line is to be inserted
void insertLine(char *filename, int writeLine, char *myLine) {
        // File pointers for the original and temp file
        FILE *fptr, *tempPtr;

        // buffer will store each line from the original file
        char buffer[1000];

        // Flush stdin to get rid of the \n char from the scan
        fflush(stdin);

        fptr = fopen(filename, "r"); // will open the original file in reading mode
        tempPtr = fopen("temp", "w"); // opens the temp file to write 

        // Check if one of the files failed to open, if either did exit
        if (fptr == NULL || tempPtr == NULL){
            printf("Error opening file(s).\n");
            return;
        }

        // Keep track of currentLine (counter)
        int currentLine = 1;

        // Use a do-while loop so loop executes at least once
        while(1) {
            // If we've reached the end of the file, it can stop reading
            if (feof(fptr)){
                break;
            }
                
            // Read the next line of the file into the buffer
            fgets(buffer, sizeof(buffer), fptr);
            
            // If we've reached the line to write the new line,
            // the program will write the new text then the line(s) of text after
            // that are currently in the original file 
            if (currentLine == writeLine){
                fputs(myLine, tempPtr);
                fputs("\n",tempPtr);
            }
            
            fputs(buffer, tempPtr);
            
            // Increment to go to the next line
            currentLine++;
        }

        fclose(fptr);
        fclose(tempPtr);

        // Then we delete the original file, rename the temp file to our original file's name
        remove(filename);
        rename("temp", filename);

        printf("Text has been inserted into Line %d of %s.\n", writeLine, filename);

        return;  
    }

    
    //Deletes the specified line from the file
   
    
    /* General OPerations
    ======================================
    */
    
    
    int totalLines(char *filename){
        FILE *fp;
        int count = 0; // Line counter (result)
        char c; // To store a character read from file
        fp = fopen(filename, "r");
        // Check if file exists
        if (fp == NULL){
            //printf("Could not total file %s", filename);
            return 0;
        }
        
        // Extract characters from file and store in character c
        for (c = getc(fp); c != EOF; c = getc(fp)){
            if (c == '\n'){ // Increment count if this character is newline
                count = count + 1;}
        }
        // Close the file
        fclose(fp);
        return count;
    }
    
    void updateLog(char *commandInp,char *fileInp){ // updates the change log
        FILE *fptr;
        int count;
        fptr = fopen("ChangeLog.txt", "a"); // will Open change log
        if (fptr == NULL) {
            printf("Error: Chang Log could not be updated. \n");
        return; }
            
        else{
                          // Remove the newline character from input if it exists
            commandInp[strcspn(commandInp, "\n")] = '\0';
                          // Append some text to the file
            count= totalLines(fileInp);
            strcat(commandInp, fileInp);
            fprintf(fptr, " \n %s - %d lines",commandInp,count);
            fclose(fptr);// Close the file
            return;
        }
    }
    
    /* Additional operations
    ======================================
    */
    
    void renameFile(char* fileName,char* newName){ //renaming file, takes in file name and the new name
        FILE *fptr = fopen(fileName, "r"); // will Open a file in read mode
        if (fptr == NULL) {
            printf("Error: Could not rename file %s\n", fileName);
         return;}
        int change;
        change= rename(fileName,newName); //saves
        if(!change){
            printf("%s name changed successfully to %s \n",fileName,newName);
        }
        else{
            printf("error");
        }
        fclose(fptr);
    }
    
    void countText(char* fileName){
        FILE *fptr;
        int count=0;
        int c;
        
        fptr = fopen(fileName, "r"); // will Open a file in read mode
        if (fptr == NULL) {
            printf("Error: Could not open file %s\n", fileName);
            return; 
         }
        
        for(c=fgetc(fptr); c !=EOF; c=fgetc(fptr)){
                count++;
        }
        fclose(fptr);
        printf("Theres %d char in %s \n",count,fileName);
        
    }


int main() {
    int choice;
    char filename[100];
    char newName[100];
    int line_number1, line_number2, line_number3;
    char line[MAX_LINE_LENGTH],text[100];
    int count;
    //createFile("ChangeLog.txt");
    //create a loop ( 1 represents true)
    while (1) {
        printf("\nThe Menu:\n");
        printf("Enter 1 to Create File\n");
        printf("Enter 2 to Copy File\n");
        printf("Enter 3 to Delete File\n");
        printf("Enter 4 to Show File\n");
        printf("Enter 5 to Append Line\n");
        printf("Enter 6 to Delete Line\n");
        printf("Enter 7 to Insert Line\n");
        printf("Enter 8 to Show Line\n");
        printf("Enter 9 to Show Change log\n");
        printf("Enter 10 to Show number of lines in a file\n");
        printf("Enter 11 to Rename a file\n");
        printf("Enter 12 to Show total char\n");
        printf("Enter 13 to Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // built in function used after input functions like scanf to consume unwanted leftover characters

        switch (choice) {
            case 1://file to create
                 // used to store user input for the file name
                printf("Enter the file name: ");
                scanf("%s", filename);
                char desc[100]="Created ";
                updateLog(desc,filename);
                NamingFile(filename);
               
                break;

            case 2: //file to copy
                printf("Enter the file name to copy: ");
                scanf("%s", filename);
    			printf("Enter destination filename: ");
    			char dest_filename[256];
    			scanf("%s", dest_filename);
    			copy_file(filename, dest_filename);
                //updateLog(desc2,filename);
    			break;
                

            case 3: //file to delete
                printf("Enter the file name to delete: ");
                fgets(filename, sizeof(filename), stdin);  // Read the file name 
                filename[strcspn(filename, "\n")] = '\0';  // Remove the newline character
                deleteFile(filename);
                char desc3[100]="Deleted ";
                //updateLog(desc3,filename);
                
                break;

            case 4: //file to display
                printf("Enter the file name to display: ");
                fgets(filename, sizeof(filename), stdin);  // Read the file name
                filename[strcspn(filename, "\n")] = '\0';  // Remove the newline character
                char desc4[100]="Displayed";
                updateLog(desc4,filename);
                showFile(filename);
                
        
                break;

            case 5:// append text to file
                printf("Enter the file name to append to: ");
                fgets(filename, sizeof(filename), stdin);  // Read the file name
                filename[strcspn(filename, "\n")] = '\0';  // Remove the newline character
                appendLine(filename);
                char desc5[100]="Appended text to ";
                updateLog(desc5,filename);
                
                break;

            case 6: //delete line in file 
                
                printf("Enter filename: "); 
    			scanf("%s", filename);
    			printf("Enter line number to delete: ");
    			scanf("%d", &line_number1);
    			deleteLine(filename, line_number1);
                //updateLog("Deleted %s in %s",line_number,filename);
               
    			break;
    

            case 7://insert line to a file
                //updateLog("Inserted line in %s",filename);
            
                printf("Enter filename: ");
    			scanf("%s", filename);
    			printf("Enter line number to insert: ");
    			scanf("%d", &line_number2);
                
    			printf("Enter line to insert: ");
                fgets(line, sizeof(line), stdin);
    			insertLine(filename, line_number2, line);
           
                break;
        

            case 8://show line in a file
                //updateLog("Display a line in %s",filename);

                printf("Enter filename: ");
    			scanf("%s", filename);
    			printf("Enter line number to display: ");
    			scanf("%d", &line_number3);
    			showLine(filename, line_number3);
                break;
         
            
            case 9: // need to show change log, append the file, rewrite so it takes 2 parameters
                char file[100]="ChangeLog.txt"; 
                showFile(file);
                break;
            
            case 10: //total number of lines
                printf("Enter file name: ");
                fgets(filename, sizeof(filename), stdin);  // Read the file name
                filename[strcspn(filename, "\n")] = '\0';  // Remove the newline character
                char desc10[100]="Total numbers of lines displayed in ";
                updateLog(desc10,filename);
                count= totalLines(filename);
                printf("The file %s has %d lines\n ", filename, count);
                break;
            
            case 11: //renaming file
                printf("Enter the file name to change: ");
                scanf("%s", filename);
                printf("Enter the new name: ");
                scanf("%s", newName);
                renameFile(filename,newName);
                char desc11[100]=" renamed to ";
                strcat(filename,desc11 );
                updateLog(filename,newName);
                break;
                
            case 12: //count
                printf("Enter the file name to count number of char: ");
                scanf("%s", filename);
                countText(filename);
                //char desc11[100]=" renamed to ";
                //strcat(filename,desc11 );
                //updateLog(filename,newName);
                break;
                

            case 13:
                printf(".....\n");
                exit(0); // built-in function to exit the program

            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }

    return 0;
}



