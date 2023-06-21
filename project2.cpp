//My Name == Eli Rubin-Calvert

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// Struct Course to hold course information
struct Course {
    string courseNumber;
    string name;
    vector<string> prerequisites;
};

// Function to split a string by a delimiter into a vector of substrings
vector<string> splitString(string str, string delimiter = " ") {
    vector<string> substrings;
    int start = 0;
    int end = str.find(delimiter);

    // Divide the string into substrings based on delimiter
    while (end != -1) {
        substrings.push_back(str.substr(start, end - start));
        start = end + delimiter.size();
        end = str.find(delimiter, start);
    }

    // Getting last substring
    substrings.push_back(str.substr(start, end - start));

    return substrings;
}

// Function to load data from a file into a vector of Course structures
vector<Course> loadCourses() {
    // Opening file using ifstream
    ifstream file("datafile.txt", ios::in);

    vector<Course> courses;
    string line;

    // Loop until the end of the file
    while(true) {
        getline(file, line);

        // Break the loop if end of file is reached
        if(line == "-1")
            break;

        Course course;

        // Tokenize the line from file which is separated by commas
        vector<string> tokens = splitString(line, ",");

        // Store the tokenized information into the course struct
        course.courseNumber = tokens[0];
        course.name = tokens[1];

        // Store the prerequisites if they exist
        for(int i = 2; i < tokens.size(); i++)
            course.prerequisites.push_back(tokens[i]);

        // Add the course to the courses vector
        courses.push_back(course);
    }

    // Close the file
    file.close();

    // Return the loaded courses
    return courses;
}


// Function to display the information for a given course
void displayCourseInfo(Course course) {
    cout << "Course Number: " << course.courseNumber << endl;
    cout << "Course Name: " << course.name << endl;
    cout << "Prerequisites: ";
    
    // Loop through the list of prerequisites and print each
    for(const auto& prerequisite : course.prerequisites)
        cout << prerequisite << " ";
    
    cout << "\n\n";
}

// Function to display the list of all courses
void displayAllCourses(vector<Course> courses) {
    int numCourses = courses.size();

    // Sort the list of courses by Bubble Sort data structure
    for(int i = 0; i < numCourses-1; i++) {
        for(int j = 0; j < numCourses-i-1; j++) {
            if(courses[j].courseNumber > courses[j+1].courseNumber) {
                swap(courses[j], courses[j+1]);
            }
        }
    }

    // Traverse the list of courses and display information for each course
    for(const auto& course : courses)
        displayCourseInfo(course);
}

// Function to search for a course by course number
void findCourseByNumber(vector<Course> courses) {
    int numCourses = courses.size();
    string courseNum;
    bool courseFound = false;

    cout << "Enter courseNumber: ";
    cin >> courseNum;

    // Loop through the list of courses
    for(const auto& course : courses) {
        // If course is found, display its information
        if(course.courseNumber == courseNum) {
            courseFound = true;
            displayCourseInfo(course);
            break;
        }
    }

    // If the course was not found, display an error message
    if(!courseFound)
        cout << "Course with given course number not found\n";
}

int main(int argc, char **argv) {
    vector<Course> courses;

    // Display menu options
    cout << "1.Load Data Structure\n";
    cout << "2.Print Course List\n";
    cout << "3.Print Course\n";
    cout << "4.Exit\n";

    int menuChoice;

    // Continue to display the menu until the user chooses to exit
    do {
        cout << "\nEnter your choice: ";
        cin >> menuChoice;

        switch(menuChoice) {
            case 1: 
                courses = loadCourses();
                break;
            case 2: 
                displayAllCourses(courses);
                break;
            case 3: 
                findCourseByNumber(courses);
                break;
            case 4: 
                cout << "Exit\n";
                break;
            default: 
                cout << "Invalid Choice\n";
        }
    } while(menuChoice != 4);

    return 0;
}

