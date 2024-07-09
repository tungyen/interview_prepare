#include <iostream>
#include <course_select.cpp>
using namespace std;

int main()
{
    int courseNum = 5;
    vector<vector<int>> pre = {{0, 1}, {2, 0}, {3, 1}, {4, 2}};
    course_select course = course_select(courseNum, pre);
    vector<int> courseRes = course.getCourseSequence();
    for(int ele:courseRes){
        cout<<ele<<endl;
    }
    return 0;
}
