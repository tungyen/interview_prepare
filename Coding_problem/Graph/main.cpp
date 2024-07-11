#include <iostream>
#include <graph.cpp>
using namespace std;

void topologicalTest(){
    int courseNum = 5;
    vector<vector<int>> pre = {{0, 1}, {2, 0}, {3, 1}, {4, 2}};
    course_select course = course_select(courseNum, pre);
    vector<int> courseRes = course.getCourseSequence();
    for(int ele:courseRes){
        cout<<ele<<endl;
    }
}

int main()
{
    topologicalTest();
    return 0;
}
