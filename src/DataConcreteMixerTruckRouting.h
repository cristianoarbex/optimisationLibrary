
#ifndef DATACONCRETEMIXERTRUCKROUTING_H
#define DATACONCRETEMIXERTRUCKROUTING_H

#include "Util.h"
#include "Data.h"
#include "StructClientDemand.h"

class DataConcreteMixerTruckRouting : public Data {

    private:
        int numberOfConstructions;
        int concreteMixerTruckFleet;
        int numberOfTypesOfConcrete;
        double fixedCost;
        double concreteMixerTruckCapacity;
        vector<ClientDemand> demands;
        vector<vector<double>> distances;

    public:

        DataConcreteMixerTruckRouting();
        virtual ~DataConcreteMixerTruckRouting();

        virtual void readData();
        virtual void print();

        int          getNumberOfConstructions       (            ) const {return numberOfConstructions  ;}
        int          getConcreteMixerTruckFleet     (            ) const {return concreteMixerTruckFleet;}
        int          getNumberOfTypesOfConcrete     (            ) const {return numberOfTypesOfConcrete;}
        double       getFixedCost                   (            ) const {return fixedCost;}
        double       getConcreteMixerTruckCapacity  (            ) const {return concreteMixerTruckCapacity;}
        ClientDemand getDemand                      (int i       ) const ;
        double       getDistance                    (int i, int j) const ;
};

#endif
