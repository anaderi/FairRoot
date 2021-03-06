/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

/** 
 *  FairDbTutContFact.h 
 * 
 *  created @ 09-01-2014 
 *  by         D.Bertini  
 */ 


#ifndef FAIRDBTUTCONTFACT2_H
#define FAIRDBTUTCONTFACT2_H

#include "FairContFact.h"               // for FairContFact, etc

#include "Rtypes.h"                     // for FairDbTutContFact::Class, etc

class FairParSet;

class FairDbTutContFact2 : public FairContFact
{
  public:
    FairDbTutContFact2();
    ~FairDbTutContFact2() {}
    FairParSet* createContainer(FairContainer* c);
  private:
    void setAllContainers();

    ClassDef( FairDbTutContFact2,0); // Factory for parameter containers
};

#endif  /* !FAIRDBTUTCONTFACT2_H */
