#include "group.h"

Group::Group()
{

}

Group::Group(string title, string token, string groupname)
{
    Title = title;
    Token = token;
    GroupName = groupname;
}

void Group::SetGroup(string title, string token, string groupname)
{
    Title = title;
    Token = token;
    GroupName = groupname;
}
