/*
    Title           :
    Author          :   Tristan Allison
    Date Created    :   June 8, 2026
    Date Edited     :   June 9, 2026
    Purpose         :
*/
#include "SCActionInitialization.hh"

SCActionInitialization::SCActionInitialization()
{

}

SCActionInitialization::~SCActionInitialization()
{

}

void SCActionInitialization::BuildForMaster() const
{
    SCRunAction *runAction = new SCRunAction();
    SetUserAction(runAction);
}

void SCActionInitialization::Build() const
{
    SCPrimaryGenerator *generator = new SCPrimaryGenerator();
    SetUserAction(generator);

    SCRunAction *runAction = new SCRunAction();
    SetUserAction(runAction);
}