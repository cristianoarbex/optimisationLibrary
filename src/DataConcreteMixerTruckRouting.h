
#ifndef DATACONCRETEMIXERTRUCKROUTING_H
#define DATACONCRETEMIXERTRUCKROUTING_H

#include "Util.h"
#include "Data.h"

// Client concrete demand
class ClientDemand {

    private:
        double  quantity;
        int     concreteTypeId;

    public:
        int     constructionId;

        ClientDemand() {}

        ~ClientDemand() {}

        double getQuantity      (int constructionId) const { return quantity; }
        int getConcreteTypeId   (int constructionId) const { return concreteTypeId; }

        void setQuantity(double value) {
            quantity = value;
        }

        void setConcreteTypeId(int id) {
            concreteTypeId = id;
        }
};

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
