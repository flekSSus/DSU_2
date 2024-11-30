#include <algorithm>
#include <iostream>
#include<vector>
#include<fstream>

std::vector<size_t> outputArr;

size_t GoToLeader(std::vector<int>& DSU,size_t index)
{
    if(DSU[index]>=0)
    {
        DSU[index]=GoToLeader(DSU,DSU[index]);
        return DSU[index];
    }

    return index;
}

void BuildDSU(std::vector<int>& DSU,std::istream& in,size_t numOfRoads,size_t numOfComponents)
{
    for(size_t i(0);i<numOfRoads;++i)
    {
        size_t el_1(0);
        size_t el_2(0);

        in>>el_1>>el_2;

        size_t rootEl_1(GoToLeader(DSU,el_1));
        size_t rootEl_2(GoToLeader(DSU,el_2));
       

        if(rootEl_1!=rootEl_2)
        {
            if(DSU[rootEl_1]>=DSU[rootEl_2]) 
            {
                DSU[rootEl_1]=rootEl_2;
                --DSU[rootEl_2];
            }
            else
            {
                DSU[rootEl_2]=rootEl_1;
                --DSU[rootEl_1];
            }
            --numOfComponents;
        }
    }
}

void BuildDSU(std::vector<int>& DSU,size_t& numOfComponents,size_t el_1,size_t el_2)
{
    size_t rootEl_1(GoToLeader(DSU,el_1));
    size_t rootEl_2(GoToLeader(DSU,el_2));
        
    if(rootEl_1!=rootEl_2)
    {
        if(DSU[rootEl_1]>=DSU[rootEl_2]) 
        {
            DSU[rootEl_1]=rootEl_2;
            --DSU[rootEl_2];
        }
        else
        {
            DSU[rootEl_2]=rootEl_1;
            --DSU[rootEl_1];
        }
        --numOfComponents;
    }

}
int main()
{
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");
    
    size_t numOfTowns(0),numOfRoads(0),numOfQuakes(0);
    size_t numOfComponents(0);
    std::vector<int> arrDSU;
    std::vector<size_t> arrDestruct;
    std::vector<std::pair<int,int>> arrRoads;
    std::vector<size_t> rresult;
    std::vector<bool> arrIsDestroy;

    in>>numOfTowns>>numOfRoads>>numOfQuakes;

    arrDSU.resize(numOfTowns+1,-1);
    arrDestruct.resize(numOfQuakes,0);
    arrRoads.resize(numOfRoads+1,std::make_pair<int,int>(0,0));
    outputArr.resize(numOfQuakes,0);
    rresult.resize(numOfQuakes,0);
    arrIsDestroy.resize(numOfRoads,false);

    numOfComponents=numOfTowns;
    arrDSU[0]=0;

    for(size_t i(1);i<arrRoads.size();++i)
    {
        in>>arrRoads[i].first>>arrRoads[i].second;
    }
    for(size_t i(0);i<arrDestruct.size();++i)
        in>>arrDestruct[i];
    for(auto& i:arrDestruct)
        arrIsDestroy[i]=true;


    
    for(size_t i(1);i<numOfRoads+1;++i)
        if(!arrIsDestroy[i])
            BuildDSU(arrDSU,numOfComponents,arrRoads[i].first,arrRoads[i].second);
    
    for(int i(numOfQuakes-1),tmp(arrDestruct[i]);i>=0;--i)
    {
        tmp=arrDestruct[i];
        if(numOfComponents==1)
            rresult[i]=1;
        else
            rresult[i]=0;

        BuildDSU(arrDSU,numOfComponents,arrRoads[tmp].first,arrRoads[tmp].second);
        
    }


    for(auto& i:rresult)
        out<<i;

    in.close();
    out.close();
}
